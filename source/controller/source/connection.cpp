// Copyright (c) 2015-2017 Hypha

#include <hypha/controller/connection.h>
#include <hypha/core/database/database.h>
#include <hypha/utils/logger.h>

#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Statement.h>

using namespace hypha::controller;
using namespace hypha::utils;

Connection::Connection(database::Database *database) {
  this->database = database;
}

void Connection::create(std::string senderId, std::string receiverId) {
  database->getSession()
      << "INSERT INTO `connection`(`sender_id`,`receiver_id`) VALUES('" +
             senderId + "','" + receiverId + "');",
      Poco::Data::Keywords::now;
}

void Connection::remove(std::string id) {
  Poco::Data::Statement statement = database->getStatement();
  statement << "delete from connection where id = ?;",
      Poco::Data::Keywords::use(id);
  statement.execute();
}

void Connection::removeConnections(std::string pluginId) {
  for (std::string id : getConnections(pluginId)) {
    remove(id);
  }
}

std::list<std::tuple<std::string, std::string, std::string> >
Connection::getConnections() {
  std::list<std::tuple<std::string, std::string, std::string> > connectionList;
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT `id`,`sender_id`,`receiver_id` FROM `connection`;";
  statement.execute();
  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    try {
      std::string id = rs[0].convert<std::string>();
      std::string senderId = rs[1].convert<std::string>();
      std::string receiverId = rs[2].convert<std::string>();
      connectionList.push_back(
          std::tuple<std::string, std::string, std::string>(id, senderId,
                                                            receiverId));
    } catch (std::exception &ex) {
      Logger::error(ex.what());
    }
    more = rs.moveNext();
  }
  return connectionList;
}

std::list<std::string> Connection::getConnections(std::string pluginId) {
  std::list<std::string> connectionList;
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT `id` FROM `connection` WHERE `sender_id` = ? OR "
               "`receiver_id` = ?;",
      Poco::Data::Keywords::use(pluginId), Poco::Data::Keywords::use(pluginId);
  statement.execute();
  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    try {
      std::string id = rs[0].convert<std::string>();
      connectionList.push_back(id);
    } catch (std::exception &ex) {
      Logger::error(ex.what());
    }
    more = rs.moveNext();
  }
  return connectionList;
}

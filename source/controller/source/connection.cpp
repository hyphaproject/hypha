// Copyright (c) 2015-2016 Hypha

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

void Connection::create(std::string handlerId, std::string pluginId) {
  database->getSession()
      << "INSERT INTO `connection`(`handler_id`,`plugin_id`) VALUES('" +
             handlerId + "','" + pluginId + "');",
          Poco::Data::Keywords::now;
}

void Connection::remove(std::string id)
{
    Poco::Data::Statement statement = database->getStatement();
    statement << "delete from connection where id = ?;",
              Poco::Data::Keywords::use(id);
    statement.execute();
}

std::list<std::tuple<std::string, std::string, std::string> >
Connection::getConnections() {
  std::list<std::tuple<std::string, std::string, std::string> > connectionList;
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT `id`,`handler_id`,`plugin_id` FROM `connection`";
  statement.execute();
  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    try {
      std::string id = rs[0].convert<std::string>();
      std::string handlerId = rs[1].convert<std::string>();
      std::string pluginId = rs[2].convert<std::string>();
      connectionList.push_back(
          std::tuple<std::string, std::string, std::string>(id, handlerId,
                                                            pluginId));
    } catch (std::exception &ex) {
      Logger::error(ex.what());
    }
    more = rs.moveNext();
  }
  return connectionList;
}

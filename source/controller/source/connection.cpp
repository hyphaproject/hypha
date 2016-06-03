// Copyright (c) 2015-2016 Hypha

#include <hypha/controller/connection.h>
#include <hypha/utils/logger.h>
#include <hypha/core/database/database.h>

#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Statement.h>

using namespace hypha::controller;
using namespace hypha::utils;

Connection::Connection(database::Database *database) {
  this->database = database;
}

std::list<std::tuple<std::string, std::string> > Connection::getConnections() {
  std::list<std::tuple<std::string, std::string> > connectionList;
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT `id`,`handler_id`,`plugin_id` FROM `connection`";
  statement.execute();
  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    try {
      std::string handlerId = rs[1].convert<std::string>();
      std::string pluginId = rs[2].convert<std::string>();
      connectionList.push_back(
          std::tuple<std::string, std::string>(handlerId, pluginId));
    } catch (std::exception &ex) {
      Logger::error(ex.what());
    }
    more = rs.moveNext();
  }
  return connectionList;
}

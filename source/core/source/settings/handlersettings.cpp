// Copyright (c) 2015-2016 Hypha
#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Statement.h>
#include <Poco/Net/DNS.h>
#include <hypha/core/database/database.h>
#include <hypha/core/settings/handlersettings.h>
#include <hypha/utils/logger.h>
#include <mutex>

using namespace hypha::database;
using namespace hypha::settings;

using namespace Poco::Data::Keywords;

HandlerSettings *HandlerSettings::singleton = 0;

HandlerSettings::HandlerSettings(hypha::database::Database *database) {
  this->database = database;
}

HandlerSettings::~HandlerSettings() {}

HandlerSettings *HandlerSettings::instance() {
  static std::mutex mutex;
  if (!singleton) {
    mutex.lock();

    if (!singleton) singleton = new HandlerSettings(Database::instance());
    mutex.unlock();
  }
  return singleton;
}

std::list<std::string> HandlerSettings::getAllHandlerIds() {
  std::list<std::string> plugins;
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT id FROM handler;";
  statement.execute();
  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    hypha::utils::Logger::info(rs[0].convert<std::string>());
    plugins.insert(plugins.end(), rs[0].convert<std::string>());
    more = rs.moveNext();
  }
  return plugins;
}

std::list<std::string> HandlerSettings::getLocalHandlerIds() {
  std::list<std::string> plugins;
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT id FROM handler WHERE host='" +
                   Poco::Net::DNS::hostName() + "' OR host='localhost';";
  statement.execute();
  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    hypha::utils::Logger::info(rs[0].convert<std::string>());
    plugins.insert(plugins.end(), rs[0].convert<std::string>());
    more = rs.moveNext();
  }
  return plugins;
}

std::string HandlerSettings::getName(std::string id) {
  std::string retValue = "";
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT type FROM handler WHERE id='" + id + "'", into(retValue);
  statement.execute();
  return retValue;
}

std::string HandlerSettings::getHost(std::string id) {
  std::string retValue = "";
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT host FROM handler WHERE id='" + id + "'", into(retValue);
  statement.execute();
  return retValue;
}

std::string HandlerSettings::getConfig(std::string id) {
  std::string retValue = "";
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT config FROM handler WHERE id='" + id + "'",
      into(retValue);
  statement.execute();
  return retValue;
}

std::list<std::string> HandlerSettings::getConnectedPlugins(
    std::string handlerId) {
  std::list<std::string> plugins;
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT id,handler_id,plugin_id  FROM connection WHERE "
               "handler_id = '" +
                   handlerId + "';";
  statement.execute();
  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    plugins.insert(plugins.end(), rs[2].convert<std::string>());
    more = rs.moveNext();
  }
  return plugins;
}

bool HandlerSettings::exists(std::string id) { return getName(id) != ""; }

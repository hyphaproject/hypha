#include <Poco/Net/DNS.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Statement.h>
#include <mutex>
#include <hypha/utils/logger.h>
#include "hypha/settings/pluginsettings.h"

using namespace hypha::utils;
using namespace hypha::database;
using namespace hypha::settings;
#ifdef _WIN32
using namespace Poco::Data::Keywords;
#else
using namespace Poco::Data;
#endif

PluginSettings *PluginSettings::singleton = 0;

PluginSettings::PluginSettings(hypha::database::Database *database) {
  this->database = database;
}

PluginSettings::~PluginSettings() {
}

PluginSettings *PluginSettings::instance() {
  static std::mutex mutex;
  if (!singleton) {
    mutex.lock();
    if (!singleton)
      singleton = new PluginSettings(Database::instance());
    mutex.unlock();
  }

  return singleton;
}

std::list<std::string> PluginSettings::getAllPluginIds() {
  std::list<std::string> plugins;

  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT id FROM plugins";
  statement.execute();
  Poco::Data::RecordSet rs(statement);
  bool more = rs.moveFirst();
  while (more) {
    plugins.insert(plugins.end(), rs[0].convert<std::string>());
    more = rs.moveNext();
  }
  return plugins;
}

std::list<std::string> PluginSettings::getLocalPluginIds() {
  std::list<std::string> plugins;
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT id FROM plugins WHERE host='" + Poco::Net::DNS::hostName() + "' OR host='localhost';";
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

std::string PluginSettings::getName(std::string id) {
  std::string retValue = "";
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT type FROM plugins WHERE id='" + id + "'", into(retValue);
  statement.execute();
  return retValue;
}

std::string PluginSettings::getHost(std::string id) {
  std::string retValue = "";
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT host FROM plugins WHERE id='" + id + "'", into(retValue);
  statement.execute();
  return retValue;
}

std::string PluginSettings::getConfig(std::string id) {
  std::string retValue = "";
  Poco::Data::Statement statement = database->getStatement();
  statement << "SELECT config FROM plugins WHERE id='" + id + "'", into(retValue);
  statement.execute();
  return retValue;
}

bool PluginSettings::exists(std::string id) {
  return getName(id) != "";
}


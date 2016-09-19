// Copyright (c) 2015-2016 Hypha
#include <hypha/core/settings/databasesettings.h>
#include <hypha/core/settings/hyphasettings.h>
#include <mutex>

using namespace hypha::settings;

DatabaseSettings *DatabaseSettings::singleton = 0;

DatabaseSettings::DatabaseSettings(
    hypha::settings::HyphaSettings *hyphaSettings) {
  this->hyphaSettings = hyphaSettings;
}

DatabaseSettings::~DatabaseSettings() {}

DatabaseSettings *DatabaseSettings::instance() {
  static std::mutex mutex;
  if (!singleton) {
    mutex.lock();
    if (!singleton) singleton = new DatabaseSettings(HyphaSettings::instance());
    mutex.unlock();
  }

  return singleton;
}

void DatabaseSettings::save() { hyphaSettings->save(); }

std::string DatabaseSettings::getString(const std::string &key,
                                        const std::string &defaultValue) {
  return hyphaSettings->getString("database." + key, defaultValue);
}

int DatabaseSettings::getInt(const std::string &key, const int &defaultValue) {
  return hyphaSettings->getInt("database." + key, defaultValue);
}

std::string DatabaseSettings::getDriver() {
  return getString("driver", "SQLite");
}

std::string DatabaseSettings::getHost() {
  return getString("host", "localhost");
}

std::string DatabaseSettings::getDatabase() {
  return getString("database", ":memory:");
}

std::string DatabaseSettings::getUser() {
  return getString("username", "hypha");
}

std::string DatabaseSettings::getPassword() {
  return getString("password", "hypha");
}

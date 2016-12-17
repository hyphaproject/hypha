// Copyright (c) 2015-2016 Hypha

#include <hypha/core/exceptions/configfilenotfound.h>
#include <hypha/core/settings/configgenerator.h>
#include <hypha/core/settings/hyphasettings.h>

#include <boost/filesystem.hpp>
#include <mutex>

using Poco::AutoPtr;
using Poco::Util::XMLConfiguration;
using namespace hypha::settings;
using namespace hypha::exceptions;

HyphaSettings *HyphaSettings::singleton = 0;

HyphaSettings::HyphaSettings(std::string configfile) {
  this->configfile = configfile;
}

HyphaSettings::~HyphaSettings() {}

HyphaSettings *HyphaSettings::instance() {
  if (!singleton) {
    return loadInstance("hypha.xml");
  }

  return singleton;
}

HyphaSettings *HyphaSettings::loadInstance(std::string configFile) {
  static std::mutex mutex;
  mutex.lock();
  singleton = new HyphaSettings(configFile);
  singleton->load();
  mutex.unlock();
  return singleton;
}

void HyphaSettings::createNewFile() {
  hypha::settings::ConfigGenerator cg;
  cg.generateConfigFile(configfile);
}

void HyphaSettings::load(bool create_if_not_exist) {
  if (!boost::filesystem::exists(configfile)) {
    if (create_if_not_exist) {
      createNewFile();
    } else {
      throw ConfigFileNotFound();
    }
  }

  settings = AutoPtr<XMLConfiguration>(new XMLConfiguration(configfile));
}

void HyphaSettings::save() { settings->save(configfile); }

std::string HyphaSettings::getString(const std::string &key,
                                     const std::string &defaultValue) {
  return settings->getString(key, defaultValue);
}

int HyphaSettings::getInt(const std::string &key, const int &defaultValue) {
  return settings->getInt(key, defaultValue);
}

void HyphaSettings::setString(const std::string &key, std::string &value) {
  settings->setString(key, value);
}

void HyphaSettings::setInt(const std::string &key, std::string &value) {
  settings->setString(key, value);
}

// Copyright (c) 2015-2016 Hypha
#include "hypha/core/settings/configgenerator.h"
#include <Poco/AutoPtr.h>
#include <Poco/Util/IniFileConfiguration.h>
#include <Poco/Util/XMLConfiguration.h>
#include <fstream>
#include <iostream>

using namespace hypha::settings;

ConfigGenerator::ConfigGenerator() {}

void ConfigGenerator::generateConfigFile(std::string filename) {
  Poco::AutoPtr<Poco::Util::XMLConfiguration> settings =
      new Poco::Util::XMLConfiguration();
  settings->loadEmpty("hypha");
  settings->save(filename);
  settings->createView("database");
  settings->setString("database.database", dbDatabase);
  settings->setString("database.driver", dbDriver);
  settings->setString("database.host", dbHost);
  settings->setString("database.username", dbUsername);
  settings->setString("database.password", dbPassword);

  settings->createView("userdatabase");
  settings->setString("userdatabase.database", udbDatabase);
  settings->setString("userdatabase.driver", udbDriver);
  settings->setString("userdatabase.host", udbHost);
  settings->setString("userdatabase.username", udbUsername);
  settings->setString("userdatabase.password", udbPassword);
  settings->setString("userdatabase.table", udbTable);

  settings->setString("userdatabase.attrDevices", udbAttributeDevices);
  settings->setString("userdatabase.attrFirstname", udbAttributeFirstname);
  settings->setString("userdatabase.attrLastname", udbAttributeLastname);
  settings->setString("userdatabase.attrMail", udbAttributeMail);
  settings->setString("userdatabase.attrUsername", udbAttributeUsername);

  settings->save(filename);
}

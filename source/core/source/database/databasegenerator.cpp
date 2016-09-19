// Copyright (c) 2015-2016 Hypha
#include "hypha/core/database/databasegenerator.h"
#include "hypha/core/database/database.h"
#include "hypha/core/database/userdatabase.h"
#include "hypha/core/database/userdbsql.h"
#include "hypha/utils/logger.h"

#include <Poco/AutoPtr.h>
#include <Poco/Util/IniFileConfiguration.h>
#include <Poco/Util/XMLConfiguration.h>
#include <fstream>
#include <iostream>

using namespace hypha::database;

DatabaseGenerator::DatabaseGenerator() {}

void DatabaseGenerator::generateExampleDatabase(
    hypha::settings::DatabaseSettings *settings) {
  hypha::database::Database database(settings);
  try {
    database.connect();
  } catch (std::exception &e) {
    hypha::utils::Logger::error(e.what());
  }
  database.getSession()
      << "INSERT INTO `plugins`(`id`,`host`,`type`,`config`) VALUES('"
      << "espeak"
      << "','"
      << "localhost"
      << "','"
      << "espeak"
      << "','');",
      Poco::Data::Keywords::now;
  database.getSession()
      << "INSERT INTO `handler`(`id`,`host`,`type`,`config`) values('"
      << "testhandler"
      << "','"
      << "localhost"
      << "','"
      << "testhandler"
      << "','{\"message\":\"Hello World!\"}');",
      Poco::Data::Keywords::now;
  database.getSession()
      << "INSERT INTO `connection`(`handler_id`,`plugin_id`) VALUES('"
      << "testhandler"
      << "','"
      << "espeak"
      << "');",
      Poco::Data::Keywords::now;
}

void DatabaseGenerator::generateExampleUserDatabase(
    settings::UserDatabaseSettings *settings) {
  hypha::database::UserDBSql database(settings);
  try {
    database.connect();
  } catch (std::exception &e) {
    hypha::utils::Logger::error(e.what());
  }
}

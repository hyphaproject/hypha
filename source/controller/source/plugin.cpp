// Copyright (c) 2015-2016 Hypha

#include <hypha/controller/plugin.h>
#include <hypha/core/database/database.h>
#include <hypha/utils/logger.h>

#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Statement.h>

using namespace hypha::controller;
using namespace hypha::utils;

hypha::controller::Plugin::Plugin(hypha::database::Database *database) {
  this->database = database;
}

void Plugin::add(std::string id, std::string host, std::string type,
                 std::string config) {
  database->getSession()
      << "INSERT INTO `plugins`(`id`,`host`,`type`,`config`) VALUES('" + id +
             "','" + host + "','" + type + "','" + config + "');",
      Poco::Data::Keywords::now;
}

void Plugin::remove(std::string id) {
  database->getSession() << "DELETE FROM `plugins` WHERE id='" + id + "';",
      Poco::Data::Keywords::now;
}

void Plugin::updateConfig(std::string id, std::string config) {
  database->getSession() << "UPDATE `plugins` SET `config`=? WHERE `id`=?",
      Poco::Data::Keywords::use(config), Poco::Data::Keywords::use(id),
      Poco::Data::Keywords::now;
}

// Copyright (c) 2015-2016 Hypha

#include <hypha/controller/handler.h>
#include <hypha/core/database/database.h>
#include <hypha/utils/logger.h>

#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Statement.h>

using namespace hypha::controller;
using namespace hypha::utils;

hypha::controller::Handler::Handler(hypha::database::Database *database) {
  this->database = database;
}

void Handler::add(std::string id, std::string host, std::string type,
                  std::string config) {
  database->getSession()
      << "INSERT INTO `handler`(`id`,`host`,`type`,`config`) values('" + id +
             "','" + host + "','" + type + "','" + config + "');",
      Poco::Data::Keywords::now;
}

void Handler::remove(std::string id) {
  database->getSession() << "DELETE FROM `handler` WHERE id='" + id + "';",
      Poco::Data::Keywords::now;
}

void Handler::updateConfig(std::string id, std::string config) {
  database->getSession() << "UPDATE `handler` SET `config`=? WHERE `id`=?",
      Poco::Data::Keywords::use(config), Poco::Data::Keywords::use(id),
      Poco::Data::Keywords::now;
}

// Copyright (c) 2015-2016 Hypha
#pragma once

#include <sstream>
#include <string>

#include <Poco/Data/Statement.h>
#include <hypha/controller/controller_api.h>
#include <hypha/core/database/database.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace hypha {
namespace database {
class Database;
}

namespace controller {

class CONTROLLER_API Plugin {
 public:
  Plugin(hypha::database::Database *database);

  /**
   * @brief add Adds a new plugin to the database
   * @param id The unique ID of the plugin
   * @param host The host where the plugin should run
   * @param type The type of plugin
   * @param config The Configuration the plugin should load
   */
  void add(std::string id, std::string host, std::string type,
           std::string config);

  /**
   * @brief remove
   * removes plugin instance from database
   * @param id the plugin instance to remove
   */
  void remove(std::string id);

  void updateConfig(std::string id, std::string config);

  template <typename Type>
  Type getConfigValue(std::string id, std::string key) {
    std::string config = "{}";
    Poco::Data::Statement statement = database->getStatement();
    statement << "SELECT config FROM plugins WHERE id='" + id + "'",
        Poco::Data::Keywords::into(config);
    statement.execute();

    boost::property_tree::ptree ptconfig;
    std::stringstream ssconfig(config);
    boost::property_tree::read_json(ssconfig, ptconfig);

    if (ptconfig.get_optional<Type>(key)) {
      return ptconfig.get<Type>(key);
    } else {
      throw std::runtime_error("does not contain value");
    }
  }

 protected:
  hypha::database::Database *database = nullptr;
};
}
}

// Copyright (c) 2015-2016 Hypha
#pragma once

#include <string>

#include <hypha/controller/controller_api.h>

namespace hypha {
namespace database {
class Database;
}

namespace controller {

class CONTROLLER_API Handler {
 public:
  Handler(hypha::database::Database *database);

  /**
   * @brief add Adds a new handler to the database
   * @param id The unique ID of the handler
   * @param host The host where the handler should run
   * @param type The type of handler
   * @param config The Configuration the handler should load
   */
  void add(std::string id, std::string host, std::string type,
           std::string config);

  void remove(std::string id);

  void updateConfig(std::string id, std::string config);

 protected:
  hypha::database::Database *database = nullptr;
};
}
}

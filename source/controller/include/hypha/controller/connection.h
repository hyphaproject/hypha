// Copyright (c) 2015-2016 Hypha
#pragma once

#include <list>
#include <map>
#include <string>
#include <tuple>

#include <hypha/controller/controller_api.h>

namespace hypha {
namespace database {
class Database;
}

namespace controller {

class CONTROLLER_API Connection {
 public:
  Connection(hypha::database::Database *database);

  void create(std::string handlerId, std::string pluginId);

  /**
   * @brief remove removes connection from database
   * @param id The ID of the connection
   */
  void remove(std::string id);
  std::list<std::tuple<std::string, std::string, std::string>> getConnections();

 protected:
  hypha::database::Database *database = nullptr;
};
}
}

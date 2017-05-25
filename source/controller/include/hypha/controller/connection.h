// Copyright (c) 2015-2017 Hypha
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

  void create(std::string senderId, std::string receiverId);

  /**
   * @brief remove removes connection from database
   * @param id The ID of the connection
   */
  void remove(std::string id);

  /**
   * @brief removeConnections
   * removes all connections of a plugin instance
   * @param pluginId the id of plugin to remove all connections of.
   */
  void removeConnections(std::string pluginId);

  /**
   * @brief getConnections
   * @return list of tuples containing connectionId, senderId and receiverId
   */
  std::list<std::tuple<std::string, std::string, std::string>> getConnections();

  /**
   * @brief getConnections
   * get all connections of plugin
   * @param pluginId the plugins instance id
   * @return list of plugin ids
   */
  std::list<std::string> getConnections(std::string pluginId);

 protected:
  hypha::database::Database *database = nullptr;
};
}
}

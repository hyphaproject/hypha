// Copyright (c) 2015-2016 Hypha
#pragma once

#include <hypha/core/core_api.h>
#include <hypha/core/database/database.h>
#include <list>
#include <string>

namespace hypha {
namespace settings {

/**
 * PluginSettings loads settings of plugins from Database and represents them.
 * You can get access to name, host or config for given plugin id.
 */
class CORE_API PluginSettings {
 public:
  static PluginSettings *instance();

  explicit PluginSettings(hypha::database::Database *database);
  ~PluginSettings();

  /**
   * @brief getAllPluginIds get sender and receiver
   * @return
   */
  std::list<std::string> getAllPluginIds();
  std::list<std::string> getAllIds(std::string table);
  std::list<std::string> getAllSenderIds();
  std::list<std::string> getAllReceiverIds();

  /**
   * @brief getLocalPluginIds get sender and receiver running on localhost
   * @return
   */
  std::list<std::string> getLocalPluginIds();
  std::list<std::string> getLocalIds(std::string table);
  std::list<std::string> getLocalSenderIds();
  std::list<std::string> getLocalReceiverIds();

  std::string getName(std::string id);
  std::string getHost(std::string id);
  std::string getConfig(std::string id);
  std::list<std::string> getConnectedReceiver(std::string senderId);
  bool exists(std::string id);

 protected:
  static PluginSettings *singleton;

  hypha::database::Database *database;
};
}
}

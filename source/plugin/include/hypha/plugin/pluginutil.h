// Copyright (c) 2017 Hypha
#pragma once

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/plugin_api.h>

namespace hypha {
namespace plugin {
/**
 * @brief The HyphaReceiver class
 */
class PLUGIN_API PluginUtil {
 public:
  /**
 * @brief isHandler
 * @param plugin The Plugin to test
 * @return if plugin is instance of HyphaHandler
 */
  static bool isHandler(HyphaBasePlugin* plugin);

  /**
   * @brief isActor
   * @param plugin The Plugin to test
   * @return if plugin is instance of HyphaActor
   */
  static bool isActor(HyphaBasePlugin* plugin);

  /**
   * @brief isSensor
   * @param plugin The Plugin to test
   * @return if plugin is instance of HyphaSensor
   */
  static bool isSensor(HyphaBasePlugin* plugin);

  /**
   * @brief isReceiver
   * @param plugin The Plugin to test
   * @return if plugin is instance of HyphaReceiver
   */
  static bool isReceiver(HyphaBasePlugin* plugin);

  /**
   * @brief isSender
   * @param plugin The Plugin to test
   * @return if plugin is instance of HyphaSender
   */
  static bool isSender(HyphaBasePlugin* plugin);
};
}
}

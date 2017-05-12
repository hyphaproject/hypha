// Copyright (c) 2015-2017 Hypha
#pragma once

#include <hypha/core/settings/pluginsettings.h>
#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/plugin_api.h>
#include <list>
#include <map>
#include <string>

namespace hypha {
namespace plugin {

class PluginFactory;

class PLUGIN_API PluginLoader {
 public:
  static PluginLoader *instance();
  PluginLoader(hypha::settings::PluginSettings *settings);
  ~PluginLoader();

  void loadLocalInstances();
  void loadAllInstances();
  void loadPlugins(std::string dir);
  /**
   * @brief listPlugins
   * @param dir
   * @return a list of plugins
   */
  static std::list<HyphaBasePlugin *> listPlugins(std::string dir);

  /**
   * @brief getPluginStyle
   * @param name the type of plugin
   * @return string of stylesheet loaded from pluginname css file.
   */
  std::string getPluginStyle(std::string name);

  HyphaBasePlugin *getPlugin(std::string name);
  std::list<HyphaBasePlugin *> getPlugins();

  std::list<HyphaBasePlugin *> getInstances();
  HyphaBasePlugin *getPluginInstance(std::string id);

 protected:
  /**
   * @brief loadPluginStyle
   * @param name the type of plugin
   * @param dir the plugins directory
   * @return string of css style sheet file content
   */
  std::string loadPluginStyle(std::string name, std::string dir);

  static PluginLoader *singleton;

  std::list<HyphaBasePlugin *> plugins;
  std::map<std::string, HyphaBasePlugin *> pluginInstances;
  std::map<std::string, std::string> styles;

  hypha::settings::PluginSettings *settings;
  hypha::plugin::PluginFactory *factory;
};
}
}

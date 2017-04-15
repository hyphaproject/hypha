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

  HyphaBasePlugin *getPlugin(std::string name);
  std::list<HyphaBasePlugin *> getPlugins();

  std::list<HyphaBasePlugin *> getInstances();
  HyphaBasePlugin *getPluginInstance(std::string id);



 protected:
  static PluginLoader *singleton;

  std::list<HyphaBasePlugin *> plugins;
  std::map<std::string, HyphaBasePlugin *> pluginInstances;

  hypha::settings::PluginSettings *settings;
  hypha::plugin::PluginFactory *factory;
};
}
}

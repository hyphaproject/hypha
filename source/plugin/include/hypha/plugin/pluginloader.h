// Copyright (c) 2015-2016 Hypha
#pragma once

#include <hypha/core/settings/pluginsettings.h>
#include <hypha/plugin/hyphaplugin.h>
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

  HyphaPlugin *getPlugin(std::string name);
  std::list<HyphaPlugin *> getPlugins();

  std::list<HyphaPlugin *> getInstances();
  HyphaPlugin *getPluginInstance(std::string id);

 protected:
  static PluginLoader *singleton;

  std::list<HyphaPlugin *> plugins;
  std::map<std::string, HyphaPlugin *> pluginInstances;

  hypha::settings::PluginSettings *settings;
  hypha::plugin::PluginFactory *factory;
};
}
}

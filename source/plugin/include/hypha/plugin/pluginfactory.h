// Copyright (c) 2015-2016 Hypha
#pragma once

#include <string>
#include <hypha/plugin/hyphaplugin.h>
#include <hypha/plugin/plugin_api.h>

namespace hypha {

namespace settings {
class PluginSettings;
}

namespace plugin {
class PluginLoader;

class PLUGIN_API PluginFactory {
 public:
  static PluginFactory *instance();
  explicit PluginFactory(hypha::settings::PluginSettings *settings,
                         hypha::plugin::PluginLoader *loader);
  ~PluginFactory();

  HyphaPlugin *loadPlugin(std::string id);

  void setId(std::string id);
  void setHost(std::string host);
  void setConfig(std::string config);

 private:
  static PluginFactory *singleton;

  std::string id;
  std::string host;
  std::string config;
  HyphaPlugin *create();
  hypha::settings::PluginSettings *settings;
  hypha::plugin::PluginLoader *loader;
};
}
}

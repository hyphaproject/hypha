#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "../plugin.h"
#include <string>
#include <list>
#include <map>
#include <hypha/settings/pluginsettings.h>
#include "hypha/plugin/hyphaplugin.h"

namespace hypha {
namespace plugin {

class PluginFactory;

class Plugin_API PluginLoader {
  public:
    static PluginLoader *instance();
    explicit PluginLoader(hypha::settings::PluginSettings *settings);
    ~PluginLoader();

    void loadLocalInstances();
    void loadAllInstances();

    HyphaPlugin *getPlugin(std::string name);
    std::list<HyphaPlugin *> getPlugins();

    std::list<HyphaPlugin *> getInstances();
    HyphaPlugin *getPluginInstance(std::string id);

  private:
    static PluginLoader *singleton;

    std::list<HyphaPlugin *> plugins;
    std::map<std::string, HyphaPlugin *> pluginInstances;
    void loadPlugins(std::string dir);
    hypha::settings::PluginSettings *settings;
    hypha::plugin::PluginFactory *factory;

};
}
}

#endif // PLUGINLOADER_H

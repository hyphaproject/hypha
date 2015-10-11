#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "../plugin.h"
#include <string>
#include <list>
#include "hyphaplugin.h"

namespace hypha {
namespace plugin {
class Plugin_API PluginLoader {
  public:
    static PluginLoader * instance();

    void loadLocalInstances();

    HyphaPlugin* getPlugin(std::string name);
    std::list<HyphaPlugin *> getPlugins();


    std::list<HyphaPlugin *> getInstances();
    HyphaPlugin *getPluginInstance(std::string id);

  private:
    PluginLoader();
    ~PluginLoader();

    static PluginLoader *singleton;

    std::list<HyphaPlugin *> plugins;
    std::map<std::string, HyphaPlugin *> pluginInstances;
    void loadPlugins(std::string dir);

};
}
}

#endif // PLUGINLOADER_H

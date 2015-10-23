#ifndef PLUGINFACTORY_H
#define PLUGINFACTORY_H

#include "../plugin.h"
#include <string>
#include "hypha/plugin/hyphaplugin.h"

namespace hypha {

namespace settings {
class PluginSettings;
}

namespace plugin {
class PluginLoader;

class Plugin_API PluginFactory {
  public:
    static PluginFactory * instance();
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

#endif // PLUGINFACTORY_H

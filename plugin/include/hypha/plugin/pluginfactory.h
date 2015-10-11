#ifndef PLUGINFACTORY_H
#define PLUGINFACTORY_H

#include "../plugin.h"
#include <string>
#include "hyphaplugin.h"

namespace hypha {
namespace plugin {

class Plugin_API PluginFactory {
  public:
    static PluginFactory * instance();

  public:
    static HyphaPlugin *loadPlugin(std::string id);

    void setId(std::string id);
    void setHost(std::string host);
    void setConfig(std::string config);

  private:
    explicit PluginFactory();
    ~PluginFactory();

    static PluginFactory *singleton;

    std::string id;
    std::string host;
    std::string config;
    HyphaPlugin *create();

};
}
}

#endif // PLUGINFACTORY_H

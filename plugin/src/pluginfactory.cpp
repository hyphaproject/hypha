#include <mutex>
#include <hypha/settings/pluginsettings.h>
#include "hypha/plugin/pluginfactory.h"
#include "hypha/plugin/pluginloader.h"


using namespace hypha::plugin;
using namespace hypha::settings;

PluginFactory *PluginFactory::singleton = 0;

PluginFactory::PluginFactory() {
}

PluginFactory::~PluginFactory() {

}

HyphaPlugin *PluginFactory::create() {
    PluginSettings * pluginSettings = PluginSettings::instance();
    HyphaPlugin *p = PluginLoader::instance()->getPlugin(pluginSettings->getName(id));
    if(p) {
        HyphaPlugin *plugin = p->getInstance(id);
        plugin->setHost(PluginSettings::instance()->getHost(id));
        plugin->loadConfig(config);
        return plugin;
    } else {
        return 0;
    }
}

PluginFactory *PluginFactory::instance() {
    static std::mutex mutex;
    if (!singleton) {
        mutex.lock();

        if (!singleton)
            singleton = new PluginFactory();
        mutex.unlock();
    }

    return singleton;
}

HyphaPlugin *PluginFactory::loadPlugin(std::string id) {
    PluginSettings * pluginSettings = PluginSettings::instance();
    if(!pluginSettings->exists(id))
        return 0;
    PluginFactory factory;
    factory.setId(id);
    factory.setHost(pluginSettings->getHost(id));
    factory.setConfig(pluginSettings->getConfig(id));
    return factory.create();
}

void PluginFactory::setId(std::string id) {
    this->id = id;
}

void PluginFactory::setHost(std::string host) {
    this->host = host;
}

void PluginFactory::setConfig(std::string config) {
    this->config = config;
}

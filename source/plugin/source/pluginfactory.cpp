#include <mutex>
#include <hypha/core/settings/pluginsettings.h>
#include <hypha/plugin/pluginfactory.h>
#include <hypha/plugin/pluginloader.h>


using namespace hypha::plugin;
using namespace hypha::settings;

PluginFactory *PluginFactory::singleton = 0;

PluginFactory::PluginFactory(hypha::settings::PluginSettings *settings,
                             hypha::plugin::PluginLoader *loader) {
    this->settings = settings;
    this->loader = loader;
}

PluginFactory::~PluginFactory() {

}

HyphaPlugin *PluginFactory::create() {
    HyphaPlugin *p = loader->getPlugin(settings->getName(id));
    if (p) {
        HyphaPlugin *plugin = p->getInstance(id);
        plugin->setHost(host);
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
            singleton = new PluginFactory(hypha::settings::PluginSettings::instance(),
                                          hypha::plugin::PluginLoader::instance());
        mutex.unlock();
    }

    return singleton;
}

HyphaPlugin *PluginFactory::loadPlugin(std::string id) {
    if (!settings->exists(id))
        return 0;
    setId(id);
    setHost(settings->getHost(id));
    setConfig(settings->getConfig(id));
    return create();
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
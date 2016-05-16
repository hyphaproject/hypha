#include <Poco/ClassLoader.h>
#include <Poco/Manifest.h>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <mutex>
#include <hypha/plugin/pluginloader.h>
#include <hypha/plugin/pluginfactory.h>
#include <hypha/core/settings/pluginsettings.h>
#include <hypha/utils/logger.h>

using namespace hypha::plugin;
using namespace hypha::settings;
using namespace hypha::utils;

typedef Poco::ClassLoader<HyphaPlugin> PLoader;
typedef Poco::Manifest<HyphaPlugin> PManifest;

PluginLoader *PluginLoader::singleton = 0;

PluginLoader::PluginLoader(hypha::settings::PluginSettings *settings) {
    this->settings = settings;
    this->factory = new hypha::plugin::PluginFactory(settings, this);
    loadPlugins(boost::filesystem::path( boost::filesystem::current_path()).generic_string());
}

PluginLoader::~PluginLoader() {

}

PluginLoader *PluginLoader::instance() {
    static std::mutex mutex;
    if (!singleton) {
        mutex.lock();

        if (!singleton)
            singleton = new PluginLoader(hypha::settings::PluginSettings::instance());
        mutex.unlock();
    }

    return singleton;
}

void PluginLoader::loadLocalInstances() {
    for (std::string id : settings->getLocalPluginIds()) {
        if (getPluginInstance(id) == 0) {
            HyphaPlugin *plugin = factory->loadPlugin(id);
            if (plugin)
                pluginInstances[id] = plugin;
        }
    }
}

void PluginLoader::loadAllInstances() {
    for (std::string id : settings->getAllPluginIds()) {
        if (getPluginInstance(id) == 0) {
            HyphaPlugin *plugin = factory->loadPlugin(id);
            if (plugin)
                pluginInstances[id] = plugin;
        }
    }
}

HyphaPlugin *PluginLoader::getPlugin(std::string name) {
    for (HyphaPlugin *plugin : plugins) {
        if (plugin->name() == name)
            return plugin;
    }

    return 0;
}

std::list<HyphaPlugin *> PluginLoader::getPlugins() {
    return plugins;
}

std::list<HyphaPlugin *> PluginLoader::getInstances() {
    std::list<HyphaPlugin *> retList;
    for (std::map<std::string, HyphaPlugin *>::const_iterator it = pluginInstances.begin(); it != pluginInstances.end(); ++it) {
        retList.push_back( it->second );
    }
    return retList;
}

HyphaPlugin *PluginLoader::getPluginInstance(std::string id) {
    return this->pluginInstances[id];
}

void PluginLoader::loadPlugins(std::string dir) {
    boost::filesystem::path pluginsDir(dir + "/../plugins");
    if (boost::filesystem::exists(pluginsDir)) {

    } else {
        return;
    }
    PLoader loader;

    boost::filesystem::directory_iterator dit( pluginsDir ), eod;
    BOOST_FOREACH( boost::filesystem::path const & p, std::make_pair( dit, eod ) ) {
        if ( boost::filesystem::is_regular_file( p ) ) {
            std::string fileName = boost::filesystem::absolute(p).string();
            try {

                loader.loadLibrary(fileName);
                Logger::info(fileName);
            } catch (Poco::Exception &e) {
                Logger::warning(e.message());
            }
        }
    }

    PLoader::Iterator it(loader.begin());
    PLoader::Iterator end(loader.end());
    for (; it != end; ++it) {
        PManifest::Iterator itMan(it->second->begin());
        PManifest::Iterator endMan(it->second->end());
        for (; itMan != endMan; ++itMan) {
            this->plugins.insert(plugins.end(), itMan->create());
        }
    }
}

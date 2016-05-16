#include <Poco/ClassLoader.h>
#include <Poco/Manifest.h>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <mutex>
#include <map>
#include <hypha/core/settings/handlersettings.h>
#include <hypha/handler/handlerfactory.h>
#include <hypha/handler/handlerloader.h>

using namespace hypha::handler;
using namespace hypha::settings;

typedef Poco::ClassLoader<HyphaHandler> PLoader;
typedef Poco::Manifest<HyphaHandler> PManifest;

HandlerLoader *HandlerLoader::singleton = 0;

HandlerLoader::HandlerLoader(hypha::settings::HandlerSettings *settings) {
    this->settings = settings;
    this->factory = new hypha::handler::HandlerFactory(settings, this);
    loadHandlers(boost::filesystem::path( boost::filesystem::current_path()).generic_string());
}

HandlerLoader::~HandlerLoader() {

}

HandlerLoader *HandlerLoader::instance() {
    static std::mutex mutex;
    if (!singleton) {
        mutex.lock();
        if (!singleton)
            singleton = new HandlerLoader(hypha::settings::HandlerSettings::instance());
        mutex.unlock();
    }

    return singleton;
}

void HandlerLoader::loadLocalInstances() {
    for (std::string id : settings->getLocalHandlerIds()) {
        if (getHandlerInstance(id) == 0) {
            HyphaHandler *handler = factory->loadHandler(id);
            if (handler)
                handlerInstances[id] = handler;
        }
    }
}

void HandlerLoader::loadAllInstances() {
    for (std::string id : settings->getAllHandlerIds()) {
        if (getHandlerInstance(id) == 0) {
            HyphaHandler *handler = factory->loadHandler(id);
            if (handler)
                handlerInstances[id] = handler;
        }
    }
}

HyphaHandler *HandlerLoader::getHandler(std::string name) {
    for (HyphaHandler *plugin : handlers) {
        if (plugin->name() == name)
            return plugin;
    }

    return 0;
}

std::list<HyphaHandler *> HandlerLoader::getHandlers() {
    return handlers;
}

std::list<HyphaHandler *> HandlerLoader::getInstances() {
    std::list<HyphaHandler *> retList;
    for (std::map<std::string, HyphaHandler *>::const_iterator it = handlerInstances.begin(); it != handlerInstances.end(); ++it) {
        retList.push_back( it->second );
    }
    return retList;
}

HyphaHandler *HandlerLoader::getHandlerInstance(std::string id) {
    return this->handlerInstances[id];
}

std::list<std::string> HandlerLoader::getConnectedPlugins(std::string handlerId) {
    return settings->getConnectedPlugins(handlerId);
}

void HandlerLoader::loadHandlers(std::string dir) {
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
                std::cout << fileName << std::endl;

            } catch (Poco::Exception &e) {
                std::cout << e.what();
            }
        }
    }

    PLoader::Iterator it(loader.begin());
    PLoader::Iterator end(loader.end());
    for (; it != end; ++it) {
        PManifest::Iterator itMan(it->second->begin());
        PManifest::Iterator endMan(it->second->end());
        for (; itMan != endMan; ++itMan) {
            this->handlers.insert(handlers.end(), itMan->create());
        }
    }
}

#include <mutex>
#include <hypha/settings/handlersettings.h>
#include "hypha/handler/handlerloader.h"
#include "hypha/handler/handlerfactory.h"

using namespace hypha::handler;
using namespace hypha::settings;

HandlerFactory *HandlerFactory::singleton = 0;

HandlerFactory::HandlerFactory() {

}

HandlerFactory::~HandlerFactory() {

}

HyphaHandler *HandlerFactory::create() {
    HandlerSettings * handlerSettings = HandlerSettings::instance();
    HyphaHandler * handler = HandlerLoader::instance()->getHandler(handlerSettings->getName(id));
    if(handler) {
        HyphaHandler *plugin = handler->getInstance(id);
        plugin->setHost(HandlerSettings::instance()->getHost(id));
        plugin->loadConfig(handlerSettings->getConfig(id));
        return plugin;
    } else {
        return 0;
    }
}

HandlerFactory *HandlerFactory::instance() {
    static std::mutex mutex;
    if (!singleton) {
        mutex.lock();

        if (!singleton)
            singleton = new HandlerFactory();
        mutex.unlock();
    }

    return singleton;
}

HyphaHandler *HandlerFactory::loadHandler(std::string id) {
    HandlerSettings * handlerSettings = HandlerSettings::instance();
    if(!handlerSettings->exists(id))
        return 0;
    HandlerFactory factory;
    factory.setId(id);
    factory.setHost(handlerSettings->getHost(id));
    factory.setConfig(handlerSettings->getConfig(id));
    return factory.create();
}

void HandlerFactory::setId(std::string id) {
    this->id = id;
}

void HandlerFactory::setHost(std::string host) {
    this->host = host;
}

void HandlerFactory::setConfig(std::string config) {
    this->config = config;
}


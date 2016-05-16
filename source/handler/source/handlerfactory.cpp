#include <mutex>

#include <hypha/core/settings/handlersettings.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/handler/handlerfactory.h>

using namespace hypha::handler;
using namespace hypha::settings;

HandlerFactory *HandlerFactory::singleton = 0;

HandlerFactory::HandlerFactory(hypha::settings::HandlerSettings *settings,
                               hypha::handler::HandlerLoader *loader) {
    this->settings = settings;
    this->loader = loader;
}

HandlerFactory::~HandlerFactory() {

}

HyphaHandler *HandlerFactory::create() {
    HyphaHandler *handler = loader->getHandler(settings->getName(id));
    if (handler) {
        HyphaHandler *plugin = handler->getInstance(id);
        plugin->setHost(host);
        plugin->loadConfig(config);
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
            singleton = new HandlerFactory(hypha::settings::HandlerSettings::instance(),
                                           hypha::handler::HandlerLoader::instance());
        mutex.unlock();
    }

    return singleton;
}

HyphaHandler *HandlerFactory::loadHandler(std::string id) {
    if (!settings->exists(id))
        return 0;

    setId(id);
    setHost(settings->getHost(id));
    setConfig(settings->getConfig(id));
    return create();
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


#include <mutex>

#include <hypha/core/settings/handlersettings.h>
#include <hypha/handler/handlerfactory.h>
#include <hypha/handler/handlerloader.h>
#include <hypha/utils/logger.h>

using namespace hypha::handler;
using namespace hypha::settings;

HandlerFactory *HandlerFactory::singleton = 0;

HandlerFactory::HandlerFactory(hypha::settings::HandlerSettings *settings,
                               hypha::handler::HandlerLoader *loader) {
  this->settings = settings;
  this->loader = loader;
}

HandlerFactory::~HandlerFactory() {}

HyphaHandler *HandlerFactory::create() {
  HyphaHandler *handler = loader->getHandler(settings->getName(id));
  if (handler) {
    HyphaHandler *plugin = handler->getInstance(id);
    plugin->setHost(host);
    try {
      plugin->loadConfig(config);
    } catch (std::exception &e) {
      hypha::utils::Logger::warning("Exception while loading config for " + plugin->getId() +
                      " : ");
      hypha::utils::Logger::warning(e.what());
    }
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
      singleton =
          new HandlerFactory(hypha::settings::HandlerSettings::instance(),
                             hypha::handler::HandlerLoader::instance());
    mutex.unlock();
  }

  return singleton;
}

HyphaHandler *HandlerFactory::loadHandler(std::string id) {
  if (!settings->exists(id)) return 0;

  setId(id);
  setHost(settings->getHost(id));
  setConfig(settings->getConfig(id));
  return create();
}

void HandlerFactory::setId(std::string id) { this->id = id; }

void HandlerFactory::setHost(std::string host) { this->host = host; }

void HandlerFactory::setConfig(std::string config) { this->config = config; }

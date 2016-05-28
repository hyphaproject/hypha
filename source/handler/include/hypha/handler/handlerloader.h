// Copyright (c) 2015-2016 Hypha

#ifndef HANDLERLOADER_H
#define HANDLERLOADER_H

#include <hypha/core/settings/handlersettings.h>
#include <hypha/handler/handler_api.h>
#include <hypha/handler/hyphahandler.h>
#include <list>
#include <map>
#include <string>

namespace hypha {
namespace handler {

class HandlerFactory;

class HANDLER_API HandlerLoader {
 public:
  static HandlerLoader *instance();
  explicit HandlerLoader(hypha::settings::HandlerSettings *settings);
  ~HandlerLoader();

  void loadLocalInstances();
  void loadAllInstances();
  void loadHandlers(std::string dir);

  HyphaHandler *getHandler(std::string name);
  std::list<HyphaHandler *> getHandlers();

  std::list<HyphaHandler *> getInstances();
  HyphaHandler *getHandlerInstance(std::string id);

  std::list<std::string> getConnectedPlugins(std::string handlerId);

 protected:
  static HandlerLoader *singleton;

  std::list<HyphaHandler *> handlers;
  std::map<std::string, HyphaHandler *> handlerInstances;

  hypha::settings::HandlerSettings *settings;
  hypha::handler::HandlerFactory *factory;
};
}
}

#endif  // HANDLERLOADER_H

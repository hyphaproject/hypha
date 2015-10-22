#ifndef HANDLERLOADER_H
#define HANDLERLOADER_H

#include "../handler.h"
#include <list>
#include <map>
#include <string>
#include <hypha/settings/handlersettings.h>
#include "hypha/handler/hyphahandler.h"


namespace hypha {
namespace handler {

class HandlerFactory;

class Handler_API HandlerLoader {
  public:
    static HandlerLoader * instance();
    explicit HandlerLoader(hypha::settings::HandlerSettings *settings, hypha::handler::HandlerFactory *factory);
    ~HandlerLoader();

    void loadLocalInstances();

    HyphaHandler* getHandler(std::string name);
    std::list<HyphaHandler *> getHandlers();

    std::list<HyphaHandler *> getInstances();
    HyphaHandler *getHandlerInstance(std::string id);

    std::list<std::string> getConnectedPlugins(std::string handlerId);

  private:


    static HandlerLoader *singleton;

    std::list<HyphaHandler *> handlers;
    std::map<std::string, HyphaHandler *> handlerInstances;
    void loadHandlers(std::string dir);
    hypha::settings::HandlerSettings *settings;
    hypha::handler::HandlerFactory *factory;

};
}
}

#endif // HANDLERLOADER_H

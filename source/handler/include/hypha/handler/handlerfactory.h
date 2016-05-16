#ifndef HANDLERFACTORY_H
#define HANDLERFACTORY_H

#include <hypha/handler/handler_api.h>
#include <hypha/handler/hyphahandler.h>

namespace hypha {

namespace settings {
class HandlerSettings;
}

namespace handler {
class HandlerLoader;

class HANDLER_API HandlerFactory {
  public:
    static HandlerFactory *instance();
    explicit HandlerFactory(hypha::settings::HandlerSettings *settings,
                            hypha::handler::HandlerLoader *loader);
    ~HandlerFactory();

    HyphaHandler *loadHandler(std::string id);

    void setId(std::string id);
    void setHost(std::string host);
    void setConfig(std::string config);

  private:

    static HandlerFactory *singleton;

    std::string id;
    std::string host;
    std::string config;
    HyphaHandler *create();
    hypha::settings::HandlerSettings *settings;
    hypha::handler::HandlerLoader *loader;

};
}
}

#endif // HANDLERFACTORY_H

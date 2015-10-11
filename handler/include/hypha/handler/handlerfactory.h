#ifndef HANDLERFACTORY_H
#define HANDLERFACTORY_H

#include "../handler.h"
#include "hypha/handler/hyphahandler.h"

namespace hypha {
namespace handler {

class Handler_API HandlerFactory {
  public:
    static HandlerFactory * instance();

  public:
    static HyphaHandler *loadHandler(std::string id);

    void setId(std::string id);
    void setHost(std::string host);
    void setConfig(std::string config);

  private:
    HandlerFactory();
    ~HandlerFactory();

    static HandlerFactory *singleton;

    std::string id;
    std::string host;
    std::string config;
    HyphaHandler *create();

};
}
}

#endif // HANDLERFACTORY_H

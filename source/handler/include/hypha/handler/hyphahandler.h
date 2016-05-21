#ifndef HYPHAHANDLER_H
#define HYPHAHANDLER_H

#include <boost/signals2.hpp>
#include <hypha/handler/handler_api.h>
#include <hypha/plugin/hyphabaseplugin.h>

namespace hypha {
namespace handler {
class HANDLER_API HyphaHandler: public hypha::plugin::HyphaBasePlugin {
  public:

    virtual HyphaHandler *getInstance(std::string id) = 0;

};
}
}

#endif // HYPHAHANDLER_H

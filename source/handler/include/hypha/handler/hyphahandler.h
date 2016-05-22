// Copyright (c) 2015-2016 Hypha

#ifndef HYPHAHANDLER_H
#define HYPHAHANDLER_H

#include <hypha/handler/handler_api.h>
#include <hypha/plugin/hyphabaseplugin.h>
#include <boost/signals2.hpp>

namespace hypha {
namespace handler {
class HANDLER_API HyphaHandler : public hypha::plugin::HyphaBasePlugin {
 public:
  virtual HyphaHandler *getInstance(std::string id) = 0;
};
}
}

#endif  // HYPHAHANDLER_H

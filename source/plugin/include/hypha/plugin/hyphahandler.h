// Copyright (c) 2015-2017 Hypha
#pragma once

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/plugin_api.h>
#include <boost/signals2.hpp>

namespace hypha {
namespace handler {
class PLUGIN_API HyphaHandler : public hypha::plugin::HyphaBasePlugin {
 public:
  virtual HyphaHandler *getInstance(std::string id) = 0;
};
}
}

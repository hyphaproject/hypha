// Copyright (c) 2015-2016 Hypha
#pragma once

#include <boost/signals2.hpp>

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/plugin_api.h>

namespace hypha {
namespace plugin {

class PLUGIN_API HyphaPlugin : public HyphaBasePlugin {
 public:
  virtual void setup() = 0;
  virtual std::string communicate(std::string message) = 0;
  virtual HyphaPlugin *getInstance(std::string id) = 0;
};
}
}

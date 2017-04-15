// Copyright (c) 2017 Hypha
#pragma once

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/hyphareceiver.h>
#include <hypha/plugin/hyphasender.h>
#include <hypha/plugin/plugin_api.h>

namespace hypha {
namespace plugin {
class PLUGIN_API HyphaHandler : virtual public HyphaBasePlugin,
                                virtual public HyphaReceiver,
                                virtual public HyphaSender {
 public:
  virtual ~HyphaHandler() {}
};
}
}

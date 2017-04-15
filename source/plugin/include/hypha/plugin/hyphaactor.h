// Copyright (c) 2017 Hypha
#pragma once

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/plugin_api.h>
#include <hypha/plugin/hyphareceiver.h>

namespace hypha {
namespace plugin {

class PLUGIN_API HyphaActor : virtual public HyphaBasePlugin,
                              virtual public HyphaReceiver {
 public:
  virtual ~HyphaActor() {}
};
}
}

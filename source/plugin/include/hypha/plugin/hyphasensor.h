// Copyright (c) 2017 Hypha
#pragma once

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/plugin_api.h>
#include <hypha/plugin/hyphasender.h>

namespace hypha {
namespace plugin {

class PLUGIN_API HyphaSensor : virtual public HyphaBasePlugin,
                               virtual public HyphaSender {
 public:
  virtual ~HyphaSensor() {}
};
}
}

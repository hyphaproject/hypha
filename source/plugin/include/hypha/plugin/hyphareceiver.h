// Copyright (c) 2017 Hypha
#pragma once

#include <hypha/plugin/plugin_api.h>

namespace hypha {
namespace plugin {
/**
 * @brief The HyphaReceiver class
 */
class PLUGIN_API HyphaReceiver{
 public:
  virtual ~HyphaReceiver() {}
  virtual void receiveMessage(std::string message) = 0;
};
}
}

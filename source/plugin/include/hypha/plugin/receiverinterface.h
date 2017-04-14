// Copyright (c) 2017 Hypha
#pragma once

#include <hypha/plugin/plugin_api.h>

namespace hypha {
namespace plugin {
/**
 * @brief The ReceiverInterface class
 */
class PLUGIN_API ReceiverInterface {
 public:
  virtual ~ReceiverInterface() {}
  virtual void receiveMessage(std::string message) = 0;
};
}
}

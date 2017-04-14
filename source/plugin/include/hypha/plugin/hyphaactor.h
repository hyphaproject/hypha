// Copyright (c) 2017 Hypha
#pragma once

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/receiverinterface.h>
#include <hypha/plugin/plugin_api.h>

namespace hypha {
namespace plugin {

class PLUGIN_API HyphaActor : public HyphaBasePlugin, public ReceiverInterface {
 public:
  virtual void setup() = 0;
  virtual void receiveMessage(std::string message) = 0;
  virtual std::string communicate(std::string message) = 0;
  virtual HyphaSensor *getInstance(std::string id) = 0;
};
}
}

// Copyright (c) 2017 Hypha
#pragma once

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/plugin_api.h>
#include <hypha/plugin/receiverinterface.h>
#include <hypha/plugin/senderinterface.h>

namespace hypha {
namespace plugin {
class PLUGIN_API HyphaHandler : virtual public HyphaBasePlugin,
                                virtual public ReceiverInterface,
                                virtual public SenderInterface {
 public:
  virtual ~HyphaHandler() {}
};
}
}

// Copyright (c) 2017 Hypha
#pragma once

#include <hypha/plugin/plugin_api.h>
#include <boost/signals2.hpp>

namespace hypha {
namespace plugin {

/**
 * @brief The HyphaSender class
 */
class PLUGIN_API HyphaSender {
 public:
  virtual ~HyphaSender() {}
  typedef boost::signals2::signal<void(std::string)> SendMessage;
  typedef SendMessage::slot_type SendMessageSlotType;

  std::string callMessage(std::string id, std::string message) {
    return callMessageFunction(id, message);
  }

  void setCallMessageFunction(
      std::function<std::string(std::string, std::string)> f) {
    callMessageFunction = f;
  }
  boost::signals2::connection connect(const SendMessageSlotType &slot) {
    return sendMessage.connect(slot);
  }

 protected:
  SendMessage sendMessage;
  std::function<std::string(std::string, std::string)> callMessageFunction;
};
}
}

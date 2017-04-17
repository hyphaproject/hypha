// Copyright (c) 2015-2017 Hypha
#pragma once

#include <hypha/plugin/plugin_api.h>

#include <memory>
#include <string>

namespace hypha {
namespace plugin {

/**
 * @brief The Connection class
 */
class PLUGIN_API Connection {
 public:
  Connection(std::string senderId, std::string receiverId) {
    this->senderId = senderId;
    this->receiverId = receiverId;
  }
  virtual ~Connection() {}
  virtual bool connect(std::shared_ptr<Connection> connection) = 0;
  virtual bool disconnect() = 0;
  virtual void sendMessage(std::string message) = 0;

 protected:
  std::string senderId;
  std::string receiverId;
};
}
}

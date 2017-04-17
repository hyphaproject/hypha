// Copyright (c) 2017 Hypha
#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include <hypha/plugin/connection.h>
#include <hypha/plugin/plugin_api.h>

namespace hypha {
namespace plugin {

/**
 * @brief The HyphaSender class
 */
class PLUGIN_API HyphaSender {
 public:
  HyphaSender() {}
  virtual ~HyphaSender() {}

  std::string callMessage(std::string id, std::string message) {
    return callMessageFunction(id, message);
  }

  virtual void setCallMessageFunction(
      std::function<std::string(std::string, std::string)> f) {
    callMessageFunction = f;
  }

  void addListener(std::shared_ptr<Connection> connection) {
    connections.push_back((connection));
  }

  void sendMessage(std::string message) {
    for (std::shared_ptr<Connection> connection : connections) {
      connection->sendMessage(message);
    }
  }

 protected:
  std::function<std::string(std::string, std::string)> callMessageFunction;
  std::vector<std::shared_ptr<Connection>> connections;
};
}
}

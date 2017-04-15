// Copyright (c) 2017 Hypha

#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <hypha/plugin/hyphaactor.h>
#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/hyphasensor.h>
#include <string>

namespace hypha {
namespace plugin {
namespace helloworld {
class HelloWorld : public HyphaSensor, public HyphaActor {
 public:
  virtual void doWork() override;
  virtual void setup() override;
  const std::string name() override { return "helloworld"; }
  const std::string getTitle() override { return "Hello World Plugin"; }
  const std::string getVersion() override { return "0.1"; }
  const std::string getDescription() override {
    return "Sensor for time and actor for printing hello world to std out";
  }
  const std::string getConfigDescription() override { return "{}"; }
  void loadConfig(std::string json) override;
  std::string getConfig() override;
  HyphaBasePlugin *getInstance(std::string id) override;

  std::string communicate(std::string /*message*/) override;
  virtual void receiveMessage(std::string message) override;

 protected:
  std::string config;
};
}
}
}
#endif  // HELLOWORLD_H

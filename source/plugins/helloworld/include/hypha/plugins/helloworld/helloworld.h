// Copyright (c) 2017 Hypha

#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/hyphasensor.h>
#include <string>

namespace hypha {
namespace plugin {
namespace helloworld {
class HelloWorld : public HyphaSensor {
 public:
  void doWork();
  void setup();
  const std::string name() { return "helloworld"; }
  const std::string getTitle() { return "Hello World Plugin"; }
  const std::string getVersion() { return "0.1"; }
  const std::string getDescription() {
    return "Sensor for time and actor for printing hello world to std out";
  }
  const std::string getConfigDescription() { return "{}"; }
  void loadConfig(std::string json);
  std::string getConfig();
  HyphaBasePlugin *getInstance(std::string id);

  std::string communicate(std::string /*message*/);

 protected:
  std::string config;
};
}
}
}
#endif  // HELLOWORLD_H

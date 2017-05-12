// Copyright (c) 2015-2017 Hypha
// source:
// https://github.com/muhrix/espeak_ros/blob/master/src/espeak_ros_node.cpp
// source:
// https://github.com/kashimAstro/ofxEspeakSynth/blob/master/src/ofxEspeakSynth.cpp

#ifndef ESPEAK_H
#define ESPEAK_H

#include <string>

#include <espeak/speak_lib.h>
#include <hypha/plugin/hyphaactor.h>

namespace hypha {
namespace plugin {
namespace espeak {
class ESpeak : public HyphaActor {
 public:
  ESpeak();
  void doWork() override;
  void setup() override;
  std::string communicate(std::string message) override;
  const std::string name() override { return "espeak"; }
  const std::string getTitle() override { return "ESpeak"; }
  const std::string getVersion() override { return "0.1"; }
  const std::string getDescription() override {
    return "Plugin to speak text with espeak.";
  }
  virtual const std::string getConfigDescription() override {
    return "{"
           "\"confdesc\":["
           "{\"name\":\"language\", "
           "\"type\":\"string\",\"value\":\"en\",\"description\":\"spoken "
           "language\"}"
           "]}";
  }
  void loadConfig(std::string json) override;
  std::string getConfig() override;
  hypha::plugin::HyphaBasePlugin *getInstance(std::string id) override;

  void receiveMessage(std::string message) override;

 private:
  std::string language = "en";
};
}
}
}
#endif  // ESPEAK_H

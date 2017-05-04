// Copyright (c) 2015-2017 Hypha

#ifndef JAVASCRIPTPLUGIN_H
#define JAVASCRIPTPLUGIN_H

#include <string>

#include <hypha/plugin/hyphaactor.h>
#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/hyphasensor.h>
#include <v8.h>

namespace hypha {
namespace plugin {
namespace javascriptplugin {
class JavascriptPlugin : public HyphaBasePlugin {
 public:
  JavascriptPlugin();
  ~JavascriptPlugin();

  void doWork() override;
  void setup() override;
  const std::string name() override { return "javascriptplugin"; }
  const std::string getTitle() override { return "Javascript Plugin"; }
  const std::string getVersion() override { return "0.1"; }
  const std::string getDescription() override {
    return "Plugin to use Javascript code.";
  }
  const std::string getConfigDescription() override { return "{}"; }
  void loadConfig(std::string json) override;
  std::string getConfig() override;
  HyphaBasePlugin* getInstance(std::string id) override;

  void receiveMessage(std::string message);
  std::string communicate(std::string message) override;
  std::string parse_python_exception();

  static v8::Handle<v8::Value> LogCallback(const v8::Arguments& args);

 protected:
  bool ExecuteScript(v8::Handle<v8::String> script);

  v8::Handle<v8::String> script_;
  v8::Persistent<v8::Context> context_;

  v8::Persistent<v8::Function> function_doWork;

  std::string config;
  std::string javascriptmodule = "javascriptplugin";
  std::string javascriptclass = "javascriptplugin";
};
}
}
}
#endif  // JAVASCRIPTPLUGIN_H

// Copyright (c) 2015-2017 Hypha

#ifndef PYTHONPLUGIN_H
#define PYTHONPLUGIN_H

#include <hypha/plugin/hyphabaseplugin.h>
#include <boost/python.hpp>
#include <string>

namespace hypha {
namespace plugin {
namespace pythonplugin {
class PythonPlugin : public HyphaBasePlugin {
 public:
  void doWork() override;
  void setup() override;
  const std::string name() override { return "pythonplugin"; }
  const std::string getTitle() override { return "Python Plugin"; }
  const std::string getVersion() override { return "0.1"; }
  const std::string getDescription() override {
    return "Plugin to use Python code.";
  }
  const std::string getConfigDescription() override { return "{}"; }
  void loadConfig(std::string json) override;
  std::string getConfig() override;
  HyphaBasePlugin *getInstance(std::string id) override;

  void receiveMessage(std::string message);
  std::string communicate(std::string message) override;
  std::string parse_python_exception();

 protected:
  std::string config;
  std::string pythonmodule = "pythonplugin";
  std::string pythonclass = "pythonplugin";
  boost::python::object main;
  boost::python::object global;
  boost::python::object result;
  boost::python::object py_class;
};
}
}
}
#endif  // PYTHONPLUGIN_H

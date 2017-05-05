// Copyright (c) 2017 Hypha

#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include <gmock/gmock.h>

#include <hypha/plugin/hyphasender.h>
#include <hypha/plugin/pluginloader.h>
#include <hypha/plugin/pluginutil.h>
#include <hypha/utils/logger.h>

class plugins_test : public testing::Test {
 public:
  static std::string senderFunction(std::string id, std::string message) {
    std::cout << id << " " << message << std::endl;
    return "";
  }
};

TEST_F(plugins_test, printPluginsFolder) {
  boost::filesystem::path p("plugins");
  if (boost::filesystem::is_directory(p)) {
    std::cout << p << " is a directory containing:\n";

    for (auto& entry : boost::make_iterator_range(
             boost::filesystem::directory_iterator(p), {})) {
      std::cout << entry << "\n";
    }
  }
}

TEST_F(plugins_test, printPlugins) {
  boost::filesystem::path p("plugins");
  for (hypha::plugin::HyphaBasePlugin* plugin :
       hypha::plugin::PluginLoader::listPlugins("plugins")) {
    std::cout << plugin->name() << std::endl;
  }
}

TEST_F(plugins_test, espeak) {
  boost::filesystem::path p("plugins");
  for (hypha::plugin::HyphaBasePlugin* plugin :
       hypha::plugin::PluginLoader::listPlugins("plugins")) {
    if (plugin->name() == "espeak") {
      plugin->setup();
    }
  }
}

TEST_F(plugins_test, pythonplugin) {
  boost::filesystem::path p("plugins");
  for (hypha::plugin::HyphaBasePlugin* plugin :
       hypha::plugin::PluginLoader::listPlugins("plugins")) {
    if (plugin->name() == "pythonplugin") {
      // plugin->setup();
    }
  }
}

TEST_F(plugins_test, javascriptplugin) {
  boost::filesystem::path p("plugins");
  for (hypha::plugin::HyphaBasePlugin* plugin :
       hypha::plugin::PluginLoader::listPlugins("plugins")) {
    if (plugin->name() == "javascriptplugin") {
      plugin->setup();
      plugin->doWork();
      hypha::utils::Logger::info(plugin->communicate("{ \"tell\":\"hello world!\" }"));
    }
  }
}

TEST_F(plugins_test, setSenderFunction) {
  boost::filesystem::path p("plugins");
  for (hypha::plugin::HyphaBasePlugin* plugin :
       hypha::plugin::PluginLoader::listPlugins("plugins")) {
    if (plugin->name() == "helloworld") {
      ((hypha::plugin::HyphaSender*)plugin)
          ->setCallMessageFunction(plugins_test::senderFunction);
      //((hypha::plugin::HyphaSender *)plugin)->sendMessage("the message");
      ((hypha::plugin::HyphaSender*)plugin)->callMessage("id", "blalba");
    }
  }
}

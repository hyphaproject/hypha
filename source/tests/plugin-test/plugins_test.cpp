// Copyright (c) 2017 Hypha

#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>

#include <gmock/gmock.h>

#include <hypha/plugin/pluginloader.h>
#include <hypha/plugin/pluginutil.h>

class plugins_test : public testing::Test {
 public:
};

TEST_F(plugins_test, printPluginsFolder) {
  boost::filesystem::path p("plugins");
  if (boost::filesystem::is_directory(p)) {
    std::cout << p << " is a directory containing:\n";

    for (auto& entry : boost::make_iterator_range(
             boost::filesystem::directory_iterator(p), {})) {
      // std::cout << entry << "\n";
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

// Copyright (c) 2017 Hypha

#include <gmock/gmock.h>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <iostream>

class plugins_test : public testing::Test {
 public:
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

TEST_F(plugins_test, helloWorldReceive) {}

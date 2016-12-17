// Copyright (c) 2016 Hypha

#include <gmock/gmock.h>
#include <hypha/core/exceptions/configfilenotfound.h>
#include <hypha/core/settings/hyphasettings.h>

class settings_test : public testing::Test {
 public:
};

TEST_F(settings_test, CheckHyphaSettings) {
  bool exception_thrown = false;
  try {
    hypha::settings::HyphaSettings::loadInstance(
        "not_existing_config_file.xml");
  } catch (hypha::exceptions::ConfigFileNotFound &e) {
    e.what();
    exception_thrown = true;
  }
  ASSERT_TRUE(exception_thrown);
}

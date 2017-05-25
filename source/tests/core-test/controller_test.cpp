// Copyright (c) 2016-2017 Hypha

#include <hypha/controller/connection.h>
#include <hypha/controller/plugin.h>

#include <hypha/core/database/database.h>
#include <hypha/core/database/databasegenerator.h>
#include <hypha/core/database/userdatabase.h>
#include <hypha/core/exceptions/configfilenotfound.h>
#include <hypha/core/settings/configgenerator.h>
#include <hypha/core/settings/databasesettings.h>
#include <hypha/core/settings/hyphasettings.h>
#include <hypha/core/settings/pluginsettings.h>

#include <gmock/gmock.h>
#include <boost/filesystem.hpp>

class controller_test : public testing::Test {
 public:
};

TEST_F(controller_test, PluginTest) {
  try {
    std::string configFile = "controller_test_config.xml";

    hypha::settings::HyphaSettings hs(configFile);
    hs.load(true);

    hypha::settings::DatabaseSettings dbs(&hs);
    hypha::database::Database db(&dbs);
    db.connect();

    hypha::database::DatabaseGenerator dbg;
    try {
      dbg.generateExampleDatabase(&dbs);
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }

    hypha::settings::PluginSettings ps(&db);
    int pluginsCount = ps.getAllPluginIds().size();
    ASSERT_TRUE(pluginsCount > 0);

    ASSERT_TRUE(boost::filesystem::exists(configFile));

    hypha::controller::Plugin pluginController(&db);
    pluginController.add("testespeak", "deactivated", "espeak", "{}");
    ASSERT_TRUE(pluginsCount < ps.getAllPluginIds().size());
    pluginController.remove("testespeak");
    ASSERT_TRUE(pluginsCount == ps.getAllPluginIds().size());

  } catch (...) {
  }
}

TEST_F(controller_test, ConnectionTest) {
  try {
    std::string configFile = "controller_test_config.xml";

    hypha::settings::HyphaSettings hs(configFile);
    hs.load(true);

    hypha::settings::DatabaseSettings dbs(&hs);
    hypha::database::Database db(&dbs);
    db.connect();

    hypha::database::DatabaseGenerator dbg;
    try {
      dbg.generateExampleDatabase(&dbs);
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }

    hypha::settings::PluginSettings ps(&db);
    int pluginsCount = ps.getAllPluginIds().size();
    ASSERT_TRUE(pluginsCount > 0);

    ASSERT_TRUE(boost::filesystem::exists(configFile));

    hypha::controller::Connection connectionController(&db);

    int connectionsCount = connectionController.getConnections().size();
    connectionController.create("helloworld", "espeak");
    ASSERT_TRUE(connectionsCount <
                connectionController.getConnections().size());

    for (auto row : connectionController.getConnections()) {
      if (std::get<1>(row) == "helloworld" && std::get<2>(row) == "espeak") {
        connectionController.remove(std::get<0>(row));
        break;
      }
    }
    ASSERT_TRUE(connectionsCount ==
                connectionController.getConnections().size());

    hypha::controller::Plugin pluginController(&db);
    pluginController.add("testespeak", "deactivated", "espeak", "{}");

    connectionsCount = connectionController.getConnections().size();
    connectionController.create("helloworld", "testespeak");

    connectionController.removeConnections("testespeak");
    for (auto row : connectionController.getConnections()) {
      ASSERT_FALSE(std::get<2>(row) == "testespeak");
    }

    pluginController.remove("testespeak");

  } catch (...) {
  }
}

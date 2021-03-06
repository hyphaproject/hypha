// Copyright (c) 2016-2017 Hypha

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

class database_test : public testing::Test {
 public:
};

TEST_F(database_test, CheckHyphaDatabase) {
  try {
    std::string configFile = "database_test_config.xml";

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
    ASSERT_TRUE(ps.getAllPluginIds().size() > 0);

    ASSERT_TRUE(boost::filesystem::exists(configFile));
  } catch (...) {
  }
}

TEST_F(database_test, CheckHyphaUserDatabase) {
  try {
    std::string configFile = "database_test_config.xml";

    hypha::settings::HyphaSettings hs(configFile);
    hs.load(true);

    hypha::settings::DatabaseSettings dbs(&hs);
    hypha::database::Database db(&dbs);
    db.connect();

    hypha::settings::UserDatabaseSettings udbs(&hs);
    hypha::database::UserDatabase *udb =
        hypha::database::UserDatabase::factoreInstance(&udbs);
    udb->connect();

    hypha::database::DatabaseGenerator dbg;
    try {
      dbg.generateExampleUserDatabase(&udbs);
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
    }

    hypha::settings::PluginSettings ps(&db);
    ASSERT_TRUE(ps.getAllPluginIds().size() > 0);

    ASSERT_TRUE(boost::filesystem::exists(configFile));

    delete udb;
  } catch (...) {
  }
}

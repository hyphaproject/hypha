// Copyright (c) 2016 Hypha

#include <hypha/core/database/database.h>
#include <hypha/core/database/userdatabase.h>
#include <hypha/core/database/databasegenerator.h>
#include <hypha/core/exceptions/configfilenotfound.h>
#include <hypha/core/settings/configgenerator.h>
#include <hypha/core/settings/databasesettings.h>
#include <hypha/core/settings/handlersettings.h>
#include <hypha/core/settings/hyphasettings.h>
#include <hypha/core/settings/pluginsettings.h>

#include <gmock/gmock.h>
#include <boost/filesystem.hpp>

class database_test : public testing::Test {
 public:
};

TEST_F(database_test, CheckHyphaDatabase) {
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

  hypha::settings::HandlerSettings has(&db);
  ASSERT_TRUE(has.getAllHandlerIds().size() > 0);

  ASSERT_TRUE(boost::filesystem::exists(configFile));
}

TEST_F(database_test, CheckHyphaUserDatabase) {
  std::string configFile = "database_test_config.xml";

  hypha::settings::HyphaSettings hs(configFile);
  hs.load(true);

  hypha::settings::DatabaseSettings dbs(&hs);
  hypha::database::Database db(&dbs);
  db.connect();

  hypha::settings::UserDatabaseSettings udbs(&hs);
  hypha::database::UserDatabase* udb = hypha::database::UserDatabase::factoreInstance(&udbs);
  udb->connect();

  hypha::database::DatabaseGenerator dbg;
  try {
    dbg.generateExampleDatabase(&dbs);
    dbg.generateExampleUserDatabase(&udbs);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  hypha::settings::PluginSettings ps(&db);
  ASSERT_TRUE(ps.getAllPluginIds().size() > 0);

  hypha::settings::HandlerSettings has(&db);
  ASSERT_TRUE(has.getAllHandlerIds().size() > 0);

  ASSERT_TRUE(boost::filesystem::exists(configFile));

  //ASSERT_TRUE(udb->getUsers().size() > 0);

  delete udb;
}

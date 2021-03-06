// Copyright (c) 2015-2016 Hypha
#include <hypha/core/database/userdbsql.h>
#include <mutex>
#ifdef WITH_LDAP
#include <hypha/core/database/ldap/userdbldap.h>
#endif
#include <hypha/core/database/userdatabase.h>

using namespace hypha::settings;
using namespace hypha::database;

UserDatabase *UserDatabase::singleton = 0;

UserDatabase::UserDatabase(UserDatabaseSettings *settings) {
  this->settings = settings;
}

UserDatabase::~UserDatabase() {}

UserDatabase *UserDatabase::factoreInstance(UserDatabaseSettings *settings) {
  UserDatabase *database = nullptr;
  if (settings->getDriver() == "LDAP") {
    //#ifdef WITH_LDAP
    //                database = new UserDBLDAP(settings);
    //#else
    throw "LDAP not supported";
    //#endif
  } else {
    database = new hypha::database::UserDBSql(settings);
  }
  database->connect();
  return database;
}

UserDatabase *UserDatabase::instance() {
  static std::mutex mutex;
  if (!singleton) {
    mutex.lock();

    if (!singleton) {
      singleton =
          factoreInstance(hypha::settings::UserDatabaseSettings::instance());
    }

    mutex.unlock();
  }
  return singleton;
}

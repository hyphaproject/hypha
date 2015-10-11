#include <mutex>
#include "hypha/database/userdbsql.h"
#ifdef WITH_LDAP
#include "hypha/userdbldap.h"
#endif
#include "hypha/database/userdatabase.h"

using namespace hypha::settings;
using namespace hypha::database;

UserDatabase *UserDatabase::singleton = 0;

UserDatabase::UserDatabase(UserDatabaseSettings *settings) {
    this->settings = settings;
}

UserDatabase::~UserDatabase() {
}

UserDatabase *UserDatabase::instance() {
    static std::mutex mutex;
    if (!singleton) {
        mutex.lock();

        if (!singleton) {
            if(UserDatabaseSettings::instance()->getDriver() == "LDAP") {
//#ifdef WITH_LDAP
//                singleton = new UserDBLDAP(UserDatabaseSettings::instance());
//                singleton->connect();
//#else
                throw "LDAP not supported";
//#endif
            } else {
                singleton = new UserDBSql(UserDatabaseSettings::instance());
                singleton->connect();
            }
        }

        mutex.unlock();
    }
    return singleton;
}


#include <mutex>
#include "hypha/settings/hyphasettings.h"
#include "hypha/settings/userdatabasesettings.h"

using namespace hypha::settings;

UserDatabaseSettings *UserDatabaseSettings::singleton = 0;

UserDatabaseSettings::UserDatabaseSettings() {
}

UserDatabaseSettings::~UserDatabaseSettings() {

}

UserDatabaseSettings *UserDatabaseSettings::instance() {
    static std::mutex mutex;
    if (!singleton) {
        mutex.lock();

        if (!singleton)
            singleton = new UserDatabaseSettings();
        mutex.unlock();
    }

    return singleton;
}

void UserDatabaseSettings::save() {
    HyphaSettings::instance()->save();
}

std::string UserDatabaseSettings::getString(const std::string &key, const std::string &defaultValue) {
    return HyphaSettings::instance()->getString("userdatabase." + key, defaultValue);
}

int UserDatabaseSettings::getInt(const std::string &key, const int &defaultValue) {
    return HyphaSettings::instance()->getInt("userdatabase." + key, defaultValue);
}

std::string UserDatabaseSettings::getDriver() {
    return getString("driver", "LDAP");
}

std::string UserDatabaseSettings::getHost() {
    return getString("host", "localhost");
}

std::string UserDatabaseSettings::getDatabase() {
    return getString("database", "dc=blechuhr");
}

std::string UserDatabaseSettings::getUser() {
    return getString("username", "cn=admin");
}

std::string UserDatabaseSettings::getPassword() {
    return getString("password", "password");
}

std::string UserDatabaseSettings::getTable() {
    return getString("table", "ou=people");
}

std::string UserDatabaseSettings::getAttributeUsername() {
    return getString("attrUsername", "cn");
}

std::string UserDatabaseSettings::getAttributeFirstname() {
    return getString("attrFirstname", "givenname");
}

std::string UserDatabaseSettings::getAttributeLastname() {
    return getString("attrLastname", "sn");
}

std::string UserDatabaseSettings::getAttributeMail() {
    return getString("attrMail", "mail");
}

std::string UserDatabaseSettings::getAttributeDevices() {
    return getString("attrDevices", "registeredaddress");
}

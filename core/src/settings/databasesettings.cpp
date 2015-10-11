#include <mutex>
#include "hypha/settings/hyphasettings.h"
#include "hypha/settings/databasesettings.h"

using namespace hypha::settings;

DatabaseSettings *DatabaseSettings::singleton = 0;

DatabaseSettings::DatabaseSettings() {
}

DatabaseSettings::~DatabaseSettings() {

}

DatabaseSettings *DatabaseSettings::instance() {
    static std::mutex mutex;
    if (!singleton) {
        mutex.lock();
        if (!singleton)
            singleton = new DatabaseSettings();
        mutex.unlock();
    }

    return singleton;
}

void DatabaseSettings::save() {
    HyphaSettings::instance()->save();
}

std::string DatabaseSettings::getString(const std::string &key, const std::string &defaultValue) {
    return HyphaSettings::instance()->getString("database." + key, defaultValue);
}

int DatabaseSettings::getInt(const std::string &key, const int &defaultValue) {
    return HyphaSettings::instance()->getInt("database." + key, defaultValue);
}

std::string DatabaseSettings::getDriver() {
    return getString("driver", "QSQLITE");
}

std::string DatabaseSettings::getHost() {
    return getString("host", "localhost");
}

std::string DatabaseSettings::getDatabase() {
    return getString("database", ":memory:");
}

std::string DatabaseSettings::getUser() {
    return getString("username", "hypha");
}

std::string DatabaseSettings::getPassword() {
    return getString("password", "hypha");
}

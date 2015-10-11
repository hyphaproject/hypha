#include <boost/filesystem.hpp>
#include <mutex>
#include "hypha/settings/hyphasettings.h"

using Poco::AutoPtr;
using Poco::Util::IniFileConfiguration;
using namespace hypha::settings;

HyphaSettings *HyphaSettings::singleton = 0;

HyphaSettings::HyphaSettings(std::string configfile) {
    this->configfile = configfile;
}

HyphaSettings::~HyphaSettings() {

}

HyphaSettings *HyphaSettings::instance() {
    if (!singleton) {
        return loadInstance("hypha.ini");
    }

    return singleton;
}

HyphaSettings *HyphaSettings::loadInstance(std::string configFile) {
    static std::mutex mutex;
    mutex.lock();
    singleton = new HyphaSettings(configFile);
    singleton->load();
    mutex.unlock();
    return singleton;
}

void HyphaSettings::createNewFile() {
    /*
    settings = new QSettings(QString::fromStdString(configfile), QSettings::IniFormat );
    settings->beginGroup("database");
    settings->setValue("driver", "QSQLITE");
    settings->setValue("host", "localhost");
    settings->setValue("database", ":memory:");
    settings->setValue("username", "user");
    settings->setValue("password", "password");
    settings->endGroup();
    settings->beginGroup("userdatabase");
    settings->setValue("driver", "LDAP");
    settings->setValue("host", "localhost");
    settings->setValue("database", "dc=blechuhr");
    settings->setValue("username", "cn=admin");
    settings->setValue("password", "password");
    settings->setValue("table", "ou=people");
    settings->setValue("attrUsername", "cn");
    settings->setValue("attrFirstname", "givenname");
    settings->setValue("attrLastname", "sn");
    settings->setValue("attrMail", "mail");
    settings->setValue("attrDevices", "registeredaddress");
    settings->endGroup();
    save();
    */
}

void HyphaSettings::load() {

    if(boost::filesystem::exists( configfile )) {
        settings = AutoPtr<IniFileConfiguration>(new IniFileConfiguration(configfile));
    } else {
        createNewFile();
    }
}

void HyphaSettings::save() {
    //settings->sync();
}

std::string HyphaSettings::getString(const std::string &key, const std::string &defaultValue) {
    return settings->getString(key, defaultValue);
}

int HyphaSettings::getInt(const std::string &key, const int &defaultValue) {
    return settings->getInt(key, defaultValue);
}

void HyphaSettings::setString(const std::string &key, std::string &value) {

}

void HyphaSettings::setInt(const std::string &key, std::string &value) {

}

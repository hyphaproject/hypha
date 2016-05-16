#include <boost/filesystem.hpp>
#include <mutex>
#include <hypha/core/settings/hyphasettings.h>

using Poco::AutoPtr;
using Poco::Util::XMLConfiguration;
using namespace hypha::settings;

HyphaSettings *HyphaSettings::singleton = 0;

HyphaSettings::HyphaSettings(std::string configfile) {
    this->configfile = configfile;
}

HyphaSettings::~HyphaSettings() {

}

HyphaSettings *HyphaSettings::instance() {
    if (!singleton) {
        return loadInstance("hypha.xml");
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
}

void HyphaSettings::load() {

    if (boost::filesystem::exists( configfile )) {
        settings = AutoPtr<XMLConfiguration>(new XMLConfiguration(configfile));

    } else {
        createNewFile();
    }
}

void HyphaSettings::save() {
    settings->save(configfile);
}

std::string HyphaSettings::getString(const std::string &key, const std::string &defaultValue) {
    return settings->getString(key, defaultValue);
}

int HyphaSettings::getInt(const std::string &key, const int &defaultValue) {
    return settings->getInt(key, defaultValue);
}

void HyphaSettings::setString(const std::string &key, std::string &value) {
    settings->setString(key, value);
}

void HyphaSettings::setInt(const std::string &key, std::string &value) {
    settings->setString(key, value);
}

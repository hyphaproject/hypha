#ifndef HYPHASETTINGS_H
#define HYPHASETTINGS_H

#include "../core.h"

#include <string>
#include <Poco/AutoPtr.h>
#include <Poco/Util/IniFileConfiguration.h>

namespace hypha {
namespace settings {

class Core_API HyphaSettings {
  public:
    static HyphaSettings * instance();
    static HyphaSettings *loadInstance(std::string configFile);

    HyphaSettings(std::string configfile);

    void createNewFile();
    void load();
    void save();

    std::string getString(const std::string &key, const std::string &defaultValue);
    int getInt(const std::string &key, const int &defaultValue);

    void setString(const std::string &key, std::string &value);
    void setInt(const std::string &key, std::string &value);

  private:
    ~HyphaSettings();

    Poco::AutoPtr<Poco::Util::IniFileConfiguration> settings;

    std::string configfile;

    static HyphaSettings *singleton;

};
}
}

#endif // HYPHASETTINGS_H

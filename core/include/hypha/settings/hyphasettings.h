#ifndef HYPHASETTINGS_H
#define HYPHASETTINGS_H

#include <string>
#include <Poco/AutoPtr.h>
#include <Poco/Util/IniFileConfiguration.h>
#include <Poco/Util/XMLConfiguration.h>
#include "../core.h"

namespace hypha {
namespace settings {

/** HyphaSettings gives access to the config xml file.
 * The Class must given the path to the config file.
 * Then there could be read values from it or set values.
 * If no config file exists a new one can be created.
 */
class Core_API HyphaSettings {
  public:

    static HyphaSettings *instance();
    static HyphaSettings *loadInstance(std::string configFile);

    explicit HyphaSettings(std::string configfile);
    ~HyphaSettings();

    void createNewFile();
    void load();
    void save();

    std::string getString(const std::string &key, const std::string &defaultValue);
    int getInt(const std::string &key, const int &defaultValue);

    void setString(const std::string &key, std::string &value);
    void setInt(const std::string &key, std::string &value);

  protected:
    Poco::AutoPtr<Poco::Util::XMLConfiguration> settings;

    std::string configfile;

    static HyphaSettings *singleton;

};
}
}

#endif // HYPHASETTINGS_H

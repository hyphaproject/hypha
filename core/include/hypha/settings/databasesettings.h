#ifndef DATABASESETTINGS_H
#define DATABASESETTINGS_H

#include <string>
#include "hypha/settings/hyphasettings.h"
#include "../core.h"

namespace hypha {
namespace settings {

/** UserDatabaseSettings gives information which Database should be used.
 * Information about the Database contain driver, host, accessing user and password
 * and also the 'Database'.
 */
class Core_API DatabaseSettings {
  public:
    static DatabaseSettings *instance();
    DatabaseSettings(hypha::settings::HyphaSettings *hyphaSettings);
    ~DatabaseSettings();

    void save();
    std::string getString(const std::string &key, const std::string &defaultValue);
    int getInt(const std::string &key, const int &defaultValue);

    std::string getDriver();
    std::string getHost();
    std::string getDatabase();
    std::string getUser();
    std::string getPassword();

  protected:
    static DatabaseSettings *singleton;

    hypha::settings::HyphaSettings *hyphaSettings;

};
}
}

#endif // DATABASESETTINGS_H

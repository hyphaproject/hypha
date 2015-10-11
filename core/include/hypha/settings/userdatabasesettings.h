#ifndef USERDATABASESETTINGS_H
#define USERDATABASESETTINGS_H

#include "../core.h"
#include <string>

namespace hypha {
namespace settings {
class Core_API UserDatabaseSettings {
  public:
    static UserDatabaseSettings * instance();
    void save();
    std::string getString(const std::string &key, const std::string &defaultValue);
    int getInt(const std::string &key, const int &defaultValue);

    std::string getDriver();
    std::string getHost();
    std::string getDatabase();
    std::string getUser();
    std::string getPassword();
    std::string getTable();
    std::string getAttributeUsername();
    std::string getAttributeFirstname();
    std::string getAttributeLastname();
    std::string getAttributeMail();
    std::string getAttributeDevices();

  private:
    UserDatabaseSettings();
    ~UserDatabaseSettings();

    static UserDatabaseSettings *singleton;
};
}
}

#endif // USERDATABASESETTINGS_H

#ifndef DATABASESETTINGS_H
#define DATABASESETTINGS_H
#include "../core.h"
#include <string>
namespace hypha {
namespace settings {
class Core_API DatabaseSettings {
  public:
    static DatabaseSettings * instance();
    void save();
    std::string getString(const std::string &key, const std::string &defaultValue);
    int getInt(const std::string &key, const int &defaultValue);

    std::string getDriver();
    std::string getHost();
    std::string getDatabase();
    std::string getUser();
    std::string getPassword();

  private:
    DatabaseSettings();
    ~DatabaseSettings();

    static DatabaseSettings *singleton;

};
}
}

#endif // DATABASESETTINGS_H

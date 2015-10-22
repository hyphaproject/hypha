#ifndef USERDATABASE_H
#define USERDATABASE_H

#include "../core.h"
#include <list>
#include "hypha/settings/userdatabasesettings.h"

namespace hypha {
namespace database {
class Core_API UserDatabase {
  public:
    explicit UserDatabase(hypha::settings::UserDatabaseSettings *settings);
    ~UserDatabase();
    static UserDatabase * factoreInstance(hypha::settings::UserDatabaseSettings *settings);
    static UserDatabase * instance();
    virtual bool connect() = 0;
    virtual std::list<std::string> getUsers() = 0;
    virtual std::string getFirstname(std::string username) = 0;
    virtual std::string getLastname(std::string username) = 0;
    virtual std::string getMail(std::string username) = 0;
    virtual std::list<std::string> getDevices(std::string username) = 0;
    virtual std::string getOwnerOfDevice(std::string device) = 0;

  protected:
    static UserDatabase *singleton;
    hypha::settings::UserDatabaseSettings *settings;
};
}
}

#endif // USERDATABASE_H

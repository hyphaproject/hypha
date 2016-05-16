#ifndef USERDBLDAP_H
#define USERDBLDAP_H
#ifdef WITH_LDAP
#include "../core.h"
#include <ldap.h>
#include <string>
#include <list>

#include "../userdatabase.h"
namespace hypha {
namespace database {
class Core_API UserDBLDAP : public UserDatabase {
  public:
    UserDBLDAP(hypha::settings::UserDatabaseSettings *settings);
    ~UserDBLDAP();
    bool connect();
    std::list<std::string> getUsers();
    std::string getFirstname(std::string username);
    std::string getLastname(std::string username);
    std::string getMail(std::string username);
    std::list<std::string> getDevices(std::string username);
    std::string getOwnerOfDevice(std::string device);

  protected:
    LDAP *ld;
};
}
}
#endif
#endif // USERDBLDAP_H

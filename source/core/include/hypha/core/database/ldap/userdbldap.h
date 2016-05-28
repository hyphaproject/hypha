// Copyright (c) 2015-2016 Hypha
#pragma once
#ifdef WITH_LDAP

#include <string>
#include <list>

#include <ldap.h>

#include <hypha/core/core_api.h>
#include <hypha/core/settings//userdatabase.h>

namespace hypha {
namespace database {
class CORE_API UserDBLDAP : public UserDatabase {
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


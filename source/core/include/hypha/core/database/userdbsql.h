// Copyright (c) 2015-2016 Hypha
#pragma once

#include <Poco/Data/SessionPool.h>
#include <Poco/Data/Statement.h>

#include <hypha/core/core_api.h>
#include <hypha/core/database/userdatabase.h>

namespace hypha {
namespace database {
class CORE_API UserDBSql : public UserDatabase {
 public:
  UserDBSql(hypha::settings::UserDatabaseSettings *settings);
  ~UserDBSql();
  static UserDBSql *instance();
  Poco::Data::Statement getStatement();

  bool connect();
  bool reconnect();
  std::list<std::string> getUsers();
  std::string getFirstname(std::string username);
  std::string getLastname(std::string username);
  std::string getMail(std::string username);
  std::list<std::string> getDevices(std::string username);
  std::string getOwnerOfDevice(std::string device);
  bool createUser(std::string username, std::string firstname,
                  std::string lastname, std::string mail);
  bool updateUser(std::string username, std::string firstname,
                  std::string lastname, std::string mail, std::string devices);

  void createTables();

 protected:
  Poco::Data::SessionPool *pool = nullptr;
  std::string host;
};
}
}

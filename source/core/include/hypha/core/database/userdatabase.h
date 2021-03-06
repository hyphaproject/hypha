// Copyright (c) 2015-2017 Hypha
#pragma once

#include <hypha/core/core_api.h>
#include <hypha/core/settings/userdatabasesettings.h>

#include <list>

namespace hypha {
namespace database {
class CORE_API UserDatabase {
 public:
  explicit UserDatabase(hypha::settings::UserDatabaseSettings *settings);
  virtual ~UserDatabase();
  static UserDatabase *factoreInstance(
      hypha::settings::UserDatabaseSettings *settings);
  static UserDatabase *instance();
  virtual bool connect() = 0;
  virtual std::list<std::string> getUsers() = 0;
  virtual std::string getFirstname(std::string username) = 0;
  virtual std::string getLastname(std::string username) = 0;
  virtual std::string getMail(std::string username) = 0;
  virtual std::list<std::string> getDevices(std::string username) = 0;
  virtual std::string getOwnerOfDevice(std::string device) = 0;
  virtual bool createUser(std::string username, std::string firstname,
                          std::string lastname, std::string mail) = 0;
  virtual bool updateUser(std::string username, std::string firstname,
                          std::string lastname, std::string mail,
                          std::string devices) = 0;

 protected:
  static UserDatabase *singleton;
  hypha::settings::UserDatabaseSettings *settings;
};
}
}

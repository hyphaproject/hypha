// Copyright (c) 2015-2016 Hypha
#pragma once

#include <hypha/core/core_api.h>
#include <hypha/core/settings/hyphasettings.h>
#include <string>

namespace hypha {
namespace settings {

/** UserDatabaseSettings gives information which Database should be used for
 * Users.
 */
class CORE_API UserDatabaseSettings {
 public:
  static UserDatabaseSettings *instance();
  UserDatabaseSettings(hypha::settings::HyphaSettings *hyphaSettings);
  ~UserDatabaseSettings();
  void save();
  std::string getString(const std::string &key,
                        const std::string &defaultValue);
  int getInt(const std::string &key, const int &defaultValue);

  std::string getDriver();
  std::string getHost();
  int getPort();
  std::string getDatabase();
  std::string getUser();
  std::string getPassword();
  std::string getTable();
  std::string getAttributeUsername();
  std::string getAttributeFirstname();
  std::string getAttributeLastname();
  std::string getAttributeMail();
  std::string getAttributeDevices();

 protected:
  hypha::settings::HyphaSettings *hyphaSettings;
  static UserDatabaseSettings *singleton;
};
}
}

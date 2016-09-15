// Copyright (c) 2015-2016 Hypha
#pragma once

#include <hypha/core/core_api.h>
#include <hypha/core/settings/hyphasettings.h>
#include <string>

namespace hypha {
namespace settings {

/** UserDatabaseSettings gives information which Database should be used.
 * Information about the Database contain driver, host, accessing user and
 * password
 * and also the 'Database'.
 */
class CORE_API DatabaseSettings {
 public:
  static DatabaseSettings *instance();
  DatabaseSettings(hypha::settings::HyphaSettings *hyphaSettings);
  ~DatabaseSettings();

  void save();
  std::string getString(const std::string &key,
                        const std::string &defaultValue);
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

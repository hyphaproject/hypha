#ifndef DATABASESETTINGS_H
#define DATABASESETTINGS_H

#include <string>
#include "hypha/settings/hyphasettings.h"
#include "../core.h"

namespace hypha {
namespace settings {
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

 private:
  static DatabaseSettings *singleton;

  hypha::settings::HyphaSettings *hyphaSettings;

};
}
}

#endif // DATABASESETTINGS_H

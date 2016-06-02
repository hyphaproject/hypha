#pragma once

#include <hypha/core/core_api.h>
#include <string>

namespace hypha {
namespace settings {
class DatabaseSettings;
class UserDatabaseSettings;
}
namespace database {

class CORE_API DatabaseGenerator {
 public:
  DatabaseGenerator();

  void generateExampleDatabase(hypha::settings::DatabaseSettings *settings);
  void generateExampleUserDatabase(
      hypha::settings::UserDatabaseSettings *settings);
};
}  // namespace database
}  // namespace hypha

#pragma once

#include <hypha/core/core_api.h>
#include <string>

namespace hypha {
namespace settings {

class CORE_API ConfigGenerator {
 public:
  ConfigGenerator();

  // Database
  std::string dbDatabase = "hypha";
  std::string dbDriver = "SQLite";
  std::string dbHost = "localhost";
  std::string dbPassword = "password";
  std::string dbUsername = "hypha";

  // User Database
  std::string udbAttributeDevices = "deviceids";
  std::string udbAttributeFirstname = "firstname";
  std::string udbAttributeLastname = "lastname";
  std::string udbAttributeMail = "mail";
  std::string udbAttributeUsername = "username";
  std::string udbDatabase = "hypha";
  std::string udbDriver = "SQLite";
  std::string udbHost = "localhost";
  std::string udbPassword = "password";
  std::string udbTable = "user";
  std::string udbUsername = "hypha";

  void generateConfigFile(std::string filename);
};
}  // namespace settings
}  // namespace hypha
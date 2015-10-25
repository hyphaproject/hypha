#ifndef LOGGER_H
#define LOGGER_H

#include "../utils.h"
#include <string>
namespace hypha {
namespace utils {

class Utils_API Logger {
 public:
  static Logger *instance();
  static void info(std::string message);
  static void warning(std::string message);
  static void error(std::string message);
  static void fatal(std::string message);
 private:
  Logger();
  ~Logger();

 protected:
  static Logger *singleton;
  void init();
};
}
}

#endif // LOGGER_H

// Copyright (c) 2015-2016 Hypha
#pragma once

#include <string>
#include <hypha/utils/utils_api.h>

namespace hypha {
namespace utils {
/** Logger Singleton Class.
 * The Logger is implemented as singleton and supports
 * info, warning, error and fatal.
 */
class UTILS_API Logger {
  public:
    /** Singleton Instance for the Logger.
     * The Logger is used as a singleton so it is easy to just
     * Log with Logger::warning("").
     */
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

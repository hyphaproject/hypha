// Copyright (c) 2015-2016 Hypha
#pragma once

#include <chrono>
#include <functional>
#include <string>
#include <thread>

#ifdef __linux__
#include <sys/prctl.h>
#endif

#include <Poco/Runnable.h>
#include <Poco/Thread.h>
#include <hypha/plugin/plugin_api.h>
#include <boost/signals2.hpp>

#ifdef UNUSED
#elif defined(__GNUC__)
#define UNUSED(x) UNUSED_##x __attribute__((unused))
#elif defined(__LCLINT__)
#define UNUSED(x) /*@unused@*/ x
#else
#define UNUSED(x) x
#endif

namespace hypha {
namespace plugin {

/**
 * @brief The HyphaBasePlugin class
 *      Base Plugin for all handler and plugins.
 *      Will run as its own thread.
 */
class PLUGIN_API HyphaBasePlugin : public Poco::Runnable {
 public:
  virtual ~HyphaBasePlugin() {}

  void run() {
#ifdef __linux__
    const char *name = id.substr(0, 16).c_str();
    prctl(PR_SET_NAME, (unsigned long)name, 0, 0, 0);
#endif
    while (running) {
      doWork();
    }
  }

  virtual void doWork() = 0;
  virtual const std::string name() = 0;
  virtual const std::string getTitle() = 0;
  virtual const std::string getVersion() = 0;
  virtual const std::string getDescription() = 0;
  virtual std::string getStatusMessage() { return ""; }
  virtual HyphaBasePlugin *getInstance(std::string id) = 0;

  /**
   * @brief getConfigDescription
   *        Get used Datatype description for the plugin in ConfDesc readable
   * json format.
   *
   * You can find description for the
   * [ConfDesc](https://github.com/falsecam/confdesc).
   *
   * @return ConfDesc json string
   */
  virtual const std::string getConfigDescription() = 0;

  /**
   * @brief loadConfig
   *
   * @param json
   *        Configuration for this plugin from database in json format.
   */
  virtual void loadConfig(std::string json) = 0;

  /**
   * @brief getConfig
   *    Get configuration for this plugin to store it in database, for example.
   *
   * @return current configuration in json format
   */
  virtual std::string getConfig() = 0;
  std::string getId() { return id; }
  void setId(std::string id) { this->id = id; }
  std::string getHost() { return host; }
  void setHost(std::string host) { this->host = host; }

  virtual std::string communicate(std::string message) = 0;

  void start() {
    running = true;
    thread.setName(id);
    thread.start(*this);
  }

  void stop() { running = false; }

 protected:
  /**
   * @brief id
   *    Unique id for the plugin.
   */
  std::string id;
  /**
   * @brief host
   *    The host where the plugin will run on.
   */
  std::string host;

  bool running = true;
  Poco::Thread thread;
};
}
}

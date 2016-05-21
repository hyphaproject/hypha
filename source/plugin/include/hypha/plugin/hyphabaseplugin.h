#ifndef HYPHABASEPLUGIN_H
#define HYPHABASEPLUGIN_H

#include <Poco/Runnable.h>
#include <Poco/Thread.h>
#include <boost/signals2.hpp>
#include <chrono>
#include <functional>
#include <string>
#include <thread>

#ifdef __linux__
#include <sys/prctl.h>
#endif
#include <hypha/plugin/plugin_api.h>

namespace hypha {
namespace plugin {

class PLUGIN_API HyphaBasePlugin : public Poco::Runnable {
 public:
  typedef boost::signals2::signal<void(std::string)> SendMessage;
  typedef SendMessage::slot_type SendMessageSlotType;

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
  virtual void loadConfig(std::string json) = 0;
  virtual std::string getConfig() = 0;
  std::string getId() { return id; }
  void setId(std::string id) { this->id = id; }
  std::string getHost() { return host; }
  void setHost(std::string host) { this->host = host; }
  void setCallMessageFunction(
      std::function<std::string(std::string, std::string)> f) {
    callMessageFunction = f;
  }
  boost::signals2::connection connect(const SendMessageSlotType &slot) {
    return sendMessage.connect(slot);
  }

  virtual void receiveMessage(std::string message) = 0;
  virtual std::string communicate(std::string message) = 0;
  std::string callMessage(std::string id, std::string message) {
    return callMessageFunction(id, message);
  }

  void start() {
    running = true;
    thread.setName(id);
    thread.start(*this);
  }

  void stop() { running = false; }

 protected:
  std::string id;
  std::string host;
  SendMessage sendMessage;
  bool running = true;
  Poco::Thread thread;
  std::function<std::string(std::string, std::string)> callMessageFunction;
};
}
}

#endif  // HYPHABASEPLUGIN_H

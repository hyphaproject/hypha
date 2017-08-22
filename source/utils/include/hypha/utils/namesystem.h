// Copyright (c) 2017 Hypha
#pragma once

#include <hypha/utils/utils_api.h>
#include <map>
#include <string>

#include <Poco/Runnable.h>
#include <Poco/Thread.h>

namespace hypha {
namespace utils {

/**
 * @brief The NameSystem class
 * Runs kadnode in a thread.
 * Provides ip lookup by hostname or public key fron kadnode.
 */
class UTILS_API NameSystem : public Poco::Runnable {
 public:
  NameSystem();

  /**
   * @brief run
   * threads run function, used for kadnode
   */
  void run() override;

  /**
   * @brief start
   * starts namesystem thread
   */
  void start();

  /**
   * @brief stop
   * stops namesystem thread
   */
  void stop();

  /**
   * @brief toIP
   * Looks up hostname or publicKey and returns an ip.
   * @param str
   * @return
   * ip as string
   */
  std::string toIP(std::string str);

  /**
   * @brief hostnameToIP
   * gets ip by hostname
   * @param hostname
   * @return ip address as string
   */
  std::string hostnameToIP(std::string hostname);

  /**
   * @brief publicKeyToIP
   * gets ip by public key from dht
   * @param publicKey
   * @return ip address as string
   */
  std::string publicKeyToIP(std::string publicKey);

 protected:
  // Kadnode kadnode;

  std::map<std::string, std::string> ipCache;

  bool running = false;
  Poco::Thread thread;
};
}
}

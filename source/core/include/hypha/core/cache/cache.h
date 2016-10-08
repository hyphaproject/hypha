// Copyright (c) 2015-2016 Hypha
#pragma once

#include <Poco/Redis/Client.h>
#include <hypha/core/core_api.h>

namespace hypha {
namespace cache {

/**
 * @brief The Cache class
 * Stores key value pairs. In background data are cached with Redis.
 */
class CORE_API Cache {
 public:
  Cache();
  ~Cache();

  /**
   * @brief instance
   * @return the singleton
   */
  static Cache *instance();
  /**
   * @brief connect
   * Connects to the Redis database.
   * @return
   */
  bool connect();
  /**
   * @brief reconnect
   * Disconnects from and reconnects to the Redis database.
   * @return
   */
  bool reconnect();

  /**
   * @brief put
   * @param key
   * @param data
   */
  void put(std::string &key, std::string data);
  /**
   * @brief get
   * @param key
   * @return
   */
  std::string getRaw(std::string &key);

  /**
   * @brief put
   * stores data by newly generated key. Key starts with hostname and ':'
   * followed by UUID.
   * @param data to put
   * @return the generated key
   */
  std::string put(std::string data);
  /**
   * @brief get
   * @param key
   * @return
   */
  std::string get(std::string &key);

  static std::string getHostname(std::string &key);
  static std::string getUUID(std::string &key);

 private:
  std::string host;
  unsigned int port;
  static Cache *singleton;
  Poco::Redis::Client redis;
};
}  // namespace cache
}  // namespace hypha

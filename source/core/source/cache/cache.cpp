// Copyright (c) 2016 Hypha
#include "hypha/core/cache/cache.h"
#include <Poco/Redis/Command.h>
#include <mutex>

using namespace hypha::cache;

Cache *Cache::singleton = 0;

Cache::Cache() : host("localhost"), port(6379) {}

Cache::~Cache() {}

Cache *Cache::instance() {
  static std::mutex mutex;
  if (!singleton) {
    mutex.lock();

    if (!singleton) {
      singleton = new Cache();
      singleton->connect();
    }

    mutex.unlock();
  }
  return singleton;
}

bool Cache::connect() {
  Poco::Timespan t(10, 0);
  redis.connect(host, port, t);
  return true;
}

bool Cache::reconnect() {
  redis.disconnect();
  return connect();
}

void Cache::put(std::string &key, std::string data) {
  Poco::Redis::Command setCommand = Poco::Redis::Command::set(key, data);
  redis.execute<std::string>(setCommand);
}

std::string Cache::get(std::string &key) {
  Poco::Redis::Command getCommand = Poco::Redis::Command::get(key);
  Poco::Redis::BulkString result =
      redis.execute<Poco::Redis::BulkString>(getCommand);
  return result.value();
}

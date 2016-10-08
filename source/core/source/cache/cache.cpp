// Copyright (c) 2016 Hypha

#include "hypha/core/cache/cache.h"
#include "hypha/utils/logger.h"

#include <mutex>

#include <Poco/Net/DNS.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Redis/Command.h>
#include <Poco/StreamCopier.h>
#include <Poco/UUIDGenerator.h>

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

std::string Cache::getRaw(std::string &key) {
  Poco::Redis::Command getCommand = Poco::Redis::Command::get(key);
  Poco::Redis::BulkString result =
      redis.execute<Poco::Redis::BulkString>(getCommand);
  return result.value();
}

std::string Cache::put(std::string data) {
  Poco::UUIDGenerator generator;
  std::string key =
      Poco::Net::DNS::hostName() + ":" + generator.createOne().toString();
  put(key, data);
  return key;
}

std::string Cache::get(std::string &key) {
  std::string hostname = getHostname(key);
  if (hostname == Poco::Net::DNS::hostName()) {
    return getRaw(key);
  } else {
    std::string uuid = getUUID(key);
    try {
      Poco::Net::HTTPClientSession session(hostname, 47965);
      session.setKeepAlive(false);

      Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET,
                                 "/pointer/" + uuid);
      session.sendRequest(req);

      Poco::Net::HTTPResponse response;
      std::istream &rs = session.receiveResponse(response);
      std::string responseStr;
      Poco::StreamCopier::copyToString(rs, responseStr);
      return responseStr;
    } catch (Poco::Exception &e) {
      hypha::utils::Logger::error(e.displayText());
    }
  }
  return "";
}

std::string Cache::getHostname(std::string &key) {
  int pos = key.find(':');
  return key.substr(0, pos);
}

std::string Cache::getUUID(std::string &key) {
  int pos = key.find(':');
  return key.substr(pos + 1, key.size() - pos);
}

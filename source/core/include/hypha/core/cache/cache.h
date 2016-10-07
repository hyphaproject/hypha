// Copyright (c) 2015-2016 Hypha
#pragma once

#include <hypha/core/core_api.h>
#include <Poco/Redis/Client.h>

namespace hypha {
namespace cache {
class CORE_API Cache
{
public:
    Cache();
    ~Cache();
    static Cache *instance();
    bool connect();
    bool reconnect();

    void put(std::string &key, std::string data);
    std::string get(std::string &key);

private:
 std::string host;
 unsigned int port;
 static Cache *singleton;
 Poco::Redis::Client redis;
};
} // namespace cache
} // namespace hypha

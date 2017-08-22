// Copyright (c) 2017 Hypha

#include <hypha/utils/namesystem.h>

#include <Poco/Net/DNS.h>

using namespace hypha::utils;

NameSystem::NameSystem() {
  std::string privateKey = "***********";
  std::string publicKey = "examplehashstring";
  std::string port;
  std::string announce = publicKey + ".hypha:" + port;
  // kadnode_set("announce", publicKey.c_str());
  // kadnode_set("port", 6881);
  // kadnode_set("query-tld", ".hypha");
  // kadnode_set("load-key-string", privateKey.c_str());
  // kadnode_init();
}

void NameSystem::run() {
  while (running) {
    // kadnode_run_loop();
  }
}

void NameSystem::start() {
  running = true;
  thread.setName("namesystem");
  thread.start(*this);
}

void NameSystem::stop() { running = false; }

std::string NameSystem::toIP(std::string str)
{
    return hostnameToIP(str);
}

std::string NameSystem::hostnameToIP(std::string hostname) {
  if (ipCache.find(hostname) == ipCache.end()) {
    Poco::Net::IPAddress address = Poco::Net::DNS::resolveOne(hostname);
    ipCache.insert(
        std::pair<std::string, std::string>(hostname, address.toString()));
    return address.toString();
  }
  return ipCache[hostname];
}

std::string NameSystem::publicKeyToIP(std::string publicKey) {
  if (ipCache.find(publicKey) == ipCache.end()) {
    // IP addrs[1];
    // kadnode_lookup( publicKey.c_str(), addrs, 1 );
    // ...
  }
  return ipCache[publicKey];
}

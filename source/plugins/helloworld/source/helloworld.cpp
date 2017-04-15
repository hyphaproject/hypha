// Copyright (c) 2017 Hypha

#include "hypha/plugins/helloworld/helloworld.h"

#include <iostream>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <Poco/ClassLibrary.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Timestamp.h>

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/utils/logger.h>

using namespace hypha::plugin;
using namespace hypha::plugin::helloworld;

using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;

std::string timeJson() {
  Poco::Timestamp now;
  std::string nowStr =
      DateTimeFormatter::format(now, DateTimeFormat::SORTABLE_FORMAT);

  boost::property_tree::ptree sendobject;
  sendobject.put("time", nowStr);
  std::stringstream sstream;
  return sstream.str();
}

void HelloWorld::doWork() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void HelloWorld::setup() {}

std::string HelloWorld::communicate(std::string /*message*/) {
  std::string ret;
  return ret;
}

void HelloWorld::receiveMessage(std::string message) {
  std::cout << "Message received by " << this->id << ": " << message
            << std::endl;
}

void HelloWorld::loadConfig(std::string json) { this->config = json; }

std::string HelloWorld::getConfig() { return "{}"; }

hypha::plugin::HyphaBasePlugin *HelloWorld::getInstance(std::string id) {
  HelloWorld *instance = new HelloWorld();
  instance->setId(id);
  return instance;
}

POCO_BEGIN_MANIFEST(HyphaBasePlugin)
POCO_EXPORT_CLASS(HelloWorld)
POCO_END_MANIFEST

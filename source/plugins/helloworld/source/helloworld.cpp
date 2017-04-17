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
  sendobject.put("say", "Time is: " + nowStr);
  std::stringstream sstream;
  boost::property_tree::write_json(sstream, sendobject);
  return sstream.str();
}

HelloWorld::HelloWorld() : HyphaBasePlugin(), HyphaSender() {}

void HelloWorld::doWork() {
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  std::string text = "{\"say\":\"Hello World!\"}";
  sendMessage(text);
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  sendMessage(timeJson());
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

PLUGIN_API POCO_BEGIN_MANIFEST(HyphaBasePlugin)
    POCO_EXPORT_CLASS(HelloWorld) POCO_END_MANIFEST

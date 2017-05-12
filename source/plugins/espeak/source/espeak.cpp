// Copyright (c) 2015-2017 Hypha

#include "hypha/plugins/espeak/espeak.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <Poco/ClassLibrary.h>

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/utils/logger.h>

using namespace hypha::plugin;
using namespace hypha::plugin::espeak;
using namespace hypha::utils;

ESpeak::ESpeak() : HyphaBasePlugin(), HyphaActor() {}

void ESpeak::doWork() { std::this_thread::sleep_for(std::chrono::seconds(1)); }

void ESpeak::setup() {
  espeak_Initialize(AUDIO_OUTPUT_PLAYBACK, 0, NULL, 0);
  receiveMessage("{\"say\":\"Starting.\"}");
}

std::string ESpeak::communicate(std::string UNUSED(message)) {
  return "SUCCESS";
}

void ESpeak::loadConfig(std::string json) {
  boost::property_tree::ptree pt;
  std::stringstream ss(json);
  boost::property_tree::read_json(ss, pt);
  if (pt.get_optional<std::string>("language")) {
    language = pt.get<std::string>("language");
  }
}

std::string ESpeak::getConfig() {
  return "{\"language\":\"" + language + "\"}";
}

HyphaBasePlugin *ESpeak::getInstance(std::string id) {
  ESpeak *instance = new ESpeak();
  instance->setId(id);
  return instance;
}

void ESpeak::receiveMessage(std::string message) {
  std::string text = "";
  try {
    boost::property_tree::ptree pt;
    std::stringstream ss(message);
    boost::property_tree::read_json(ss, pt);
    if (pt.get_optional<std::string>("language")) {
      language = pt.get<std::string>("language");
    }
    if (pt.get_optional<std::string>("say")) {
      text = pt.get<std::string>("say");
    }
    if (pt.get_optional<std::string>("tell")) {
      text = pt.get<std::string>("tell");
    }
    if (pt.get_optional<std::string>("speak")) {
      text = pt.get<std::string>("speak");
    }
    if (pt.get_optional<std::string>("out")) {
      text = pt.get<std::string>("out");
    }
  } catch (...) {
    hypha::utils::Logger::error("could not parse message: " + message);
  }

  if (text != "") {
    espeak_Synth(text.c_str(), text.length() + 1, 0, POS_CHARACTER, 0,
                 espeakCHARS_AUTO | espeakPHONEMES | espeakENDPAUSE, NULL,
                 NULL);
    espeak_Synchronize();
  }
}

PLUGIN_API POCO_BEGIN_MANIFEST(HyphaBasePlugin)
    POCO_EXPORT_CLASS(ESpeak) POCO_END_MANIFEST

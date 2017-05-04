// Copyright (c) 2015-2017 Hypha

#include "hypha/plugins/javascriptplugin/javascriptplugin.h"

#include <iostream>

#include <Poco/ClassLibrary.h>
#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/utils/logger.h>

using namespace hypha::plugin;
using namespace hypha::plugin::javascriptplugin;

JavascriptPlugin::JavascriptPlugin() {
  v8::HandleScope handle_scope;
  v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New();
  global->Set(v8::String::New("log"), v8::FunctionTemplate::New(LogCallback));
  context_ = v8::Context::New(NULL, global);
}

JavascriptPlugin::~JavascriptPlugin() {}

void JavascriptPlugin::doWork() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  try {
    v8::HandleScope handle_scope;
    v8::Context::Scope context_scope(context_);
    v8::Handle<v8::Value> result =
        this->function_doWork->Call(context_->Global(), 0, {});
  } catch (...) {
  }
}

bool JavascriptPlugin::ExecuteScript(v8::Handle<v8::String> script) {
  v8::HandleScope handle_scope;

  // We're just about to compile the script; set up an error handler to
  // catch any exceptions the script might throw.
  v8::TryCatch try_catch;

  // Compile the script and check for errors.
  v8::Handle<v8::Script> compiled_script = v8::Script::Compile(script);
  if (compiled_script.IsEmpty()) {
    v8::String::Utf8Value error(try_catch.Exception());
    hypha::utils::Logger::error(std::string(*error));
    // The script failed to compile; bail out.
    return false;
  }

  // Run the script!
  v8::Handle<v8::Value> result = compiled_script->Run();
  if (result.IsEmpty()) {
    // The TryCatch above is still in effect and will have caught the error.
    v8::String::Utf8Value error(try_catch.Exception());
    hypha::utils::Logger::error(std::string(*error));
    // Running the script failed; bail out.
    return false;
  }
  return true;
}

void JavascriptPlugin::setup() {
  // v8::V8::Initialize();

  try {
    v8::HandleScope handle_scope;
    v8::Context::Scope context_scope(context_);
    std::string scriptjs("function doWork(){ log(\"hello world!\"); }");
    this->script_ = v8::String::New(scriptjs.c_str());

    if (!ExecuteScript(script_)) return;

    v8::Handle<v8::String> function_name = v8::String::New("doWork");
    v8::Handle<v8::Value> function_val = context_->Global()->Get(function_name);
    if (!function_val->IsFunction()) {
      hypha::utils::Logger::error("doWork function not found!");
    } else {
      function_doWork = v8::Persistent<v8::Function>::New(
          v8::Handle<v8::Function>::Cast(function_val));
    }

  } catch (std::exception &e) {
    hypha::utils::Logger::error(e.what());
  } catch (...) {
  }
}

std::string JavascriptPlugin::communicate(std::string message) {
  std::string ret;
  try {
  } catch (...) {
  }
  return ret;
}

v8::Handle<v8::Value> JavascriptPlugin::LogCallback(const v8::Arguments &args) {
  if (args.Length() < 1) return v8::Undefined();
  v8::HandleScope scope;
  v8::Handle<v8::Value> arg = args[0];
  v8::String::Utf8Value value(arg);

  hypha::utils::Logger::info(std::string((const char *)*value));
  return v8::Undefined();
}

void JavascriptPlugin::loadConfig(std::string json) {
  boost::property_tree::ptree pt;
  std::stringstream ss(json);
  boost::property_tree::read_json(ss, pt);
  if (pt.get_optional<std::string>("javascriptmodule")) {
    javascriptmodule = pt.get<std::string>("javascriptmodule");
  } else {
    javascriptmodule = "javascriptplugin";
  }
  if (pt.get_optional<std::string>("javascriptclass")) {
    javascriptclass = pt.get<std::string>("javascriptclass");
  } else {
    javascriptclass = "javascriptplugin";
  }

  this->config = json;
}

std::string JavascriptPlugin::getConfig() { return "{}"; }

hypha::plugin::HyphaBasePlugin *JavascriptPlugin::getInstance(std::string id) {
  JavascriptPlugin *instance = new JavascriptPlugin();
  instance->setId(id);
  return instance;
}

void JavascriptPlugin::receiveMessage(std::string message) {
  try {
  } catch (...) {
  }
}

PLUGIN_API POCO_BEGIN_MANIFEST(HyphaBasePlugin)
    POCO_EXPORT_CLASS(JavascriptPlugin) POCO_END_MANIFEST

#ifndef HYPHAPLUGIN_H
#define HYPHAPLUGIN_H

#include <hypha/plugin/hyphabaseplugin.h>
#include <hypha/plugin/plugin_api.h>
#include <boost/signals2.hpp>

namespace hypha {
namespace plugin {

class PLUGIN_API HyphaPlugin : public HyphaBasePlugin {
 public:
  virtual void setup() = 0;
  virtual std::string communicate(std::string message) = 0;
  virtual HyphaPlugin *getInstance(std::string id) = 0;
};
}
}

#endif  // HYPHAPLUGIN_H

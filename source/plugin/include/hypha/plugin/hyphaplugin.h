#ifndef HYPHAPLUGIN_H
#define HYPHAPLUGIN_H

#include <boost/signals2.hpp>
#include <hypha/plugin/plugin_api.h>
#include <hypha/plugin/hyphabaseplugin.h>

namespace hypha {
namespace plugin {

class PLUGIN_API HyphaPlugin: public HyphaBasePlugin {
  public:
    virtual void setup() = 0;
    virtual std::string communicate(std::string message) = 0;
    virtual HyphaPlugin *getInstance(std::string id) = 0;
    virtual std::string name() {
        return "hyphaplugin";
    }
    virtual std::string getTitle() {
        return "HyphaPlugin";
    }
    virtual std::string getVersion() {
        return "1.0";
    }
    virtual std::string getDescription() {
        return "Hypha plugin";
    }
};
}
}

#endif // HYPHAPLUGIN_H

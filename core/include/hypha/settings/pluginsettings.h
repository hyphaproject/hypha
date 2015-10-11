#ifndef PLUGINSETTINGS_H
#define PLUGINSETTINGS_H

#include "../core.h"
#include <list>
#include <string>

namespace hypha {
namespace settings {
class Core_API PluginSettings {
  public:
    static PluginSettings * instance();
    std::list<std::string> getAllPluginIds();
    std::list<std::string> getLocalPluginIds();
    std::string getName(std::string id);
    std::string getHost(std::string id);
    std::string getConfig(std::string id);
    bool exists(std::string id);

  private:
    explicit PluginSettings();
    ~PluginSettings();

    static PluginSettings *singleton;

};
}
}

#endif // PLUGINSETTINGS_H

#ifndef PLUGINSETTINGS_H
#define PLUGINSETTINGS_H

#include "../core.h"
#include <list>
#include <string>
#include "hypha/database/database.h"

namespace hypha {
namespace settings {
class Core_API PluginSettings {
  public:
    static PluginSettings * instance();

    explicit PluginSettings(hypha::database::Database *database);
    ~PluginSettings();

    std::list<std::string> getAllPluginIds();
    std::list<std::string> getLocalPluginIds();
    std::string getName(std::string id);
    std::string getHost(std::string id);
    std::string getConfig(std::string id);
    bool exists(std::string id);

  private:
    PluginSettings();


    static PluginSettings *singleton;

    hypha::database::Database *database;

};
}
}

#endif // PLUGINSETTINGS_H

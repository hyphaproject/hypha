#ifndef PLUGINSETTINGS_H
#define PLUGINSETTINGS_H

#include "../core.h"
#include <list>
#include <string>
#include <hypha/database/database.h>

namespace hypha {
namespace settings {

/** PluginSettings loads settings of plugins from Database and represents them.
 * You can get access to name, host or config for given plugin id.
 */
class Core_API PluginSettings {
  public:
    static PluginSettings *instance();

    explicit PluginSettings(hypha::database::Database *database);
    ~PluginSettings();

    std::list<std::string> getAllPluginIds();
    std::list<std::string> getLocalPluginIds();
    std::string getName(std::string id);
    std::string getHost(std::string id);
    std::string getConfig(std::string id);
    bool exists(std::string id);

  protected:
    static PluginSettings *singleton;

    hypha::database::Database *database;

};
}
}

#endif // PLUGINSETTINGS_H

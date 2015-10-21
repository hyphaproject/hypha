#ifndef HANDLERSETTINGS_H
#define HANDLERSETTINGS_H

#include "../core.h"
#include <string>
#include <list>
#include <hypha/database/database.h>

namespace hypha {
namespace settings {
class Core_API HandlerSettings {
  public:
    static HandlerSettings * instance();

    explicit HandlerSettings(hypha::database::Database *database);
    ~HandlerSettings();

    std::list<std::string> getAllHandlerIds();
    std::list<std::string> getLocalHandlerIds();
    std::string getName(std::string id);
    std::string getHost(std::string id);
    std::string getConfig(std::string id);
    std::list<std::string> getConnectedPlugins(std::string handlerId);
    bool exists(std::string id);

  private:
    static HandlerSettings *singleton;

    hypha::database::Database *database;
};
}
}

#endif // HANDLERSETTINGS_H

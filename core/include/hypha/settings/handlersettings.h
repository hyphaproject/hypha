#ifndef HANDLERSETTINGS_H
#define HANDLERSETTINGS_H

#include "../core.h"
#include <string>
#include <list>

namespace hypha {
namespace settings {
class Core_API HandlerSettings {
  public:
    static HandlerSettings * instance();
    std::list<std::string> getAllHandlerIds();
    std::list<std::string> getLocalHandlerIds();
    std::string getName(std::string id);
    std::string getHost(std::string id);
    std::string getConfig(std::string id);
    std::list<std::string> getConnectedPlugins(std::string handlerId);
    bool exists(std::string id);

  private:
    explicit HandlerSettings();
    ~HandlerSettings();

    static HandlerSettings *singleton;
};
}
}

#endif // HANDLERSETTINGS_H

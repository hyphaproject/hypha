// Copyright (c) 2015-2016 Hypha
#pragma once

#include <string>
#include <list>
#include <hypha/core/core_api.h>
#include <hypha/core/database/database.h>

namespace hypha {
namespace settings {

/** HandlerSettings loads settings of handlers from Database and represents them.
 * You can get access to name, host or config for given handler id.
 */
class CORE_API HandlerSettings {
  public:
    static HandlerSettings *instance();

    explicit HandlerSettings(hypha::database::Database *database);
    ~HandlerSettings();

    std::list<std::string> getAllHandlerIds();
    std::list<std::string> getLocalHandlerIds();
    std::string getName(std::string id);
    std::string getHost(std::string id);
    std::string getConfig(std::string id);
    std::list<std::string> getConnectedPlugins(std::string handlerId);
    bool exists(std::string id);

  protected:
    static HandlerSettings *singleton;

    hypha::database::Database *database;
};
}
}


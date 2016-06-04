// Copyright (c) 2015-2016 Hypha
#pragma once

#include <string>

#include <hypha/controller/controller_api.h>


namespace hypha {
namespace database {
    class Database;
}

namespace controller {

class CONTROLLER_API Plugin {

public:
    Plugin(hypha::database::Database *database);

    /**
     * @brief add Adds a new plugin to the database
     * @param id The unique ID of the plugin
     * @param host The host where the plugin should run
     * @param type The type of plugin
     * @param config The Configuration the plugin should load
     */
    void add(std::string id, std::string host, std::string type, std::string config);

protected:
    hypha::database::Database *database = nullptr;
};
}
}

#ifndef DATABASE_H
#define DATABASE_H

#include <Poco/Data/Session.h>
#include <Poco/Data/SessionPool.h>
#include <Poco/Data/Statement.h>
#include <hypha/settings/databasesettings.h>
#include "../core.h"

namespace hypha {
namespace database {
class Core_API Database {
  public:
    static Database * instance();
    explicit Database(hypha::settings::DatabaseSettings * databaseSettings);
    ~Database();
    bool connect();
    bool reconnect();
    Poco::Data::Session getSession();
    Poco::Data::Statement getStatement();

  private:
    static Database *singleton;
    void createTables();
    Poco::Data::SessionPool *pool;
    hypha::settings::DatabaseSettings * databaseSettings;
};
}
}

#endif // DATABASE_H

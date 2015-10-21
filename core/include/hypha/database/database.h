#ifndef DATABASE_H
#define DATABASE_H

#include <Poco/Data/Session.h>
#include <Poco/Data/SessionPool.h>
#include <Poco/Data/Statement.h>
#include "../core.h"

namespace hypha {
namespace database {
class Core_API Database {
  public:
    static Database * instance();
    bool connect();
    bool reconnect();
    Poco::Data::Session getSession();
    Poco::Data::Statement getStatement();

  private:
    explicit Database();
    ~Database();
    static Database *singleton;
    void createTables();
    Poco::Data::SessionPool *pool;
};
}
}

#endif // DATABASE_H

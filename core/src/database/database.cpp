#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/SQLite/Connector.h>
#include <mutex>
#include <hypha/utils/logger.h>
#include "hypha/database/database.h"
#include <hypha/settings/databasesettings.h>

using namespace hypha::utils;
using namespace hypha::settings;
using namespace hypha::database;

Database *Database::singleton = 0;

Database::Database() {

}

Database::~Database() {
}

void Database::createTables() {
    Poco::Data::Statement statement = getStatement();

    statement << "CREATE TABLE IF NOT EXISTS `deviceonline` ("
              "`id` int(11) NOT NULL AUTO_INCREMENT, "
              "`deviceid` varchar(45) DEFAULT NULL, "
              "`type` ENUM('rfid', 'fingerprint', 'wifi', 'other') DEFAULT 'other', "
              "`time` datetime NOT NULL, "
              "PRIMARY KEY (`id`) "
              ") DEFAULT CHARSET=utf8;";
    statement.execute();

    statement << "CREATE TABLE IF NOT EXISTS handler ("
              "id varchar(32) NOT NULL,"
              "host varchar(128) NOT NULL DEFAULT 'localhost',"
              "type varchar(32) NOT NULL,"
              "config varchar(1024) NOT NULL,"
              "PRIMARY KEY (id)"
              ") DEFAULT CHARSET=utf8;";
    statement.execute();

    statement << "CREATE TABLE IF NOT EXISTS `plugins` ("
              "`id` varchar(32) NOT NULL,"
              "`host` varchar(128) NOT NULL DEFAULT 'localhost',"
              "type varchar(32) NOT NULL,"
              "`config` varchar(1024) NOT NULL,"
              "PRIMARY KEY (`id`)"
              ") DEFAULT CHARSET=utf8;";
    statement.execute();

    statement << "CREATE TABLE IF NOT EXISTS connection ("
              "`id` int(11) NOT NULL AUTO_INCREMENT,"
              "handler_id varchar(32) NOT NULL,"
              "plugin_id varchar(32) NOT NULL,"
              "PRIMARY KEY (id)"
              ") DEFAULT CHARSET=utf8;";
    statement.execute();
}

Database *Database::instance() {
    static std::mutex mutex;
    if (!singleton) {
        mutex.lock();

        if (!singleton) {
            singleton = new Database();
            singleton->connect();
        }

        mutex.unlock();
    }
    return singleton;
}

bool Database::connect() {

    Poco::Data::MySQL::Connector::registerConnector();
    Poco::Data::SQLite::Connector::registerConnector();

    DatabaseSettings *dbs = DatabaseSettings::instance();
    std::string connectStr = "host=" + dbs->getHost() + ";user=" + dbs->getUser() + ";password=" +dbs->getPassword() + ";db=" + dbs->getDatabase() + ";auto-reconnect=true";
    pool = new Poco::Data::SessionPool(dbs->getDriver(), connectStr);

    createTables();

    return true;
}

bool Database::reconnect() {
    return true;
}

Poco::Data::Statement Database::getStatement() {
    try {
        Poco::Data::Session sess(pool->get());
        return Poco::Data::Statement(sess);
    } catch(Poco::Exception e) {
        Logger::fatal(e.message());
    }
}


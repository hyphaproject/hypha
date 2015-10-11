#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/RecordSet.h>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <hypha/utils/logger.h>
#include <hypha/settings/databasesettings.h>
#include "hypha/database/userdbsql.h"

using namespace hypha::utils;
using namespace hypha::database;
using namespace hypha::settings;

using Poco::Data::Session;
using Poco::Data::Statement;

#ifdef _WIN32
using namespace Poco::Data::Keywords;
#else
using namespace Poco::Data;
#endif

UserDBSql::UserDBSql(UserDatabaseSettings *settings): UserDatabase(settings) {
}

UserDBSql::~UserDBSql() {
    if(pool)
        delete pool;
}

bool UserDBSql::connect() {
    Poco::Data::MySQL::Connector::registerConnector();
    UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
    std::string connectStr = "host=" + dbs->getHost() + ";user=" + dbs->getUser() + ";password=" +dbs->getPassword() + ";db="+dbs->getDatabase()+";auto-reconnect=true";
    pool = new Poco::Data::SessionPool(dbs->getDriver(), connectStr);
    return true;
}

bool UserDBSql::reconnect() {
    return true;
}

Poco::Data::Statement UserDBSql::getStatement() {
    Poco::Data::Session sess(pool->get());
    return Poco::Data::Statement(sess);
}

std::list<std::string> UserDBSql::getUsers() {
    UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
    std::list<std::string> userlist;
    Poco::Data::Statement statement = getStatement();
    statement << "select " + dbs->getAttributeUsername() + " from "+dbs->getTable();
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    while(more) {
        userlist.insert(userlist.end(), rs[0].convert<std::string>());
        more = rs.moveNext();
    }
    return userlist;
}

std::string UserDBSql::getFirstname(std::string username) {
    UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
    std::string retValue ="";
    Poco::Data::Statement statement = getStatement();
    statement << "select " + dbs->getAttributeFirstname() + " from "+dbs->getTable() + " where " + dbs->getAttributeUsername() + " = '" + username + "'", into(retValue);
    statement.execute();
    return retValue;
}

std::string UserDBSql::getLastname(std::string username) {
    UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
    std::string retValue ="";
    Poco::Data::Statement statement = getStatement();
    statement << "select " + dbs->getAttributeLastname() + " from "+dbs->getTable() + " where " + dbs->getAttributeUsername() + " = '" + username + "'", into(retValue);
    statement.execute();
    return retValue;
}

std::string UserDBSql::getMail(std::string username) {
    UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
    std::string retValue ="";
    Poco::Data::Statement statement = getStatement();
    statement << "select " + dbs->getAttributeMail() + " from "+dbs->getTable() + " where " + dbs->getAttributeUsername() + " = '" + username + "'", into(retValue);
    statement.execute();
    return retValue;
}

std::list<std::string> UserDBSql::getDevices(std::string username) {
    UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
    Poco::Data::Statement statement = getStatement();
    statement << "select " + dbs->getAttributeDevices() + " from "+dbs->getTable() +" where "+ dbs->getAttributeUsername() + " = '" + username + "'";
    statement.execute();
    Poco::Data::RecordSet rs(statement);
    bool more = rs.moveFirst();
    std::list<std::string> devicelist;
    while(more) {
        std::string d = rs[0].convert<std::string>();
        std::vector<std::string> devices;
        boost::split(devices, d, boost::is_any_of(", "), boost::token_compress_on);
        for(std::string device: devices) {
            devicelist.insert(devicelist.end(), device);
        }
        more = rs.moveNext();
    }
    return devicelist;
}

std::string UserDBSql::getOwnerOfDevice(std::string device) {
    UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
    std::string retValue ="";
    Poco::Data::Statement statement = getStatement();
    statement << "select " + dbs->getAttributeUsername() + " from "+dbs->getTable() + " where " + dbs->getAttributeDevices() + " like '%" + device + "%'", into(retValue);
    statement.execute();
    return retValue;
}

void UserDBSql::createTables() {
    UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
    Poco::Data::Statement statement = getStatement();
    statement <<"CREATE TABLE IF NOT EXISTS `"+dbs->getTable()+"` ("
              + "`"+dbs->getAttributeUsername()+"` varchar(128) NOT NULL, "
              + "`"+dbs->getAttributeLastname()+"` varchar(128) DEFAULT NULL, "
              + "`"+dbs->getAttributeFirstname()+"` varchar(128) DEFAULT NULL, "
              + "`"+dbs->getAttributeMail()+"` varchar(128) DEFAULT NULL, "
              + "`"+dbs->getAttributeDevices()+"` varchar(1024) DEFAULT NULL, "
              + "PRIMARY KEY (`"+dbs->getAttributeUsername()+"`)"
              + ") DEFAULT CHARSET=utf8;";
    statement.execute();
}

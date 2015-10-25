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
    std::string connectStr = "host=" + settings->getHost() + ";user=" + settings->getUser()
            + ";password=" + settings->getPassword() + ";db="+settings->getDatabase()+";auto-reconnect=true";
    pool = new Poco::Data::SessionPool(settings->getDriver(), connectStr);
    createTables();
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
    std::list<std::string> userlist;
    Poco::Data::Statement statement = getStatement();
    statement << "select " + settings->getAttributeUsername() + " from " + settings->getTable();
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
    std::string retValue ="";
    Poco::Data::Statement statement = getStatement();
    statement << "select " + settings->getAttributeFirstname() + " from "+settings->getTable() + " where "
                 + settings->getAttributeUsername() + " = '" + username + "'", into(retValue);
    statement.execute();
    return retValue;
}

std::string UserDBSql::getLastname(std::string username) {
    std::string retValue ="";
    Poco::Data::Statement statement = getStatement();
    statement << "select " + settings->getAttributeLastname() + " from "+settings->getTable() + " where "
                 + settings->getAttributeUsername() + " = '" + username + "'", into(retValue);
    statement.execute();
    return retValue;
}

std::string UserDBSql::getMail(std::string username) {
    std::string retValue ="";
    Poco::Data::Statement statement = getStatement();
    statement << "select " + settings->getAttributeMail() + " from "+settings->getTable() + " where "
                 + settings->getAttributeUsername() + " = '" + username + "'", into(retValue);
    statement.execute();
    return retValue;
}

std::list<std::string> UserDBSql::getDevices(std::string username) {
    Poco::Data::Statement statement = getStatement();
    statement << "select " + settings->getAttributeDevices() + " from "+settings->getTable() +" where "+ settings->getAttributeUsername() + " = '" + username + "'";
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
    std::string retValue ="";
    Poco::Data::Statement statement = getStatement();
    statement << "select " + settings->getAttributeUsername() + " from "+ settings->getTable() + " where "
                 + settings->getAttributeDevices() + " like '%" + device + "%'", into(retValue);
    statement.execute();
    return retValue;
}

bool UserDBSql::createUser(std::string username, std::string firstname, std::string lastname, std::string mail)
{
    Poco::Data::Statement statement = getStatement();
    statement << "INSERT INTO " + settings->getTable() + "(" + settings->getAttributeUsername() + ", "
                + settings->getAttributeFirstname() + ", " + settings->getAttributeLastname() + ", "
                + settings->getAttributeMail() + ") VALUES(?, ?, ?, ?);",
            use(username), use(firstname), use(lastname), use(mail);
    statement.execute();
    return true;
}

bool UserDBSql::updateUser(std::string username, std::string firstname, std::string lastname, std::string mail, std::string devices)
{
    Poco::Data::Statement statement = getStatement();
    statement <<"UPDATE " + settings->getTable() + " SET " + settings->getAttributeFirstname() + "=?, "
                + settings->getAttributeLastname() + "=?, " + settings->getAttributeMail() + "=?, "
                + settings->getAttributeDevices() + "=? WHERE " + settings->getAttributeUsername() + " = ?;",
            use(firstname), use(lastname), use(mail), use(devices), use(username);
    statement.execute();
    return true;
}

void UserDBSql::createTables() {
    Poco::Data::Statement statement = getStatement();
    statement <<"CREATE TABLE IF NOT EXISTS `"+settings->getTable()+"` ("
              + "`"+settings->getAttributeUsername()+"` varchar(128) NOT NULL, "
              + "`"+settings->getAttributeLastname()+"` varchar(128) DEFAULT NULL, "
              + "`"+settings->getAttributeFirstname()+"` varchar(128) DEFAULT NULL, "
              + "`"+settings->getAttributeMail()+"` varchar(128) DEFAULT NULL, "
              + "`"+settings->getAttributeDevices()+"` varchar(1024) DEFAULT NULL, "
              + "PRIMARY KEY (`"+settings->getAttributeUsername()+"`)"
              + ") DEFAULT CHARSET=utf8;";
    statement.execute();
}

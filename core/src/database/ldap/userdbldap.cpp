#include "hypha/settings/databasesettings.h"

#include <hypha/database/ldap/userdbldap.h>
#ifdef WITH_LDAP
using namespace hypha::settings;
using namespace hypha::database;

UserDBLDAP::UserDBLDAP(UserDatabaseSettings *settings) : UserDatabase(settings) {
    ld = NULL;
}

UserDBLDAP::~UserDBLDAP() {
    if (ld)
        ldap_unbind_ext(ld, NULL, NULL);
}

bool UserDBLDAP::connect() {
    int version = LDAP_VERSION3;
    int res;

    UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
    std::string url("ldap://" + dbs->getHost() + ":389");
    std::string ldapbinddn("" + dbs->getUser() + "," + dbs->getDatabase());
    res = ldap_initialize(&ld, url.c_str());
    if (res != LDAP_SUCCESS) {
        ld = NULL;
        return false;
    }
    res = ldap_set_option(ld, LDAP_OPT_PROTOCOL_VERSION, (void *)&version);
    if (res != LDAP_SUCCESS) {
        ldap_unbind_ext(ld, NULL, NULL);
        ld = NULL;
        return false;
    }

    char *authpass = strdup(dbs->getPassword().c_str());
    struct berval passwd;
    passwd.bv_val = authpass;
    passwd.bv_len = dbs->getPassword().length();
    res = ldap_sasl_bind_s(ld, ldapbinddn.c_str(), LDAP_SASL_SIMPLE, &passwd, NULL, NULL, NULL);
    if (res != LDAP_SUCCESS) {
        free(authpass);
        ldap_unbind_ext(ld, NULL, NULL);
        ld = NULL;
        return false;
    }
    free(authpass);

    return true;
}

std::list<std::string> UserDBLDAP::getUsers() {
    std::list<std::string> users;
    if (ld) {
        UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
        std::string filter("objectClass=person");
        char *attrs[] = { strdup(dbs->getAttributeUsername().c_str()), NULL };
        int res;
        LDAPMessage *msg, *e;
        res = ldap_search_ext_s( ld, dbs->getDatabase().c_str(), LDAP_SCOPE_SUBTREE,
                                 filter.c_str(), attrs, 0, NULL, NULL,
                                 NULL, LDAP_NO_LIMIT, &msg );

        int entries = ldap_count_entries( ld, msg );
        if ( entries > 0 ) {
            int i;
            for (e = ldap_first_entry( ld, msg ), i = 0; e != NULL;
                    e = ldap_next_entry( ld, e ), i++ ) {
                char *dn = ldap_get_dn( ld, e );
                BerElement *ber = NULL;
                struct berval bv, *bvals;
                std::string username = "";
                int i, rc;
                rc = ldap_get_dn_ber (ld, e, &ber, &bv);
                while (rc == LDAP_SUCCESS) {
                    rc = ldap_get_attribute_ber (ld, e, ber, &bv, &bvals);
                    if (bv.bv_val == NULL) break;
                    username = std::string (bvals[0].bv_val, bvals[0].bv_len);
                    users.insert(users.end(), username);
                    if (bvals) ber_memfree(bvals);
                }
            }
        }
    }



    return users;
}

std::string UserDBLDAP::getFirstname(std::string username) {
    if (ld) {
        UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
        std::string filter("(&(objectClass=person)(" + dbs->getAttributeUsername() + "=" + username + "))");
        char *attrs[] = { strdup(dbs->getAttributeFirstname().c_str()), NULL };
        int res;
        LDAPMessage *msg, *e;
        res = ldap_search_ext_s( ld, dbs->getDatabase().c_str(), LDAP_SCOPE_SUBTREE,
                                 filter.c_str(), attrs, 0, NULL, NULL,
                                 NULL, LDAP_NO_LIMIT, &msg );

        int entries = ldap_count_entries( ld, msg );
        if ( entries > 0 ) {
            int i;
            for (e = ldap_first_entry( ld, msg ), i = 0; e != NULL;
                    e = ldap_next_entry( ld, e ), i++ ) {
                char *dn = ldap_get_dn( ld, e );
                BerElement *ber = NULL;
                struct berval bv, *bvals;
                std::string username = "";
                int i, rc;
                rc = ldap_get_dn_ber (ld, e, &ber, &bv);
                while (rc == LDAP_SUCCESS) {
                    rc = ldap_get_attribute_ber (ld, e, ber, &bv, &bvals);
                    if (bv.bv_val == NULL) break;
                    username = std::string (bvals[0].bv_val, bvals[0].bv_len);
                    if (bvals) ber_memfree(bvals);
                    return username;
                }
            }
        }
    }

    return std::string();
}

std::string UserDBLDAP::getLastname(std::string username) {
    if (ld) {
        UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
        std::string filter("(&(objectClass=person)(" + dbs->getAttributeUsername() + "=" + username + "))");
        char *attrs[] = { strdup(dbs->getAttributeLastname().c_str()), NULL };
        int res;
        LDAPMessage *msg, *e;
        res = ldap_search_ext_s( ld, dbs->getDatabase().c_str(), LDAP_SCOPE_SUBTREE,
                                 filter.c_str(), attrs, 0, NULL, NULL,
                                 NULL, LDAP_NO_LIMIT, &msg );

        int entries = ldap_count_entries( ld, msg );
        if ( entries > 0 ) {
            int i;
            for (e = ldap_first_entry( ld, msg ), i = 0; e != NULL;
                    e = ldap_next_entry( ld, e ), i++ ) {
                char *dn = ldap_get_dn( ld, e );
                BerElement *ber = NULL;
                struct berval bv, *bvals;
                std::string username = "";
                int i, rc;
                rc = ldap_get_dn_ber (ld, e, &ber, &bv);
                while (rc == LDAP_SUCCESS) {
                    rc = ldap_get_attribute_ber (ld, e, ber, &bv, &bvals);
                    if (bv.bv_val == NULL) break;
                    username = std::string (bvals[0].bv_val, bvals[0].bv_len);
                    if (bvals) ber_memfree(bvals);
                    return username;
                }
            }
        }
    }

    return std::string();
}

std::string UserDBLDAP::getMail(std::string username) {
    if (ld) {
        UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
        std::string filter("(&(objectClass=person)(" + dbs->getAttributeUsername() + "=" + username + "))");
        char *attrs[] = { strdup(dbs->getAttributeMail().c_str()), NULL };
        int res;
        LDAPMessage *msg, *e;
        res = ldap_search_ext_s( ld, dbs->getDatabase().c_str(), LDAP_SCOPE_SUBTREE,
                                 filter.c_str(), attrs, 0, NULL, NULL,
                                 NULL, LDAP_NO_LIMIT, &msg );

        int entries = ldap_count_entries( ld, msg );
        if ( entries > 0 ) {
            int i;
            for (e = ldap_first_entry( ld, msg ), i = 0; e != NULL;
                    e = ldap_next_entry( ld, e ), i++ ) {
                char *dn = ldap_get_dn( ld, e );
                BerElement *ber = NULL;
                struct berval bv, *bvals;
                std::string username = "";
                int i, rc;
                rc = ldap_get_dn_ber (ld, e, &ber, &bv);
                while (rc == LDAP_SUCCESS) {
                    rc = ldap_get_attribute_ber (ld, e, ber, &bv, &bvals);
                    if (bv.bv_val == NULL) break;
                    username = std::string (bvals[0].bv_val, bvals[0].bv_len);
                    if (bvals) ber_memfree(bvals);
                    return username;
                }
            }
        }
    }

    return std::string();
}

std::list<std::string> UserDBLDAP::getDevices(std::string username) {
    std::list<std::string> users;
    if (ld) {
        UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
        std::string filter("(&(objectClass=person)(" + dbs->getAttributeUsername() + "=" + username + "))");

        char *attrs[] = { strdup(dbs->getAttributeDevices().c_str()), NULL };
        int res;
        LDAPMessage *msg, *e;
        res = ldap_search_ext_s( ld, dbs->getDatabase().c_str(), LDAP_SCOPE_SUBTREE,
                                 filter.c_str(), attrs, 0, NULL, NULL,
                                 NULL, LDAP_NO_LIMIT, &msg );

        int entries = ldap_count_entries( ld, msg );
        if ( entries > 0 ) {
            int i;
            for (e = ldap_first_entry( ld, msg ), i = 0; e != NULL;
                    e = ldap_next_entry( ld, e ), i++ ) {
                char *dn = ldap_get_dn( ld, e );
                BerElement *ber = NULL;
                struct berval bv, *bvals;
                std::string username = "";
                int i, rc;
                rc = ldap_get_dn_ber (ld, e, &ber, &bv);
                while (rc == LDAP_SUCCESS) {
                    rc = ldap_get_attribute_ber (ld, e, ber, &bv, &bvals);
                    if (bv.bv_val == NULL) break;
                    username = std::string (bvals[0].bv_val, bvals[0].bv_len);
                    users.insert(users.end(), username);
                    if (bvals) ber_memfree(bvals);
                }
            }
        }
    }



    return users;
}

std::string UserDBLDAP::getOwnerOfDevice(std::string device) {
    if (ld) {
        UserDatabaseSettings *dbs = UserDatabaseSettings::instance();
        std::string filter("(&(objectClass=person)(registeredAddress=" + device + "))");
        char *attrs[] = { strdup(dbs->getAttributeUsername().c_str()), NULL };
        int res;
        LDAPMessage *msg, *e;
        res = ldap_search_ext_s( ld, dbs->getDatabase().c_str(), LDAP_SCOPE_SUBTREE,
                                 filter.c_str(), attrs, 0, NULL, NULL,
                                 NULL, LDAP_NO_LIMIT, &msg );

        int entries = ldap_count_entries( ld, msg );
        if ( entries > 0 ) {
            int i;
            for (e = ldap_first_entry( ld, msg ), i = 0; e != NULL;
                    e = ldap_next_entry( ld, e ), i++ ) {
                char *dn = ldap_get_dn( ld, e );
                BerElement *ber = NULL;
                struct berval bv, *bvals;
                std::string username = "";
                int i, rc;
                rc = ldap_get_dn_ber (ld, e, &ber, &bv);
                while (rc == LDAP_SUCCESS) {
                    rc = ldap_get_attribute_ber (ld, e, ber, &bv, &bvals);
                    if (bv.bv_val == NULL) break;
                    username = std::string (bvals[0].bv_val, bvals[0].bv_len);
                    if (bvals) ber_memfree(bvals);
                    return username;
                }
            }
        }
    }
    return std::string();
}
#endif

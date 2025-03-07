#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

// User roles as an enum
typedef enum {
    GENERAL_USER = 0,
    ROOT_USER = 1
} UserRole;

//this handles the login information and access the type of users
UserRole login();

#endif

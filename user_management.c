#include "user_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 20
#define MAX_PASSWORD_LEN 16

UserRole login() {
    char *username = malloc(MAX_USERNAME_LEN);
    char *password = malloc(MAX_PASSWORD_LEN);

if (!username || !password) {
        printf("Memory allocation error.\n");
        free(username);
        free(password);
        return GENERAL_USER; // Default to general user on error
}
printf("Enter username: ");
    if (!fgets(username, MAX_USERNAME_LEN, stdin)) {
        printf("Error reading username.\n");
        free(username);
        free(password);
        return GENERAL_USER;
    }
// Remove trailing newline character from username
username[strcspn(username, "\n")] = '\0';
printf("Enter password: ");
    if (!fgets(password, MAX_PASSWORD_LEN, stdin)) {
        printf("Error reading password.\n");
        free(username);
        free(password);
        return GENERAL_USER;
    }
// Remove trailing newline character from password
password[strcspn(password, "\n")] = '\0';

UserRole role = (strcmp(username, "root") == 0 && strcmp(password, "admin") == 0) ? ROOT_USER : GENERAL_USER;

    free(username);
    free(password);

    return role;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bplus_tree.h"
#include "commands.h"
#include "user_management.h"
#define ROOT_PATH "/"

int main() {
node *root = createNode(ROOT_PATH, NULL, FOLDER_TYPE);
if (!root) {
        printf("Error initializing root directory.\n");
        return EXIT_FAILURE;
}
node *currentFolder = root;
char *path = malloc(2);
if (!path) {
        printf("Memory allocation error.\n");
        freeNode(root);
        return EXIT_FAILURE;
}

strcpy(path, ROOT_PATH);
uint8_t userRole = login();

printf("\n~ Welcome to SimLinux! ~\n");
printf("You are logged in as %s.\n", userRole == ROOT_USER ? "root user" : "general user");

while (1) 
{
    printf("\n%s> ", path);
    char *command = malloc(100);
    if (!command) {
            printf("Memory allocation error.\n");
        break;
        }

if (!fgets(command, 100, stdin)) {
            printf("Error reading command.\n");
            free(command);
            continue;
            }

command[strcspn(command, "\n")] = '\0';

CommandStatus result = processCommand(&currentFolder, command, &path, userRole);
free(command);

        if (result == COMMAND_EXIT) {
            break; // Exit program
        } else if (result == COMMAND_LOGOUT) {
            userRole = login(); // Re-login
            printf("You are logged in as %s.\n", userRole == ROOT_USER ? "root user" : "general user");
        }
}

freeNode(root);
free(path);
return EXIT_SUCCESS;

}
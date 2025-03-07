#include "commands.h"
#include "bplus_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "bplus_tree.h"
#include <string.h>
#include <time.h>

#define PERMISSION_DENIED "Permission denied. Only root user can perform this action.\n"

void mkdir(node *currentFolder, const char *name, uint8_t userRole) {
if (!userRole) {
        printf(PERMISSION_DENIED);
        return;
}
    node *newDir = createNode(name, currentFolder, FOLDER_TYPE);
    if (!newDir) {
            printf("Error creating directory.\n");
     return;
}

    // To set time
    time_t now = time(NULL);
    if (now != -1) {
        newDir->creationTime = now;  }

    newDir->sibling = currentFolder->child;
    currentFolder->child = newDir;
}

void tree(node *currentFolder, uint32_t depth) {
    if (!currentFolder) return;

    for (uint32_t i = 0; i < depth; i++) {
        printf("    ");
    }

    char timeBuffer[26];
    if (currentFolder->creationTime) {
        struct tm *tm_info = localtime(&currentFolder->creationTime);
        strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", tm_info);
    } else {
        strcpy(timeBuffer, "Unknown time");
    }

    printf("|-- %s%s  Created: %s \n", currentFolder->name, currentFolder->type == FOLDER_TYPE ? "/" : "", timeBuffer);

    for (node *child = currentFolder->child; child; child = child->sibling) {
        tree(child, depth + 1);
    }
}

void touch(node *currentFolder, const char *name, uint8_t userRole) {
    if (!userRole) {
        printf(PERMISSION_DENIED);
        return;
    }
    node *newFile = createNode(name, currentFolder, FILE_TYPE);
    if (!newFile) {
        printf("Error creating file.\n");
        return;
    }

    // Set the creation time
    time_t now = time(NULL);
    if (now != -1) {
        newFile->creationTime = now;
    }

    newFile->sibling = currentFolder->child;
    currentFolder->child = newFile;
}

void ls(const node *currentFolder) {
    for (node *child = currentFolder->child; child; child = child->sibling) {
        char timeBuffer[26];
        if (child->creationTime) {
            struct tm *tm_info = localtime(&child->creationTime);
            strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", tm_info);
        } else {
            strcpy(timeBuffer, "Unknown time");
        }
        printf("%s%s  Created: %s\n", child->name, child->type == FOLDER_TYPE ? "/" : "", timeBuffer);
    }
}

void pwd(const char *path) {
    printf("%s\n", path);
}

node *cd(node *currentFolder, const char *name, char **path) {
    for (node *child = currentFolder->child; child; child = child->sibling) {
        if (child->type == FOLDER_TYPE && strcmp(child->name, name) == 0) {
            *path = realloc(*path, strlen(*path) + strlen(name) + 2);
            if (!*path) {
                printf("Error allocating memory.\n");
                return currentFolder;
            }
            strcat(*path, "/");
            strcat(*path, name);
            return child;
        }
    }
    printf("Directory not found.\n");
    return currentFolder;
}

node *cdup(node *currentFolder, char **path) {
    if (!currentFolder->parent) {
        printf("Already at root directory.\n");
        return currentFolder;
    }
    char *lastSlash = strrchr(*path, '/');
    if (lastSlash) *lastSlash = '\0';
    return currentFolder->parent;
}

void rm(node *currentFolder, const char *name, uint8_t userRole) {
    if (!userRole) {
        printf(PERMISSION_DENIED);
        return;
    }
    node **prev = &currentFolder->child;
    for (node *child = currentFolder->child; child; child = child->sibling) {
        if (strcmp(child->name, name) == 0) {
            *prev = child->sibling;
            freeNode(child);
            return;
        }
        prev = &child->sibling;
    }
    printf("File/Directory not found.\n");
}

void renameNode(node *currentFolder, const char *oldName, const char *newName, uint8_t userRole) {
    if (!userRole) {
        printf(PERMISSION_DENIED);
        return;
    }

    for (node *child = currentFolder->child; child; child = child->sibling) {
        if (strcmp(child->name, oldName) == 0) {
            free(child->name);
            child->name = malloc(strlen(newName) + 1);
            if (!child->name) {
                printf("Memory allocation error.\n");
                return;
            }
            strcpy(child->name, newName);
            printf("Renamed '%s' to '%s'.\n", oldName, newName);
            return;
        }
    }

    printf("File/Directory '%s' not found.\n", oldName);
}

void help() {
    printf("Available commands:\n");
    printf("mkdir [name]    - Create a directory *Only for root user*\n");
    printf("touch [name]    - Create a file *Only for root user*\n");
    printf("ls              - List contents of the current directory\n");
    printf("pwd             - Print working directory\n");
    printf("cd [name]       - Change directory\n");
    printf("cdup            - Move to the parent directory\n");
    printf("rm [name]       - Remove a file or directory *Only for root user*\n");
    printf("rnm [old] [new] - Rename a file or directory *Only for root user*\n");
    printf("tree            - Display directory structure\n");
    printf("logout          - Log out the current user\n");
    printf("exit            - Exit the program\n");
}

CommandStatus processCommand(node **currentFolder, const char *command, char **path, uint8_t userRole) {
    if (strncmp(command, "mkdir ", 6) == 0) {
        mkdir(*currentFolder, command + 6, userRole);
    } else if (strncmp(command, "touch ", 6) == 0) {
        touch(*currentFolder, command + 6, userRole);
    } else if (strcmp(command, "ls") == 0) {
        ls(*currentFolder);
    } else if (strcmp(command, "pwd") == 0) {
        pwd(*path);
    } else if (strncmp(command, "cd ", 3) == 0) {
        *currentFolder = cd(*currentFolder, command + 3, path);
    } else if (strcmp(command, "cdup") == 0) {
        *currentFolder = cdup(*currentFolder, path);
    } else if (strncmp(command, "rm ", 3) == 0) {
        rm(*currentFolder, command + 3, userRole);
    } else if (strncmp(command, "rnm ", 4) == 0) {
        char *args = strdup(command + 4);
        char *oldName = strtok(args, " ");
        char *newName = strtok(NULL, " ");

        if (oldName && newName) {
            renameNode(*currentFolder, oldName, newName, userRole);
        } else {
            printf("Usage: rename [old_name] [new_name]\n");
        }
        free(args);
    } else if (strcmp(command, "help") == 0) {
        help();
    } else if (strcmp(command, "logout") == 0) {
        printf("Logged out. Please log in again.\n");
        return COMMAND_LOGOUT;
    } else if (strcmp(command, "tree") == 0) {
        tree(*currentFolder, 0);
    } else if (strcmp(command, "exit") == 0) {
        return COMMAND_EXIT;
    } else {
        printf("Unknown command. Type 'help' for a list of commands.\n");
    }
    return COMMAND_SUCCESS;
}

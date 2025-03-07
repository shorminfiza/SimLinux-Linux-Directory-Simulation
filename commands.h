#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdint.h>
#include "bplus_tree.h"

typedef enum {
    COMMAND_SUCCESS = 0,  // Command executed successfully
    COMMAND_EXIT = -1,    // Exit the program
    COMMAND_LOGOUT = 2    // Logout and prompt for re-login
} CommandStatus;

CommandStatus processCommand(node **currentFolder, const char *command, char **path, uint8_t userRole);

//to create directory
void mkdir(node *currentFolder, const char *name, uint8_t userRole);
//to create file
void touch(node *currentFolder, const char *name, uint8_t userRole);
//to list the directories
void ls(const node *currentFolder);
//to visualize hierchiarlly
void tree(node *currentFolder, uint32_t depth);
//to print working directory
void pwd(const char *path);
//to change directory
node *cd(node *currentFolder, const char *name, char **path);
//to change directory up
node *cdup(node *currentFolder, char **path);
//to remove any directory
void rm(node *currentFolder, const char *name, uint8_t userRole);
//to rename any directory or file
void renameNode(node *currentFolder, const char *oldName, const char *newName, uint8_t userRole);
//to print all the avaiable commands
void help();
//to process and handle any given command
CommandStatus processCommand(node **currentFolder, const char *command, char **path, uint8_t userRole);

#endif

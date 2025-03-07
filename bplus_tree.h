#ifndef BPLUS_TREE_H
#define BPLUS_TREE_H
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NAME_LEN 50

//represents the type of node
typedef enum {
    FILE_TYPE = 0,
    FOLDER_TYPE = 1
} NodeType;

typedef struct node {
    
char *name;
uint8_t type : 1; //bitfield for node type (file or folder)
struct node *parent;
struct node *child;
struct node *sibling;
time_t creationTime;
} node;

//to create a new node
node *createNode(const char *name, node *parent, NodeType type);
//after dynamically allocating to free the nodes
void freeNode(node *root);
#endif

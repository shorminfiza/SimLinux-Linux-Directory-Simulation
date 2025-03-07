#include "bplus_tree.h"
#include <string.h>
#include <time.h>

node *createNode(const char *name, node *parent, NodeType type) {
node *newNode = malloc(sizeof(node));
if (!newNode) return NULL;
    newNode->name = malloc(strlen(name) + 1);
if (!newNode->name) {
        free(newNode);
        return NULL;
    }
strcpy(newNode->name, name);
newNode->type = type;
newNode->parent = parent;
newNode->child = NULL;
newNode->sibling = NULL;
newNode->creationTime = time(NULL);
return newNode;
}

void freeNode(node *root) {
    if (!root) return;
    freeNode(root->child);
    freeNode(root->sibling);
    free(root->name);
    free(root);
}

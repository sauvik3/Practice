#pragma once
#include <stddef.h>

typedef struct Node_t {
    int             data;
    struct Node_t*  next;
} Node;

Node*   createNode(const int data);
Node*   addNodeAtEnd(Node** head, const int data);
Node*   addNodeAtBeginning(Node** head, const int data);
Node*   insertNodeAtIndex(Node** head, const int pos, Node* node);
void    deleteNodeAtIndex(Node** head, const int pos);
void    deleteAllNodes(Node** head);
int     getNodeCount(const Node* head);
size_t  findElement(const Node* head, const int data);
Node*   getNodeAtIndex(Node** const head, const int index);
Node*   reverseRecursive(Node* previous, Node* current);
void    reverseLinkedList(Node** head);
int     compare(const Node* node1, const Node* node2);
void    sortLinkedList(Node** head);
void    removeDuplicates(Node** head);

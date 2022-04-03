#include "LinkedList.h"

#include <stdio.h>
#include <stdlib.h>

Node* createNode(const int data)
{
    Node* node = malloc(sizeof(Node));
    if (node != NULL) {
        *node = (Node){ data, NULL };
    }
    return node;
}

Node* addNodeAtEnd(Node** head, const int data)
{
    const size_t count = getNodeCount(*head);
    Node* node = createNode(data);
    return insertNodeAtIndex(head, (int)(count + 1), node);
}

Node* addNodeAtBeginning(Node** head, const int data)
{
    Node* node = createNode(data);
    return insertNodeAtIndex(head, 1, node);
}

Node* insertNodeAtIndex(Node** head, const int pos, Node* node)
{
    if (pos < 1 || node == NULL)
        return NULL;

    if (pos == 1) {
        node->next = *head;
        *head = node;
    }
    else {
        Node* ptr = getNodeAtIndex(head, pos - 1);
        if (ptr == NULL)
            return NULL;

        Node* tmp = ptr->next;
        ptr->next = node;
        node->next = tmp;
    }

    return node;
}

void deleteNodeAtIndex(Node** head, const int pos)
{
    if (pos < 1 || *head == NULL)
        return;

    if (pos == 1) {
        Node* tmp = (*head)->next;
        free(*head);
        *head = tmp;
    }
    else {
        Node* ptr = getNodeAtIndex(head, pos - 1);
        if (ptr == NULL)
            return;

        Node* tmp = ptr->next;
        ptr->next = tmp->next;
        free(tmp);
    }
}

void deleteAllNodes(Node** head)
{
    Node* ptr = *head;
    while (ptr != NULL) {
        Node* tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    *head = NULL;
}

int getNodeCount(const Node* head)
{
    const Node* ptr = head;
    size_t count = 0;
    while (ptr != NULL) {
        ++count;
        ptr = ptr->next;
    }
    return count;
}

size_t findElement(const Node* head, const int data)
{
    const Node* ptr = head;
    size_t count = 0;
    while (ptr != NULL) {
        ++count;
        if (data == ptr->data)
            return count;
        ptr = ptr->next;
    }
    return 0;
}

Node* getNodeAtIndex(Node** const head, const int index)
{
    Node* ptr = *head;
    size_t count = 0;

    if (index < 1)
        return NULL;

    while (ptr != NULL) {
        ++count;
        if (count == (size_t)index)
            return ptr;
        ptr = ptr->next;
    }
    return NULL;
}

Node* reverseRecursive(Node* previous, Node* current)
{
    if (current != NULL) {
        Node* tmp = current->next;
        current->next = previous;
        previous = reverseRecursive(current, tmp);
    }
    return previous;
}

void reverseLinkedList(Node** head)
{
    Node* ptr = *head;
    Node* prev = NULL;

    while (ptr != NULL) {
        Node* next = ptr->next;
        ptr->next = prev;
        prev = ptr;
        ptr = next;
    }
    *head = prev;
}

int compare(const Node* node1, const Node* node2)
{
    if (node1 == NULL || node2 == NULL)
        return INT_MIN;

    if (node1->data > node2->data)
        return 1;
    if (node1->data < node2->data)
        return -1;

    return 0;
}

void sortLinkedList(Node** head)
{
    Node* ptr = *head;
    while (ptr != NULL) {
        Node* ptr1 = ptr->next;
        while (ptr1 != NULL) {
            if (compare(ptr, ptr1) > 0) {
                const int tmp = ptr1->data;
                ptr1->data = ptr->data;
                ptr->data = tmp;
            }
            ptr1 = ptr1->next;
        }
        ptr = ptr->next;
    }
}

void printAllNodes1(const Node* head)
{
    const Node* ptr = head;
    while (ptr != NULL)
    {
        const Node* tmp = ptr;
        ptr = ptr->next;
        printf("%2d%s", tmp->data, ptr == NULL ? "" : " -> ");
    }
    putchar('\n');
}

void removeDuplicates(Node** head)
{
    Node* ptr = *head;
    while (ptr != NULL) {
        Node** ptr1 = &ptr->next;
        printf("%-7d : ", ptr->data);
        while (*ptr1 != NULL) {
            const int index = findElement(*ptr1, ptr->data);
            if (index > 0)
                deleteNodeAtIndex(ptr1, index);
            else
				*ptr1 = (*ptr1)->next;
        }
        printAllNodes1(*head);
        ptr = ptr->next;
    }
}

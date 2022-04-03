#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

void printAllNodes(const Node* head)
{
    const Node* ptr = head;
    while (ptr != NULL)
    {
        const Node* tmp = ptr;
        ptr = ptr->next;
        printf("%d%s", tmp->data, ptr == NULL ? "" : " -> ");
    }
}

int main()
{
    Node* head = NULL;
    addNodeAtEnd(&head, 10);
    addNodeAtEnd(&head, 10);
    addNodeAtEnd(&head, 10);
    addNodeAtEnd(&head, 20);
    addNodeAtEnd(&head, 40);
    //addNodeAtBeginning(&head, 96);
    addNodeAtEnd(&head, 30);
    addNodeAtEnd(&head, 36);
    addNodeAtEnd(&head, 40);
    addNodeAtEnd(&head, 10);
    //addNodeAtBeginning(&head, 5);
    addNodeAtEnd(&head, 56);
    //deleteNodeAtIndex(&head, 4);
    addNodeAtEnd(&head, 10);
    addNodeAtEnd(&head, 10);

    printf("Initial : ");
    printAllNodes(head);
    putchar('\n');
    
    removeDuplicates(&head);
    /*sortLinkedList(&head);

    reverseLinkedList(&head);
    head = reverseRecursive(NULL, head);*/

    printf("Final   : ");
    printAllNodes(head);
    putchar('\n');
    deleteAllNodes(&head);
    
    return 0;
}

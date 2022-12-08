#include <stdlib.h>
#include "llist.h"

//function to create empty linked list
LLIST createList()
{

    LLIST list = {0, NULL, NULL};
    return list;
}

//function to search for element in linked list
int searchList(LLIST H, int k)
{

    NODE *current = H.head;
    while (current != NULL)
    {
        if (current->value == k)
            return 1;
        current = current->next;
    }
    return 0;
}

//function to insert element at front of linked list
LLIST insertAtFront(LLIST H, int k)
{

    NODE *nodeptr = (NODE *)malloc(sizeof(NODE));
    nodeptr->value = k;
    nodeptr->next = H.head;
    H.head = nodeptr;
    if (H.tail == NULL)
        H.tail = nodeptr;

    H.size++;
    return H;
}

//function to insert element at end of linked list
LLIST insertAtEnd(LLIST H, int k)
{

    NODE *nodeptr = (NODE *)malloc(sizeof(NODE));
    nodeptr->value = k;
    nodeptr->next = NULL;
    if (!H.tail)
    {

        H.head = H.tail = nodeptr;
        H.size++;
        return H;
    }
    H.tail->next = nodeptr;
    H.tail = nodeptr;
    H.size++;
    return H;
}

//function to delete element from front of linked list
LLIST deleteFromFront(LLIST H, int *k)
{

    NODE *nodeptr = H.head;
    if (nodeptr)
    {

        H.head = nodeptr->next;
        if (H.size == 1)
            H.tail = NULL;

        nodeptr->next = NULL;
        *k = nodeptr->value;
        free(nodeptr);
        H.size--;
    }
    return H;
}

//function to delete element from end of linked list
LLIST deleteFromEnd(LLIST H, int *k)
{

    NODE *current = H.head;
    if (current)
    {
        while (current->next != H.tail && current != H.tail)
            current = current->next;

        NODE *nodeptr = H.tail;
        H.tail = current;
        *k = nodeptr->value;
        current->next = NULL;
        if (H.size == 1)
            H.head = H.tail = NULL;

        free(nodeptr);
        H.size--;
    }
    return H;
}

//function to delete element from linked list if present
LLIST deleteList(LLIST H, int k)
{

    NODE *nodeptr, *prev = H.head;
    if (!H.head)
        return H;

    if (H.head->value == k)
    {
        return deleteFromFront(H, &k);
    }

    while (prev != NULL)
    {
        if ((prev->next) && prev->next->value == k)
            break;
        prev = prev->next;
    }

    if (prev && prev->next == H.tail)
    {
        return deleteFromEnd(H, &k);
    }

    if (prev != NULL)
    {

        nodeptr = prev->next;
        prev->next = nodeptr->next;
        nodeptr->next = NULL;
        free(nodeptr);
        H.size--;
    }
    return H;
}

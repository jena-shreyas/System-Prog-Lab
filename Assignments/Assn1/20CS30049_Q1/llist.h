#ifndef LIBMYIMPL_LLIST_H
#define LIBMYIMPL_LLIST_H

typedef struct node
{
    int value;
    struct node *next;
} NODE;

typedef struct
{
    int size;
    struct node *head;
    struct node *tail;
} LLIST;

LLIST createList();
int searchList(LLIST H, int k);
LLIST insertAtFront(LLIST H, int k);
LLIST insertAtEnd(LLIST H, int k);
LLIST deleteFromFront(LLIST H, int *k);
LLIST deleteFromEnd(LLIST H, int *k);
LLIST deleteList(LLIST H, int k);

#endif
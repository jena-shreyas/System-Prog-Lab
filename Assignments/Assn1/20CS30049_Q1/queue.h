#ifndef LIBMYIMPL_QUEUE_H
#define LIBMYIMPL_QUEUE_H

#ifndef LIBMYIMPL_LLIST_H 
#include <data_struct/llist.h>
#endif

typedef struct
{
    LLIST list;
} QUEUE;

QUEUE createQueue();
int isEmptyQueue(QUEUE Q);
QUEUE enqueue(QUEUE Q, int k);
QUEUE dequeue(QUEUE Q, int *k);

#endif
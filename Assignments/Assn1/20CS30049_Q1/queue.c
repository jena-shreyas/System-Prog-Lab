#include <stdlib.h>
#include "queue.h"

//function to create empty queue
QUEUE createQueue()
{
    LLIST list = {0, NULL, NULL};
    QUEUE Q = {list};
    return Q;
}

//function to check if queue empty or not
int isEmptyQueue(QUEUE Q)
{
    return (Q.list.size == 0) ? 1 : 0;
}

//function to enqueue element in queue
QUEUE enqueue(QUEUE Q, int k)
{
    Q.list = insertAtEnd(Q.list, k);
    return Q;
}

//function to dequeue element from queue
QUEUE dequeue(QUEUE Q, int *k)
{
    Q.list = deleteFromFront(Q.list, k);
    return Q;
}

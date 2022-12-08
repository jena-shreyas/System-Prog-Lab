#ifndef LIBMYIMPL_STACK_H
#define LIBMYIMPL_STACK_H

#ifndef LIBMYIMPL_LLIST_H
#include <data_struct/llist.h>
#endif

typedef struct
{
    LLIST list;
} STACK;

STACK createStack();
int isEmptyStack(STACK S);
STACK push(STACK S, int k);
STACK pop(STACK S, int *k);

#endif
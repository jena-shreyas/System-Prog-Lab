#ifndef LIBMYIMPL_UNION_FIND_H
#define LIBMYIMPL_UNION_FIND_H

#ifndef LIBMYIMPL_LLIST_H 
#include <data_struct/llist.h>
#endif

typedef NODE* NODE_PTR;

typedef struct{
    NODE** forest;
    int size;
}UNION_FIND;

UNION_FIND createUF(int n);
UNION_FIND makeSetUF(UNION_FIND F, int x, int *i);
NODE_PTR findUF(UNION_FIND F, int i);
void unionUF(UNION_FIND F, int i, int j);
int treeSize(NODE_PTR curr,int size);

#endif

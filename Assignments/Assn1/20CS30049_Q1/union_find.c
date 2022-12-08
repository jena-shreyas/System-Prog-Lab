#include <stdlib.h>
#include "union_find.h"

//function to create union find
UNION_FIND createUF(int n)
{

    UNION_FIND F;
    F.forest = (NODE **)malloc(n * sizeof(NODE *));
    for (int i = 0; i < n; i++)
    {
        F.forest[i] = NULL;
    }
    F.size = 0;
    return F;
}

//function to make singleton set for element in union find
UNION_FIND makeSetUF(UNION_FIND F, int x, int *i)
{

    NODE *ptr = (NODE *)malloc(sizeof(NODE));
    ptr->value = x;
    ptr->next = NULL;
    F.forest[F.size] = ptr;
    *i = F.size;
    F.size++;
    return F;
}

//function to find root of given element
NODE_PTR findUF(UNION_FIND F, int i)
{

    NODE_PTR curr = F.forest[i];
    while (curr)
    {
        if (curr->next == NULL)
            break;
        curr = curr->next;
    }
    return curr;
}

//function to apply union to two sets
void unionUF(UNION_FIND F, int i, int j)
{

    NODE_PTR root1 = findUF(F, i);
    NODE_PTR root2 = findUF(F, j);
    if (root1 == root2)
        return;

    if (treeSize(F.forest[i], 0) < treeSize(F.forest[j], 0))
        root1->next = root2;
    else
        root2->next = root1;
}

//function to find height of tree starting from current node
int treeSize(NODE_PTR curr, int size)
{

    if (curr == NULL)
        return 0;
    if (curr->next == NULL)
        return (size + 1);
    return treeSize(curr->next, size + 1);
}

#ifndef LIBGRAPH_GRAPH_H
#define LIBGRAPH_GRAPH_H

#ifndef LIBMYIMPL_STACK_H
#include <data_struct/stack.h>
#endif

#ifndef LIBMYIMPL_QUEUE_H
#include <data_struct/queue.h>
#endif

#define MAX_SIZE 100

typedef struct
{

    int v1;
    int v2;
    int w;
} EDGE;

typedef struct
{

    int n;
    int m;
    int adj[MAX_SIZE][MAX_SIZE];
    int visited[MAX_SIZE];
    EDGE edges[MAX_SIZE * MAX_SIZE];

} GRAPH;

GRAPH readGraph(const char *FName);
void DFS(GRAPH G);
void DFSvisit(GRAPH* gp, int v, STACK *sp);
void BFS(GRAPH G);
void BFSvisit(GRAPH* gp, int v, QUEUE *qp);
void MST(GRAPH G);
void mergesort(EDGE *edges, int n);
void merge(EDGE *left, EDGE *right, EDGE *edges, int l, int r);

#endif
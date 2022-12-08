#include <stdio.h>
#include <stdlib.h>
#include <data_struct.h>
#include <graph.h>

//function to read graph data from given file
GRAPH readGraph(const char *FName)
{

    FILE *file = fopen(FName, "r");
    GRAPH G;

    fscanf(file, "%d", &G.n);
    fscanf(file, "%d", &G.m);

    
    for (int i = 0; i < G.n; i++)
    {
        //set visited state of all nodes to 0
        G.visited[i] = 0;
        //initialize weights of edges between all nodes to 0
        for (int j = 0; j < G.n; j++)
            G.adj[i][j] = 0;
    }

    //read edges 
    for (int i = 0; i < G.m; i++)
    {

        int v1, v2, w;
        fscanf(file, "%d%d%d", &v1, &v2, &w);
        EDGE edge = {v1, v2, w};
        G.edges[i] = edge;
        G.adj[v1][v2] = G.adj[v2][v1] = w;
    }
    fclose(file);
    return G;
}

//function to implement DFS traversal of graph
void DFS(GRAPH G)
{
    STACK S = createStack();
    for (int i = 0; i < G.n; i++)
    {   
        //if node is not visited, visit it
        if (!G.visited[i])
        {
            DFSvisit(&G, i, &S);
        }
    }
    printf("\n");
}

//function to visit a node of graph during DFS traversal
void DFSvisit(GRAPH *gp, int v, STACK *sp)
{
    gp->visited[v] = 1;
    *sp = push(*sp, v);
    printf("%d ", v);

    for (int i = 0; i < gp->n; i++)
    {
        if (gp->adj[v][i] != 0 && gp->visited[i] == 0)
            DFSvisit(gp, i, sp);
    }
    *sp = pop(*sp, &v);
}

//function to implement BFS traversal of graph
void BFS(GRAPH G)
{
    QUEUE Q = createQueue();
    for (int i = 0; i < G.n; i++)
    {
        if (!G.visited[i])
        {
            BFSvisit(&G, i, &Q);
        }
    }
    printf("\n");
}

//function to visit a node of graph during BFS traversal
void BFSvisit(GRAPH *gp, int v, QUEUE *qp)
{
    int front = 0;
    gp->visited[v] = 1;
    *qp = enqueue(*qp, v);
    while (!isEmptyQueue(*qp))
    {

        *qp = dequeue(*qp, &front);
        printf("%d ", front);
        for (int i = 0; i < gp->n; i++)
        {
            if (gp->adj[front][i] != 0 && gp->visited[i] == 0)
            {

                gp->visited[i] = 1;
                *qp = enqueue(*qp, i);
            }
        }
    }
}

//function to find MST of graph using Kruskal's algorithm
void MST(GRAPH G)
{

    int idx = 0;
    UNION_FIND F = createUF(G.n);

    for (int i = 0; i < G.n; i++)
        F = makeSetUF(F, i, &idx);

    mergesort(&G.edges[0], G.m);
    int sum = 0;

    for (int i = 0; i < G.m; i++)
    {

        int v1 = G.edges[i].v1;
        int v2 = G.edges[i].v2;
        if (findUF(F, v1)->value != findUF(F, v2)->value)
        {

            unionUF(F, v1, v2);
            printf("%d %d %d\n", G.edges[i].v1, G.edges[i].v2, G.edges[i].w);
            sum += G.edges[i].w;
        }
    }
    printf("%d\n", sum);
}

//function to implement mergesort
void mergesort(EDGE *edges, int n)
{

    if (n < 2)
        return;
    int mid = n / 2;
    EDGE *left = (EDGE *)malloc(mid * sizeof(EDGE));
    EDGE *right = (EDGE *)malloc((n - mid) * sizeof(EDGE));
    for (int i = 0; i < mid; i++)
        left[i] = edges[i];
    for (int i = mid; i < n; i++)
        right[i - mid] = edges[i];
    mergesort(left, mid);
    mergesort(right, n - mid);
    merge(left, right, edges, mid, n - mid);
    free(left);
    free(right);
}

//function to implement merge for mergesort
void merge(EDGE *left, EDGE *right, EDGE *edges, int l, int r)
{

    int i = 0, j = 0, k = 0;
    while (i < l && j < r)
    {
        if (left[i].w < right[j].w)
        {
            edges[k] = left[i];
            i++;
        }
        else
        {
            edges[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < l)
    {
        edges[k] = left[i];
        i++;
        k++;
    }
    while (j < r)
    {
        edges[k] = right[j];
        j++;
        k++;
    }
}

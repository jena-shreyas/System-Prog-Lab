#include <stdio.h>
#include <graph.h>


int main(){

    GRAPH G = readGraph("graph.txt");
    printf("OUTPUT OF DFS TRAVERSAL:\n\n");
    DFS(G);
    for (int i=0;i<G.n;i++)
        G.visited[i]=0;
    printf("\nOUTPUT OF BFS TRAVERSAL:\n\n");
    BFS(G);
    printf("\nOUTPUT OF MST USING KRUSKAL:\n\n");
    MST(G);
    return 0;
}
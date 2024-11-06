#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_KEY 99
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) { \
        printf("Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
typedef struct edge_s *Edge;
typedef struct edge_s {
    int src;
    int dest;
    int weight;
} edge_t;
typedef struct graph_s *Graph;
typedef struct graph_s {
    int numVertices;
    int numEdges;
    Edge edge;
} graph_t;
typedef struct subset_s *Subset;
typedef struct subset_s {
    int parent;
    int key;
    int visited;
} subset_t;
Graph createAGraph(int, int);
void addEdge(Graph, int, int, int);
void Prim(Graph, int);

int main(void){
    Graph graph = createAGraph(7, 9);
    addEdge(graph, 0, 1, 28);
    addEdge(graph, 0, 5, 10);
    addEdge(graph, 1, 2, 16);
    addEdge(graph, 1, 6, 14);
    addEdge(graph, 2, 3, 12);
    addEdge(graph, 3, 4, 22);
    addEdge(graph, 3, 6, 18);
    addEdge(graph, 4, 5, 25);
    addEdge(graph, 4, 6, 24);
    Prim(graph, 2);
    return 0;
}

Graph createAGraph(int v, int e){
    Graph graph;
    MALLOC(graph, sizeof(*graph));
    graph->numVertices = v;
    graph->numEdges = e;
    MALLOC(graph->edge, e * sizeof(*graph->edge));
    return graph;
}

void addEdge(Graph graph, int s, int d, int w){
    static int count = 0;
    graph->edge[count].src = s;
    graph->edge[count].dest = d;
    graph->edge[count].weight = w;
    count++;
}

void Prim(Graph graph, int v){
    int V = graph->numVertices;
    int E = graph->numEdges;
    Edge result;
    MALLOC(result, (V - 1) *sizeof(*result));
    Subset subset;
    MALLOC(subset, V * sizeof(*subset));
    for(int i = 0; i < V; i++){
        subset[i].parent = -1;
        subset[i].key = MAX_KEY;
        subset[i].visited = FALSE;
    }
    subset[v].key = 0;
    subset[v].visited = TRUE;
    int j = 0, minCost = 0;
    while(j < V - 1){
        for(int i = 0; i < E; i++)
            if(graph->edge[i].src == v 
                && graph->edge[i].weight < subset[graph->edge[i].dest].key
                && subset[graph->edge[i].dest].visited == FALSE){
                    subset[graph->edge[i].dest].parent = graph->edge[i].src;
                    subset[graph->edge[i].dest].key = graph->edge[i].weight;
            }else if(graph->edge[i].dest == v 
                && graph->edge[i].weight < subset[graph->edge[i].src].key
                && subset[graph->edge[i].src].visited == FALSE){
                    subset[graph->edge[i].src].parent = graph->edge[i].dest;
                    subset[graph->edge[i].src].key = graph->edge[i].weight;
            }
        int min = MAX_KEY;
        for(int i = 0; i < V; i++)
            if(subset[i].visited == FALSE && subset[i].key < min){
                min = subset[i].key;
                v = i;
            }
        if(v < subset[v].parent){
            result[j].src = v;
            result[j].dest = subset[v].parent;
        }else if(v > subset[v].parent){
            result[j].src = subset[v].parent;
            result[j].dest = v;
        }
        subset[v].visited = TRUE;
        result[j].weight = subset[v].key;
        minCost += result[j].weight;
        j++;
    }
    for(int i = 0; i < V - 1; i++)
        printf("%d %d -> %d\n", result[i].src, result[i].dest, result[i].weight);
    printf("Minimum Cost Spanning Tree : %d\n", minCost);
}

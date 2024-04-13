#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define INFINITE 9999
#define MALLOC(p, s) \
    if (!((p) = malloc(s))){ \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
typedef struct edge_s * Edge;
typedef struct edge_s {
    int src;
    int dest;
    int weight;
} edge_t;
typedef struct subset_s * Subset;
typedef struct subset_s {
    int parent;
    int rank;
} subset_t;
typedef struct graph_s * Graph;
typedef struct graph_s {
    int numVertices;
    int numEdges;
    Edge edge;
    Subset ** Array;
} graph_t;
Graph createGraph(int, int);
Subset ** makeArray(int);
void addEdge(Graph, int, int, int);
void FloydWarshall(Graph);
void printArray(Graph);

int main(void){
    // Graph graph = createGraph(3, 5);
    // addEdge(graph, 0, 1, 4);
    // addEdge(graph, 0, 2, 11);
    // addEdge(graph, 1, 0, 6);
    // addEdge(graph, 1, 2, 2);
    // addEdge(graph, 2, 0, 3);
    Graph graph = createGraph(4, 7);
    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 2, 6);
    addEdge(graph, 0, 3, 8);
    addEdge(graph, 1, 2, -2);
    addEdge(graph, 1, 3, 3);
    addEdge(graph, 2, 0, 4);
    addEdge(graph, 2, 3, 1);
    // Graph graph = createGraph(8, 11);
    // addEdge(graph, 4, 5, 250);
    // addEdge(graph, 1, 0, 300);
    // addEdge(graph, 2, 1, 800);
    // addEdge(graph, 5, 6, 900);
    // addEdge(graph, 2, 0, 1000);
    // addEdge(graph, 6, 7, 1000);
    // addEdge(graph, 5, 3, 1000);
    // addEdge(graph, 3, 2, 1200);
    // addEdge(graph, 5, 7, 1400);
    // addEdge(graph, 4, 3, 1500);
    // addEdge(graph, 7, 0, 1700);
    FloydWarshall(graph);
    return 0;
}

Graph createGraph(int v, int e){
    Graph graph;
    MALLOC(graph, sizeof(* graph));
    graph->numVertices = v;
    graph->numEdges = e;
    MALLOC(graph->edge, e * sizeof(* graph->edge));
    graph->Array = makeArray(v);
    return graph;
}

Subset ** makeArray(int v){
    Subset ** array;
    MALLOC(array, v * sizeof(* array));
    for(int i = 0; i < v; i++){
        MALLOC(array[i], v * sizeof(* array[i]));
        for(int j = 0; j < v; j++){
            MALLOC(array[i][j], sizeof(* array[i][j]));
            if(i == j)
                array[i][j]->rank = 0;
            else
                array[i][j]->rank = INFINITE;
            array[i][j]->parent = -1;
        }
    }
    return array;
}

void addEdge(Graph graph, int s, int d, int w){
    static int count = 0;
    graph->edge[count].src = s;
    graph->edge[count].dest = d;
    graph->edge[count].weight = w;
    graph->Array[s][d]->rank = w;
    graph->Array[s][d]->parent = s;
    count++;
}

void FloydWarshall(Graph graph){
    int V = graph->numVertices;
    // printArray(graph);
    for(int k = 0; k < V; k++){
        for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                if(i == j || graph->Array[i][k]->rank == INFINITE || graph->Array[k][j]->rank == INFINITE) 
                    continue;
                if(graph->Array[i][k]->rank + graph->Array[k][j]->rank < graph->Array[i][j]->rank){
                    graph->Array[i][j]->rank = graph->Array[i][k]->rank + graph->Array[k][j]->rank;
                    graph->Array[i][j]->parent = k;
                }
            }
        }
        // printArray(graph);
    }
    printArray(graph);
}

void printArray(Graph graph){
    for(int i = 0; i < graph->numVertices; i++){
        for(int j = 0; j < graph->numVertices; j++)
            printf("%4d ", graph->Array[i][j]->rank);
        printf("\n");
    }
    printf("-----------------------\n");
    for(int i = 0; i < graph->numVertices; i++){
        for(int j = 0; j < graph->numVertices; j++)
            printf("%4d ", graph->Array[i][j]->parent);
        printf("\n");
    }
    printf("-----------------------\n");
}
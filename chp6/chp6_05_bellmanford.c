#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define INFINITE 99
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
typedef struct edge_s * Edge;
typedef struct edge_s {
    int src;
    int dest;
    int weight;
} edge_t;
typedef struct graph_s * Graph;
typedef struct graph_s {
    int numVertices;
    int numEdges;
    Edge edge;
} graph_t;
typedef struct subset_s * Subset;
typedef struct subset_s {
    int parent;
    int rank;
} subset_t;
Graph createAGraph(int, int);
void addEdge(Graph, int, int, int);
int cmp1(const void *, const void *);
int cmp2(const void *, const void *);
void BellmanFord(Graph, int);
void path(Subset, int);
void printGraph(Graph);
void printSubset(Subset, int);
int count = 0;

int main(void) {
    Graph graph = createAGraph(6, 10);
    addEdge(graph, 1, 4, -4);
    addEdge(graph, 2, 4, -3);
    addEdge(graph, 2, 5, -2);
    addEdge(graph, 4, 3, 1);
    addEdge(graph, 5, 0, 3);
    addEdge(graph, 3, 2, 4);
    addEdge(graph, 0, 1, 5);
    addEdge(graph, 1, 2, 6);
    addEdge(graph, 4, 5, 6);
    addEdge(graph, 5, 1, 7);
    BellmanFord(graph, 0);
    // Graph graph = createAGraph(6, 11);
    // addEdge(graph, 0, 1, 50);
    // addEdge(graph, 0, 2, 45);
    // addEdge(graph, 0, 3, 10);
    // addEdge(graph, 1, 2, 10);
    // addEdge(graph, 1, 3, 15);
    // addEdge(graph, 2, 4, 30);
    // addEdge(graph, 3, 0, 20);
    // addEdge(graph, 3, 4, 15);
    // addEdge(graph, 4, 1, 20);
    // addEdge(graph, 4, 2, 35);
    // addEdge(graph, 5, 4, 3);
    // BellmanFord(graph, 0);
    // Graph graph = createAGraph(8, 11);
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
    // BellmanFord(graph, 4);
    return 0;
}

Graph createAGraph(int v, int e) {
    Graph graph;
    MALLOC(graph, sizeof(* graph));
    graph->numVertices = v;
    graph->numEdges = e;
    MALLOC(graph->edge, e * sizeof(* graph->edge));
    return graph;
}

void addEdge(Graph graph, int s, int d, int w) {
    graph->edge[count].src = s;
    graph->edge[count].dest = d;
    graph->edge[count].weight = w;
    count++;
}

void BellmanFord(Graph graph, int v){
    int V = graph->numVertices;
    int E = graph->numEdges;
    Subset subset;
    MALLOC(subset, V * sizeof(* subset));
    for(int i = 0; i < V; i++){
        subset[i].parent = -1;
        subset[i].rank = INFINITE;
    }
    subset[v].rank = 0;
    // printGraph(graph);
    qsort(graph->edge, graph->numEdges, sizeof(graph->edge[0]), cmp1);
    qsort(graph->edge, graph->numEdges, sizeof(graph->edge[0]), cmp2);
    // printGraph(graph);
    // printSubset(subset, V);
    for(int i = 0; i < V - 1; i++){
        for(int j = 0; j < E; j++){
            // printf("%d %d %d\n", graph->edge[j].src, graph->edge[j].dest, graph->edge[j].weight);
            // printf("%d %d\n", graph->edge[j].weight + subset[graph->edge[j].src].rank, subset[graph->edge[j].dest].rank);
            if(graph->edge[j].weight + subset[graph->edge[j].src].rank < subset[graph->edge[j].dest].rank){
                subset[graph->edge[j].dest].parent = graph->edge[j].src;
                subset[graph->edge[j].dest].rank = graph->edge[j].weight + subset[graph->edge[j].src].rank;
            }
            // printSubset(subset, V);
        }
    }
    printSubset(subset, V);
    for(int i = 0; i < V; i++){
        printf("Vertex %d(%d) : ", i, subset[i].rank);
        path(subset, i);
        printf("%d \n", i);
    }
}

void path(Subset s, int v){
    if((s+v)->parent == -1) return;
    path(s, (s+v)->parent);
    printf("%d ", (s+v)->parent);
}

int cmp1(const void * a, const void * b){
    return ((Edge)a)->dest - ((Edge)b)->dest;
}

int cmp2(const void * a, const void * b){
    return ((Edge)a)->src - ((Edge)b)->src;
}

void printGraph(Graph graph) {
    for (int i = 0; i < graph->numEdges; i++) 
        printf("%d %d %d\n", graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
    printf("--------------------\n");
}

void printSubset(Subset s, int v){
    for(int i = 0; i < v; i++)
        printf("%2d ", i);
    printf("\n");
    for(int i = 0; i < v; i++)
        printf("%2d ", (s+i)->parent);
    printf("\n");
    for(int i = 0; i < v; i++)
        printf("%2d ", (s+i)->rank);
    printf("\n");
    printf("--------------------\n");
}
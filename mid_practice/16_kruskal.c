#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
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
    int rank;
} subset_t;
Graph createAGraph(int, int);
void addEdge(Graph, int, int, int);
int cmp(const void *, const void *);
int find(Subset, int);
void Kruskal(Graph);

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
    Kruskal(graph);
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

int cmp(const void *a, const void *b){
    return ((Edge)a)->weight - ((Edge)b)->weight;
}

int find(Subset subset, int i){
    if((subset + i)->parent == -1)
        return i;
    else
        (subset + i)->parent = find(subset, (subset + i)->parent);
}

void Kruskal(Graph graph){
    int V = graph->numVertices;
    Edge result;
    MALLOC(result, (V - 1) * sizeof(*result));
    Subset subset;
    MALLOC(subset, V * sizeof(*subset));
    for(int i = 0; i < V; i++){
        subset[i].parent = -1;
        subset[i].rank = 0;
    }
    qsort(graph->edge, graph->numEdges, sizeof(graph->edge[0]), cmp);
    int j = 0, k = 0, temp = 0, minCost = 0;
    while(j < V - 1){
        int x = find(subset, graph->edge[k].src);
        int y = find(subset, graph->edge[k].dest);
        if(x != y){
            if(x > y)
                SWAP(x, y, temp);
            if(subset[x].rank < subset[y].rank){
                subset[x].parent = y;
            }else if(subset[x].rank > subset[y].rank){
                subset[y].parent = x;
            }else{
                subset[x].parent = y;
                subset[y].rank += 1;
            }
            result[j].src = graph->edge[k].src;
            result[j].dest = graph->edge[k].dest;
            result[j].weight = graph->edge[k].weight;
            minCost += result[j].weight;
            j++;
        }
        k++;
    }
    for(int i = 0; i < V - 1; i++)
        printf("%d %d -> %d\n", result[i].src, result[i].dest, result[i].weight);
    printf("Minimum Cost Spanning Tree : %d\n", minCost);
}

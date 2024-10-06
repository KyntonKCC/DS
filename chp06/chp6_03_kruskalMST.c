#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))
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
int cmp(const void *,const void *);
int find(Subset, int);
void Kruskal(Graph);
void printGraph(Graph);
void printSubset(Subset, int);

/*
    A--28--B--16--C         A      B--16--C
    |      |      |         |      |      |
    |      14     |         |      14     |
    |      |      |         |      |      |
    |      G      |         |      G      |
    |      |\     12  --->  |             12
    10     | \    |         10            |
    |      |  18  |         |             |
    |      |   \  |         |             |
    |      24   \ |         |             |
    |      |     \|         |             |
    F--25--E--22--D         F--25--E--22--D

        B---3---E               B       E
       /|\     /|\             / \     / \
     1/ | 1   / | \3         1/   1   /   \3
     /  |  \ /  |  \         /     \ /     \
    A   3   /   2   F --->  A       /       F
     \  |  / \  |  /         \     / \     
     2\ | 1   \ | /4         2\   1   \   
       \|/     \|/             \ /     \ 
        C---2---D               C       D

        B---8---C---7---D              B       C---7---D 
       /|       |\      |\            /        |\       \ 
     4/ |       2 \     | \9        4/         2 \       \9 
     /  |       |  \    |  \        /          |  \       \  
    A   11      I   4   14  E ---> A           I   4       E 
     \  |    __/|    \  |  /        \               \        
     8\ | __7   6     \ | /10       8\               \    
       \|/      |      \|/            \               \   
        H---1---G---2---F              H---1---G---2---F  
*/

int main(void) {
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
    // Graph graph = createAGraph(6, 10);
    // addEdge(graph, 0, 1, 1);
    // addEdge(graph, 0, 2, 2);
    // addEdge(graph, 1, 2, 3);
    // addEdge(graph, 1, 3, 1);
    // addEdge(graph, 1, 4, 3);
    // addEdge(graph, 2, 3, 2);
    // addEdge(graph, 2, 4, 1);
    // addEdge(graph, 3, 4, 2);
    // addEdge(graph, 3, 5, 4);
    // addEdge(graph, 4, 5, 3);
    // Graph graph = createAGraph(9, 14);
    // addEdge(graph, 0, 1, 4);
    // addEdge(graph, 0, 7, 8);
    // addEdge(graph, 1, 2, 8);
    // addEdge(graph, 1, 7, 11);
    // addEdge(graph, 2, 3, 7);
    // addEdge(graph, 2, 5, 4);
    // addEdge(graph, 2, 8, 2);
    // addEdge(graph, 3, 4, 9);
    // addEdge(graph, 3, 5, 14);
    // addEdge(graph, 4, 5, 10);
    // addEdge(graph, 5, 6, 2);
    // addEdge(graph, 6, 7, 1);
    // addEdge(graph, 6, 8, 6);
    // addEdge(graph, 7, 8, 7);
    Kruskal(graph);
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
    static int count = 0;
    graph->edge[count].src = s;
    graph->edge[count].dest = d;
    graph->edge[count].weight = w;
    count++;
}

int cmp(const void * a, const void * b){
    return ((Edge)a)->weight - ((Edge)b)->weight;
}

int find(Subset subsets, int i){
    if((subsets+i)->parent == -1){
        // printf("Find\n");
        return i;
    }else{
        // printf("Cul ");
        (subsets+i)->parent = find(subsets, (subsets+i)->parent);
    }
}

void Kruskal(Graph graph){
    int V = graph->numVertices;
    Edge result;
    MALLOC(result, (V - 1) * sizeof(* result));
    Subset subset;
    MALLOC(subset, V * sizeof(* subset));
    for(int i = 0; i < V; i++){
        subset[i].parent = -1;
        subset[i].rank = 0;
    }
    // printGraph(graph);
    qsort(graph->edge, graph->numEdges, sizeof(graph->edge[0]), cmp);
    // printGraph(graph);
    // printSubset(subset, V);
    int j = 0, k = 0, temp = 0, minCost = 0;
    while(j < V - 1){
        int x = find(subset, graph->edge[k].src);
        int y = find(subset, graph->edge[k].dest);
        // printf("(j,k) = (%d %d)\n", j, k);
        // printf("turn --> %d %d\n", graph->edge[k].src, graph->edge[k].dest);
        // printf("(x,y) = (%d %d)\n", x, y);
        if(x != y){
            if(x > y) SWAP(x, y, temp);
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
        // printSubset(subset, V);
    }
    for(int i = 0; i < V - 1; i++)
        printf("%d %d -> %d\n", result[i].src, result[i].dest, result[i].weight);
    printf("Minimum Cost Spanning Tree : %d\n", minCost);
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
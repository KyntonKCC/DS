#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MALLOC(p, s) \
    if (!((p) = malloc(s))){ \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
typedef struct node_s * Node;
typedef struct node_s {
    int vertice;
    Node next;
} node_t;
typedef struct edge_s * Edge;
typedef struct edge_s {
    int src;
    int dest;
} edge_t;
typedef struct graph_s * Graph;
typedef struct graph_s {
    int numVertices;
    int numEdges;
    Edge edge;
    int * adjListsCount;
    Node * adjLists;
} graph_t;
Graph createGraph(int, int);
Node createNode(int);
void addEdge(Graph, int, int);
void printGraph(Graph);

int main(){
    Graph graph = createGraph(6, 8);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);
    printGraph(graph);
    return 0;
}

Graph createGraph(int v, int e){
    Graph graph;
    MALLOC(graph, sizeof(* graph));
    graph->numVertices = v;
    graph->numEdges = e;
    MALLOC(graph->edge, e * sizeof(* graph->edge));
    MALLOC(graph->adjListsCount, v * sizeof(* graph->adjListsCount));
    MALLOC(graph->adjLists, v * sizeof(* graph->adjLists));
    for(int i = 0; i < v; i++){
        graph->adjListsCount[i] = 0;
        graph->adjLists[i] = NULL;
    }
    return graph;
}

Node createNode(int d){
    Node newNode;
    MALLOC(newNode, sizeof(* newNode));
    newNode->vertice = d;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph graph, int s, int d){
    static int count = 0;
    Node newNode = createNode(d);
    newNode->next = graph->adjLists[s];
    graph->adjLists[s] = newNode;
    graph->edge[count].src = s;
    graph->edge[count].dest = d;
    graph->adjListsCount[d] += 1;
}

void printGraph(Graph graph){
    for (int i = 0; i < graph->numVertices; i++) {
        Node temp = graph->adjLists[i];
        printf("Vertex %d(%d) : ", i, graph->adjListsCount[i]);
        while (temp) {
            printf("%d -> ", temp->vertice);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    printf("-----------------------------------\n");
}
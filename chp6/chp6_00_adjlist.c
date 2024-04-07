#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
typedef struct node_s * Node;
typedef struct node_s {
    int vertex;
    Node next;
} node_t;
typedef struct graph_s * Graph;
typedef struct graph_s {
    int numVertices;
    Node * adjLists;
} graph_t;
Graph createAGraph(int);
Node createNode(int);
void addEdge(Graph, int, int);
void printGraph(Graph);

/*
       0
      /|\
     / | \
    1--|--2
     \ | /
      \|/
       3
*/

int main(void) {
    Graph graph = createAGraph(4);
    addEdge(graph, 0, 2);
    printGraph(graph);
    addEdge(graph, 0, 1);
    printGraph(graph);
    addEdge(graph, 2, 3);
    printGraph(graph);
    addEdge(graph, 1, 3);
    printGraph(graph);
    addEdge(graph, 1, 2);
    printGraph(graph);
    addEdge(graph, 0, 3);
    printGraph(graph);
    return 0;
}

Graph createAGraph(int vertices) {
    Graph graph;
    MALLOC(graph, sizeof(* graph));
    graph->numVertices = vertices;
    MALLOC(graph->adjLists, vertices * sizeof(Node));
    for (int i = 0; i < vertices; i++) 
        graph->adjLists[i] = NULL;
    return graph;
}

Node createNode(int v) {
    Node newNode;
    MALLOC(newNode, sizeof(* newNode));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph graph, int s, int d) {
    Node newNode;
    newNode = createNode(d);
    newNode->next = graph->adjLists[s];
    graph->adjLists[s] = newNode;
    newNode = createNode(s);
    newNode->next = graph->adjLists[d];
    graph->adjLists[d] = newNode;
}

void printGraph(Graph graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node temp = graph->adjLists[i];
        printf("Vertex %d : ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
    printf("-------------------------\n");
}

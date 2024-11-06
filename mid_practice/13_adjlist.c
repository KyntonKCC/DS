#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p, s) \
    if (!((p) = malloc(s))) { \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
typedef struct node_s *Node;
typedef struct node_s{
    int vertex;
    Node next;
}node_t;
typedef struct graph_s *Graph;
typedef struct graph_s{
    int numVertices;
    Node *adjList;
}graph_t;
Graph createAGraph(int);
Node createNode(int);
void addEdge(Graph, int, int);
void printGraph(Graph);

int main(void){
    Graph graph = createAGraph(4);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 2);
    addEdge(graph, 0, 3);
    return 0;
}

Graph createAGraph(int vertices){
    Graph graph;
    MALLOC(graph, sizeof(*graph));
    graph->numVertices = vertices;
    MALLOC(graph->adjList, vertices * sizeof(*graph->adjList));
    for(int i = 0; i < vertices; i++)
        graph->adjList[i] = NULL;
    return graph;
}

Node createNode(int v){
    Node newNode;
    MALLOC(newNode, sizeof(*newNode));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph graph, int s, int d){
    Node newNode;
    newNode = createNode(d);
    newNode->next = graph->adjList[s];
    graph->adjList[s] = newNode;
    newNode = createNode(s);
    newNode->next = graph->adjList[d];
    graph->adjList[d] = newNode;
    printGraph(graph);
}

void printGraph(Graph graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node temp = graph->adjList[i];
        printf("Vertex %d : ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    printf("-------------------------\n");
}

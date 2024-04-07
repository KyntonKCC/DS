#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_STACK_SIZE 50
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
    int * visited;
    Node * adjLists;
} graph_t;
Graph createAGraph(int);
Node createNode(int);
void addEdge(Graph, int, int);
void printGraph(Graph);
void BFS(Graph, int);
int queue[MAX_STACK_SIZE];
int front = -1, rear = -1;
void addq(int);
int deleteq();
void queueFull();
int queueEmpty();
void printQueue();

/*
        __0__
       /     \
      1       2
     / \     / \ 
    3   4   5   6
     \   \ /   /     
      \___7___/
*/

int main(void) {
    Graph graph = createAGraph(8);
    addEdge(graph, 6, 7);
    addEdge(graph, 2, 6);
    addEdge(graph, 5, 7);
    addEdge(graph, 4, 7);
    addEdge(graph, 3, 7);
    addEdge(graph, 2, 5);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 3);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 1);
    printGraph(graph);
    BFS(graph, 0);
    return 0;
}

Graph createAGraph(int vertices) {
    Graph graph;
    MALLOC(graph, sizeof(* graph));
    graph->numVertices = vertices;
    MALLOC(graph->adjLists, vertices * sizeof(Node));
    MALLOC(graph->visited, vertices * sizeof(int));
    for (int i = 0; i < vertices; i++){
        graph->adjLists[i] = NULL;
        graph->visited[i] = FALSE;
    }
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
        printf("NULL\n");
    }
    printf("-----------------------------------\n");
}

void BFS(Graph graph, int startVertex){
    graph->visited[startVertex] = TRUE;
    addq(startVertex);
    // printQueue();
    while(front != rear){
        int currentVertex = deleteq();
        printf("Visited : %d\n", currentVertex);
        Node temp = graph->adjLists[currentVertex];
        while(temp){
            int adjVertex = temp->vertex;
            if(graph->visited[adjVertex] == FALSE){
                graph->visited[adjVertex] = TRUE;
                addq(adjVertex);
                // printQueue();   
            }
            temp = temp->next;
        }
    }
}

void addq(int item){
    if(rear == MAX_STACK_SIZE - 1)
        queueFull();
    else
        queue[++rear] = item;
}

int deleteq(){
    if(front == rear)
        return queueEmpty();
    else
        return queue[++front];
}

void queueFull(){
    fprintf(stderr, "Queue is full, cannot add element\n");
    // exit(EXIT_FAILURE);
}

int queueEmpty(){
    fprintf(stderr, "Queue is empty, cannot delete element\n");
    // exit(EXIT_FAILURE);
}

void printQueue(){
    for(int i = front + 1; i < rear + 1; i++)
        printf("%d ", queue[i]);
    printf("\n");
}
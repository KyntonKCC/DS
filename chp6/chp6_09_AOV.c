#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 50
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
    int * visited;
    int * adjListsCount;
    Node * adjLists;
    Edge edge;
} graph_t;
Graph createGraph(int, int);
Node createNode(int);
void addEdge(Graph, int, int);
void AOV(Graph);
void printGraph(Graph);
int queue[MAX_SIZE];
void addq(int);
int deleteq();
void queueFull();
int queueEmpty();
void printQueue(Graph);
int front = -1, rear = -1;

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
    // Graph graph = createGraph(15, 15);
    // addEdge(graph, 0, 2);
    // addEdge(graph, 1, 2);
    // addEdge(graph, 2, 7);
    // addEdge(graph, 2, 6);
    // addEdge(graph, 3, 4);
    // addEdge(graph, 4, 5);
    // addEdge(graph, 5, 6);
    // addEdge(graph, 5, 14);
    // addEdge(graph, 6, 8);
    // addEdge(graph, 6, 9);
    // addEdge(graph, 6, 11);
    // addEdge(graph, 6, 12);
    // addEdge(graph, 7, 8);
    // addEdge(graph, 9, 10);
    // addEdge(graph, 12, 13);
    AOV(graph);
    return 0;
}

Graph createGraph(int v, int e){
    Graph graph;
    MALLOC(graph, sizeof(* graph));
    graph->numVertices = v;
    graph->numEdges = e;
    MALLOC(graph->visited, v * sizeof(* graph->visited));
    MALLOC(graph->adjListsCount, v * sizeof(* graph->adjListsCount));
    MALLOC(graph->adjLists, v * sizeof(* graph->adjLists));
    MALLOC(graph->edge, e * sizeof(* graph->edge));
    for(int i = 0; i < v; i++){
        graph->visited[i] = FALSE;
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

void AOV(Graph graph){
    printGraph(graph);
    // printQueue(graph);
    do{
        int keep = 0;
        for(int i = graph->numVertices - 1; i >= 0; i--)
            if(graph->visited[i] == FALSE && graph->adjListsCount[i] == 0){
                graph->visited[i] = TRUE;
                addq(i);
                keep = i;
                break;
            }
        Node temp = graph->adjLists[keep];
        while(temp){
            graph->adjListsCount[temp->vertice] -= 1;
            temp = temp->next;
        }
        // printQueue(graph);
    }while(rear != graph->numVertices - 1);
    printQueue(graph);
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

void addq(int item){
    if(rear == MAX_SIZE - 1)
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

void printQueue(Graph graph){
    // for(int i = 0; i < graph->numVertices; i++)
    //     printf("%2d ", graph->visited[i]);
    // printf("\n");
    // for(int i = 0; i < graph->numVertices; i++)
    //     printf("%2d ", graph->adjListsCount[i]);
    // printf("\n");
    for(int i = front + 1; i < rear + 1; i++)
        printf("%2d ", queue[i]);
    printf("\n");
    printf("-----------------------------------\n");
}
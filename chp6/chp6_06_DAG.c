#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 50
#define INFINITE 99
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
    int * visited;
    int * adjListCount;
    Node * adjLists;
    Edge edge;
} graph_t;
typedef struct subset_s * Subset;
typedef struct subset_s {
    int parent;
    int rank;
} subset_t;
Graph createAGraph(int, int);
Node createNode(int);
void addEdge(Graph, int, int, int);
void createQueue(Graph);
void DAG(Graph, int);
void path(Subset, int);
void printGraph(Graph);
void printSubset(Subset, int);
int queue[MAX_SIZE];
void addq(int);
int deleteq();
void queueFull();
int queueEmpty();
void printQueue(Graph);
int front = -1, rear = -1;

int main(void) {
    Graph graph = createAGraph(7, 11);
    addEdge(graph, 1, 3, -4);
    addEdge(graph, 4, 3, -3);
    addEdge(graph, 0, 2, -2);
    addEdge(graph, 4, 6, -2);
    addEdge(graph, 3, 6, 2);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 0, 1, 3);
    addEdge(graph, 1, 4, 4);
    addEdge(graph, 2, 4, 5);
    addEdge(graph, 2, 5, 6);
    addEdge(graph, 3, 5, 8);
    DAG(graph, 0);
    // Graph graph = createAGraph(7, 10);
    // addEdge(graph, 2, 1, -2);
    // addEdge(graph, 3, 2, -2);
    // addEdge(graph, 1, 4, -1);
    // addEdge(graph, 3, 5, -1);
    // addEdge(graph, 2, 4, 1);
    // addEdge(graph, 4, 6, 3);
    // addEdge(graph, 5, 6, 3);
    // addEdge(graph, 0, 2, 5);
    // addEdge(graph, 0, 3, 5);
    // addEdge(graph, 0, 1, 6);
    // DAG(graph, 0);
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
    // DAG(graph, 4);
    return 0;
}

Graph createAGraph(int v, int e) {
    Graph graph;
    MALLOC(graph, sizeof(* graph));
    graph->numVertices = v;
    graph->numEdges = e;
    MALLOC(graph->visited, v * sizeof(* graph->visited));
    MALLOC(graph->adjListCount, v * sizeof(* graph->adjListCount));
    MALLOC(graph->adjLists, v * sizeof(* graph->adjLists));
    MALLOC(graph->edge, e * sizeof(* graph->edge));
    for(int i = 0; i < v; i++){
        graph->visited[i] = FALSE;
        graph->adjListCount[i] = 0;
        graph->adjLists[i] = NULL;
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

void addEdge(Graph graph, int s, int d, int w) {
    static int count = 0;
    Node newNode = createNode(d);
    newNode->next = graph->adjLists[s];
    graph->adjLists[s] = newNode;
    graph->edge[count].src = s;
    graph->edge[count].dest = d;
    graph->edge[count].weight = w;
    graph->adjListCount[d] += 1;
    count++;
}

void createQueue(Graph graph){
    do{
        int keep = 0;
        for(int i = 0; i < graph->numVertices; i++)
            if(graph->visited[i] == FALSE && graph->adjListCount[i] == 0){
                graph->visited[i] = TRUE;
                addq(i);
                keep = i;
                break;
            }
        Node temp = graph->adjLists[keep];
        while(temp){
            graph->adjListCount[temp->vertex] -= 1;
            temp = temp->next;
        }
        // printQueue(graph);
    }while(rear != graph->numVertices - 1);
}

void DAG(Graph graph, int v){
    int V = graph->numVertices;
    int E = graph->numEdges;
    Subset subset;
    MALLOC(subset, V * sizeof(* subset));
    for(int i = 0; i < V; i++){
        subset[i].parent = -1;
        subset[i].rank = INFINITE;
    }
    subset[v].rank = 0;
    createQueue(graph);
    // printGraph(graph);
    // printSubset(subset, V);
    // printQueue(graph);
    while(front != rear){
        int i = deleteq();
        for(int j = 0; j < E; j++)
            if(graph->edge[j].weight + subset[graph->edge[j].src].rank < subset[graph->edge[j].dest].rank){
                subset[graph->edge[j].dest].parent = graph->edge[j].src;
                subset[graph->edge[j].dest].rank = graph->edge[j].weight + subset[graph->edge[j].src].rank;
            }
        // printSubset(subset, V);
    }
    // printSubset(subset, V);
    for(int i = 0; i < V; i++){
        printf("Vertex %d(%2d) : ", i, subset[i].rank);
        if(subset[i].rank == INFINITE){
            printf("No Path\n");
        }else{
            path(subset, i);
            printf("%d \n", i);
        }
    }
}

void path(Subset s, int v){
    if((s+v)->parent == -1) return;
    path(s, (s+v)->parent);
    printf("%d ", (s+v)->parent);
}

void printGraph(Graph graph) {
    for (int i = 0; i < graph->numEdges; i++) 
        printf("%d %d %d\n", graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);
    printf("-----------------------------------\n");
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
    for(int i = 0; i < graph->numVertices; i++)
        printf("%2d ", graph->visited[i]);
    printf("\n");
    for(int i = 0; i < graph->numVertices; i++)
        printf("%2d ", graph->adjListCount[i]);
    printf("\n");
    for(int i = front + 1; i < rear + 1; i++)
        printf("%2d ", queue[i]);
    printf("\n");
    printf("-----------------------------------\n");
}
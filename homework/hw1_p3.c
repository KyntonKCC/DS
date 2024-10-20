#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 50
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
void BFS(Graph, int, FILE *);
int queue[MAX_SIZE];
void addq(int);
int deleteq();
void queueFull();
int queueEmpty();
void printQueue();
int front = -1, rear = -1;

int main(void) {
    FILE *fileinput, *fileoutput;
    char fileinputname[] = "hw1_p3_input1.txt";
    char fileoutputname[] = "hw1_p3_output1.txt";
    fileinput = fopen(fileinputname, "r");
    fileoutput = fopen(fileoutputname, "w");
    if(fileinput == NULL || fileoutput == NULL){
        printf("Fail to open file\n");
        return 1;
    }

    int N;
    fscanf(fileinput, "%d", &N);
    int table[N][N];
    Graph graph = createAGraph(N);
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            fscanf(fileinput, "%d", &table[i][j]);
    for(int i = N - 1; i >= 0; i--)
        for(int j = N - 1; j >= 0; j--)
            if(table[i][j] == 1)
                addEdge(graph, i, j);
    // printGraph(graph);
    BFS(graph, 0, fileoutput);

    fclose(fileinput);
    fclose(fileoutput);
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
    // newNode = createNode(s);
    // newNode->next = graph->adjLists[d];
    // graph->adjLists[d] = newNode;
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

void BFS(Graph graph, int startVertex, FILE *fileoutput){
    graph->visited[startVertex] = TRUE;
    addq(startVertex);
    // printQueue();
    while(front != rear){
        int currentVertex = deleteq();
        // printf("Visited : %d\n", currentVertex);
        fprintf(fileoutput, "%d ", currentVertex + 1);
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
    exit(EXIT_FAILURE);
}

int queueEmpty(){
    fprintf(stderr, "Queue is empty, cannot delete element\n");
    exit(EXIT_FAILURE);
}

void printQueue(){
    for(int i = front + 1; i < rear + 1; i++)
        printf("%d ", queue[i]);
    printf("\n");
}
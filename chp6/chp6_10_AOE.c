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
    int dur;
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
    int * adjListsCount;
    int * status;
    Node * adjLists;
    Edge edge;
} graph_t;
Graph createGraph(int, int);
Node createNode(int, int);
void addEdge(Graph, int, int, int);
void AOE(Graph);
void printGraph(Graph);
void printSet(Graph);
int stack[MAX_SIZE];
void push(int);
int pop();
void stackFull();
int stackEmpty();
int top = -1;

/*
        __B__       __G__
       /     \     /     \
      6       1   9       2
     /         \ /         \
    A--4--C--1--E--7--H--4--I
     \               /
      5             4
       \_D_--2--_F_/ 

        B-6-E   
       /|\   \
      5 4 5   3
     /  |  \   \
    A-6-C-6-F-5-H
     \  |  /   /
      4 5 6   4
       \|/   /
        D-7-G
*/

int main(){
    Graph graph = createGraph(9, 11);
    addEdge(graph, 0, 1, 6);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 0, 3, 5);
    addEdge(graph, 1, 4, 1);
    addEdge(graph, 2, 4, 1);
    addEdge(graph, 3, 5, 2);
    addEdge(graph, 4, 6, 9);
    addEdge(graph, 4, 7, 7);
    addEdge(graph, 5, 7, 4);
    addEdge(graph, 6, 8, 2);
    addEdge(graph, 7, 8, 4);
    // Graph graph = createGraph(8, 13);
    // addEdge(graph, 0, 1, 5);
    // addEdge(graph, 0, 2, 6);
    // addEdge(graph, 0, 3, 4);
    // addEdge(graph, 2, 1, 4);
    // addEdge(graph, 3, 2, 5);
    // addEdge(graph, 1, 4, 6);
    // addEdge(graph, 1, 5, 5);
    // addEdge(graph, 2, 5, 6);
    // addEdge(graph, 3, 5, 6);
    // addEdge(graph, 3, 6, 7);
    // addEdge(graph, 4, 7, 3);
    // addEdge(graph, 5, 7, 5);
    // addEdge(graph, 6, 7, 4);
    AOE(graph);
    return 0;
}

Graph createGraph(int v, int e){
    Graph graph;
    MALLOC(graph, sizeof(* graph));
    graph->numVertices = v;
    graph->numEdges = e;
    MALLOC(graph->visited, v * sizeof(* graph->visited));
    MALLOC(graph->adjListsCount, v * sizeof(* graph->adjListsCount));
    MALLOC(graph->status, v * sizeof(* graph->status));
    MALLOC(graph->adjLists, v * sizeof(* graph->adjLists));
    MALLOC(graph->edge, e * sizeof(* graph->edge));
    for(int i = 0; i < v; i++){
        graph->visited[i] = FALSE;
        graph->adjListsCount[i] = 0;
        graph->status[i] = 0;
        graph->adjLists[i] = NULL;
    }
    return graph;
}

Node createNode(int d, int w){
    Node newNode;
    MALLOC(newNode, sizeof(* newNode));
    newNode->vertice = d;
    newNode->dur = w;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph graph, int s, int d, int w){
    static int count = 0;
    Node newNode = createNode(d, w);
    newNode->next = graph->adjLists[s];
    graph->adjLists[s] = newNode;
    graph->edge[s].src = s;
    graph->edge[s].dest = d;
    graph->edge[s].weight = w;
    graph->adjListsCount[d] += 1;
    count++;
}

void AOE(Graph graph){
    printGraph(graph);
    printf("Initial: | ");
    for(int i = 0; i < graph->numVertices; i++){
        for(int j = 0; j < graph->numVertices; j++)
            if(graph->adjListsCount[j] == 0 && graph->visited[j] == FALSE){
                graph->visited[j] = TRUE;
                push(j);
            }
        printSet(graph);
        int num = pop();
        printf("Output %d | ", num);
        Node temp = graph->adjLists[num];
        while(temp){
            if(graph->status[num] + temp->dur > graph->status[temp->vertice])
                graph->status[temp->vertice] = graph->status[num] + temp->dur;
            graph->adjListsCount[temp->vertice] -= 1;
            temp = temp->next;
        }
    }
}

void printGraph(Graph graph){
    for (int i = 0; i < graph->numVertices; i++) {
        Node temp = graph->adjLists[i];
        printf("Vertex %d(%d) : ", i, graph->adjListsCount[i]);
        while (temp) {
            printf("%d(%d) -> ", temp->vertice, temp->dur);
            temp = temp->next;
        }
        printf("NULL\n");
    }
    printf("-----------------------------------\n");
}

void printSet(Graph graph){
    for(int i = 0; i < graph->numVertices; i++)
        printf("%2d ", graph->status[i]);
    printf(" [");
    for(int i = top; i >= 0; i--)
        printf("%d,", stack[i]);
    printf("]\n");
}

void push(int item){
    if(top >= MAX_SIZE - 1)
        stackFull();
    else
        stack[++top] = item;
}

int pop(){
    if(top == -1)
        return stackEmpty();
    else
        return stack[top--];
}

void stackFull(){
    fprintf(stderr, "Stack is full, cannot add element\n");
    // exit(EXIT_FAILURE);
}

int stackEmpty(){
    fprintf(stderr, "Stack is empty, cannot pop element\n");
    // exit(EXIT_FAILURE);
}
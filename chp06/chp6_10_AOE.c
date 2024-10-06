#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_SIZE 50
#define INFINITE 99
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
    int earlyTime;
    int lateTime;
    int slack;
    int critical;
} edge_t;
typedef struct status_s * Vertice;
typedef struct status_s {
    int early;
    int late;
    int slack;
    int critical;
} status_t;
typedef struct graph_s * Graph;
typedef struct graph_s {
    int numVertices;
    int numEdges;
    int * visited;
    int * adjListsCount;
    Node * adjLists;
    Vertice vertice;
    Edge edge;
} graph_t;
Graph createGraph(int, int);
Node createNode(int, int);
void addEdge(Graph, int, int, int);
void AOE(Graph);
void printGraph(Graph);
void printSet(Graph);
int stack[MAX_SIZE], aov[MAX_SIZE];
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

        B---3---D-------4-------F
       /       /|\               \
      5       / | 4               4   
     /       /  |  \               \
    A       6   3   G---5---I---2---J
     \     /    |  /       /
      6   /     | 1       2 
       \ /      |/       /
        C---3---E---4---H
*/

int main(){
    Graph graph = createGraph(9, 11);
    addEdge(graph, 0, 1, 6);//a1
    addEdge(graph, 0, 2, 4);//a2
    addEdge(graph, 0, 3, 5);//a3
    addEdge(graph, 1, 4, 1);//a4
    addEdge(graph, 2, 4, 1);//a5
    addEdge(graph, 3, 5, 2);//a6
    addEdge(graph, 4, 6, 9);//a7
    addEdge(graph, 4, 7, 7);//a8
    addEdge(graph, 5, 7, 4);//a9
    addEdge(graph, 6, 8, 2);//a10
    addEdge(graph, 7, 8, 4);//a11
    // Graph graph = createGraph(10, 14);
    // addEdge(graph, 0, 1, 5);//a1
    // addEdge(graph, 0, 2, 6);//a2
    // addEdge(graph, 1, 3, 3);//a3
    // addEdge(graph, 2, 3, 6);//a4
    // addEdge(graph, 2, 4, 3);//a5
    // addEdge(graph, 3, 4, 3);//a6
    // addEdge(graph, 3, 5, 4);//a7
    // addEdge(graph, 3, 6, 4);//a8
    // addEdge(graph, 4, 6, 1);//a9
    // addEdge(graph, 4, 7, 4);//a10
    // addEdge(graph, 6, 8, 5);//a11
    // addEdge(graph, 7, 8, 2);//a12
    // addEdge(graph, 5, 9, 4);//a13
    // addEdge(graph, 8, 9, 2);//a14
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
    MALLOC(graph->adjLists, v * sizeof(* graph->adjLists));
    MALLOC(graph->vertice, v * sizeof(* graph->vertice));
    MALLOC(graph->edge, e * sizeof(* graph->edge));
    for(int i = 0; i < v; i++){
        graph->visited[i] = FALSE;
        graph->adjListsCount[i] = 0;
        graph->adjLists[i] = NULL;
        graph->vertice[i].late = INFINITE;
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
    graph->edge[count].src = s;
    graph->edge[count].dest = d;
    graph->edge[count].weight = w;
    graph->adjListsCount[d] += 1;
    count++;
}

void AOE(Graph graph){
    printGraph(graph);
    printf("Initial: | ");
    static int aovtop = -1;
    for(int i = 0; i < graph->numVertices; i++){
        for(int j = 0; j < graph->numVertices; j++)
            if(graph->adjListsCount[j] == 0 && graph->visited[j] == FALSE){
                graph->visited[j] = TRUE;
                push(j);
            }
        printSet(graph);
        int num = pop();
        aov[++aovtop] = num;
        printf("Output %d | ", num);
        Node temp = graph->adjLists[num];
        while(temp){
            if(graph->vertice[num].early + temp->dur > graph->vertice[temp->vertice].early)
                graph->vertice[temp->vertice].early = graph->vertice[num].early + temp->dur;
            graph->adjListsCount[temp->vertice] -= 1;
            temp = temp->next;
        }
    }

    printf("\n");
    printf("-----------------------------------\n");
    for(int i = 0; i < aovtop + 1; i++)
        printf("%2d ", aov[i]);
    printf("\n");
    for(int i = 0; i < graph->numEdges; i++)
        graph->edge[i].earlyTime = graph->vertice[graph->edge[i].src].early;
    printf("-----------------------------------\n");
    graph->vertice[graph->numVertices - 1].late = graph->vertice[graph->numVertices - 1].early;

    for(int i = graph->numVertices - 1; i >= 0; i--){
        int num = aov[i];
        for(int j = 0; j < graph->numEdges; j++){
            if(graph->edge[j].dest == num){
                graph->edge[j].lateTime = graph->vertice[num].late - graph->edge[j].weight;
                if(graph->edge[j].lateTime < graph->vertice[graph->edge[j].src].late){
                    graph->vertice[graph->edge[j].src].late = graph->edge[j].lateTime;
                }
            }
        }
    }
    for(int i = 0; i < graph->numVertices; i++){
        graph->vertice[i].slack = graph->vertice[i].late - graph->vertice[i].early;
        graph->vertice[i].critical = graph->vertice[i].slack == 0 ? TRUE : FALSE;
        printf("Vertex %d : %2d %2d %2d %2d\n", i, graph->vertice[i].early, graph->vertice[i].late, graph->vertice[i].slack, graph->vertice[i].critical);
    }
    printf("-----------------------------------\n");
    for(int i = 0; i < graph->numEdges; i++){
        graph->edge[i].slack = graph->edge[i].lateTime - graph->edge[i].earlyTime;
        graph->edge[i].critical = graph->edge[i].slack == 0 ? TRUE : FALSE;
        printf("Edge : a%-2d %2d %2d %2d %2d\n",i+1 , graph->edge[i].earlyTime, graph->edge[i].lateTime, graph->edge[i].slack, graph->edge[i].critical);
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
        printf("%2d ", graph->vertice[i].early);
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
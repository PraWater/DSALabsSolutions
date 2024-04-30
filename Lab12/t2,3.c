/*
The major steps of the algorithm are as follows:
Start off with all nodes being white. Initialize an empty queue.
Mark the source s as grey and enqueue it
While the queue is not empty:
    Dequeue a node u
    For each white node v adjacent to u:
        Mark v as grey
        Enqueue v
    Mark u as black
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Queue
typedef struct linked_list_node
{
    int data;
    struct linked_list_node *next;
} ll_node;

typedef struct queue
{
    ll_node *front;
    ll_node *rear;
} queue;

typedef struct stack
{
    ll_node *top;
} stack;

queue *get_queue()
{
    queue *Q = (queue *)malloc(sizeof(queue));
    Q->front = NULL;
    Q->rear = NULL;
    return Q;
}

stack *get_stack()
{
    stack *S = (stack *)malloc(sizeof(stack));
    S->top = NULL;
    return S;
}

void enqueue(queue *Q, int data)
{
    ll_node *temp = (ll_node *)malloc(sizeof(ll_node));
    temp->data = data;
    temp->next = NULL;
    if (Q->rear == NULL)
    {
        Q->front = temp;
        Q->rear = temp;
    }
    else
    {
        Q->rear->next = temp;
        Q->rear = temp;
    }
}

void push(stack *S, int data)
{
    ll_node *temp = (ll_node *)malloc(sizeof(ll_node));
    temp->data = data;
    temp->next = NULL;
    if (S->top == NULL)
    {
        S->top = temp;
    }
    else
    {
        temp->next = S->top;
        S->top = temp;
    }
}

int is_empty_queue(queue *Q)
{
    return Q->front == NULL;
}

int is_empty_stack(stack *S)
{
    return S->top == NULL;
}

int dequeue(queue *Q)
{
    if (is_empty_queue(Q))
    {
        printf("Queue is empty\n");
        return -1;
    }
    ll_node *temp = Q->front;
    int data = temp->data;
    Q->front = Q->front->next;
    if (Q->front == NULL)
    {
        Q->rear = NULL;
    }
    free(temp);
    return data;
}

int pop(stack *S)
{
    if (is_empty_stack(S))
    {
        printf("Stack is empty\n");
        return -1;
    }
    ll_node *temp = S->top;
    int data = temp->data;
    S->top = S->top->next;
    free(temp);
    return data;
}

typedef enum color
{
    WHITE,
    GREY,
    BLACK
} color;

// Graph Node
typedef struct graph_node
{
    int data;
    color c;
} graph_node;

// Graph
typedef struct Graph
{
    int V;
    int E;
    int **adjacency_matrix;
    graph_node *vertices;
} Graph;

// Modify the get_graph function from Task 1 to now only use the adjacency matrix and not the adjacency list
// Allocate memory for the vertices array (Array of |V| graph_nodes)
// Initialize all the vertices to WHITE
// Initialize data to the index of the vertex

Graph *get_graph(int V, int E)
{
    struct Graph *G = (struct Graph *)malloc(sizeof(struct Graph));
    G->V = V;
    G->E = E;
    // Allocate memory for the adjacency matrix (V x V int array)
    G->adjacency_matrix = (int **) malloc(V * sizeof(int *));

    // Allocate memory for each row of the adjacency matrix
    for (int i = 0; i < V; i++)
    {
        // Initialize the allocated row to 0 (Do not visit all elements. Use the <string.h> function bzero or memset)
        G->adjacency_matrix[i] = (int *) malloc(V*sizeof(int));
        memset(G->adjacency_matrix[i], 0, V*sizeof(int));
    }

    G->vertices = (graph_node *) malloc(sizeof(graph_node) * V);
    for (int i = 0; i < V; ++i){
        G->vertices[i].c = WHITE;
    }

    return G;
}

void graph_reset(Graph *G)
{
    for (int i = 0; i < G->V; ++i){
        G->vertices[i].c = WHITE;
    }
}

// BFS
void bfs(Graph *G, int s)
{
    // Initialize the queue
    queue *Q = get_queue();

    // Mark the source s as grey and enqueue it
    G->vertices[s].c = GREY;
    enqueue(Q, s);

    // While the queue is not empty:
    while (!is_empty_queue(Q))
    {
        // Dequeue a node u
        int u = dequeue(Q);

        // Print the data of the dequeued node that would now be explored
        printf("%d ", u);

        // For each white node v adjacent to u:
        for (int v = 0; v < G->V; v++)
        {
            if (G->adjacency_matrix[u][v] == 1 && G->vertices[v].c == WHITE)
            {
                // Mark v as grey
                G->vertices[v].c = GREY;

                // Enqueue v
                enqueue(Q, v);

            }
        }
        // Mark u as black
        G->vertices[u].c = BLACK;

    }
}

// DFS
void dfs(Graph *G, int s)
{
    // Initialize the stack
    stack *S = get_stack();

    // Mark the source s as grey and enqueue it
    G->vertices[s].c = GREY;
    push(S, s);

    // While the queue is not empty:
    while (!is_empty_stack(S))
    {
        // Dequeue a node u
        int u = pop(S);

        // Print the data of the dequeued node that would now be explored
        printf("%d ", u);

        // For each white node v adjacent to u:
        for (int v = 0; v < G->V; v++)
        {
            if (G->adjacency_matrix[u][v] == 1 && G->vertices[v].c == WHITE)
            {
                // Mark v as grey
                G->vertices[v].c = GREY;

                // Enqueue v
                push(S, v);

            }
        }
        // Mark u as black
        G->vertices[u].c = BLACK;

    }
}

void add_edge_adj_matrix(Graph *G, int u, int v)
{
    G->adjacency_matrix[u][v] = 1;
}

int main()
{
    // You can change the file name to input1.txt or input2.txt to test your code for different graphs
    FILE *fp = fopen("input3.txt", "r");
    int V, E;
    fscanf(fp, "%d", &V);
    fscanf(fp, "%d", &E);
    struct Graph *G = get_graph(V, E);
    for (int i = 0; i < E; i++) 
    {
        int u, v;
        fscanf(fp, "%d %d", &u, &v);
        add_edge_adj_matrix(G, u, v);
    }
    fclose(fp);
    bfs(G, 0);
    printf("\n");
    graph_reset(G);
    dfs(G, 0);
    printf("\n");
    return 0;
}
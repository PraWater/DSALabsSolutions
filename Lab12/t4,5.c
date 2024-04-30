#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    int d;
    int f;
} graph_node;

// Graph
typedef struct Graph
{
    int V;
    int E;
    int **adjacency_matrix;
    graph_node *vertices;
} Graph;

Graph *get_graph(int V, int E)
{
    struct Graph *G = (struct Graph *)malloc(sizeof(struct Graph));
    G->V = V;
    G->E = E;
    // Allocate memory for the adjacency matrix (V x V int array)
    G->adjacency_matrix = (int **)malloc(V * sizeof(int *));

    // Allocate memory for each row of the adjacency matrix
    for (int i = 0; i < V; i++)
    {
        // Initialize the allocated row to 0 (Do not visit all elements. Use the <string.h> function bzero or memset)
        G->adjacency_matrix[i] = (int *)malloc(V * sizeof(int));
        memset(G->adjacency_matrix[i], 0, V * sizeof(int));
    }

    G->vertices = (graph_node *)malloc(sizeof(graph_node) * V);
    for (int i = 0; i < V; ++i)
    {
        G->vertices[i].c = WHITE;
    }

    return G;
}

void graph_reset(Graph *G)
{
    for (int i = 0; i < G->V; ++i)
    {
        G->vertices[i].c = WHITE;
    }
}

void add_edge_adj_matrix(Graph *G, int u, int v)
{
    G->adjacency_matrix[u][v] = 1;
}

/*
    Recursive DFS with time stamps as given in CLRS
*/
int time = 0;
void recDFSVisit(Graph *G, int u)
{
    // As in task 4 (Print the visited vertex as well)
    ++time;
    G->vertices[u].d = time;
    G->vertices[u].c = GREY;
    printf("%d ", u);
    for (int v = 0; v < G->V; v++)
    {
        if (G->adjacency_matrix[u][v] == 1 && G->vertices[v].c == WHITE)
        {
            recDFSVisit(G, v);
        }
    }
    G->vertices[u].c = BLACK;
    ++time;
    G->vertices[u].f = time;
}

void recDFS(Graph *G)
{
    // As in task 4
    time = 0;
    for (int i = 0; i < G->V; ++i)
    {
        if (G->vertices[i].c == WHITE)
            recDFSVisit(G, i);
    }
}

Graph *get_transpose(Graph *G)
{
    // The transpose of a graph is a graph with the same vertices but with the direction of all edges reversed
    Graph *Gt = get_graph(G->V, G->E);
    for (int i = 0; i < G->V; ++i)
    {
        for (int j = 0; j < G->V; ++j)
        {
            Gt->adjacency_matrix[i][j] = G->adjacency_matrix[j][i];
        }
    }
    return Gt;
}

int strongly_connected_components(Graph *G)
{
    time = 0;
    printf("Computing strongly connected components\n");
    printf("Running DFS on the original graph\n");
    recDFS(G);
    printf("\n");
    graph_node descending_f_indices[G->V];
    for (int i = 0; i < G->V; i++)
    {
        descending_f_indices[i].data = i;
        descending_f_indices[i].f = G->vertices[i].f;
    }
    // Sort the vertices in descending order of f
    for (int i = 0; i < G->V; i++)
    {
        for (int j = i + 1; j < G->V; j++)
        {
            if (descending_f_indices[i].f < descending_f_indices[j].f)
            {
                graph_node temp = descending_f_indices[i];
                descending_f_indices[i] = descending_f_indices[j];
                descending_f_indices[j] = temp;
            }
        }
    }

    // Print descending_f_indices
    printf("Descending f indices: ");
    for (int i = 0; i < G->V; i++)
    {
        printf("%d ", descending_f_indices[i].data);
    }

    Graph *Gt = get_transpose(G);

    int num_scc = 0;
    time = 0;
    printf("\n");
    for (int i = 0; i < G->V; i++)
    {
        if (Gt->vertices[descending_f_indices[i].data].c == WHITE)
        {
            num_scc++;
            printf("SCC %d: ", num_scc);
            recDFSVisit(Gt, descending_f_indices[i].data);
            printf("\n");
        }
    }
    return num_scc;
}

Graph *get_undirected(Graph *G)
{
    Graph *Gu = get_graph(G->V, G->E);
    for (int i = 0; i < G->V; ++i)
    {
        for (int j = 0; j < G->V; ++j)
        {
            if (G->adjacency_matrix[j][i] == 1) {
                Gu->adjacency_matrix[i][j] = 1;
                Gu->adjacency_matrix[j][i] = 1;
            }
        }
    }
    return Gu;
}

int weakly_connected_components(Graph *G) // Implement after testing strongly_connected_components
{
    // TODO: Implement this function
    printf("Computing weakly connected components\n");
    Graph *Gu = get_undirected(G);
    int num_wcc = 0;
    for (int i = 0; i < G->V; i++)
    {
        if (Gu->vertices[i].c == WHITE)
        {
            num_wcc++;
            printf("WCC %d: ", num_wcc);
            recDFSVisit(Gu, i);
            printf("\n");
        }
    }
    return num_wcc;
}

int main()
{
    // You can change the file name to input1.txt or input2.txt to test your code for different graphs
    FILE *fp = fopen("input4.txt", "r");
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
    // Number of strongly connected components
    printf("Number of strongly connected components: %d\n", strongly_connected_components(G));

    graph_reset(G);

    // Number of weakly connected components.
    printf("Number of weakly connected components: %d\n", weakly_connected_components(G));
    return 0;
}
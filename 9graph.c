#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure to represent a node in the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure to represent the graph
struct Graph {
    int num_vertices;
    struct Node* adj_list[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int start_time[MAX_VERTICES];
    int end_time[MAX_VERTICES];
    int indegrees[MAX_VERTICES];
    int time;
};

// Function to initialize a graph
void initializeGraph(struct Graph* G, int num_vertices) {
    G->num_vertices = num_vertices;
    for (int i = 0; i < num_vertices; ++i) {
        G->adj_list[i] = NULL;
        G->visited[i] = 0;
        G->start_time[i] = 0;
        G->end_time[i] = 0;
        G->indegrees[i] = 0;
    }
    G->time = 0;
}

// Function to add an edge to the graph
void addEdge(struct Graph* G, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = G->adj_list[src];
    G->adj_list[src] = newNode;
    G->indegrees[dest]++;
}

// DFS Visit function with start and end times
void DFS_VISIT(struct Graph* G, int u) {
    G->visited[u] = 1;
    G->start_time[u] = ++(G->time);
    printf("%d ", u);

    struct Node* temp = G->adj_list[u];
    while (temp != NULL) {
        int v = temp->vertex;
        if (!G->visited[v]) {
            DFS_VISIT(G, v);
        }
        temp = temp->next;
    }

    G->end_time[u] = ++(G->time);
}

// Depth-First Search (DFS) traversal with start and end times
void DFS(struct Graph* G) {
    printf("DFS Traversal: ");
    for (int i = 0; i < G->num_vertices; ++i) {
        if (!G->visited[i]) {
            DFS_VISIT(G, i);
        }
    }
    printf("\n");

    printf("Node\tStart Time\tEnd Time\n");
    for (int i = 0; i < G->num_vertices; ++i) {
        printf("%d\t%d\t\t%d\n", i, G->start_time[i], G->end_time[i]);
    }
}

// Function to perform topological sort using finishing time
void topologicalSort(struct Graph* G) {
    int stack[MAX_VERTICES];
    int sortedVertices[MAX_VERTICES];

    for (int i = 0; i < G->num_vertices; ++i) {
        sortedVertices[i] = i;
    }

    // Sorting vertices based on decreasing finishing time
    for (int i = 0; i < G->num_vertices - 1; ++i) {
        for (int j = i + 1; j < G->num_vertices; ++j) {
            if (G->end_time[sortedVertices[i]] < G->end_time[sortedVertices[j]]) {
                int temp = sortedVertices[i];
                sortedVertices[i] = sortedVertices[j];
                sortedVertices[j] = temp;
            }
        }
    }

    printf("Topological Order: ");
    for (int i = 0; i < G->num_vertices; ++i) {
        printf("%d ", sortedVertices[i]);
    }
    printf("\n");
}

// Breadth-First Search (BFS) traversal
void BFS(struct Graph* G, int start_vertex) {
    printf("BFS Traversal: ");
    int queue[MAX_VERTICES];
    int front = 0, rear = -1;

    G->visited[start_vertex] = 1;
    printf("%d ", start_vertex);
    queue[++rear] = start_vertex;

    while (front <= rear) {
        int u = queue[front++];

        struct Node* temp = G->adj_list[u];
        while (temp != NULL) {
            int v = temp->vertex;
            if (!G->visited[v]) {
                G->visited[v] = 1;
                printf("%d ", v);
                queue[++rear] = v;
            }
            temp = temp->next;
        }

        // If there are remaining unvisited nodes, set the next node as the starting node
        if (front <= rear && !G->visited[queue[front]]) {
            printf("%d ", queue[front]);
            G->visited[queue[front++]] = 1;
        }
    }

    // If there are still unvisited nodes, set any remaining node as the starting node
    for (int i = 0; i < G->num_vertices; ++i) {
        if (!G->visited[i]) {
            printf("%d ", i);
            G->visited[i] = 1;
            queue[++rear] = i;

            while (front <= rear) {
                int u = queue[front++];

                struct Node* temp = G->adj_list[u];
                while (temp != NULL) {
                    int v = temp->vertex;
                    if (!G->visited[v]) {
                        G->visited[v] = 1;
                        printf("%d ", v);
                        queue[++rear] = v;
                    }
                    temp = temp->next;
                }
            }
        }
    }

    printf("\n");
}

int main() {
    struct Graph G;
    int num_vertices, num_edges;

    // Input: Number of vertices and edges
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &num_vertices, &num_edges);

    initializeGraph(&G, num_vertices);

    // Input: Edges of the graph
    printf("Enter edges (vertex u and v connected): \n");
    for (int i = 0; i < num_edges; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(&G, u, v);
    }

    DFS(&G); // Perform DFS traversal with start and end times
    printf("\n");

    // Reset visited array for BFS
    for (int i = 0; i < G.num_vertices; ++i) {
        G.visited[i] = 0;
    }

    // Input: Starting vertex for BFS
    int start_vertex;
    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &start_vertex);

    BFS(&G, start_vertex); // Perform BFS traversal
    printf("\n");

    topologicalSort(&G); // Perform topological sort using finishing time

    return 0;
}

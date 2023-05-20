#include "Struct.h"



#define MAX_NODES 1000

void dijkstra(Struct_Graph graph) {
    int numVertices = graph.numVertices;
    int* distance = (int*)malloc(numVertices * sizeof(int));
    int* visited = (int*)calloc(numVertices, sizeof(int));
    int* prev = (int*)malloc(numVertices * sizeof(int));

    if (distance == NULL || visited == NULL || prev == NULL) {
        printf("Memory allocation failed\n");
        // Handle the error condition, such as returning or freeing previously allocated memory
        return;
    }

    for (int i = 0; i < numVertices; i++) {
        distance[i] = INT_MAX;
        prev[i] = -1;
    }

    distance[graph.start] = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int minDistance = INT_MAX;
        int minIndex = -1;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && distance[v] <= minDistance) {
                minDistance = distance[v];
                minIndex = v;
            }
        }

        int u = minIndex;
        visited[u] = 1;

        for (int v = 0; v < numVertices; v++) {
            int weight = graph.adjacencyMatrix[u][v];

            if (!visited[v] && weight && distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                prev[v] = u;
            }
        }
    }

    printf("Vertex\t Distance\tPath\n");
    for (int i = 0; i < numVertices; i++) {
        if (distance[i] != INT_MAX) {
            printf("%d\t %d\t\t%d", i, distance[i], i);
            int j = i;
            while (j != graph.start && prev[j] != -1) {
                printf(" <- %d", prev[j]);
                j = prev[j];
            }
            printf("\n");
        }
    }

    int nonReachableCount = 0;
    for (int i = 0; i < numVertices; i++) {
        if (distance[i] == INT_MAX) {
            if (nonReachableCount == 0) {
                printf("Non-reachable vertices: ");
            }
            printf("%d ", i);
            nonReachableCount++;
        }
    }
    if (nonReachableCount == 0) {
        printf("All vertices are reachable.\n");
    } else {
        printf("\n");
    }

    free(distance);
    free(visited);
    free(prev);
}


// Fonction utilitaire pour trouver le minimum de deux valeurs
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Fonction de recherche d'un chemin augmentant à travers le graphe résiduel en utilisant la recherche en profondeur (DFS)
bool dfs(int** graph, int V, int s, int t, int parent[]) {
    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    visited[s] = true;
    parent[s] = -1;

    // Utilisation d'une pile pour effectuer la recherche en profondeur
    int stack[V];
    int top = 0;
    stack[top] = s;

    while (top >= 0) {
        int u = stack[top--];

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] > 0) {
                visited[v] = true;
                parent[v] = u;
                stack[++top] = v;

                if (v == t)
                    return true;
            }
        }
    }

    return false;
}

// Fonction principale de l'algorithme de Ford-Fulkerson
int fordFulkerson(int** graph, int V, int source, int sink) {
    int** residualGraph = (int**)malloc(V * sizeof(int*)); // Graphe résiduel
    for (int i = 0; i < V; i++)
        residualGraph[i] = (int*)malloc(V * sizeof(int));

    int u, v;

    // Initialiser le graphe résiduel avec les capacités du graphe d'origine
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            residualGraph[u][v] = graph[u][v];

    int parent[V]; // Tableau pour stocker le chemin augmentant

    int maxFlow = 0; // Flux maximal

    // Tant qu'il existe un chemin augmentant dans le graphe résiduel
    while (dfs(residualGraph, V, source, sink, parent)) {
        int pathFlow = INT_MAX;

        // Trouver la capacité résiduelle minimale le long du chemin augmentant
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Mettre à jour les capacités résiduelles du graphe résiduel
        for (v = sink; v != source; v = parent[v]) {
            u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Ajouter le flux du chemin augmentant au flux maximal
        maxFlow += pathFlow;
    }

    // Libérer la mémoire allouée pour le graphe résiduel
    for (int i = 0; i < V; i++)
        free(residualGraph[i]);
    free(residualGraph);

    return maxFlow;
}
/*
// Exemple d'utilisation de l'algorithme de Ford-Fulkerson
int main() {
    int V; // Nombre de sommets du graphe
    
    printf("Entrez le nombre de sommets du graphe : ");
    scanf("%d", &V);

    int** graph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++)
        graph[i] = (int*)malloc(V * sizeof(int));

    printf("Entrez la matrice d'adjacence du graphe :\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            graph[i][j] = graph3[i][j];
        }
    }

    int source, sink;
    printf("Entrez le sommet source : ");
    scanf("%d", &source);
    printf("Entrez le sommet puits : ");
    scanf("%d", &sink);

    int maxFlow = fordFulkerson(graph, V, source, sink);
    printf("Flux maximal : %d\n", maxFlow);

    // Libérer la mémoire allouée pour le graphe
    for (int i = 0; i < V; i++)
        free(graph[i]);
    free(graph);

    return 0;
}
*/
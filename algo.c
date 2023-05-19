#include "Struct.h"



#define MAX_NODES 1000

void dijkstra(int graph[MAX_NODES][MAX_NODES], int size, int start) {
    int dist[MAX_NODES];
    int visited[MAX_NODES];
    int prev[MAX_NODES];

    // Initialiser les distances et les prédecesseurs
    int i;
    for (i = 0; i < size; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        prev[i] = -1;
    }

    dist[start] = 0;

    // Parcourir tous les nœuds pour trouver les distances les plus courtes
    int count;
    for (count = 0; count < size - 1; count++) {
        int minDist = INT_MAX;
        int minNode = -1;

        // Trouver le nœud non visité avec la plus petite distance
        int j;
        for (j = 0; j < size; j++) {
            if (visited[j] == 0 && dist[j] < minDist) {
                minDist = dist[j];
                minNode = j;
            }
        }

        // Marquer le nœud courant comme visité
        visited[minNode] = 1;

        // Mettre à jour les distances des nœuds adjacents
        int k;
        for (k = 0; k < size; k++) {
            if (visited[k] == 0 && graph[minNode][k] && dist[minNode] != INT_MAX && dist[minNode] + graph[minNode][k] < dist[k]) {
                dist[k] = dist[minNode] + graph[minNode][k];
                prev[k] = minNode;
            }
        }
    }

    // Afficher les distances les plus courtes et les chemins les plus courts
    printf("Vertex\t Distance\tPath");
    for (i = 0; i < size; i++) {
        printf("\n%d \t\t %d\t\t%d", i, dist[i], i);
        int j = i;
        while (j != start && prev[j] != -1) {
            printf(" <- %d", prev[j]);
            j = prev[j];
        }
    }
    printf("\n");
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
#include "Struct.h"



#define MAX_NODES 1000

void dijkstra(Struct_Graph graph) {
    int numVertices = graph.numVertices;
    int* distance = (int*)calloc(MAX_NODES, sizeof(int));
    int* visited = (int*)calloc(MAX_NODES, sizeof(int));
    int* prev = (int*)calloc(MAX_NODES, sizeof(int));

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

void ford(){

    Struct_Graph graph3 = createGraph(14);
    //                S  A  B  C  D  E  F  G  H  I  J  K  L  P
int mat[14][14] =  {{ 0,70,30,40,55, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0,30, 0, 0,60, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0,15, 0, 0,35, 0, 5, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,25, 0,50, 0},
                    { 0, 0, 0, 0, 0, 0, 0,11,12,17,10, 4, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 5,10, 2, 0, 6, 0, 7, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,21},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,16},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,45},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,50},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
           graph3.adjacencyMatrix [i][j] = mat[i][j];
        }
    }
    printf("Le nombre maximal de voiture que l'on peut mettre en circulation en même temps pendants une heure est :%d",fordFulkerson(graph3.adjacencyMatrix,14,0,13));
    
}

void fordCouple(){

    Struct_Graph graph2 = createGraph(14);
    //                S  A  B  C  D  E  F  G  H  I  J  K  L  P
int mat[14][14] =  {{ 0,70,30,40,55, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0,30, 0, 0,60, 0, 0, 0},
                    { 0, 0, 0, 0, 0, 0,15, 0, 0,35, 0, 5, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,25, 0,50, 0},
                    { 0, 0, 0, 0, 0, 0, 0,11,12,17,10, 4, 0, 0},
                    { 0, 0, 0, 0, 0, 0, 5,10, 2, 0, 6, 0, 7, 0},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,21},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,16},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,45},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,50},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,20},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
           graph2.adjacencyMatrix [i][j] = mat[i][j];
        }
    }
     for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
           printf("Le nombre maximal de voiture entre %c et %c est %d\n",65+i,65+j,fordFulkerson(graph2.adjacencyMatrix,14,i,j));
        }
    }
}

// Fonction pour résoudre le problème du voyageur de commerce en utilisant l'algorithme du plus proche voisin
void solveTSP(Struct_Graph graph) {
    int visited[graph.numVertices]; // Tableau pour marquer les bases visitées
    for (int i = 0; i < graph.numVertices; i++)
    {
        visited[i] = 0;
    }
    
    visited[0] = 1; // Marquer la base de départ comme visitée
    
    int currentBase = 0; // Base de départ
    
    double totalDistance = 0.0; // Distance totale parcourue
    
    printf("Ordre de visite des bases :\n");
    printf("Début -> ");
    
    for (int i = 0; i < graph.numVertices - 2; i++) {
        double minDistance = INFINITY;
        int nextBase = -1;
        
        for (int j = 0; j < graph.numVertices; j++) {
            if (!visited[j] && j != currentBase && graph.adjacencyMatrix[currentBase][j] < minDistance) {
                minDistance = graph.adjacencyMatrix[currentBase][j];
                nextBase = j;
            }
        }
        
        visited[nextBase] = 1; // Marquer la prochaine base comme visitée
        
        printf("%d -> ",nextBase);
        
        totalDistance += minDistance;
        
        currentBase = nextBase;
    }
    
    // Retour à la base de départ
    printf("Début\n");
    totalDistance += graph.adjacencyMatrix[currentBase][0];
    
    printf("Distance totale parcourue : %.2f\n", totalDistance);
}

void solveTSP2(Struct_Graph graph) {
    int N = graph.numVertices;
    int order[N]; // Tableau pour stocker l'ordre de visite des bases
    int visited[N]; // Tableau pour marquer les bases visitées
    for (int i = 0; i < graph.numVertices; i++)
    {
        visited[i] = 0;
    }
    order[0] = 0; // Base de départ
    order[N - 1] = N - 1; // Base d'arrivée
    visited[0] = 1; // Marquer la base de départ comme visitée
    visited[N - 1] = 1; // Marquer la base d'arrivée comme visitée
    
    for (int i = 1; i < N - 1; i++) {
        int bestPosition = -1;
        double minDistanceIncrease = INFINITY;
        
        for (int j = 1; j < N - 1; j++) {
            if (!visited[j]) {
                double distanceIncrease = graph.adjacencyMatrix[order[i - 1]][j] + graph.adjacencyMatrix[j][order[i]] - graph.adjacencyMatrix[order[i - 1]][order[i]];
                
                if (distanceIncrease < minDistanceIncrease) {
                    minDistanceIncrease = distanceIncrease;
                    bestPosition = j;
                }
            }
        }
        
        // Décaler les bases déjà insérées pour faire de la place à la nouvelle base
        for (int j = N - 2; j > bestPosition; j--) {
            order[j] = order[j - 1];
        }
        
        order[bestPosition] = i; // Insérer la nouvelle base à la meilleure position
        visited[bestPosition] = 1; // Marquer la base comme visitée
    }
    
    // Afficher l'ordre de visite des bases
    printf("Ordre de visite des bases :\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", order[i]);
    }
    printf("\n");
}

int trouverValeurMax(Struct_Base* boites, int n, int poidsMax) {
    // Créer une matrice pour stocker les sous-problèmes résolus
    int valeurs[n + 1][poidsMax + 1];
    
    // Initialiser la première ligne et la première colonne à 0
    for (int i = 0; i <= n; i++) {
        valeurs[i][0] = 0;
    }
    
    for (int j = 0; j <= poidsMax; j++) {
        valeurs[0][j] = 0;
    }
    
    // Remplir la matrice de programmation dynamique
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= poidsMax; j++) {
            // Si le poids de la boîte actuelle est inférieur ou égal à la capacité maximale
            // alors nous avons deux choix : soit inclure la boîte, soit ne pas l'inclure
            if (boites[i - 1].vertex_weight <= j) {
                int valeurAvecBoite = boites[i - 1].vertex_nutritive_value + valeurs[i - 1][j - boites[i - 1].vertex_weight];
                int valeurSansBoite = valeurs[i - 1][j];
                
                // Prendre la valeur maximale entre les deux choix
                valeurs[i][j] = (valeurAvecBoite > valeurSansBoite) ? valeurAvecBoite : valeurSansBoite;
            }
            // Sinon, la boîte ne peut pas être incluse
            else {
                valeurs[i][j] = valeurs[i - 1][j];
            }
        }
    }
    
    // La valeur maximale est stockée dans la dernière cellule de la matrice
    return valeurs[n][poidsMax];
}

void afficherObjetsEmportes(Struct_Base *boites, int n, int poidsMax) {
    int valeurMax = trouverValeurMax(boites, n, poidsMax);
    int poidsActuel = poidsMax;
    
    printf("Objets emportés :\n");
    
    for (int i = n; i > 0 && valeurMax > 0; i--) {
         if (valeurMax != boites[i - 1].vertex_nutritive_value && poidsActuel >= boites[i - 1].vertex_weight && valeurMax - boites[i - 1].vertex_nutritive_value == trouverValeurMax(boites, i - 1, poidsActuel - boites[i - 1].vertex_weight)) {
            printf("Numéro : %d, ValNu : %d, Poids : %d\n", boites[i - 1].vertex_number,boites[i - 1].vertex_nutritive_value, boites[i - 1].vertex_weight);
            valeurMax -= boites[i - 1].vertex_nutritive_value;
            poidsActuel -= boites[i - 1].vertex_weight;
        }
    }
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
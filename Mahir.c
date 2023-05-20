
#include "Struct.h"
#define MAX_NODES 1000



Struct_Graph createGraph(int numVertices) {
    Struct_Graph graph;
    graph.numVertices = numVertices;

    // Dynamically allocate memory for the adjacency matrix
    graph.adjacencyMatrix = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        graph.adjacencyMatrix[i] = (int*)calloc(numVertices, sizeof(int));
    }

    return graph;
}

void addEdge(Struct_Graph* graph, int src, int dest, int weight) {
    if (src >= 0 && src < graph->numVertices && dest >= 0 && dest < graph->numVertices) {
        // Set the corresponding edge weight
        graph->adjacencyMatrix[src][dest] = weight;
    }
}

void showAdjMat(Struct_Graph graph,int spacing) {
    printf("Weighted Adjacency Matrix:\n");
    if (spacing ==3)
    {
        for (int i = 0; i < graph.numVertices; i++) {
        for (int j = 0; j < graph.numVertices; j++) {
            printf("%3d ", graph.adjacencyMatrix[i][j]);
        }
        printf("\n\n");
    }
    }else{
    for (int i = 0; i < graph.numVertices; i++) {
        for (int j = 0; j < graph.numVertices; j++) {
            printf("%d ", graph.adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
    }
}

int countLines(FILE* file) {
    int count = 0;
    int ch;
    // Iterate through the file character by character
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    // Increment count if the file doesn't end with a newline
    if (ftell(file) > 0 && ch != '\n') {
        count++;
    }
    fseek(file, 0, SEEK_SET);
    return count;
}

void goToLine(FILE* file, int lineNumber) {
    fseek(file, 0, SEEK_SET);  // Start reading from the beginning of the file

    char buffer[256];
    int currentLine = 1;

    while (currentLine < lineNumber && fgets(buffer, sizeof(buffer), file) != NULL) {
        currentLine++;
    }
}

Struct_Base Process_base(FILE* file)
{
    int nbrVertices = countLines(file);

        Struct_Base* data = (Struct_Base*)malloc(nbrVertices * sizeof(Struct_Base));
        if (data == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            exit(1);
        }

        int vertex_number, vertex_weight, vertex_nutritive_value;

        for (int i = 0; i < nbrVertices; i++) {
            fscanf(file, "%d %d %d", &vertex_number, &vertex_weight, &vertex_nutritive_value);

            data[i].vertex_number = vertex_number;
            data[i].vertex_weight = vertex_weight;
            data[i].vertex_nutritive_value = vertex_nutritive_value;
        }

        // Print the extracted data
        for (int i = 0; i < nbrVertices; i++) {
            printf("Vertex %d: weight=%d, nutritive value=%d\n",
                data[i].vertex_number, data[i].vertex_weight, data[i].vertex_nutritive_value);
        }

        free(data);
}
Struct_Type Process_type(FILE* file)
{
    int nbrVertices;
        fscanf(file, "%d", &nbrVertices); // Read the number of names
        Struct_Type* data = (Struct_Type*)malloc(nbrVertices * sizeof(Struct_Type));
        if (data == NULL) {
            printf("Memory allocation failed.\n");
            fclose(file);
            exit(1);
        }

        for (int i = 0; i < nbrVertices; i++) {
            fscanf(file, "%s %f", data[i].name, &data[i].value);
        }

        for (int i = 0; i < nbrVertices; i++) {
            printf("%s %.1f\n", data[i].name, data[i].value);
        }

        free(data);
}
Struct_VertexData Process_typeSommet(FILE* file)
{
    int nbrVertices = countLines(file);

        Struct_VertexData data[nbrVertices];
        for (int i = 0; i < nbrVertices; i++) {
            fscanf(file, "%d %s", &data[i].vertex_number, data[i].terrain_type);
        }

        for (int i = 0; i < nbrVertices; i++) {
            printf("Vertex %d: biome = %s\n", data[i].vertex_number, data[i].terrain_type);
        }
}
Struct_Graph Process_bonus_terrain(FILE* file){
    int src, dest, weight;
        int maxVertex=0;    
        Struct_Graph graph;
        while (fscanf(file, "%d %*2[-<>] %d %d", &src, &dest, &weight) == 3) {
            if (src > maxVertex) {
                maxVertex = src;
            }
            if (dest > maxVertex) {
                maxVertex = dest;
            }
        }
        int numVertices = maxVertex + 1;
        graph = createGraph(numVertices);

        // Reset the file pointer to the beginning
        fseek(file, 0, SEEK_SET);
        // Add edges to the graph
        while (fscanf(file, "%d %*2[-<>] %d %d", &src, &dest, &weight) == 3) {
            if (src != dest) {
                if (src < dest) {
                    addEdge(&graph, src, dest, weight);
                } else {
                    addEdge(&graph, dest, src, weight);
                }
            }
        }

    showAdjMat(graph,3);
    // Free dynamically allocated memory
    for (int i = 0; i < graph.numVertices; i++) {
        free(graph.adjacencyMatrix[i]);
    }
    free(graph.adjacencyMatrix);
    printf("Vertex number: %d\n",graph.numVertices);
}
Struct_Graph Process_planet_terrain(FILE* file){
    //program for  "planetX.txt" "terrainx.txt" without weight
        
        Struct_Graph graph ;
        int src, dest, weight=1,start,end;
        int maxVertex=0;
        int lineNumber = 3;
        
        fscanf(file, "Debut:%*[^0-9]%d\n", &graph.start);
        fscanf(file, "Fin:%*[^0-9]%d\n", &graph.end);
        printf("Debut: %d\n", graph.start);
        printf("Fin: %d\n", graph.end);
        while (fscanf(file, "%d %*2[-<>] %d ", &src, &dest) == 2) {
            if (src > maxVertex) {
                maxVertex = src;
            }
            if (dest > maxVertex) {
                maxVertex = dest;
            }
        }
        int numVertices = maxVertex + 1;
        graph = createGraph(numVertices);
        goToLine(file, lineNumber);

        long currentPosition = ftell(file);
        // Read and print the line
        char line[100];
        if (fgets(line, sizeof(line), file) != NULL) {
            printf("Current line: %s", line);
        } else {
            printf("Failed to read the line.\n");
        }

        // Restore the position
        fseek(file, currentPosition, SEEK_SET);
        
        while (fscanf(file, "%d %*2[-<>] %d ", &src, &dest) == 2) {
            if (src != dest) {
                if (src < dest) {
                    graph.adjacencyMatrix[src][dest] = weight;
                } else {
                   graph.adjacencyMatrix[src][dest] = weight;
                }
            }
        }
        
       //showAdjMat(graph,1);
       
        // Free dynamically allocated memory

        printf("Vertex number: %d\n",graph.numVertices);
        return graph;
}
Struct_Graph Process_planet_terrain_w(FILE* file){
    int src, dest, weight,start,end;
        int maxVertex=0;
        int lineNumber = 3;
        
        Struct_Graph graph;
        fscanf(file, "Debut:%*[^0-9]%d\n", &graph.start);
        fscanf(file, "Fin:%*[^0-9]%d\n", &graph.end);
        printf("Debut: %d\n", graph.start);
        printf("Fin: %d\n", graph.end);
        while (fscanf(file, "%d %*2[-<>] %d %d", &src, &dest,&weight) == 3) {
            if (src > maxVertex) {
                maxVertex = src;
            }
            if (dest > maxVertex) {
                maxVertex = dest;
            }
        }
        int numVertices = maxVertex + 1;
        graph = createGraph(numVertices);
        goToLine(file, lineNumber);

        long currentPosition = ftell(file);
        // Read and print the line
        char line[100];
        if (fgets(line, sizeof(line), file) != NULL) {
            printf("Current line: %s", line);
        } else {
            printf("Failed to read the line.\n");
        }

        // Restore the position
        fseek(file, currentPosition, SEEK_SET);
        
        while (fscanf(file, "%d %*2[-<>] %d %d", &src, &dest,&weight) == 3) {
            if (src != dest) {
                if (src < dest) {
                    addEdge(&graph, src, dest, weight);
                } else {
                    addEdge(&graph, dest, src, weight);
                }
            }
        }
        
        showAdjMat(graph,3);
       
        // Free dynamically allocated memory
        for (int i = 0; i < graph.numVertices; i++) {
            free(graph.adjacencyMatrix[i]);
        }
        free(graph.adjacencyMatrix);
        printf("Vertex number: %d\n",graph.numVertices);
}

/*thibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthib*/

/*
void dijkstra2(int graph[MAX_NODES][MAX_NODES], int size, int start) {
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
}*/
/*thibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthib*/

/*
int main() {
    char choice[20];
    FILE *file = NULL;


    printf("Choose a file to open:\n");
    printf("1. base.txt\n");
    printf("2. bonus.txt\n");
    printf("3. planete1.txt\n");
    printf("4. planete2.txt\n");
    printf("5. planete3.txt\n");
    printf("6. planete4.txt\n");
    printf("7. planete5.txt\n");
    printf("8. planete6.txt\n");
    printf("9. terrain1.txt\n");
    printf("10. terrain2.txt\n");
    printf("11. terrain3.txt\n");
    printf("12. type1.txt\n");
    printf("13. type2.txt\n");
    printf("14. typeSommet1.txt\n");
    printf("15. typeSommet2.txt\n");
    printf("16. to test others code\n");
    printf("Enter your choice: ");
    scanf("%s", choice);

     switch (atoi(choice)) {
        case 1:
            file = fopen("Data/base.txt", "r");
            printf("Choice: base.txt\n");
            break;
        case 2:
            file = fopen("Data/bonus.txt", "r");
            printf("Choice: bonus.txt\n");
            break;
        case 3:
            file = fopen("Data/planete1.txt", "r");
            printf("Choice: planete1.txt\n");
            break;
        case 4:
            file = fopen("Data/planete2.txt", "r");
            printf("Choice: planete2.txt\n");
            break;
        case 5:
            file = fopen("Data/planete3.txt", "r");
            printf("Choice: planete3.txt\n");
            break;
        case 6:
            file = fopen("Data/planete4.txt", "r");
            printf("Choice: planete4.txt\n");
            break;
        case 7:
            file = fopen("Data/planete5.txt", "r");
            printf("Choice: planete5.txt\n");
            break;
        case 8:
            file = fopen("Data/planete6.txt", "r");
            printf("Choice: planete6.txt\n");
            break;
        case 9:
            file = fopen("Data/terrain1.txt", "r");
            printf("Choice: terrain1.txt\n");
            break;
        case 10:
            file = fopen("Data/terrain2.txt", "r");
            printf("Choice: terrain2.txt\n");
            break;
        case 11:
            file = fopen("Data/terrain3.txt", "r");
            printf("Choice: terrain3.txt\n");
            break;
        case 12:
            file = fopen("Data/type1.txt", "r");
            printf("Choice: type1.txt\n");
            break;
        case 13:
            file = fopen("Data/type2.txt", "r");
            printf("Choice: type2.txt\n");
            break;
        case 14:
            file = fopen("Data/typeSommet1.txt", "r");
            printf("Choice: typeSommet1.txt\n");
            break;
        case 15:
            file = fopen("Data/typeSommet2.txt", "r");
            printf("Choice: typeSommet2.txt\n");
            break;
        case 16://to test others code
        
            int size = 5;
            int graph[MAX_NODES][MAX_NODES] = {{0, 0, 18, 0, 3},
                                                {8, 0, 4, 0, 0},
                                                {0, 0, 0, 0, 0},
                                                {0, 1, 0, 0, 0},
                                                {0, 10, 0, 2, 0}};
            
            
            //appeler la fonction dijkstra avec la matrice d'adjacence, la taille et le nœud de départ
            dijkstra2(graph, size, 4);
            printf("done\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
     }
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }
    printf("%s\n",choice);
    // File operations here...
    if (atoi(choice)==1)
    {
        //program for "base.txt"
        Process_base(file);

    }
    else if (atoi(choice)==2 || atoi(choice)==11)
    {
        //program for  "bonus.txt" "terrainx.txt"
        Process_bonus_terrain(file);

    }
    else if(atoi(choice)>2 && atoi(choice)<11 && atoi(choice)!=6 && atoi(choice)!=7 && atoi(choice)!=8)
    {
        //program for  "planetX.txt" "terrainx.txt" without weight
        Process_planet_terrain(file);
        
    }
    else if( atoi(choice)==6 || atoi(choice)==7 || atoi(choice)==8)
    {
        //program for  "planetX.txt" "terrainx.txt" with weight
      Process_planet_terrain_w(file);
        
    }
    else if(atoi(choice)==12 || atoi(choice)==13)
    {
        //program for "typeX.txt"*
        Process_type(file);

    }
    else if(atoi(choice)==14 || atoi(choice)==15)
    {
        //program for "typeSommetX.txt"
        Process_typeSommet(file);


    }

    fclose(file);
    
    return 0;
}
*/

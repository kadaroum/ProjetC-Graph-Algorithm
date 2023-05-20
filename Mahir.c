
#include "Struct.h"
#define MAX_NODES 1000


Struct_Graph createGraph(int numVertices) {
    Struct_Graph graph;
    graph.numVertices = numVertices;
    graph.start = -1;  // Initialize start to a valid default value
    graph.end = -1;  // Initialize end to a valid default value

    // Dynamically allocate memory for the adjacency matrix
    graph.adjacencyMatrix = (int**)malloc(numVertices * sizeof(int*));
    if (graph.adjacencyMatrix == NULL) {
        return graph;
    }
    for (int i = 0; i < numVertices; i++) {
        graph.adjacencyMatrix[i] = (int*)calloc(numVertices, sizeof(int));
        if (graph.adjacencyMatrix[i] == NULL) {

            printf("Failed to allocate memory for row %d of adjacency matrix\n", i);
            freeGraph(&graph);
            return graph;
        }
    }

    return graph;
}
void freeGraph(Struct_Graph* graph) {
    if (graph == NULL) {
        printf("Nothing to free\n");
        return;  // Nothing to free
    }
    for (int i = 0; i < graph->numVertices; i++) {
        free(graph->adjacencyMatrix[i]);
    }
    free(graph->adjacencyMatrix);  // Free the matrix itself
    // Set numVertices to 0 or any appropriate value indicating the graph is no longer valid
    graph->numVertices = 0;
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
Struct_Base *Process_base(FILE* file)
{
    int nbrVertices = countLines(file);

        Struct_Base *data = (Struct_Base*)malloc(nbrVertices * sizeof(Struct_Base));
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
            //printf("Vertex %d: weight=%d, nutritive value=%d\n",data[i].vertex_number, data[i].vertex_weight, data[i].vertex_nutritive_value);
        }

        return data;
}
Struct_Type *Process_type(FILE* file)
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

        return data;
}
Struct_VertexData *Process_typeSommet(FILE* file)
{
    int nbrVertices = countLines(file);

        Struct_VertexData * data = (Struct_VertexData*)malloc(nbrVertices * sizeof(Struct_VertexData));
        for (int i = 0; i < nbrVertices; i++) {
            fscanf(file, "%d %s", &data[i].vertex_number, data[i].terrain_type);
        }

        for (int i = 0; i < nbrVertices; i++) {
            printf("Vertex %d: biome = %s\n", data[i].vertex_number, data[i].terrain_type);
        }
        return data;
        
}
Struct_Graph Process_bonus_terrain(FILE* file){
    int src, dest, weight;
    char asciichar55;
    char asciichar76;
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
        while(fscanf(file,"%d %c%c %d %d\n",&src,&asciichar55,&asciichar76,&dest,&weight)==5){
        if(asciichar55 == '-'){
            //printf("%d -> %d\n",src,dest);
            addEdge(&graph,src,dest,weight);
        }
        if(asciichar55 == '<'){
            //printf("%d <- %d\n",src,dest);
            addEdge(&graph,dest,src,weight);
        }
    }
    //showAdjMat(graph,3);
    
    //printf("Vertex number: %d\n",graph.numVertices);
    return graph;
}
Struct_Graph Process_planet_terrain(FILE* file){
    //program for  "planetX.txt" "terrainx.txt" without weight
        
        Struct_Graph graph ;
        int src, dest, weight=1,start,end;
        char asciichar55;
        char asciichar76;
        int maxVertex=0;
        int lineNumber = 3;
        
        fscanf(file, "Debut:%*[^0-9]%d\n", &start);
        fscanf(file, "Fin:%*[^0-9]%d\n", &end);

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
        graph.start = start;
        graph.end  = end;
        // printf("Debut: %d\n", graph.start);
        // printf("Fin: %d\n", graph.end);
        goToLine(file, lineNumber);

        long currentPosition = ftell(file);
        // Read and print the line
        char line[100];
        if (fgets(line, sizeof(line), file) != NULL) {
           //printf("Current line: %s", line);
        } else {
           // printf("Failed to read the line.\n");
        }

        // Restore the position
        fseek(file, currentPosition, SEEK_SET);
        
        while(fscanf(file,"%d %c%c %d\n",&src,&asciichar55,&asciichar76,&dest)==4){
        if(asciichar55 == '-'){
            //printf("%d -> %d\n",src,dest);
            addEdge(&graph,src,dest,1);
        }
        if(asciichar55 == '<'){
            //printf("%d <- %d\n",src,dest);
            addEdge(&graph,dest,src,1);
        }

        }
       //showAdjMat(graph,1);
        //printf("Vertex number: %d\n",graph.numVertices);
        return graph;
        
}
Struct_Graph Process_planet_terrain_w(FILE* file){
    int src, dest, weight,start,end;
        char asciichar55;
        char asciichar76;
        int maxVertex=0;
        int lineNumber = 3;
        
        Struct_Graph graph;
        fscanf(file, "Debut:%*[^0-9]%d\n",&start);
        fscanf(file, "Fin:%*[^0-9]%d\n",&end);

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
        graph.start = start;
        graph.end  = end;
        printf("Debut: %d\n", graph.start);
        printf("Fin: %d\n", graph.end);
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
        
        while(fscanf(file,"%d %c%c %d %d\n",&src,&asciichar55,&asciichar76,&dest,&weight)==5){
        if(asciichar55 == '-'){
            printf("%d -> %d\n",src,dest);
            addEdge(&graph,src,dest,weight);
        }
        if(asciichar55 == '<'){
            printf("%d <- %d\n",src,dest);
            addEdge(&graph,dest,src,weight);
        }

        }
        
        showAdjMat(graph,3);
        printf("Vertex number: %d\n",graph.numVertices);
        return graph;
}

/*thibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthib*/


/*thibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthibthib*/

void dijkstra2(Struct_Graph graph) {
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

    while (!visited[graph.end]) {
        int minDistance = INT_MAX;
        int minIndex = -1;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v] && distance[v] <= minDistance) {
                minDistance = distance[v];
                minIndex = v;
            }
        }

        if (minIndex == -1) {
            printf("No path exists between the start and end vertices.\n");
            break;
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

    if (prev[graph.end] != -1 && distance[graph.end] != INT_MAX) {
        printf("Vertex\t Distance\tPath\n");
        printf("%d\t %d\t\t%d", graph.end, distance[graph.end], graph.end);
        int j = graph.end;
        while (j != graph.start && prev[j] != -1) {
            printf(" <- %d", prev[j]);
            j = prev[j];
        }
        printf("\n");
        printf("Shortest distance from vertex %d to vertex %d: %d\n", graph.start, graph.end, distance[graph.end]);
    } else {
        printf("No path exists between the start and end vertices.\n");
    }

    free(distance);
    free(visited);
    free(prev);
}
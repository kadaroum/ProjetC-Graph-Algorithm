#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define FONT_PATH_SIZE 1024

#define MAX_NODES 1000



//Coordonées X Y
typedef struct Point{
    int x;
    int y;
}Point;

//Structure de graph
typedef struct Graph{
int nbrSommets;
int * matriceAdja;
}Gaph;

typedef struct {
    SDL_Rect rect;
    SDL_bool isHovered;
}Button;

typedef struct {
    int vertex_number, vertex_weight, vertex_nutritive_value;
}Struct_Base;

typedef struct {
    int src ,dest,weight;
}Struct_Edge;

typedef struct {
    int** adjacencyMatrix;
    int numVertices;
    int start,end;
} Struct_Graph;

typedef struct {
    char name[20];
    float value;
} Struct_Type;

typedef struct {
    int vertex_number;
    char terrain_type[20];
} Struct_VertexData;

Struct_Graph Process_planet_terrain_w(FILE* file);

Struct_Graph Process_planet_terrain(FILE* file);

Struct_Graph Process_bonus_terrain(FILE* file);

Struct_VertexData *Process_typeSommet(FILE* file);

Struct_Type *Process_type(FILE* file);

Struct_Base *Process_base(FILE* file);

void goToLine(FILE* file, int lineNumber);

int countLines(FILE* file);

void showAdjMat(Struct_Graph graph,int spacing);

void addEdge(Struct_Graph* graph, int src, int dest, int weight);

Struct_Graph createGraph(int numVertices);

void afficherMenu(SDL_Renderer* renderer);

void dijkstra(Struct_Graph graph);

int CollisionSommetCursor(SDL_Event event, int graphLength, Point points, int radius);

struct coordonnee* AttributionCoo(Point* points, int NbrSommet, float radius);

void DrawArcs(Point A, Point B, SDL_Renderer* rend);

SDL_Surface* renderNumberToSurface(TTF_Font* font, int number, SDL_Color color);

void AfficheTxtSurPoint(SDL_Renderer* rend, Point point, int radius, int num);

void DrawGraph(int graphLength, Point points[], int** graph1, SDL_Renderer* render, SDL_Event event);
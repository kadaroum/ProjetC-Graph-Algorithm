#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define FONT_PATH_SIZE 1024*

#define MAX_NODES 1000 *FONT_PATH_SIZE



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

void dijkstra(int graph[MAX_NODES][MAX_NODES], int size, int start);

int CollisionSommetCursor(SDL_Event event, int graphLength, Point points, int radius);

struct coordonnee* AttributionCoo(Point* points, int NbrSommet, float radius);

void DrawArcs(Point A, Point B, SDL_Renderer* rend);

SDL_Surface* renderNumberToSurface(TTF_Font* font, int number, SDL_Color color);

void AfficheTxtSurPoint(SDL_Renderer* rend, Point point, int radius, int num);

void DrawGraph(int graphLength, Point points[], int** graph1, SDL_Renderer* render, SDL_Event event);



#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <limits.h>

#define MAX_NODES 1000

//Taille Ecran
const int TAILLE_X = 640*2;
const int TAILLE_Y = 480*2;
const int CENTER_X = TAILLE_X/2;
const int CENTER_Y = TAILLE_Y/2;

//Colors
const int BLACK = 0;
const int WHITE = 255;

//Coordonées X Y
typedef struct{
    int x;
    int y;
}Point;

//Structure de graph
typedef struct{
int nbrSommets;
int * matriceAdja;
}Gaph;


struct coordonnee * AttributionCoo(Point* points,int NbrSommet, float radius){
    float angle_step = 2 * M_PI / NbrSommet;
    for (int i = 0; i < NbrSommet; i++) {
        float angle = i * angle_step;
        points[i].x = radius * cos(angle);
        points[i].y = radius * sin(angle);
    }
}

void DrawArcs(Point A,Point B,SDL_Renderer * rend){
     SDL_RenderDrawLine(rend,CENTER_X + A.x, CENTER_Y + A.y, CENTER_X + B.x,CENTER_Y + B.y);
}

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
 
void DrawGraph(int graphLength, int **graph1,SDL_Renderer* render){
    printf("\n");
    Point points[5];
    float radius = 150;
    AttributionCoo(points,5,radius);
    for(int i = 0; i < 5; i++){
        filledCircleRGBA(render,CENTER_X + points[i].x,CENTER_Y + points[i].y,(radius/graphLength)*1.2,WHITE,WHITE,WHITE,WHITE);
    }
    for(int x = 0; x != 5; x++){
        for (int y = 0; y != 5; y++)
        {
            printf("%d %d = %d\n",y,x,graph1[y][x]);
            if(graph1[y][x] != 0){
                
                DrawArcs(points[y],points[x],render);
            }
        }
    }
 }

void AfficheTxt(SDL_Renderer* rend){
    //TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);


}


int main(int argc, char* argv[]) {
   
    SDL_Init( SDL_INIT_VIDEO );
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("SDL2 gfx Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TAILLE_X, TAILLE_Y, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    int graph1[5][5] = {{0, 1, 1, 1, 1},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 0},
                        {0, 1, 0, 0, 0},
                        {1, 0, 0, 0, 0}};
   int size = 5;
   int** graph = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        graph[i] = (int*)malloc(size * sizeof(int));
    }

    // Initialize the array with some values
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            graph[i][j] = graph1[i][j];
        }
    }
   

    DrawGraph(5,graph,renderer);
    
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    printf("\n");

    for (int i = 0; i < size; i++) {
        free(graph[i]);
    }
    free(graph);
   return 0;
}
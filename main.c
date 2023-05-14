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
int addition(int a){
    a++;
    return a;
}

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



int main(int argc, char* argv[]) {
   
    SDL_Window* window = SDL_CreateWindow("SDL2 gfx Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TAILLE_X, TAILLE_Y, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    int num_points = 400;
    float radius = 450;
    Point point[num_points];

    AttributionCoo(point,num_points,radius);
    for(int i = 0; i < num_points; i++){
        circleRGBA(renderer,CENTER_X + point[i].x,CENTER_Y + point[i].y,(radius/num_points)*2,BLACK,BLACK,BLACK,BLACK);
    }
   
    //circleRGBA(renderer, 320, 240, 80, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for(int i = 1; i != num_points-1; i++){
        for(int y = 0; y != 2; y++){
    DrawArcs(point[y],point[i],renderer);
        }
    }
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();

   /*
     // Créer la matrice d'adjacence

    int size = 5;
    int graph[MAX_NODES][MAX_NODES] = {{0, 0, 18, 0, 3},
                                        {8, 0, 4, 0, 0},
                                        {0, 0, 0, 0, 0},
                                        {0, 1, 0, 0, 0},
                                        {0, 10, 0, 2, 0}};
    
    
    //appeler la fonction dijkstra avec la matrice d'adjacence, la taille et le nœud de départ
    dijkstra(graph, size, 0);
    return 0;
    */
}
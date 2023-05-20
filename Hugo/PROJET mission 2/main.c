#include "code.h"



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

int CollisionSommetCursor(SDL_Event event,int graphLength,Point points, int radius){
    if(event.motion.x <= points.x + radius && event.motion.x >= points.x - radius && event.motion.y <= points.y + radius && event.motion.y >= points.y - radius){
        return 1;
    }
    return 0;
}

struct coordonnee * AttributionCoo(Point* points,int NbrSommet, float radius){
    float angle_step = 2 * M_PI / NbrSommet;
    for (int i = 0; i < NbrSommet; i++) {
        float angle = i * angle_step;
        points[i].x = radius * cos(angle) + CENTER_X;
        points[i].y = radius * sin(angle) + CENTER_Y;
    }
}

void DrawArcs(Point A,Point B,SDL_Renderer * rend){
     SDL_RenderDrawLine(rend,A.x,A.y,B.x,B.y);

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
SDL_Surface* renderNumberToSurface(TTF_Font* font, int number, SDL_Color color) {
    char numberStr[20]; // Taille suffisamment grande pour stocker la chaîne de caractères du nombre
    sprintf(numberStr, "%d", number); // Conversion du nombre entier en une chaîne de caractères

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, numberStr, color);
    return surfaceMessage;
}

void AfficheTxtSurPoint(SDL_Renderer* rend,Point point,int radius, int num){
    TTF_Font* Sans = TTF_OpenFont("arial.ttf", 100);
    SDL_Color White = {0, 0, 0};
    SDL_Surface* surfaceMessage = renderNumberToSurface(Sans, num, White); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(rend, surfaceMessage);
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = point.x - radius;  //controls the rect's x coordinate 
    Message_rect.y = point.y - radius; // controls the rect's y coordinte
    Message_rect.w = radius*2; // controls the width of the rect
    Message_rect.h = radius*2; // controls the height of the rect
    SDL_RenderCopy(rend, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    
    SDL_DestroyTexture(Message);
    TTF_CloseFont(Sans);
}
 
void DrawGraph(int graphLength,Point points[graphLength], int **graph1,SDL_Renderer* render,SDL_Event event){
    printf("\n");
    SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
    float radius = (400/graphLength)*1.75;
    int pressed = 0;
    if(event.button.button == SDL_BUTTON_LEFT){
        for (int a = 0; a != graphLength; a++)
        {
            if(CollisionSommetCursor(event,graphLength,points[a],radius) == 1 ){
                points[a].x = event.motion.x;
                points[a].y = event.motion.y;
                pressed = 1;
            } 
            
        }

    }
    for(int i = 0; i < graphLength; i++){
        filledCircleRGBA(render,points[i].x,points[i].y,radius,WHITE,WHITE,WHITE,WHITE);
        //AfficheTxtSurPoint(render,points[i],radius,i);
    }
    

    


    for(int x = 0; x < graphLength; x++){
        for (int y = 0; y < graphLength  ; y++)
        {
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

  int nbgrp=1;
  int nbgrp2=1;

 



    FILE *file8 = fopen("Donnees/terrain3.txt", "r");
    if (file8 == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }
    Process_planet_terrain(file8);


















    SDL_Init( SDL_INIT_VIDEO );
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("SDL2 gfx Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TAILLE_X, TAILLE_Y, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    int graph1[34][34] = {{0, 1, 1, 1, 1},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 0},
                        {0, 1, 0, 0, 0},
                        {1, 0, 0, 0, 0}};
                    
   int size = 34;
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
   SDL_Event event;

    //DrawGraph(5,graph,renderer);
    int graphLength = 34;
    Point points[graphLength];
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    AttributionCoo(points,graphLength,400);
    DrawGraph(graphLength,points,graph,renderer,event);

   
    int running = 1;
    while ((running))
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            
            case SDL_MOUSEMOTION:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);
            DrawGraph(graphLength,points,graph1,renderer,event);
            //filledCircleRGBA(renderer,mouseX,mouseY,20,WHITE,WHITE,WHITE,WHITE);
            SDL_RenderPresent(renderer);
            
            }
        
        }
    }
     


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    printf("\n");

    for (int i = 0; i < size; i++) {
        free(graph[i]);
    }
    free(graph);




















  /*
  FILE *file5 = fopen("Donnees/terrain2.txt", "r");
  FILE *file6 = fopen("Donnees/type2.txt", "r");
  FILE *file7 = fopen("Donnees/typeSommet2.txt", "r");
  graphe *g = ini_graphe(file5,file6);
  printf("mars : %d",g->nbpeak);
  makegraphe(file5,g,&nbgrp,file6,file7);
  int** tabchemin=(int**)malloc(1000* sizeof(int*));
  for(int i=0 ; i<1000 ; i++){
        tabchemin[i] = (int*)malloc(1000* sizeof(int));

  }
  int cost = 0;

  for(int o = 0;o<250;o++){
    tabchemin[o][0]=0;
  }
  
    int did;
    int did2;
    
  AAAAAAAAAAAAAAAAAAAAAAAAAAA(g,g->debut,tabchemin,1,0,0);


printf("\n");
  for(int o = 0;o<60;o++){
    for(int h =0;h<1000;h++){
        printf("%2d ",tabchemin[o][h]);
        did=1;
        did2=1;
        
    }
    if(did==1){
    printf("did1\n");
    }
    did=0;
  }
    int oui;
    int itshere=0;
    int gre=1;
  int** thetab=(int**)malloc(1000* sizeof(int*));
  for(int i=0 ; i<1000 ; i++){
        thetab[i] = (int*)malloc(1000* sizeof(int));

  }
  thetab[0][0]=0;
  float thecost=10000000;
  float costtt=0;
    for(int o = 0;o<1000;o++){
        for(int h =0;h<1000;h++){
            if(tabchemin[h][o]==g->end){
                printf("h:%do:%d ",h,o);
                while(tabchemin[gre][o]!=0){
                costtt+=g->costofeachtyle[tabchemin[gre][o]];
                thetab[gre][oui]=tabchemin[gre][o];
                gre++;
                
                }
                oui+=1;
                gre =1;
                printf("\ncost:%1.1f cost2:%1.1f \n",costtt,thecost);
                if(thecost>costtt){
                    thecost=costtt;
                    itshere=oui-1;
                }
                costtt=0;
            }
        }
    }
    printf("\nthe cost plus court est :%1.1f\n",thecost);
    for(int o = 0;o<50;o++){
        printf("%d ",thetab[o][itshere]);
    }  
    int** thematrix=(int**)malloc(1000* sizeof(int*));
  for(int i=0 ; i<1000 ; i++){
        thematrix[i] = (int*)malloc(1000* sizeof(int));

  }
  int av=1;
  thematrix[0][thetab[av][itshere]]=1;
  for(int p = 0;p<g->nbpeak;p++){
  for(int o =1;o<=g->nbpeak;o++){
    if(o==thetab[av][itshere] && thetab[av+1][itshere]!=0){
        printf("\n%d %d \n",thetab[av][itshere],thetab[av+1][itshere]);

        av+=1;
        thematrix[o][thetab[av][itshere]]=1;
        
    }
  }
  }
    
    


  
    

   SDL_Init( SDL_INIT_VIDEO );
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("SDL2 gfx Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TAILLE_X, TAILLE_Y, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    int graph1[34][34] = {{0, 1, 1, 1, 1},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 0},
                        {0, 1, 0, 0, 0},
                        {1, 0, 0, 0, 0}};
                    
   int size = 100;
   int** graph = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        graph[i] = (int*)malloc(size * sizeof(int));
    }

    // Initialize the array with some values
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            graph[i][j] = g->matgraphe[i][j];
        }
    }
   SDL_Event event;

    //DrawGraph(5,graph,renderer);
    int graphLength = 100;
    Point points[graphLength];
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    AttributionCoo(points,graphLength,400);
    DrawGraph(graphLength,points,graph,renderer,event);

   
    int running = 1;
    while ((running))
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            
            case SDL_MOUSEMOTION:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);
            DrawGraph(graphLength,points,thematrix,renderer,event);
            //filledCircleRGBA(renderer,mouseX,mouseY,20,WHITE,WHITE,WHITE,WHITE);
            SDL_RenderPresent(renderer);
            
            }
        
        }
    }
     


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    printf("\n");

    for (int i = 0; i < size; i++) {
        free(graph[i]);
    }
    free(graph);
    


  fclose(file5);
  fclose(file6);
  fclose(file7);
  */
  
/*pour mission 3 terrain1
  FILE *file2 = fopen("Donnees/terrain1.txt", "r");
  FILE *file3 = fopen("Donnees/type1.txt", "r");
  FILE *file4 = fopen("Donnees/typeSommet1.txt", "r");
  graphe *g = ini_graphe(file2,file3);
  printf(" %d",g->nbpeak);
  makegraphe(file2,g,&nbgrp2,file3,file4);
  int** tabchemin=(int**)malloc(1000* sizeof(int*));
  for(int i=0 ; i<1000 ; i++){
        tabchemin[i] = (int*)malloc(1000* sizeof(int));

  }
  int cost = 0;

  for(int o = 0;o<250;o++){
    tabchemin[o][0]=0;
  }
  
    int did;
    int did2;
  AAAAAAAAAAAAAAAAAAAAAAAAAAA(g,g->debut,tabchemin,1,0,0);


printf("\n");
  for(int o = 0;o<60;o++){
    for(int h =0;h<1000;h++){
        printf("%2d ",tabchemin[o][h]);
        did=1;
        did2=1;
        
    }
    if(did==1){
    printf("did1\n");
    }
    did=0;
  }
    int oui;
    int itshere=0;
    int gre=1;
  int** thetab=(int**)malloc(1000* sizeof(int*));
  for(int i=0 ; i<1000 ; i++){
        thetab[i] = (int*)malloc(1000* sizeof(int));

  }
  thetab[0][0]=0;
  float thecost=10000000;
  float costtt=0;
    for(int o = 0;o<1000;o++){
        for(int h =0;h<1000;h++){
            if(tabchemin[h][o]==g->end){
                printf("h:%do:%d ",h,o);
                while(tabchemin[gre][o]!=0){
                costtt+=g->costofeachtyle[tabchemin[gre][o]];
                thetab[gre][oui]=tabchemin[gre][o];
                gre++;
                
                }
                oui+=1;
                gre =1;
                printf("\ncost:%1.1f cost2:%1.1f \n",costtt,thecost);
                if(thecost>costtt){
                    thecost=costtt;
                    itshere=oui-1;
                }
                costtt=0;
            }
        }
    }
    printf("\nthe cost plus court est :%1.1f\n",thecost);
    for(int o = 0;o<50;o++){
        printf("%d ",thetab[o][itshere]);
    }
    int** thematrix=(int**)malloc(1000* sizeof(int*));
  for(int i=0 ; i<1000 ; i++){
        thematrix[i] = (int*)malloc(1000* sizeof(int));

  }
  int av=1;
  thematrix[0][thetab[av][itshere]]=1;
  for(int p = 0;p<g->nbpeak;p++){
  for(int o =1;o<=g->nbpeak;o++){
    if(o==thetab[av][itshere] && thetab[av+1][itshere]!=0){
        printf("\n%d %d \n",thetab[av][itshere],thetab[av+1][itshere]);

        av+=1;
        thematrix[o][thetab[av][itshere]]=1;
        
    }
  }
  }



 SDL_Init( SDL_INIT_VIDEO );
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("SDL2 gfx Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TAILLE_X, TAILLE_Y, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    int graph1[34][34] = {{0, 1, 1, 1, 1},
                        {0, 0, 0, 0, 0},
                        {0, 0, 0, 1, 0},
                        {0, 1, 0, 0, 0},
                        {1, 0, 0, 0, 0}};
                    
   int size = 25;
   int** graph = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        graph[i] = (int*)malloc(size * sizeof(int));
    }

    // Initialize the array with some values
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            graph[i][j] = g->matgraphe[i][j];
        }
    }
   SDL_Event event;

    //DrawGraph(5,graph,renderer);
    int graphLength = 25;
    Point points[graphLength];
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    AttributionCoo(points,graphLength,400);
    DrawGraph(graphLength,points,graph,renderer,event);

   
    int running = 1;
    while ((running))
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                break;
            
            case SDL_MOUSEMOTION:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);
            DrawGraph(graphLength,points,g->matgraphe,renderer,event);
            //filledCircleRGBA(renderer,mouseX,mouseY,20,WHITE,WHITE,WHITE,WHITE);
            SDL_RenderPresent(renderer);
            
            }
        
        }
    }
     


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    printf("\n");

    for (int i = 0; i < size; i++) {
        free(graph[i]);
    }
    free(graph);
  fclose(file2);
  fclose(file3);
  fclose(file4);
  */
  return 0;

}

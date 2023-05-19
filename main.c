#include "Struct.h"


int main(int argc, char* argv[]) {
   
    SDL_Init( SDL_INIT_VIDEO );
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("SDL2 gfx Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TAILLE_X, TAILLE_Y, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

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
    int graphLength = 20;
    Point points[graphLength];
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    AttributionCoo(points,graphLength,400);
    DrawGraph(graphLength,points,graph,renderer,event);
    //dijkstra(graph,graphLength,0);
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
            

            case SDL_MOUSEBUTTONDOWN :
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);
            DrawGraph(graphLength,points,graph,renderer,event);
            SDL_RenderPresent(renderer);

            }
        
        }
    }
     


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    printf("\n");

    for (int i = 0; i < size; i++) {
        free(graph[i]);
    }
    free(graph);
   return 0;
}

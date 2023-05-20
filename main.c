#include "Struct.h"

const int TAILLE_X = 640 * 2.7;
const int TAILLE_Y = 480 * 2;

const int CENTER_X = TAILLE_X / 2;
const int CENTER_Y = TAILLE_Y / 2;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("SDL2 gfx Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, TAILLE_X, TAILLE_Y, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    FILE* fichier1 = fopen("Data/planete1.txt","r");
    Struct_Graph Graph = Process_planet_terrain(fichier1);
    // Your code to process planet terrain and initialize the graph

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);



    Point points[Graph.numVertices];
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    AttributionCoo(points, Graph.numVertices, 400);
    SDL_Event event;
    int running = 1;
    while (running)
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
                DrawGraph(Graph.numVertices,points,Graph.adjacencyMatrix,renderer,event);
                SDL_RenderPresent(renderer);
                break;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("\n");
    TTF_Quit();
    return 0;
}
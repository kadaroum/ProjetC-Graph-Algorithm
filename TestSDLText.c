#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <unistd.h>

#define FONT_PATH_SIZE 1024

int main(int argc, char* argv[]) {
    // Étape 1 : Inclure les en-têtes nécessaires

    // Étape 2 : Initialiser la bibliothèque SDL et créer une fenêtre
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Affichage de texte avec SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Étape 3 : Initialiser la bibliothèque SDL_ttf
    TTF_Init();

    // Étape 4 : Charger la police souhaitée
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        char fontPath[FONT_PATH_SIZE];
        snprintf(fontPath, FONT_PATH_SIZE, "%s/arial.ttf", cwd);
        TTF_Font* font = TTF_OpenFont(fontPath, 50); // Remplacez "arial-font/arial.ttf" par le chemin de votre police de caractères Arial

        if(!font)
{
    printf("Erreur de création de la police : %s", TTF_GetError());
    return 1;
}

        SDL_RenderDrawLine(renderer,0,0,10,10);
        // Étape 5 : Créer une surface SDL à partir du texte que vous souhaitez afficher
        SDL_Color color = { 255, 0, 255 }; // Couleur du texte (blanc dans cet exemple)
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Votre texte", color); // Remplacez "Votre texte" par le texte que vous souhaitez afficher

        // Étape 6 : Créer une texture SDL à partir de la surface
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        // Étape 7 : Libérer la surface maintenant que la texture est créée
        SDL_FreeSurface(textSurface);

        // Étape 8 : Définir la position où vous souhaitez afficher le texte
        SDL_Rect textRect;
        textRect.x = 100; // Coordonnée X
        textRect.y = 100; // Coordonnée Y

        // Étape 9 : Effacer le rendu précédent et afficher la texture du texte
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_RenderPresent(renderer);

        // Étape 10 : Attendre la fermeture de la fenêtre
        SDL_Event event;
        while (SDL_WaitEvent(&event))
        {
            if (event.type == SDL_QUIT)
                break;
        }

        // Étape 11 : Libérer la mémoire utilisée
        SDL_DestroyTexture(textTexture);
        TTF_CloseFont(font);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

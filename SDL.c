#include "Struct.h"

const int TAILLE_X = 640 * 2;
const int TAILLE_Y = 480 * 2;

const int CENTER_X = TAILLE_X / 2;
const int CENTER_Y = TAILLE_Y / 2;

const int BLACK = 0;
const int WHITE = 255;

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
    int isCollision;
    if(event.button.button == SDL_BUTTON_LEFT){
        for (int a = 0; a != graphLength; a++)
        {
            isCollision = CollisionSommetCursor(event,graphLength,points[a],radius);
            if(isCollision == 1 ){
                points[a].x = event.motion.x;
                points[a].y = event.motion.y;
                pressed = 1;
            } 
            
        }

    }
    for(int i = 0; i < graphLength; i++){
        filledCircleRGBA(render,points[i].x,points[i].y,radius,WHITE,WHITE,WHITE,WHITE);
        AfficheTxtSurPoint(render,points[i],radius,i+1);
    }
    for(int x = 0; x != 5; x++){
        for (int y = 0; y != 5; y++)
        {
            if(graph1[y][x] != 0){
                
                DrawArcs(points[y],points[x],render);
            }
        }
    }
 }

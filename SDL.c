#include "Struct.h"

extern const int TAILLE_X;
extern const int TAILLE_Y;

extern const int CENTER_X;
extern const int CENTER_Y;

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
// B.x -> A.y  A.y->
void DrawArrow(Point A, Point B, SDL_Renderer* rend, int radius) {
    // Calculate the vector from A to B
    double dx = B.x - A.x;
    double dy = B.y - A.y;
    double length = sqrt(dx * dx + dy * dy);
    double dirX = dx / length;
    double dirY = dy / length;

    // Calculate the coordinates of the end point (B - radius)
    int endX = B.x - radius * dirX;
    int endY = B.y - radius * dirY;

    // Draw a line between A and the end point
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255); // White color
    SDL_RenderDrawLine(rend, A.x, A.y, endX, endY);

    // Calculate the arrowhead size based on the radius
    double arrowSize = radius *0.75  // Adjust this factor to change the angle

    // Calculate the coordinates of the arrowhead
    int arrowX1 = endX - arrowSize * dirX + arrowSize * dirY;
    int arrowY1 = endY - arrowSize * dirY - arrowSize * dirX;
    int arrowX2 = endX - arrowSize * dirX - arrowSize * dirY;
    int arrowY2 = endY - arrowSize * dirY + arrowSize * dirX;

    // Draw the arrowhead
    SDL_RenderDrawLine(rend, endX, endY, arrowX1, arrowY1);
    SDL_RenderDrawLine(rend, endX, endY, arrowX2, arrowY2);
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

void 


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
    for(int x = 0; x != graphLength; x++){
        for (int y = 0; y != graphLength; y++)
        {
            if(graph1[y][x] != 0){
                
                DrawArrow(points[y],points[x],render,radius);
            }
        }
    }
 }



/*
void afficherMenu(SDL_Renderer* renderer) {
    // Chargement de l'image de fond
    //SDL_Surface* backgroundSurface = IMG_Load("StarImage.png");
    if (!backgroundSurface) {
        printf("Erreur lors du chargement de l'image de fond : %s\n", IMG_GetError());
        return;
    }

    // Conversion de la surface en texture
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture) {
        printf("Erreur lors de la création de la texture de fond : %s\n", SDL_GetError());
        return;
    }

    // Chargement des images pour les boutons
    SDL_Surface* buttonSurface = IMG_Load("bouton.png");
    if (!buttonSurface) {
        printf("Erreur lors du chargement de l'image du bouton : %s\n", IMG_GetError());
        SDL_DestroyTexture(backgroundTexture);
        return;
    }

  
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

       


 
}


*/
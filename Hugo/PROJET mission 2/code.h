#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <limits.h>

typedef struct graphe graphe;
struct graphe{
    char char1;
    char char2;
    int debut;
    int end;
    int nbpeak;
    int nbintype1;
    float **matgraphe;
    int *matgrp;
    int **test;
    int *mintheo;
    char **type;
    float *coutpartype;
    float *costofeachtyle;

    float valeurattheend;
};

graphe *ini_graphe(FILE *file1,FILE *file2);
void makegraphe(FILE *file1,graphe *g,int *nbgrp,FILE *file2,FILE *file3);
void makegraphe2(FILE *file1,graphe *g,int *nbgrp,FILE *file2,FILE *file3,graphe *gr2);
int* AAAAAAAAAAAAAAAAAAAAAAAAAAA(graphe *g,int iofthegraph ,int **tabchemin,int xofthetab,int yofthetab, float cost);
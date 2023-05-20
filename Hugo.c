#include "Struct.h"


graphe *ini_graphe(FILE *file1,FILE *file2){
    graphe* g = (graphe*)malloc(sizeof(graphe));
    for(int i = 0;i<7;i++){
        fscanf(file1,"%c",&g->char1);
        printf("%c ",g->char1);
    }
    fscanf(file1, "%d", &g->debut);
    printf("%d ",g->debut);
    
   for(int i = 0;i<5;i++){
        fscanf(file1,"%c",&g->char1);
        printf("%c ",g->char1);
    }
    fscanf(file1, "%d", &g->end);
    g->nbpeak=g->end+1-g->debut;
    g->matgraphe=(float**)malloc(g->nbpeak * sizeof(float*));
    for(int i=0 ; i<g->nbpeak ; i++){
        g->matgraphe[i] = (float*)malloc(g->nbpeak * sizeof(float));
    }
    g->test=(int**)malloc(g->nbpeak * sizeof(int*));
    for(int i=0 ; i<g->nbpeak ; i++){
        g->test[i] = (int*)malloc(g->nbpeak * sizeof(int));
    }
    g->matgrp = (int*)malloc(g->nbpeak * sizeof(int));
    g->mintheo=(int*)malloc(g->nbpeak * sizeof(int));
    fscanf(file2,"%d",&g->nbintype1);
    g->type=(char**)malloc(g->nbintype1 * sizeof(char*));
    for(int i=0 ; i<20 ; i++){
        g->type[i] = (char*)calloc(20 , sizeof(char));
    }
    g->coutpartype = (float*)malloc(g->nbintype1 * sizeof(float));
    g->costofeachtyle = (float*)malloc(g->nbpeak * sizeof(float));
return g;
}

int** AAAAAAAAAAAAAAAAAAAAAAAAAAA(graphe *g,int iofthegraph ,int **tabchemin,int iofthetab,int yofthetab, float cost){ 
    float costt=0;
    float costtt=0;
    int gre=1;
    int gre2 =1;

    while(tabchemin[gre][yofthetab]!=0){
                costtt+=g->costofeachtyle[tabchemin[gre][yofthetab]];
                gre++;
            }
            printf("\n cost:%1.1f\n",costtt);
    
    int no =0;
    if(iofthegraph==g->end){
        g->valeurattheend=cost;
        printf("%d",yofthetab);
        return tabchemin;
    }
    for(int i = 0;i<g->nbpeak;i++){
        for(int h =0;h<=iofthetab;h++){
            for(int j =0;j<=yofthetab;j++){
                    if(i==tabchemin[h][j] && tabchemin[h][j] != 0 && gre2<=gre){
                            while(tabchemin[gre2][yofthetab]!=0){
                            costt+=g->costofeachtyle[tabchemin[gre2][yofthetab]];
                            gre2++;
                        }
                        if(costt+0.1>costtt){
                            no = 1;
                           printf("no%d",h);
                        }
                        costt=0;
                        gre2=1;
                    }
            }
        }
        if(g->matgraphe[iofthegraph][i] != 0 && g->matgraphe[iofthegraph][i] != 8 &&g->matgraphe[iofthegraph][i] != 6 && no ==0){
            while(tabchemin[iofthetab][yofthetab]!=0){
                yofthetab+=1;
                for(int s = 1;s<iofthetab;s++){
                tabchemin[s][yofthetab]=tabchemin[s][yofthetab-1];
                }
            }
            printf("yes%d",i);  
            tabchemin[iofthetab][yofthetab]=i;
            AAAAAAAAAAAAAAAAAAAAAAAAAAA(g,i,tabchemin,iofthetab+1,yofthetab,cost+g->matgraphe[iofthegraph][i]);
        }
        no=0;
    }
}

void makegraphe(FILE *file1,graphe *g,int *nbgrp,FILE *file2,FILE *file3){

    int entry1;
    int entry2;
    int entry3;
    char char21;
    int y = 0;
    for(int k = 0;k<g->nbintype1;k++){
        for(int h = 0 ;h<20;h++){
            g->type[k][h]='\0';
        }
    }
    for(int i = 0;i<g->nbintype1;i++){
        while(fscanf(file2,"%c",&char21)==1 && char21!=' '){
            printf("%c",char21);
            g->type[i][y]=char21;
            y++;
        }
        fscanf(file2,"%f",&g->coutpartype[i]);
        printf(" %f\n",g->coutpartype[i]);
        y=0;
    }
    int itsthisnumber;
    int verifier=0;
    int verifier2=0;
    y = 0;
    //char *typesommet = (char*)malloc(20 * sizeof(char));
    char *typesommet = (char*)calloc(20, sizeof(char));
    for(int i = 0;i<g->nbpeak;i++){
        fscanf(file3,"%c",&char21);
        fscanf(file3,"%c",&char21);
        if(char21 != ' '){
            fscanf(file3,"%c",&char21);
        }
        while(fscanf(file3,"%c",&char21)==1 && char21 != '\n' && y <=10){
        typesommet[y] = char21;
        y++;
        }
    printf("\n");
    printf("%s",typesommet);
    for(int o = 0;o<g->nbintype1;o++){
        for(int cv = 0;cv<10;cv++){
            printf("%c",g->type[o][cv]);
            printf("%c",typesommet[cv]);
            if(g->type[o][cv+1]==typesommet[cv]){
                verifier+=1;
            }
            printf("%d",verifier);
            verifier2+=1;
        }
        if(verifier2 ==verifier){
            itsthisnumber=o;
        }
        verifier2=0;
        verifier=0;
    }
    printf("\n");


    g->costofeachtyle[i]=g->coutpartype[itsthisnumber];
    printf("%f\n",g->costofeachtyle[i]);

    memset(typesommet, 0, 20 * sizeof(char));
    y = 0;
    }

    for(int h = 0;h<g->nbpeak;h++){
    printf("\n%f\n",g->costofeachtyle[h]);
    }

    char asciichar76;
    char asciichar55;
    
    entry3 = 2;
    while(fscanf(file1,"%d %c%c %d\n",&entry1,&asciichar55,&asciichar76,&entry2)==4){
        if(asciichar55 == '-'){
            printf("%d -> %d\n",entry1,entry2);
            g->matgraphe[entry1][entry2]=g->costofeachtyle[entry2];
        }
        if(asciichar55 == '<'){
            printf("%d <- %d\n",entry1,entry2);
            g->matgraphe[entry2][entry1]=g->costofeachtyle[entry1];
        }

    }
        printf("\nMatrice ces couts :\n");
	for(int i=0; i<g->nbpeak; i++){
		for(int j=0; j<g->nbpeak; j++){
			printf(" %1.1f", g->matgraphe[i][j]);
		}
		printf("\n");
	}

    int bidule = 0;
    for(int i=0; i<g->nbpeak; i++){
		for(int j=0; j<g->nbpeak; j++){
			if(g->matgraphe[i][j] != 0.000000){
                bidule+=1;
            }
		}
		printf("%d\n",bidule);
	}

    
}






void makegraphe2(FILE *file1,graphe *g,int *nbgrp,FILE *file2,FILE *file3,graphe *raph2){

    int entry1;
    int entry2;
    int entry3;
    char char21;
    int y = 0;

    for(int k = 0;k<g->nbintype1;k++){
        for(int h = 0 ;h<20;h++){
            g->type[k][h]='\0';
        }
    }

    for(int i = 0;i<g->nbintype1;i++){
        while(fscanf(file2,"%c",&char21)==1 && char21!=' '){
        
        printf("%c",char21);
        g->type[i][y]=char21;
        
        y++;
        }
        fscanf(file2,"%f",&g->coutpartype[i]);
        printf(" %f\n",g->coutpartype[i]);
        y=0;
    }


    int itsthisnumber;
    int verifier=0;
    int verifier2=0;
    y = 0;


    //char *typesommet = (char*)malloc(20 * sizeof(char));
    char *typesommet = (char*)calloc(20, sizeof(char));


    for(int i = 0;i<g->nbpeak;i++){
        
        fscanf(file3,"%c",&char21);
        fscanf(file3,"%c",&char21);
        if(char21 != ' '){
            fscanf(file3,"%c",&char21);
        }
        while(fscanf(file3,"%c",&char21)==1 && char21 != '\n' && y <=10){
        typesommet[y] = char21;
        y++;
        }
    
    printf("\n");
    printf("%s",typesommet);
    

    for(int o = 0;o<g->nbintype1;o++){
        for(int cv = 0;cv<10;cv++){
            printf("%c",g->type[o][cv]);
            printf("%c",typesommet[cv]);
            if(g->type[o][cv+1]==typesommet[cv]){
                verifier+=1;
            }
            printf("%d",verifier);
            verifier2+=1;
        }
        if(verifier2 ==verifier){
            itsthisnumber=o;
        }
        verifier2=0;
        verifier=0;
    }
    printf("\n");


    g->costofeachtyle[i]=g->coutpartype[itsthisnumber];
    printf("%f\n",g->costofeachtyle[i]);

    memset(typesommet, 0, 20 * sizeof(char));
    y = 0;
    }



    char asciichar76;
    char asciichar55;
    
    entry3 = 2;
    while(fscanf(file1,"%d %c%c %d\n",&entry1,&asciichar55,&asciichar76,&entry2)==4){
        if(asciichar55 == '-'){
            g->matgraphe[entry1][entry2]=g->costofeachtyle[entry2];
        }
        if(asciichar55 == '<'){
            g->matgraphe[entry1][entry2]=g->costofeachtyle[entry1];
        }

    }



        printf("\nMatrice ces couts :\n");
	for(int i=0; i<g->nbpeak; i++){
		for(int j=0; j<g->nbpeak; j++){
			printf("%1.1f", g->matgraphe[i][j]);
		}
		printf("\n");
	}


    for(int i=0; i<g->nbpeak; i++){
		for(int j=0; j<g->nbpeak; j++){
            if(g->mintheo[i]==0 && g->matgraphe[i][j] != 0){
                g->mintheo[i]=100000000;
            }
            if(g->mintheo[i] > g->matgraphe[i][j] && g->matgraphe[i][j] != 0){
			    g->mintheo[i]=g->matgraphe[i][j];
            }
		}
	}

    for(int i=0; i<g->nbpeak; i++){
		for(int j=0; j<g->nbpeak; j++){

			if(g->matgraphe[i][j] != 0 && g->mintheo[i] == g->matgraphe[i][j] && g->matgrp[i] == 0 ){
                if(g->matgrp[j] == 0){
                g->matgrp[i] =*nbgrp;
                g->matgrp[j] =*nbgrp;
                g->test[i][j] =1;
                g->test[j][i] =1;
                *nbgrp +=1;
                }else{
                g->matgrp[i] =g->matgrp[j];
                g->test[i][j] =1;
                g->test[j][i] =1;
                }
            }
		}
	}
    printf("\n");
    printf("chaque point est connecte avec son arrete la plus legere\n");
    for(int i=0; i<g->nbpeak; i++){
		for(int j=0; j<g->nbpeak; j++){
			printf("%3d", g->test[i][j]);
		}
		printf("\n");
	}
    printf("\n");
    printf("appartenance groupe pour chaque point : ");
    for(int i=0; i<g->nbpeak; i++){
			printf("%3d", g->matgrp[i]);
	}
    		printf("\n");
    printf("arrete avec le poids le plus faible pour chaque point : ");
    for(int i=0; i<g->nbpeak; i++){
			printf("%3d", g->mintheo[i]);
	}
    		printf("\n");
    
    int mmatgrp = 1;
    for(int i=0; i<g->nbpeak; i++){
        if(mmatgrp != g->matgrp[i]){
            mmatgrp = g->matgrp[i];
        }
	}
    int posi = 0;
    int posj = 0;
    int minini= 100000;
    while(mmatgrp != 1 ){
        for(int i=0; i<g->nbpeak; i++){
		for(int j=0; j<g->nbpeak; j++){
            if(mmatgrp == g->matgrp[j] && minini >= g->matgraphe[i][j] && g->matgraphe[i][j] != 0 && g->test[i][j] !=1){
                posi = i;
                posj = j;
                minini = g->matgraphe[i][j];
            }
		}
	}

    g->test[posi][posj] =1;
    g->test[posj][posi] =1;

    for(int i=0; i<g->nbpeak; i++){
        if(mmatgrp == g->matgrp[i]){
            g->matgrp[i] = 1;
        }
	}
    mmatgrp = 1;
    for(int i=0; i<g->nbpeak; i++){
        if(mmatgrp != g->matgrp[i]){
            mmatgrp = g->matgrp[i];
        }
	}

    printf("\n");
    printf("suite\n");
    for(int i=0; i<g->nbpeak; i++){
		for(int j=0; j<g->nbpeak; j++){
			printf("%3d", g->test[i][j]);
		}
		printf("\n");
	}
    printf("\n");
    printf("appartenance groupe pour chaque point : ");
    for(int i=0; i<g->nbpeak; i++){
			printf("%3d", g->matgrp[i]);
	}
    		printf("\n");
    }

    printf("voici les liaisons necessaire pour dessiner l'arbre de poids minumum : \n");
    for(int i=0; i<g->nbpeak; i++){
		for(int j=0; j<g->nbpeak; j++){
            if(g->test[i][j]!=0){
			printf("%d -> %d\n",i,j);
            }
		}
	}

}
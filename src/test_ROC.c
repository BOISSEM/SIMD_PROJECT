/* -----------------------------------------------
	test_ROC.c
	Edité par Martin Boisse
	Le 5 Decembre 2018

	Projet SIMD
	Matrice ROC (test final)
----------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "nrdef.h"
#include "nrutil.h"

#define NB_IMAGE    200
#define BORD_TAB    0

char buffer[200];
// Matrice Roc
long int ROC[2][2];

/*
*   Matrice ROC (Receiver Operating Characteristic).
*   Le principe est de comparer une image résultant d'un des deux algo 
*   à une image de verité terrain (image construite manuellement).
*
*   @param Et       Etiquette binaire (résultant des différents algorithmes)
*   @image_verite   Etiquette binaire provenant de la recuperation des images faites à la main
*   @img_size_l     Largeur de l'image
*   @img_size_h     Hauteur de l'image
*   @return         Matrice ROC ajustée
*
*/

void matriceROC(uint8_t** Et, uint8_t** image_verite, int img_size_l, int img_size_h) {
    int i, j; 

    for(i = 0; i < img_size_h; i++)  {
        for(j = 0; j < img_size_l; j++)    {
            if(Et[i][j] == 255 && image_verite[i][j] == 255) //VP
                ROC[0][0]++;
            else if(Et[i][j] == 0 && image_verite[i][j] == 255) //FN
                ROC[0][1]++;
            else if(Et[i][j] == 255 && image_verite[i][j] == 0) //FP
                ROC[1][0]++;
            else if(Et[i][j] == 0 && image_verite[i][j] == 0) //VN
                ROC[1][1]++;
        }
    }
}

/**
*   Comparaison de nos résultat avec les images verités terrain
**/

void f_test_veriteTerrain_FD()	{
	int i, j;
    long img_size_h = 0, img_size_l = 0;
    long img_size_h0 = 0, img_size_l0 = 0;

    int maxval = 0;

    FILE* fp;
    char imgEt_name[50];
    char imgVerite_name[50];

    uint8_t **img_Et, **image_verite;

    sprintf(imgEt_name, "img/car3_bin_FD/car_%d.pgm", 3080);
    sprintf(imgVerite_name, "img/verite_terrain/car_%d.pgm", 3080);

    img_Et = LoadPGM_ui8matrix(imgEt_name, &img_size_h0, &img_size_h, &img_size_l0, &img_size_l);
    image_verite = LoadPGM_ui8matrix(imgVerite_name, &img_size_h0, &img_size_h, &img_size_l0, &img_size_l);

    ROC[0][0] = 0;
    ROC[0][1] = 0;
    ROC[1][0] = 0;
    ROC[1][1] = 0;

    for(i=80; i<110; i++)
    {
        sprintf(imgEt_name, "img/car3_bin_FD/car_%d.pgm", 3000+i);
        sprintf(imgVerite_name, "img/verite_terrain/car_%d.pgm", 3000+i);

        MLoadPGM_ui8matrix(imgEt_name, img_size_h0, img_size_h, img_size_l0, img_size_l, img_Et);
        MLoadPGM_ui8matrix(imgVerite_name, img_size_h0, img_size_h, img_size_l0, img_size_l, image_verite);

        matriceROC(img_Et, image_verite, img_size_l, img_size_h);
    }

    //-------------------- AFFICHAGE --------------------- //
    printf("============== Resultat =============== ");
    printf("\n");
    printf("matr_roc: ");
    printf("\n");
    printf(" %ld ", ROC[0][0]);
    printf(" %ld ", ROC[0][1]);
    printf("\n");
    printf(" %ld ", ROC[1][0]);
    printf(" %ld ", ROC[1][1]);
    printf("\n");

    
    double total = ROC[0][0]+ROC[0][1]+ROC[1][0]+ROC[1][1];
    double Spos = (ROC[0][0]+ROC[1][1]);
    double Sneg = (ROC[0][1]+ROC[1][0]);

    printf("============= Positif =================\n ");
    printf("Détection correcte: %2lf pourcent\n", (float)Spos/total*100);

    printf("============= negatif =================\n ");
    printf("Détection incorrecte: %2lf pourcent\n", (float)Sneg/total*100);
    //--------------------------------------------------- //
}

void f_test_veriteTerrain_FD_SSE2()	{
	int i, j;
    long img_size_h = 0, img_size_l = 0;
    long img_size_h0 = 0, img_size_l0 = 0;

    int maxval = 0;

    FILE* fp;
    char imgEt_name[50];
    char imgVerite_name[50];

    uint8_t **img_Et, **image_verite;

    sprintf(imgEt_name, "img/car3_bin_FD_SSE2/car_%d.pgm", 3080);
    sprintf(imgVerite_name, "img/verite_terrain/car_%d.pgm", 3080);

    img_Et = LoadPGM_ui8matrix(imgEt_name, &img_size_h0, &img_size_h, &img_size_l0, &img_size_l);
    image_verite = LoadPGM_ui8matrix(imgVerite_name, &img_size_h0, &img_size_h, &img_size_l0, &img_size_l);

    ROC[0][0] = 0;
    ROC[0][1] = 0;
    ROC[1][0] = 0;
    ROC[1][1] = 0;

    for(i=80; i<110; i++)
    {
        sprintf(imgEt_name, "img/car3_bin_FD_SSE2/car_%d.pgm", 3000+i);
        sprintf(imgVerite_name, "img/verite_terrain/car_%d.pgm", 3000+i);

        MLoadPGM_ui8matrix(imgEt_name, img_size_h0, img_size_h, img_size_l0, img_size_l, img_Et);
        MLoadPGM_ui8matrix(imgVerite_name, img_size_h0, img_size_h, img_size_l0, img_size_l, image_verite);

        matriceROC(img_Et, image_verite, img_size_l, img_size_h);
    }

    //-------------------- AFFICHAGE --------------------- //
    printf("============== Resultat =============== ");
    printf("\n");
    printf("matr_roc: ");
    printf("\n");
    printf(" %ld ", ROC[0][0]);
    printf(" %ld ", ROC[0][1]);
    printf("\n");
    printf(" %ld ", ROC[1][0]);
    printf(" %ld ", ROC[1][1]);
    printf("\n");

    
    double total = ROC[0][0]+ROC[0][1]+ROC[1][0]+ROC[1][1];
    double Spos = (ROC[0][0]+ROC[1][1]);
    double Sneg = (ROC[0][1]+ROC[1][0]);

    printf("============= Positif =================\n ");
    printf("Détection correcte: %2lf pourcent\n", (float)Spos/total*100);

    printf("============= negatif =================\n ");
    printf("Détection incorrecte: %2lf pourcent\n", (float)Sneg/total*100);
    //--------------------------------------------------- //
}

void f_test_veriteTerrain_SD()	{
	int i, j;
    long img_size_h = 0, img_size_l = 0;
    long img_size_h0 = 0, img_size_l0 = 0;

    int maxval = 0;

    FILE* fp;
    char imgEt_name[50];
    char imgVerite_name[50];

    uint8_t **img_Et, **image_verite;

    // sprintf(imgEt_name, "img/car3_bin_SD_SSE2/car_%d.pgm", 3080);
    sprintf(imgEt_name, "img/car3_bin_SD/car_%d.pgm", 3080);
    sprintf(imgVerite_name, "img/verite_terrain/car_%d.pgm", 3080);

    img_Et = LoadPGM_ui8matrix(imgEt_name, &img_size_h0, &img_size_h, &img_size_l0, &img_size_l);
    image_verite = LoadPGM_ui8matrix(imgVerite_name, &img_size_h0, &img_size_h, &img_size_l0, &img_size_l);

    ROC[0][0] = 0;
    ROC[0][1] = 0;
    ROC[1][0] = 0;
    ROC[1][1] = 0;

    for(i=80; i<110; i++)
    {
        sprintf(imgEt_name, "img/car3_bin_SD/car_%d.pgm", 3000+i);
        sprintf(imgVerite_name, "img/verite_terrain/car_%d.pgm", 3000+i);

        MLoadPGM_ui8matrix(imgEt_name, img_size_h0, img_size_h, img_size_l0, img_size_l, img_Et);
        MLoadPGM_ui8matrix(imgVerite_name, img_size_h0, img_size_h, img_size_l0, img_size_l, image_verite);

        matriceROC(img_Et, image_verite, img_size_l, img_size_h);
    }

    //-------------------- AFFICHAGE --------------------- //
    printf("============== Resultat =============== ");
    printf("\n");
    printf("matr_roc: ");
    printf("\n");
    printf(" %ld ", ROC[0][0]);
    printf(" %ld ", ROC[0][1]);
    printf("\n");
    printf(" %ld ", ROC[1][0]);
    printf(" %ld ", ROC[1][1]);
    printf("\n");

    
    double total = ROC[0][0]+ROC[0][1]+ROC[1][0]+ROC[1][1];
    double Spos = (ROC[0][0]+ROC[1][1]);
    double Sneg = (ROC[0][1]+ROC[1][0]);

    printf("============= Positif =================\n ");
    printf("Détection correcte: %2lf pourcent\n", (float)Spos/total*100);

    printf("============= negatif =================\n ");
    printf("Détection incorrecte: %2lf pourcent\n", (float)Sneg/total*100);
    //--------------------------------------------------- //
}

void f_test_veriteTerrain_SD_SSE2()	{
	int i, j;
    long img_size_h = 0, img_size_l = 0;
    long img_size_h0 = 0, img_size_l0 = 0;

    int maxval = 0;

    FILE* fp;
    char imgEt_name[50];
    char imgVerite_name[50];

    uint8_t **img_Et, **image_verite;

    // sprintf(imgEt_name, "img/car3_bin_SD_SSE2/car_%d.pgm", 3080);
    sprintf(imgEt_name, "img/car3_SD+morpho_0/car_%d.pgm", 3080);
    sprintf(imgVerite_name, "img/verite_terrain/car_%d.pgm", 3080);

    img_Et = LoadPGM_ui8matrix(imgEt_name, &img_size_h0, &img_size_h, &img_size_l0, &img_size_l);
    image_verite = LoadPGM_ui8matrix(imgVerite_name, &img_size_h0, &img_size_h, &img_size_l0, &img_size_l);

    ROC[0][0] = 0;
    ROC[0][1] = 0;
    ROC[1][0] = 0;
    ROC[1][1] = 0;

    for(i=80; i<110; i++)
    {
        sprintf(imgEt_name, "img/car3_SD+morpho_1/car_%d.pgm", 3000+i);
        sprintf(imgVerite_name, "img/verite_terrain/car_%d.pgm", 3000+i);

        MLoadPGM_ui8matrix(imgEt_name, img_size_h0, img_size_h, img_size_l0, img_size_l, img_Et);
        MLoadPGM_ui8matrix(imgVerite_name, img_size_h0, img_size_h, img_size_l0, img_size_l, image_verite);

        matriceROC(img_Et, image_verite, img_size_l, img_size_h);
    }

    //-------------------- AFFICHAGE --------------------- //
    printf("============== Resultat =============== ");
    printf("\n");
    printf("matr_roc: ");
    printf("\n");
    printf(" %ld ", ROC[0][0]);
    printf(" %ld ", ROC[0][1]);
    printf("\n");
    printf(" %ld ", ROC[1][0]);
    printf(" %ld ", ROC[1][1]);
    printf("\n");

    
    double total = ROC[0][0]+ROC[0][1]+ROC[1][0]+ROC[1][1];
    double Spos = (ROC[0][0]+ROC[1][1]);
    double Sneg = (ROC[0][1]+ROC[1][0]);

    printf("============= Positif =================\n ");
    printf("Détection correcte: %2lf pourcent\n", (float)Spos/total*100);

    printf("============= negatif =================\n ");
    printf("Détection incorrecte: %2lf pourcent\n", (float)Sneg/total*100);
    //--------------------------------------------------- //
}

void f_test_veriteTerrain_SD_morpho()	{
}

void f_test_roc_car3()	{
	//f_test_veriteTerrain_FD();
	//f_test_veriteTerrain_FD_SSE2();
	//f_test_veriteTerrain_FD_morpho();

	//f_test_veriteTerrain_SD();
	f_test_veriteTerrain_SD_SSE2();
	//f_test_veriteTerrain_SD_morpho();
}
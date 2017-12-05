/* -----------------------------------------------
	test_car3_SSE2.c
	Edité par Martin Boisse
	Le 26 Novembre 2018

	Projet SIMD
	test detection de mouvement sur image
	(verification des fonctions presente dans
	mouvement.c)
----------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "nrdef.h"
#include "nrutil.h"
#include "vnrutil.h"
#include "mouvement_SSE2.h"
#include "morpho_SSE2.h"


// Matrice Roc 
long int ROC[2][2];

void f_test_fd_car3_SSE2()	{

	int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char img0_name[30];
    char img1_name[30];
    char img_out_name[60];

    vuint8 **img_t0, **img_t1;
    vuint8 **diff, **Et;

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(img0_name, "img/car3/car_3000.pgm");

    fp = fopen(img0_name, "rb");
    if(fp == NULL){
        printf("Erreur d'ouverture de l'image : %s", img0_name);
        exit(1);
    }

    // Mettre le curseur au début du fichier
    rewind(fp);

    // Placement du curseur apres les deux premieres lignes
    fgets(buffer, 50, fp);
    fgets(buffer, 50, fp);

    // Recuperation de la taille de l'image
    fscanf(fp, "%d %d", &img_size_l, &img_size_h);

    img_t0 = vui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, (img_size_l-1)+BORD_TAB);
    img_t1 = vui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, (img_size_l-1)+BORD_TAB);

    diff = vui8matrix(0, (img_size_h-1), 0, (img_size_l-1));
    Et = vui8matrix(0, (img_size_h-1), 0, (img_size_l-1));

    for(i=0-BORD_TAB; i<img_size_h+BORD_TAB; i++){
        for(j=0-BORD_TAB; j<img_size_l+BORD_TAB; j++){
            img_t0[i][j] = 0;
            img_t1[i][j] = 0;
        }
    }

}


void f_test_sd_car3_SSE2()	{

}

void f_test_fd_morpho_car3_SSE2()	{

}

void f_test_sd_morpho_car3_SSE2()	{

}


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

void f_test_veriteTerrain() {
    int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char imgEt_name[30];
    char imgVerite_name[40];

    uint8_t **img_Et, **image_verite;

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(imgEt_name, "img/car3_bin_SD/car_3000.pgm");
    //sprintf(imgEt_name, "../img/car3_bin_FD/car_0.pgm");

    fp = fopen(imgEt_name, "rb");
    if(fp == NULL){
        printf("Erreur d'ouverture de l'image : %s", imgEt_name);
        exit(1);
    }

    rewind(fp);

    // Placement du curseur apres les deux premieres lignes
    fgets(buffer, 50, fp);
    fgets(buffer, 50, fp);

    // Recuperation de la taille de l'image
    fscanf(fp, "%d %d", &img_size_l, &img_size_h);

    img_Et = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, (img_size_l-1)+BORD_TAB);
    image_verite = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, (img_size_l-1)+BORD_TAB);

    for(i=0-BORD_TAB; i<img_size_h+BORD_TAB; i++){
        for(j=0-BORD_TAB; j<img_size_l+BORD_TAB; j++){
            img_Et[i][j] = 0;
            image_verite[i][j] = 0;
        }
    }

    ROC[0][0] = 0;
    ROC[0][1] = 0;
    ROC[1][0] = 0;
    ROC[1][1] = 0;

    // Recuperation de la valeur maximale dans le fichier
    fscanf(fp,"%d", &maxval);

    fclose(fp);

    for(i=80; i<110; i++)
    {
        sprintf(imgEt_name, "img/car3_bin_SD/car_%d.pgm", 3000+i);
        //sprintf(imgEt_name, "../img/car3_bin_FD/car_%d.pgm", 3000+i);
        sprintf(imgVerite_name, "img/verite_terrain/car_%d.pgm", 3000+i);

        copy_pgm_matrix(imgEt_name, img_Et, img_size_h, img_size_l);
        copy_pgm_matrix(imgVerite_name, image_verite, img_size_h, img_size_l);

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

    printf("============= Positif =================\n ");
    double Spos = (ROC[0][0]+ROC[1][0]);
    printf("Vrai positif: %2lf pourcent\n", (float)(ROC[0][0]/Spos)*100);
    printf("Faux positif: %2lf pourcent\n", (float)(ROC[1][0]/Spos)*100);

    printf("============= negatif =================\n ");
    double Sneg = (ROC[0][1]+ROC[1][1]);
    printf("Faux négatif: %2lf pourcent\n", (float)(ROC[0][1]/Sneg)*100);
    printf("Vrai négatif: %2lf pourcent\n", (float)(ROC[1][1]/Sneg)*100);
    //--------------------------------------------------- //
    
}

void f_test_mouvement_car3_SSE2()	{
	//f_test_fd_car3_SSE2();
	//f_test_sd_car3_SSE2();
	//f_test_fd_morpho_car3_SSE2();
	//f_test_sd_morpho_car3_SSE2();
	//f_test_veriteTerrain();
}
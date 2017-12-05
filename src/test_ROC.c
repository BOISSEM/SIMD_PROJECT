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
#include "test_car3.h"

#define NB_IMAGE    200
#define BORD_TAB    2

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
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char imgEt_name[50];
    char imgVerite_name[50];

    uint8_t **img_Et, **image_verite;

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(imgEt_name, "img/car3_bin_FD/car_3000.pgm");

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
        sprintf(imgEt_name, "img/car3_bin_FD/car_%d.pgm", 3000+i);
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

void f_test_veriteTerrain_FD_SSE2()	{
	int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char imgEt_name[50];
    char imgVerite_name[50];

    uint8_t **img_Et, **image_verite;

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(imgEt_name, "img/car3_bin_FD/car_3000.pgm");

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
        sprintf(imgEt_name, "img/car3_bin_FD_SSE2/car_%d.pgm", 3000+i);
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

void f_test_veriteTerrain_FD_morpho()	{
	int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char imgEt_name[50];
    char imgVerite_name[50];

    uint8_t **img_Et, **image_verite;

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(imgEt_name, "img/car3_bin_FD/car_3000.pgm");

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
        sprintf(imgEt_name, "img/car3_bin_FD_morpho/car_%d.pgm", 3000+i);
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

void f_test_veriteTerrain_SD()	{
	int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char imgEt_name[50];
    char imgVerite_name[50];

    uint8_t **img_Et, **image_verite;

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(imgEt_name, "img/car3_bin_FD/car_3000.pgm");

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

void f_test_veriteTerrain_SD_SSE2()	{
	int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char imgEt_name[50];
    char imgVerite_name[50];

    uint8_t **img_Et, **image_verite;

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(imgEt_name, "img/car3_bin_FD/car_3000.pgm");

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
        sprintf(imgEt_name, "img/car3_bin_SD_SSE2/car_%d.pgm", 3000+i);
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

void f_test_veriteTerrain_SD_morpho()	{
	int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char imgEt_name[50];
    char imgVerite_name[50];

    uint8_t **img_Et, **image_verite;

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(imgEt_name, "img/car3_bin_FD/car_3000.pgm");

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
        sprintf(imgEt_name, "img/car3_bin_SD_morpho/car_%d.pgm", 3000+i);
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

void f_test_roc_car3()	{
	//f_test_veriteTerrain_FD();
	//f_test_veriteTerrain_FD_SSE2();
	//f_test_veriteTerrain_FD_morpho();

	//f_test_veriteTerrain_SD();
	//f_test_veriteTerrain_SD_SSE2();
	//f_test_veriteTerrain_SD_morpho();
}
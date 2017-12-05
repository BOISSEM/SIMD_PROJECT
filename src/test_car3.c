/* -----------------------------------------------
	test_car3.c
	Edité par Martin Boisse
	Le 22 Octobre 2018

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
#include "mouvement.h"
#include "morpho.h"

#define NB_IMAGE    200
#define BORD_TAB    2

char buffer[200];
// Matrice Roc
long int ROC[2][2];

/**
 *	Fonction permettant de recopier les pixels d'une image pgm dans une matrice
 *
 *  @param fname    Nom du fichier
 *  @param image    Tableau destination de l'image
 *  @param size_l   Largeur de l'image
 *  @param size_h   Hauteur de l'image
 *  @return     Pointeur vers le tableau de l'image
 */
uint8_t** copy_pgm_matrix(char* fname, uint8_t** image, int size_h, int size_l){
    int i, j;
    FILE* fp;

    if((fp = fopen(fname, "rb"))==NULL){
        printf("Erreur d'ouverture de l'image : %s", fname);
        exit(1);
    }
    rewind(fp);

    // Passer les 4 premieres lignes
    for(int k=0; k<4; k++){
        fgets(buffer, 50, fp);
    }

    // Copie de l'image dans la matrice
    for(i=0; i<size_h; i++){
        for(j=0; j<size_l; j++){
            image[i][j] = fgetc(fp);
        }
    }

    fclose(fp);

    return image;
}

/**
 *	Fonction représentation des sorties d'algorithme de
 *	detection (creation d'images .pgm)
 *
 *  @param fname                Nom du fichier
 *  @param Et  Etiquette binaire
 *  @param size_l   Largeur de l'image
 *  @param size_h   Hauteur de l'image
 *  @param maxval   Valeur maximale dans l'image (correspond a la couleur blanche)
 *  @return     Pointeur vers le fichier
 */
FILE* creation_pgm(char* fname, int size_h, int size_l, uint8_t maxval, uint8_t** Et)
{
	int i, j;
	FILE* image = NULL;

	image = fopen(fname, "wb");

	if(image != NULL)	{
		fputs("P5\n",image);
        fputs("# Created by Martin Le King\n", image);
        fprintf(image,"%d %d\n",size_l, size_h);    // Ecriture de la taille de l'image
        fprintf(image,"%d\n", maxval);              // Ecriture de la valeur maximale de l'image

		for(i = 0; i < size_h; i++)	{
			for(j = 0; j < size_l; j++)	{
				fputc(Et[i][j], image);
			}
		}
	}

	fclose(image);
}

void f_test_fd_car3(){
    int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char img0_name[30];
    char img1_name[30];
    char img_out_name[60];

    uint8_t **img_t0, **img_t1;
    uint8_t **diff, **Et;

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(img0_name, "img/car3/car_3000.pgm");

    fp = fopen(img0_name, "rb");
    if(fp == NULL){
        printf("Erreur d'ouverture de l'image : %s", img0_name);
        exit(1);
    }

    rewind(fp);

    // Placement du curseur apres les deux premieres lignes
    fgets(buffer, 50, fp);
    fgets(buffer, 50, fp);

    // Recuperation de la taille de l'image
    fscanf(fp, "%d %d", &img_size_l, &img_size_h);

    img_t0 = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, (img_size_l-1)+BORD_TAB);
    img_t1 = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, (img_size_l-1)+BORD_TAB);

    diff = ui8matrix(0, (img_size_h-1), 0, img_size_l-1);
    Et = ui8matrix(0, (img_size_h-1), 0, img_size_l-1);

    for(i=0-BORD_TAB; i<img_size_h+BORD_TAB; i++){
        for(j=0-BORD_TAB; j<img_size_l+BORD_TAB; j++){
            img_t0[i][j] = 0;
            img_t1[i][j] = 0;
        }
    }

    // Recuperation de la valeur maximale dans le fichier
    fscanf(fp,"%d", &maxval);

    fclose(fp);

    for(i=0; i<NB_IMAGE-1; i++)
    {
        sprintf(img0_name, "img/car3/car_%d.pgm", 3000+i);
        sprintf(img1_name, "img/car3/car_%d.pgm", 3000+i+1);

        copy_pgm_matrix(img0_name, img_t0, img_size_h, img_size_l);
        copy_pgm_matrix(img1_name, img_t1, img_size_h, img_size_l);

        Et = routine_FrameDifference(img_t0, img_t1, img_size_h, img_size_l, diff, Et);

        sprintf(img_out_name, "img/car3_bin_FD/car_%03d.pgm", 3000+i);
        creation_pgm(img_out_name, img_size_h, img_size_l, maxval, Et);
    }
}


void f_test_sd_car3(){
    int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char img0_name[30];
    char img_out_name[60];

    uint8_t **img_t0;
    uint8_t **var, **diff, **moy, **Et;

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(img0_name, "img/car3/car_3000.pgm");

    fp = fopen(img0_name, "rb");
    if(fp == NULL){
        printf("Erreur d'ouverture de l'image : %s", img0_name);
        exit(1);
    }

    rewind(fp);

    // Placement du curseur apres les deux premieres lignes
    fgets(buffer, 50, fp);
    fgets(buffer, 50, fp);

    // Recuperation de la taille de l'image
    fscanf(fp, "%d %d", &img_size_l, &img_size_h);

    img_t0 = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);

    diff = ui8matrix(0, (img_size_h-1), 0, img_size_l-1);
    var = ui8matrix(0, (img_size_h-1), 0, img_size_l-1);
    moy = ui8matrix(0, (img_size_h-1), 0, img_size_l-1);
    Et = ui8matrix(0, (img_size_h-1), 0, img_size_l-1);

    for(i=0-BORD_TAB; i<img_size_h+BORD_TAB; i++){
        for(j=0-BORD_TAB; j<img_size_l+BORD_TAB; j++){
            img_t0[i][j] = 0;
        }
    }

    copy_pgm_matrix(img0_name, img_t0, img_size_h, img_size_l);

    // Recuperation de la valeur maximale dans le fichier
    fscanf(fp,"%d", &maxval);

    moy = SigmaDelta_step0(var, moy, img_t0, img_size_h, img_size_l);

    fclose(fp);

    for(i=0; i<NB_IMAGE-1; i++)
    {
        sprintf(img0_name, "img/car3/car_%d.pgm", 3000+i+1);

        img_t0 = copy_pgm_matrix(img0_name, img_t0, img_size_h, img_size_l);

        Et = SigmaDelta_1step(img_t0, diff, img_size_h, img_size_l, moy, var, Et);

        sprintf(img_out_name, "img/car3_bin_SD/car_%d.pgm", 3000+i);
        creation_pgm(img_out_name, img_size_h, img_size_l, maxval, Et);
    }
}

void f_test_fd_morpho_car3(){
    int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char img0_name[30];
    char img1_name[30];
    char img_out_name[60];

    uint8_t **img_t0, **img_t1;
    uint8_t **diff, **Et1, **Et2, **Et_f;
    uint8_t **buff_morph;

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(img0_name, "img/car3/car_3000.pgm");

    fp = fopen(img0_name, "rb");
    if(fp == NULL){
        printf("Erreur d'ouverture de l'image : %s", img0_name);
        exit(1);
    }

    rewind(fp);

    // Placement du curseur apres les deux premieres lignes
    fgets(buffer, 50, fp);
    fgets(buffer, 50, fp);

    // Recuperation de la taille de l'image
    fscanf(fp, "%d %d", &img_size_l, &img_size_h);

    img_t0 = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);
    img_t1 = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);
    Et1 = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);
    Et2 = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);
    Et_f = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);
    buff_morph = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);

    diff = ui8matrix(0, (img_size_h-1), 0, img_size_l-1);

    for(i=0-BORD_TAB; i<img_size_h+BORD_TAB; i++){
        for(j=0-BORD_TAB; j<img_size_l+BORD_TAB; j++){
            img_t0[i][j] = 0;
            img_t1[i][j] = 0;
        }
    }

    // Recuperation de la valeur maximale dans le fichier
    fscanf(fp,"%d", &maxval);

    fclose(fp);

    for(i=0; i<NB_IMAGE-1; i++)
    {
        sprintf(img0_name, "img/car3/car_%d.pgm", 3000+i);
        sprintf(img1_name, "img/car3/car_%d.pgm", 3000+i+1);

        // generate_filename_k_ndigit_extension("../car3/car_", 3000+i, 4, "pgm", img0_name);
        // generate_filename_k_ndigit_extension("../car3/car_", 3000+i1, 4, "pgm", img1_name);

        copy_pgm_matrix(img0_name, img_t0, img_size_h, img_size_l);
        copy_pgm_matrix(img1_name, img_t1, img_size_h, img_size_l);

        Et1 = routine_FrameDifference(img_t0, img_t1, img_size_h, img_size_l, diff, Et1);

        close3(Et1, img_size_h, img_size_l, Et2, buff_morph);
        close5(Et2, img_size_h, img_size_l, Et1, buff_morph);

        sprintf(img_out_name, "img/car3_FD_morpho_bin/car_%03d.pgm", i);
        creation_pgm(img_out_name, img_size_h, img_size_l, maxval, Et1);
    }

    free_ui8matrix(img_t0, 0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);
    free_ui8matrix(img_t1, 0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);
    free_ui8matrix(Et1, 0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);
    free_ui8matrix(Et2, 0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);
    free_ui8matrix(Et_f, 0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);
    free_ui8matrix(buff_morph, 0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);

    free_ui8matrix(diff, 0, (img_size_h-1), 0, img_size_l-1);

}

void f_test_sd_morpho_car3(){
    int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char img0_name[30];
    char img_out_name[60];

    uint8_t **img_t0;
    uint8_t **var, **diff, **moy, **Et;

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(img0_name, "img/car3/car_3000.pgm");

    fp = fopen(img0_name, "rb");
    if(fp == NULL){
        printf("Erreur d'ouverture de l'image : %s", img0_name);
        exit(1);
    }

    rewind(fp);

    // Placement du curseur apres les deux premieres lignes
    fgets(buffer, 50, fp);
    fgets(buffer, 50, fp);

    // Recuperation de la taille de l'image
    fscanf(fp, "%d %d", &img_size_l, &img_size_h);

    img_t0 = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, img_size_l-1+BORD_TAB);

    diff = ui8matrix(0, (img_size_h-1), 0, img_size_l-1);
    var = ui8matrix(0, (img_size_h-1), 0, img_size_l-1);
    moy = ui8matrix(0, (img_size_h-1), 0, img_size_l-1);
    Et = ui8matrix(0, (img_size_h-1), 0, img_size_l-1);

    for(i=0-BORD_TAB; i<img_size_h+BORD_TAB; i++){
        for(j=0-BORD_TAB; j<img_size_l+BORD_TAB; j++){
            img_t0[i][j] = 0;
        }
    }

    copy_pgm_matrix(img0_name, img_t0, img_size_h, img_size_l);

    // Recuperation de la valeur maximale dans le fichier
    fscanf(fp,"%d", &maxval);

    moy = SigmaDelta_step0(var, moy, img_t0, img_size_h, img_size_l);

    fclose(fp);

    for(i=0; i<NB_IMAGE-1; i++)
    {
        sprintf(img0_name, "img/car3/car_%d.pgm", 3000+i+1);

        img_t0 = copy_pgm_matrix(img0_name, img_t0, img_size_h, img_size_l);

        Et = SigmaDelta_1step(img_t0, diff, img_size_h, img_size_l, moy, var, Et);

        sprintf(img_out_name, "img/car3_SD_bin/car_%03d.pgm", i);
        creation_pgm(img_out_name, img_size_h, img_size_l, maxval, Et);
    }
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

void f_test_mouvement_car3(){
    f_test_fd_car3();
    //f_test_sd_car3();
    //f_test_fd_morpho_car3();
    //f_test_veriteTerrain();
}

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

#define NB_IMAGE    200
#define BORD_TAB    16

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

vuint8** copy_pgm_vector(char* fname, vuint8** image, int size_h, int size_l)	{
	int i, j;
	vuint8 pixels;
	FILE* fp;

	if((fp = fopen(fname, "rb"))==NULL)	{
		printf("Erreur d'ouverture de l'image : %s", fname);
		exit(1);
	}
	rewind(fp);

	//Passer les 4 première lignes
	for(int k = 0; k < 4; k++)	{
		fgets(buffer, 50, fp);
	}

	//Copie de l'image dans la matrice de vecteur 
	for(i = 0; i < size_h; i++)	{
		for(j = 0; j < size_l; j+=16)	{
			fread(&pixels, sizeof(vuint8), 1, fp);
			_mm_store_si128(&image[i][j/16], pixels);
			// display_vuint8(image[i][j], " %3d ", "image");
   //  		printf("\n");
		}
	}

	fclose(fp);

	return image;
}

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

    /*------ Allocation ------*/
    img_t0 = vui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, (img_size_l-1)+BORD_TAB);
    img_t1 = vui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, (img_size_l-1)+BORD_TAB);

    diff = vui8matrix(0, (img_size_h-1), 0, (img_size_l-1));
    Et = vui8matrix(0, (img_size_h-1), 0, (img_size_l-1));

    /*------ Initialisation constante ------*/
	vuint8 v_0 = _mm_setzero_si128();

    for(i=0-BORD_TAB; i<(img_size_h+BORD_TAB)/16; i++){
        for(j=0-BORD_TAB; j<(img_size_l+BORD_TAB)/16; j++){
            img_t0[i][j] = v_0;
            img_t1[i][j] = v_0;
        }
    }

    // Recuperation de la valeur maximale dans le fichier
    fscanf(fp,"%d", &maxval);

    fclose(fp);

    sprintf(img0_name, "img/car3/car_%d.pgm", 3002);
    sprintf(img1_name, "img/car3/car_%d.pgm", 3002+1);
    copy_pgm_vector(img0_name, img_t0, img_size_h, img_size_l);
    copy_pgm_vector(img1_name, img_t1, img_size_h, img_size_l);

    for(i = 0; i < img_size_h; i++)	{
    	for(j = 0; j < img_size_l; j+=16)	{
    		display_vuint8(img_t0[i][j], " %3d ", "img_t0");
    		printf("\n");
    		display_vuint8(img_t1[i][j], " %3d ", "img_t1");
    		printf("\n");
    	}
    }

    // for(i=0; i<NB_IMAGE-1; i++)
    // {
    //     sprintf(img0_name, "img/car3/car_%d.pgm", 3000+i);
    //     sprintf(img1_name, "img/car3/car_%d.pgm", 3000+i+1);

    //     copy_pgm_vector(img0_name, img_t0, img_size_h, img_size_l);
    //     copy_pgm_vector(img1_name, img_t1, img_size_h, img_size_l);

    //     display_vuint8(img_t0[i][32], " %3d ", "img_t0");
    // 	printf("\n");
    // 	display_vuint8(img_t1[i][j], " %3d ", "img_t1");
    // 	printf("\n");

    //     // Et = routine_FrameDifference_SSE2(img_t1, img_t0, img_size_h, img_size_l, diff, Et);

    //     // sprintf(img_out_name, "img/car3_bin_FD/car_%03d.pgm", 3000+i);
    //     // creation_pgm(img_out_name, img_size_h, img_size_l, maxval, Et);
    // }

    // display_vuint8(img_t0[10][11], " %3d ", "img_t0");
    // printf("\n");
    // display_vuint8(img_t1[10][11], " %3d ", "img_t1");
    // printf("\n");

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

// void matriceROC(uint8_t** Et, uint8_t** image_verite, int img_size_l, int img_size_h) {
//     int i, j; 

//     for(i = 0; i < img_size_h; i++)  {
//         for(j = 0; j < img_size_l; j++)    {
//             if(Et[i][j] == 255 && image_verite[i][j] == 255) //VP
//                 ROC[0][0]++;
//             else if(Et[i][j] == 0 && image_verite[i][j] == 255) //FN
//                 ROC[0][1]++;
//             else if(Et[i][j] == 255 && image_verite[i][j] == 0) //FP
//                 ROC[1][0]++;
//             else if(Et[i][j] == 0 && image_verite[i][j] == 0) //VN
//                 ROC[1][1]++;
//         }
//     }
// }

// /**
// *   Comparaison de nos résultat avec les images verités terrain
// **/

// void f_test_veriteTerrain() {
//     int i, j;
//     int img_size_h = 0, img_size_l = 0;
//     int maxval = 0;

//     FILE* fp;
//     char imgEt_name[30];
//     char imgVerite_name[40];

//     uint8_t **img_Et, **image_verite;

//     /* Recuperation de la taille des images en ouvrant la premiere image */
//     sprintf(imgEt_name, "img/car3_bin_SD/car_3000.pgm");
//     //sprintf(imgEt_name, "../img/car3_bin_FD/car_0.pgm");

//     fp = fopen(imgEt_name, "rb");
//     if(fp == NULL){
//         printf("Erreur d'ouverture de l'image : %s", imgEt_name);
//         exit(1);
//     }

//     rewind(fp);

//     // Placement du curseur apres les deux premieres lignes
//     fgets(buffer, 50, fp);
//     fgets(buffer, 50, fp);

//     // Recuperation de la taille de l'image
//     fscanf(fp, "%d %d", &img_size_l, &img_size_h);

//     img_Et = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, (img_size_l-1)+BORD_TAB);
//     image_verite = ui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, (img_size_l-1)+BORD_TAB);

//     for(i=0-BORD_TAB; i<img_size_h+BORD_TAB; i++){
//         for(j=0-BORD_TAB; j<img_size_l+BORD_TAB; j++){
//             img_Et[i][j] = 0;
//             image_verite[i][j] = 0;
//         }
//     }

//     ROC[0][0] = 0;
//     ROC[0][1] = 0;
//     ROC[1][0] = 0;
//     ROC[1][1] = 0;

//     // Recuperation de la valeur maximale dans le fichier
//     fscanf(fp,"%d", &maxval);

//     fclose(fp);

//     for(i=80; i<110; i++)
//     {
//         sprintf(imgEt_name, "img/car3_bin_SD/car_%d.pgm", 3000+i);
//         //sprintf(imgEt_name, "../img/car3_bin_FD/car_%d.pgm", 3000+i);
//         sprintf(imgVerite_name, "img/verite_terrain/car_%d.pgm", 3000+i);

//         copy_pgm_matrix(imgEt_name, img_Et, img_size_h, img_size_l);
//         copy_pgm_matrix(imgVerite_name, image_verite, img_size_h, img_size_l);

//         matriceROC(img_Et, image_verite, img_size_l, img_size_h);
//     }

//     //-------------------- AFFICHAGE --------------------- //
//     printf("============== Resultat =============== ");
//     printf("\n");
//     printf("matr_roc: ");
//     printf("\n");
//     printf(" %ld ", ROC[0][0]);
//     printf(" %ld ", ROC[0][1]);
//     printf("\n");
//     printf(" %ld ", ROC[1][0]);
//     printf(" %ld ", ROC[1][1]);
//     printf("\n");

//     printf("============= Positif =================\n ");
//     double Spos = (ROC[0][0]+ROC[1][0]);
//     printf("Vrai positif: %2lf pourcent\n", (float)(ROC[0][0]/Spos)*100);
//     printf("Faux positif: %2lf pourcent\n", (float)(ROC[1][0]/Spos)*100);

//     printf("============= negatif =================\n ");
//     double Sneg = (ROC[0][1]+ROC[1][1]);
//     printf("Faux négatif: %2lf pourcent\n", (float)(ROC[0][1]/Sneg)*100);
//     printf("Vrai négatif: %2lf pourcent\n", (float)(ROC[1][1]/Sneg)*100);
//     //--------------------------------------------------- //
    
// }

void f_test_mouvement_car3_SSE2()	{
	f_test_fd_car3_SSE2();
	//f_test_sd_car3_SSE2();
	//f_test_fd_morpho_car3_SSE2();
	//f_test_sd_morpho_car3_SSE2();
	//f_test_veriteTerrain();
}


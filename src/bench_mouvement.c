/* -----------------------------------------------
	bench_mouvement.c
	Edité par Martin Boisse
	Le 6 Decembre 2018

	Projet SIMD
	Benchmark des tests de detection de mouvement sur image
	(verification des fonctions presente dans
	mouvement.c)
----------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mouvement.h"
#include "debug_macro.h"

#define NB_IMAGE    200
#define BORD_TAB    2

char buffer[200];

/**
 *	Fonction permettant de recopier les pixels d'une image pgm dans une matrice
 *
 *  @param fname    Nom du fichier
 *  @param image    Tableau destination de l'image
 *  @param size_l   Largeur de l'image
 *  @param size_h   Hauteur de l'image
 *  @return     Pointeur vers le tableau de l'image
 */
uint8_t** copy_pgm_matrix_2(char* fname, uint8_t** image, int size_h, int size_l){
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
FILE* creation_pgm_2(char* fname, int size_h, int size_l, uint8_t maxval, uint8_t** Et)
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

void f_bench_fd()   {
    int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char img0_name[30];
    char img1_name[30];
    char img_out_name[60];

    uint8_t **img_t0, **img_t1;
    uint8_t **diff, **Et;

    //BENCHMARK
    char *format_f32= "%4.0f ";
    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;
    double moyenne = 0;

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

        copy_pgm_matrix_2(img0_name, img_t0, img_size_h, img_size_l);
        copy_pgm_matrix_2(img1_name, img_t1, img_size_h, img_size_l);

        //BENCH(printf("Frame Difference scalaire : "));
        CHRONO(Et = routine_FrameDifference(img_t0, img_t1, img_size_h, img_size_l, diff, Et), cycles);
        //BENCH(printf(format, cycles/((img_size_h+1-img_size_l)*(img_size_h+1-img_size_l))));
        //BENCH(puts(""));
        moyenne+= cycles/((img_size_h+1-img_size_l)*(img_size_h+1-img_size_l));

        sprintf(img_out_name, "img/car3_bin_FD/car_%03d.pgm", 3000+i);
        creation_pgm_2(img_out_name, img_size_h, img_size_l, maxval, Et);
    }
    printf("Moyenne des Cycle Par Point Frame Difference scalaire: %f\n", moyenne/i);
}


void f_bench_sd()   {
    int i, j;
    int img_size_h = 0, img_size_l = 0;
    int maxval = 0;

    FILE* fp;
    char img0_name[30];
    char img_out_name[60];

    uint8_t **img_t0;
    uint8_t **var, **diff, **moy, **Et;

    //BENCHMARK
    char *format_f32= "%4.0f ";
    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;
    double moyenne = 0;

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

    copy_pgm_matrix_2(img0_name, img_t0, img_size_h, img_size_l);

    // Recuperation de la valeur maximale dans le fichier
    fscanf(fp,"%d", &maxval);

    moy = SigmaDelta_step0(var, moy, img_t0, img_size_h, img_size_l);

    fclose(fp);

    for(i=0; i<NB_IMAGE-1; i++)
    {
        sprintf(img0_name, "img/car3/car_%d.pgm", 3000+i+1);

        img_t0 = copy_pgm_matrix_2(img0_name, img_t0, img_size_h, img_size_l);

        //BENCH(printf("Sigma Delta scalaire : "));
        CHRONO(Et = SigmaDelta_1step(img_t0, diff, img_size_h, img_size_l, moy, var, Et), cycles);
        //BENCH(printf(format, cycles/((img_size_h+1-img_size_l)*(img_size_h+1-img_size_l))));
        //BENCH(puts(""));
        moyenne+= cycles/((img_size_h+1-img_size_l)*(img_size_h+1-img_size_l));

        sprintf(img_out_name, "img/car3_bin_SD/car_%d.pgm", 3000+i);
        creation_pgm_2(img_out_name, img_size_h, img_size_l, maxval, Et);
    }
    printf("Moyenne des Cycle Par Point Sigma Delta scalaire: %f\n", moyenne/i);
}


void f_bench_mouvement()    {
    f_bench_fd();
    f_bench_sd();
}



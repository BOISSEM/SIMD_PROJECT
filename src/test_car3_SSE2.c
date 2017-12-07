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
#include "debug_macro.h"

#define NB_IMAGE    200
#define BORD_TAB    16

char buffer[200];

void f_test_fd_car3_SSE2()	{

	int i;
    int img_size_h = 0, img_size_l = 0;

    FILE* fp;
    char img0_name[30];
    char img1_name[30];
    char img_out_name[60];

    char *format_f32= "%4.0f ";
    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    /*------------ Declaration tableau de vecteur ---------- */
    vuint8 **img_t0;
    vuint8 **img_t1;

    vuint8 **Ot;
    vuint8 **Et;
    /*------------------------------------------------------ */

    /*------------------ Declaration vecteur --------------- */
    uint8 **v_img_t0;
    uint8 **v_img_t1;

    uint8 **v_Ot;
    uint8 **v_Et;
    /*------------------------------------------------------ */
    

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

   	fclose(fp);

    /*--------------------------------- Allocation ----------------------------------------------*/
    img_t0 = vui8matrix(0, (img_size_h-1), 0, (img_size_l-1));
    img_t1 = vui8matrix(0, (img_size_h-1), 0, (img_size_l-1));
    Ot = vui8matrix(0, (img_size_h-1), 0, (img_size_l-1));

    Et = vui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, (img_size_l-1)+BORD_TAB);
    /*-------------------------------------------------------------------------------------------*/

    /*-------------------------------- Association zone mémoire ---------------------------------*/
    v_img_t0 = (uint8**) img_t0;
    v_img_t1 = (uint8**) img_t1;
    v_Ot = (uint8**) Ot;
    v_Et = (uint8**) Et;
    /*-------------------------------------------------------------------------------------------*/

    /*----------------------------------------- FD ----------------------------------------------*/
    for(i = 0; i < NB_IMAGE-1; i++)	{
    	sprintf(img0_name, "img/car3/car_%d.pgm", 3000+i);
    	sprintf(img1_name, "img/car3/car_%d.pgm", 3000+i+1);

		MLoadPGM_ui8matrix(img0_name, 0, img_size_h-1, 0, img_size_l-1, v_img_t0);
		MLoadPGM_ui8matrix(img1_name, 0, img_size_h-1, 0, img_size_l-1, v_img_t1);

		
		BENCH(printf("Frame Difference : "));
		CHRONO(routine_FrameDifference_SSE2(img_t1, img_t0, img_size_h, img_size_l/16, Ot, Et), cycles);BENCH(printf(format, cycles/((img_size_h+1-img_size_l)*(img_size_h+1-img_size_l)))); BENCH(puts(""));


		sprintf(img_out_name, "img/car3_bin_FD_SSE2/car_%03d.pgm", 3000+i);
		SavePGM_ui8matrix(v_Et, 0, img_size_h-1, 0, img_size_l-1, img_out_name);
    }
    /*-------------------------------------------------------------------------------------------*/
}


void f_test_sd_car3_SSE2()	{
	int i;

	int img_size_h = 0;
	int img_size_l = 0;

	FILE* fp;
	char img1_name[30];
	char img_out_name[60];

	char *format_f32= "%4.0f ";
    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

	/*------------ Declaration tableau de vecteur ---------- */
    vuint8 **img_t1;

    vuint8 **Ot;
    vuint8 **Et;
    vuint8 **V;
    vuint8 **M;
    /*------------------------------------------------------ */

    /*------------------ Declaration vecteur --------------- */
    uint8 **v_img_t1;

    uint8 **v_Ot;
    uint8 **v_Et;
    uint8 **v_M;
    uint8 **v_V;
    /*------------------------------------------------------ */

    /* Recuperation de la taille des images en ouvrant la premiere image */
    sprintf(img1_name, "img/car3/car_3000.pgm");

    fp = fopen(img1_name, "rb");
    if(fp == NULL){
        printf("Erreur d'ouverture de l'image : %s", img1_name);
        exit(1);
    }

    // Mettre le curseur au début du fichier
    rewind(fp);

    // Placement du curseur apres les deux premieres lignes
    fgets(buffer, 50, fp);
    fgets(buffer, 50, fp);

    // Recuperation de la taille de l'image
    fscanf(fp, "%d %d", &img_size_l, &img_size_h);

   	fclose(fp);

   	/*--------------------------------- Allocation ----------------------------------------------*/
    img_t1 = vui8matrix(0, (img_size_h-1), 0, (img_size_l-1));
    Ot = vui8matrix(0, (img_size_h-1), 0, (img_size_l-1));
    V = vui8matrix(0, (img_size_h-1), 0, (img_size_l-1));
    M = vui8matrix(0, (img_size_h-1), 0, (img_size_l-1));

    Et = vui8matrix(0-BORD_TAB, (img_size_h-1)+BORD_TAB, 0-BORD_TAB, (img_size_l-1)+BORD_TAB);
    /*-------------------------------------------------------------------------------------------*/

    /*-------------------------------- Association zone mémoire ---------------------------------*/
    v_img_t1 = (uint8**) img_t1;
    v_V = (uint8**) V;
    v_M = (uint8**) M;
    v_Ot = (uint8**) Ot;
    v_Et = (uint8**) Et;
    /*-------------------------------------------------------------------------------------------*/

    /*-------------------------------------- STEP0 ----------------------------------------------*/
    sprintf(img1_name, "img/car3/car_%d.pgm", 3000);
    MLoadPGM_ui8matrix(img1_name, 0, img_size_h-1, 0, img_size_l-1, v_img_t1);

    M = SigmaDelta_step0_SSE2(V, M, img_t1, img_size_h, img_size_l);
    /*-------------------------------------------------------------------------------------------*/
   	
   	/*-------------------------------------- STEP1 ----------------------------------------------*/
    for(i = 0; i < NB_IMAGE-1; i++)	{
    	sprintf(img1_name, "img/car3/car_%d.pgm", 3000+i+1);

		MLoadPGM_ui8matrix(img1_name, 0, img_size_h-1, 0, img_size_l-1, v_img_t1);

		// BENCH(printf("Sigma Delta : "));
		// CHRONO(SigmaDelta_1step_SSE2(img_t1, Ot, img_size_h, img_size_l, M, V, Et), cycles);BENCH(printf(format, cycles/((img_size_h+1-img_size_l)*(img_size_h+1-img_size_l)))); BENCH(puts(""));
        SigmaDelta_1step_SSE2(img_t1, Ot, img_size_h, img_size_l, M, V, Et);

		sprintf(img_out_name, "img/car3_bin_SD_SSE2/car_%03d.pgm", 3000+i);
		SavePGM_ui8matrix(v_Et, 0, img_size_h-1, 0, img_size_l-1, img_out_name);
    }
    /*-------------------------------------------------------------------------------------------*/
}

void f_test_fd_morpho_car3_SSE2()	{

}

void f_test_sd_morpho_car3_SSE2()	{

}


void f_test_mouvement_car3_SSE2()	{
	//f_test_fd_car3_SSE2();
	f_test_sd_car3_SSE2();
	//f_test_fd_morpho_car3_SSE2();
	//f_test_sd_morpho_car3_SSE2();
}


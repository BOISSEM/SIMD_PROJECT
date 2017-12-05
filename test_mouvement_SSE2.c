/*--------------------------------
    test_mouvement_SSE2.c

    Fonctions de tests unitaires et d'intégration des fonctions de
    detection de mouvement (non optimises)

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Martin Boisse - 2017
----------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "vnrdef.h"
#include "nrdef.h"
#include "vnrutil.h"
#include "mymacro.h"

#include "mouvement_SSE2.h"
#include "test_mouvement_SSE2.h"

// A virer
#define SIZE_H 	6
#define SIZE_L	1


/**
*	Test fonctions Frame Difference SIMD
**/
void f_test_fd_SSE2()
{
	int i, j;
	vuint8** img1_1;
	vuint8** img1_2;
	vuint8** img2_1;
	vuint8** img2_2;

	vuint8** img_diff1;
	vuint8** img_diff2;
	vuint8** img_etq1;
	vuint8** img_etq2;

	/*------ Allocation image test ------*/
	img1_1 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img1_2 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img2_1 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img2_2 = vui8matrix(0, SIZE_H, 0, SIZE_L);

	img_diff1 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_diff2 = vui8matrix(0, SIZE_H, 0, SIZE_L);

	img_etq1 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_etq2 = vui8matrix(0, SIZE_H, 0, SIZE_L);

	/*------ Initialisation constante ------*/
	vuint8 v_0 = _mm_setzero_si128();

	/*----- Initialisation image test -----*/
	for(i = 0; i < SIZE_H; i++)	{
		for(j = 0; j <= SIZE_L; j++)	{
			img1_1[i][j] = v_0;	
			img1_2[i][j] = v_0;	
			img2_1[i][j] = v_0;	
			img2_2[i][j] = v_0;	

			img_diff1[i][j] = v_0;
			img_diff2[i][j] = v_0;

			img_etq1[i][j] = v_0;
			img_etq2[i][j] = v_0;
		}
	}

	/*------ Test fonctions ------*/
	//============= TEST 1 ===============
	img1_2[2][1] = init_vuint8_all(25, 25, 25, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1);
	img1_2[3][0] = init_vuint8_all(0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 150, 150);
	img1_2[3][1] = init_vuint8_all(128, 127, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0);
	img1_2[4][0] = init_vuint8_all(0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 230, 230);
	img1_2[5][0] = init_vuint8_all(0, 3, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 15, 25);

	display_vui8matrix(img1_1, 0, SIZE_H, 0, SIZE_L, " %3d ", "img1_1");
	printf("\n");

	display_vui8matrix(img1_2, 0, SIZE_H, 0, SIZE_L, " %3d ", "img1_2");
	printf("\n=========== Routine Frame Difference ===========\n");
	printf("\n");

	img_etq1 = routine_FrameDifference_SSE2(img1_2, img1_1, SIZE_H, SIZE_L, img_diff1, img_etq1);

	display_vui8matrix(img_etq1, 0, SIZE_H, 0, SIZE_L, " %3d ", "img_etq1");
	printf("\n");

	//============= TEST 2 ===============
	img2_1[2][1] = init_vuint8_all(25, 25, 25, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1);
	img2_1[3][0] = init_vuint8_all(0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 150, 150);
	img2_1[3][1] = init_vuint8_all(128, 127, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0);
	img2_1[4][0] = init_vuint8_all(0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 230, 230);
	img2_1[5][0] = init_vuint8_all(0, 3, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 15, 25);

	img2_2[2][1] = init_vuint8_all(0, 3, 0, 0, 0, 1, 125, 200, 255, 0, 0, 0, 0, 0, 15, 25);
	img2_2[3][1] = init_vuint8_all(0, 3, 0, 20, 0, 49, 125, 20, 255, 0, 0, 1, 0, 0, 0, 0);
	img2_2[4][0] = init_vuint8_all(0, 3, 0, 0, 0, 1, 0, 30, 55, 0, 2, 0, 0, 0, 1, 2);
	img2_2[5][1] = init_vuint8_all(0, 3, 0, 0, 0, 1, 0, 30, 55, 0, 0, 0, 0, 0, 120, 123);

	display_vui8matrix(img2_1, 0, SIZE_H, 0, SIZE_L, " %3d ", "img2_1");
	printf("\n");

	display_vui8matrix(img2_2, 0, SIZE_H, 0, SIZE_L, " %3d ", "img2_2");
	printf("\n=========== Routine Frame Difference ===========\n");
	printf("\n");

	img_etq2 = routine_FrameDifference_SSE2(img2_2, img2_1, SIZE_H, SIZE_L, img_diff2, img_etq2);

	display_vui8matrix(img_etq2, 0, SIZE_H, 0, SIZE_L, " %3d ", "img_etq2");
	printf("\n");

	//============ DESALLOCATION MEMOIRE =============
	free_vui8matrix(img1_1, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img1_2, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img2_1, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img2_2, 0, SIZE_H, 0, SIZE_L);

	free_vui8matrix(img_diff1, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_diff2, 0, SIZE_H, 0, SIZE_L);

	free_vui8matrix(img_etq1, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_etq2, 0, SIZE_H, 0, SIZE_L);
}

/**
*	Test fonctions Sigma Delta SIMD
**/
void f_test_sd_SSE2()
{
	int i, j;
	vuint8** img1_0;
	vuint8** img1_1;
	vuint8** img1_2;
	vuint8** img1_3;
	vuint8** img1_4;

	vuint8** img_dif1_1;
	vuint8** img_dif1_2;
	vuint8** img_dif1_3;
	vuint8** img_dif1_4;

	vuint8** img_var1_0;
	vuint8** img_var1_1;
	vuint8** img_var1_2;
	vuint8** img_var1_3;
	vuint8** img_var1_4;

	vuint8** img_moy1_0;
	vuint8** img_moy1_1;
	vuint8** img_moy1_2;
	vuint8** img_moy1_3;
	vuint8** img_moy1_4;

	vuint8** img_etq1_1;
	vuint8** img_etq1_2;
	vuint8** img_etq1_3;
	vuint8** img_etq1_4;

	/*------ Allocation image test ------*/
	img1_0 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img1_1 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img1_2 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img1_3 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img1_4 = vui8matrix(0, SIZE_H, 0, SIZE_L);

	img_dif1_1 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_dif1_2 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_dif1_3 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_dif1_4 = vui8matrix(0, SIZE_H, 0, SIZE_L);

	img_var1_0 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_var1_1 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_var1_2 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_var1_3 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_var1_4 = vui8matrix(0, SIZE_H, 0, SIZE_L);

	img_moy1_0 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_moy1_1 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_moy1_2 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_moy1_3 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_moy1_4 = vui8matrix(0, SIZE_H, 0, SIZE_L);

	img_etq1_1 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_etq1_2 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_etq1_3 = vui8matrix(0, SIZE_H, 0, SIZE_L);
	img_etq1_4 = vui8matrix(0, SIZE_H, 0, SIZE_L);

	/*------ Initialisation constante ------*/
	vuint8 v_0 = _mm_setzero_si128();

	/*----- Initialisation image test -----*/
	for(i = 0; i < SIZE_H; i++)	{
		for(j = 0; j <= SIZE_L; j++)	{
			img1_0[i][j] = v_0;
			img1_1[i][j] = v_0;
			img1_2[i][j] = v_0;
			img1_3[i][j] = v_0;
			img1_4[i][j] = v_0;

			img_dif1_1[i][j] = v_0;
            img_dif1_2[i][j] = v_0;
            img_dif1_3[i][j] = v_0;
            img_dif1_4[i][j] = v_0;

            img_var1_0[i][j] = v_0;
            img_var1_1[i][j] = v_0;
            img_var1_2[i][j] = v_0;
            img_var1_3[i][j] = v_0;
            img_var1_4[i][j] = v_0;

            img_moy1_0[i][j] = v_0;
            img_moy1_1[i][j] = v_0;
            img_moy1_2[i][j] = v_0;
            img_moy1_3[i][j] = v_0;
            img_moy1_4[i][j] = v_0;

            img_etq1_1[i][j] = v_0;
            img_etq1_2[i][j] = v_0;
            img_etq1_3[i][j] = v_0;
            img_etq1_4[i][j] = v_0;
		}
	}

	/*------ Test fonctions ------*/
    //============= TEST 1 ===============
	img1_0[3][0] = init_vuint8_all(0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 15, 125, 150);

    img1_1[2][1] = init_vuint8_all(25, 25, 25, 0, 0, 1, 0, 255, 0, 1, 0, 1, 0, 1, 0, 1);
	img1_1[3][0] = init_vuint8_all(0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 150, 150);
	img1_1[3][1] = init_vuint8_all(128, 127, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0);
	img1_1[4][0] = init_vuint8_all(0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 230, 230);
	img1_1[5][0] = init_vuint8_all(0, 3, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 15, 25);

	img1_2[2][1] = init_vuint8_all(0, 3, 0, 0, 0, 1, 125, 200, 255, 0, 0, 0, 0, 0, 15, 25);
	img1_2[3][1] = init_vuint8_all(0, 3, 0, 20, 0, 49, 125, 20, 255, 0, 0, 1, 0, 0, 0, 0);
	img1_2[4][0] = init_vuint8_all(0, 3, 0, 0, 0, 1, 0, 30, 55, 0, 2, 0, 0, 0, 1, 2);
	img1_2[5][1] = init_vuint8_all(0, 3, 0, 0, 0, 1, 0, 30, 55, 0, 0, 0, 0, 0, 120, 123);

	printf("\n======================\n");

	img_moy1_0 = SigmaDelta_step0_SSE2(img_var1_0, img_moy1_0, img1_0, SIZE_H, SIZE_L);

	display_vui8matrix(img1_0, 0, SIZE_H, 0, SIZE_L, " %3d ", "img1_0");
	printf("\n");

	display_vui8matrix(img1_1, 0, SIZE_H, 0, SIZE_L, " %3d ", "img1_1");
	printf("\n");

	display_vui8matrix(img_moy1_0, 0, SIZE_H, 0, SIZE_L, " %3d ", "img_moy1_0");
	printf("\n");

	display_vui8matrix(img_var1_0, 0, SIZE_H, 0, SIZE_L, " %3d ", "img_var1_0");
	printf("\n");

	printf("\n======================\n");

	img_etq1_1 = SigmaDelta_1step_SSE2(img1_1, img_dif1_1, SIZE_H, SIZE_L, img_moy1_0, img_var1_0, img_etq1_1);

	display_vui8matrix(img_moy1_0, 0, SIZE_H, 0, SIZE_L, " %3d ", "img_moy1_0");
	printf("\n");

	display_vui8matrix(img_var1_0, 0, SIZE_H, 0, SIZE_L, " %3d ", "img_var1_0");
	printf("\n");

	display_vui8matrix(img_etq1_1, 0, SIZE_H, 0, SIZE_L, " %3d ", "img_etq1_1");
	printf("\n");


	printf("\n======================\n");

	//============ DESALLOCATION MEMOIRE =============
	free_vui8matrix(img1_0, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img1_1, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img1_2, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img1_3, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img1_4, 0, SIZE_H, 0, SIZE_L);

	free_vui8matrix(img_dif1_2, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_dif1_1, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_dif1_3, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_dif1_4, 0, SIZE_H, 0, SIZE_L);

	free_vui8matrix(img_var1_0, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_var1_1, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_var1_2, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_var1_3, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_var1_4, 0, SIZE_H, 0, SIZE_L);

	free_vui8matrix(img_moy1_0, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_moy1_1, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_moy1_2, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_moy1_3, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_moy1_4, 0, SIZE_H, 0, SIZE_L);

	free_vui8matrix(img_etq1_1, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_etq1_2, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_etq1_3, 0, SIZE_H, 0, SIZE_L);
	free_vui8matrix(img_etq1_4, 0, SIZE_H, 0, SIZE_L);
}


void f_test_mouvement_SSE2()	{

	f_test_fd_SSE2();
	//f_test_sd_SSE2();
}

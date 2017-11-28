/*--------------------------------
    test_mouvement_unit.c

    Fonctions de tests unitaires et d'intégration des fonctions de
    detection de mouvement (non optimises)

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Martin Boisse - 2017
 ----------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "nrdef.h"
#include "nrutil.h"
#include "mouvement.h"
#include "test_mouvement.h"

#define SIZE_TAB    7
#define BORD_TAB    2

/**
 *  Test fonctions Frame Difference
 */
void f_test_fd()
{
    int i, j;
    uint8_t** img1_1;
    uint8_t** img1_2;
    uint8_t** img2_1;
    uint8_t** img2_2;

    uint8_t** img_diff1;
    uint8_t** img_diff2;
    uint8_t** img_etq1;
    uint8_t** img_etq2;

    /*------ Allocation image test ------*/
    img1_1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img1_2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img_diff1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_diff2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img_etq1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_etq2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    /*----- Initialisation image test -----*/
    for(i=-BORD_TAB; i<=SIZE_TAB-1+BORD_TAB; i++)
    {
        for(j=-BORD_TAB; j<=SIZE_TAB-1+BORD_TAB; j++)
        {
            img1_1[i][j] = 0;
            img1_2[i][j] = 0;
            img2_1[i][j] = 0;
            img2_2[i][j] = 0;
            img_diff1[i][j] = 0;
            img_diff2[i][j] = 0;
            img_etq1[i][j] = 0;
            img_etq2[i][j] = 0;
        }
    }

    /*------ Test fonctions ------*/
    //============= TEST 1 ===============
    img1_2[2][2] = 25;      img1_2[2][3] = 50;      img1_2[2][4] = 75;
    img1_2[3][2] = 10;      img1_2[3][3] = 20;      img1_2[3][4] = 90;
    img1_2[4][2] = 255;     img1_2[4][3] = 100;     img1_2[4][4] = 50;


    display_ui8matrix(img1_1, -BORD_TAB, SIZE_TAB-1+BORD_TAB, -BORD_TAB, SIZE_TAB-1+BORD_TAB," %3d ","Tableau 1-1");
    printf("\n======================\n");

    routine_FrameDifference(img1_1, img1_2, SIZE_TAB, SIZE_TAB, img_diff1, img_etq1);

    display_ui8matrix(img1_1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1-1");
    printf("\n");

    display_ui8matrix(img1_2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1-2");
    printf("\n");

    display_ui8matrix(img_diff1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Diff 1");
    printf("\n");

    display_ui8matrix(img_etq1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Etq 1");
    printf("\n");

    printf("\n======================\n");

    //============= TEST 2 ===============
    img2_1[2][2] = 25;      img2_1[2][3] = 50;      img2_1[2][4] = 75;
    img2_1[3][2] = 10;      img2_1[3][3] = 20;      img2_1[3][4] = 90;
    img2_1[4][2] = 255;     img2_1[4][3] = 100;     img2_1[4][4] = 50;

    img2_2[2][2] = 0;       img2_2[2][3] = 150;     img2_2[2][4] = 25;
    img2_2[3][2] = 59;      img2_2[3][3] = 68;      img2_2[3][4] = 255;
    img2_2[4][2] = 255;     img2_2[4][3] = 105;     img2_2[4][4] = 50;


    routine_FrameDifference(img2_1, img2_2, SIZE_TAB, SIZE_TAB, img_diff2, img_etq2);

    display_ui8matrix(img2_1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 2-1");
    printf("\n");

    display_ui8matrix(img2_2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 2-2");
    printf("\n");

    display_ui8matrix(img_diff2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Diff 2");
    printf("\n");

    display_ui8matrix(img_etq2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Etq 2");
    printf("\n");

    //============ DESALLOCATION MEMOIRE =============
    free_ui8matrix(img1_1,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img1_2,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_1,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_2,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img_diff1,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_diff2,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_etq1,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_etq2,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
}


/**
 *  Test fonctions Sigma Delta
 */
void f_test_sd()
{
    int i, j;
    uint8_t** img1_0;
    uint8_t** img1_1;
    uint8_t** img1_2;
    uint8_t** img1_3;
    uint8_t** img1_4;

    uint8_t** img_dif1_1;
    uint8_t** img_dif1_2;
    uint8_t** img_dif1_3;
    uint8_t** img_dif1_4;

    uint8_t** img_var1_0;
    uint8_t** img_var1_1;
    uint8_t** img_var1_2;
    uint8_t** img_var1_3;
    uint8_t** img_var1_4;

    uint8_t** img_moy1_0;
    uint8_t** img_moy1_1;
    uint8_t** img_moy1_2;
    uint8_t** img_moy1_3;
    uint8_t** img_moy1_4;

    uint8_t** img_etq1_1;
    uint8_t** img_etq1_2;
    uint8_t** img_etq1_3;
    uint8_t** img_etq1_4;

    /*------ Allocation image test ------*/
    img1_0 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img1_1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img1_2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img1_3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img1_4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img_dif1_1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_dif1_2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_dif1_3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_dif1_4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img_var1_0 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_var1_1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_var1_2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_var1_3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_var1_4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img_moy1_0 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_moy1_1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_moy1_2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_moy1_3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_moy1_4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img_etq1_1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_etq1_2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_etq1_3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img_etq1_4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    /*----- Initialisation image test -----*/
    for(i=-BORD_TAB; i<=SIZE_TAB-1+BORD_TAB; i++)
    {
        for(j=-BORD_TAB; j<=SIZE_TAB-1+BORD_TAB; j++)
        {
            img1_0[i][j] = 0;
            img1_1[i][j] = 0;
            img1_2[i][j] = 0;
            img1_3[i][j] = 0;
            img1_4[i][j] = 0;

            img_dif1_1[i][j] = 0;
            img_dif1_2[i][j] = 0;
            img_dif1_3[i][j] = 0;
            img_dif1_4[i][j] = 0;

            img_var1_0[i][j] = 0;
            img_var1_1[i][j] = 0;
            img_var1_2[i][j] = 0;
            img_var1_3[i][j] = 0;
            img_var1_4[i][j] = 0;

            img_moy1_0[i][j] = 0;
            img_moy1_1[i][j] = 0;
            img_moy1_2[i][j] = 0;
            img_moy1_3[i][j] = 0;
            img_moy1_4[i][j] = 0;

            img_etq1_1[i][j] = 0;
            img_etq1_2[i][j] = 0;
            img_etq1_3[i][j] = 0;
            img_etq1_4[i][j] = 0;
        }
    }

    /*------ Test fonctions ------*/
    //============= TEST 1 ===============
    img1_0[2][2] = 25;      img1_0[2][3] = 25;      img1_0[2][4] = 25;
    img1_0[3][2] = 25;      img1_0[3][3] = 25;      img1_0[3][4] = 25;
    img1_0[4][2] = 25;      img1_0[4][3] = 25;      img1_0[4][4] = 25;

    img1_1[2][2] = 25;      img1_1[2][3] = 27;      img1_1[2][4] = 32;
    img1_1[3][2] = 23;      img1_1[3][3] = 25;      img1_1[3][4] = 25;
    img1_1[4][2] = 22;      img1_1[4][3] = 22;      img1_1[4][4] = 24;

    img1_2[2][2] = 25;      img1_2[2][3] = 24;      img1_2[2][4] = 22;
    img1_2[3][2] = 27;      img1_2[3][3] = 25;      img1_2[3][4] = 25;
    img1_2[4][2] = 150;     img1_2[4][3] = 148;     img1_2[4][4] = 25;

    img1_3[2][2] = 26;      img1_3[2][3] = 28;      img1_3[2][4] = 20;
    img1_3[3][2] = 28;      img1_3[3][3] = 153;     img1_3[3][4] = 150;
    img1_3[4][2] = 25;      img1_3[4][3] = 22;      img1_3[4][4] = 26;

    img1_4[2][2] = 23;      img1_4[2][3] = 34;      img1_4[2][4] = 153;
    img1_4[3][2] = 23;      img1_4[3][3] = 32;      img1_4[3][4] = 25;
    img1_4[4][2] = 32;      img1_4[4][3] = 25;      img1_4[4][4] = 22;

    printf("\n======================\n");

    SigmaDelta_step0(img_var1_0, img_moy1_0, img1_0, SIZE_TAB, SIZE_TAB);

    display_ui8matrix(img1_0, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1-0");
    printf("\n");

    display_ui8matrix(img_moy1_0, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Ms 1-0");
    printf("\n");

    display_ui8matrix(img_var1_0, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Vs 1-0");
    printf("\n");

    printf("\n======================\n");

    copy_ui8matrix_ui8matrix(img_var1_0, 0, SIZE_TAB-1, 0, SIZE_TAB-1, img_var1_1);
    copy_ui8matrix_ui8matrix(img_moy1_0, 0, SIZE_TAB-1, 0, SIZE_TAB-1, img_moy1_1);

    SigmaDelta_1step(img1_1, img_dif1_1, SIZE_TAB, SIZE_TAB, img_moy1_1, img_var1_1, img_etq1_1);

    display_ui8matrix(img1_1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1-1");
    printf("\n");

    display_ui8matrix(img_dif1_1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Diff 1-1");
    printf("\n");

    display_ui8matrix(img_moy1_1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Ms 1-1");
    printf("\n");

    display_ui8matrix(img_var1_1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Vs 1-1");
    printf("\n");

    display_ui8matrix(img_etq1_1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Etiquette 1-1");
    printf("\n");

    printf("\n======================\n");

    copy_ui8matrix_ui8matrix(img_var1_1, 0, SIZE_TAB-1, 0, SIZE_TAB-1, img_var1_2);
    copy_ui8matrix_ui8matrix(img_moy1_1, 0, SIZE_TAB-1, 0, SIZE_TAB-1, img_moy1_2);

    SigmaDelta_1step(img1_2, img_dif1_2, SIZE_TAB, SIZE_TAB, img_moy1_2, img_var1_2, img_etq1_2);

    display_ui8matrix(img1_2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1-2");
    printf("\n");

    display_ui8matrix(img_dif1_2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Diff 1-2");
    printf("\n");

    display_ui8matrix(img_moy1_2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Ms 1-2");
    printf("\n");

    display_ui8matrix(img_var1_2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Vs 1-2");
    printf("\n");

    display_ui8matrix(img_etq1_2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Etiquette 1-2");
    printf("\n");

    printf("\n======================\n");

    copy_ui8matrix_ui8matrix(img_var1_2, 0, SIZE_TAB-1, 0, SIZE_TAB-1, img_var1_3);
    copy_ui8matrix_ui8matrix(img_moy1_2, 0, SIZE_TAB-1, 0, SIZE_TAB-1, img_moy1_3);

    SigmaDelta_1step(img1_3, img_dif1_3, SIZE_TAB, SIZE_TAB, img_moy1_3, img_var1_3, img_etq1_3);

    display_ui8matrix(img1_3, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1-2");
    printf("\n");

    display_ui8matrix(img_dif1_3, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Diff 1-2");
    printf("\n");

    display_ui8matrix(img_moy1_3, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Ms 1-2");
    printf("\n");

    display_ui8matrix(img_var1_3, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Vs 1-2");
    printf("\n");

    display_ui8matrix(img_etq1_3, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Etiquette 1-2");
    printf("\n");

    printf("\n======================\n");

    copy_ui8matrix_ui8matrix(img_var1_3, 0, SIZE_TAB-1, 0, SIZE_TAB-1, img_var1_4);
    copy_ui8matrix_ui8matrix(img_moy1_3, 0, SIZE_TAB-1, 0, SIZE_TAB-1, img_moy1_4);

    SigmaDelta_1step(img1_4, img_dif1_4, SIZE_TAB, SIZE_TAB, img_moy1_4, img_var1_4, img_etq1_4);

    display_ui8matrix(img1_4, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1-2");
    printf("\n");

    display_ui8matrix(img_dif1_4, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Diff 1-2");
    printf("\n");

    display_ui8matrix(img_moy1_4, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Ms 1-2");
    printf("\n");

    display_ui8matrix(img_var1_4, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Vs 1-2");
    printf("\n");

    display_ui8matrix(img_etq1_4, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau Etiquette 1-2");
    printf("\n");

    printf("\n======================\n");

    free_ui8matrix(img1_0,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img1_1,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img1_2,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img1_3,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img1_4,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img_dif1_2,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_dif1_1,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_dif1_3,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_dif1_4,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img_var1_0,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_var1_1,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_var1_2,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_var1_3,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_var1_4,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img_moy1_0,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_moy1_1,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_moy1_2,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_moy1_3,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_moy1_4,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img_etq1_1,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_etq1_2,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_etq1_3,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img_etq1_4,0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
}

void f_test_mouvement()
{
   f_test_fd();
    // f_test_sd();
}

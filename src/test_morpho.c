/*--------------------------------
    test_morpho.c

    Fonctions de tests unitaires et d'intégration des fonctions de
    morphologie mathématique

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Kevin Seng - 2017
 ----------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "test_morpho.h"
#include "morpho.h"
#include "nrdef.h"
#include "nrutil.h"

#define SIZE_TAB    8
#define BORD_TAB    2

/**
 *  Test fonctions de dilatation binaire
 */
void f_test_dilate_bin()
{
    int i, j;
    uint8_t** img1;
    uint8_t** img2;
    uint8_t** img3;
    uint8_t** img4;

    uint8_t** img1_o;
    uint8_t** img2_o;
    uint8_t** img3_o;
    uint8_t** img4_o;

    /*------ Allocation image test ------*/
    img1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img1_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    /*----- Initialisation image test -----*/
    for(i=-BORD_TAB; i<=SIZE_TAB-1+BORD_TAB; i++)
    {
        for(j=-BORD_TAB; j<=SIZE_TAB-1+BORD_TAB; j++)
        {
            img1[i][j] = 0;
            img2[i][j] = 0;
            img3[i][j] = 0;
            img4[i][j] = 0;
            img1_o[i][j] = 0;
            img2_o[i][j] = 0;
            img3_o[i][j] = 0;
            img4_o[i][j] = 0;
        }
    }

    /*------ Test fonctions ------*/
    //============= TEST 1 - Dilataion binaire 3 ===============
    img1[3][3] = 1;

    display_ui8matrix(img1, -BORD_TAB, SIZE_TAB-1+BORD_TAB, -BORD_TAB, SIZE_TAB-1+BORD_TAB," %d ","Tableau 1");
    printf("\n======================\n");

    dilate_bin3(img1, SIZE_TAB, SIZE_TAB, img1_o);

    display_ui8matrix(img1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1");
    printf("\n");

    display_ui8matrix(img1_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1 - Dilatation Binaire 3");
    printf("\n");


    //============= TEST 2 - Dilataion binaire 3 ===============
    img2[0][1] = 1;
    img2[4][2] = 1;
    img2[3][5] = 1;

    dilate_bin3(img2, SIZE_TAB, SIZE_TAB, img2_o);

    display_ui8matrix(img2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 2");
    printf("\n");

    display_ui8matrix(img2_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 2 - Dilatation Binaire 3");
    printf("\n");

    //============= TEST 3 - Dilataion binaire 5 ===============
    img3[3][3] = 1;

    dilate_bin5(img3, SIZE_TAB, SIZE_TAB, img3_o);

    display_ui8matrix(img3, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 3");
    printf("\n");

    display_ui8matrix(img3_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 3 - Dilatation Binaire 5");
    printf("\n");

    //============= TEST 4 - Dilataion binaire 5 ===============
    img4[0][1] = 1;
    img4[4][4] = 1;

    dilate_bin5(img4, SIZE_TAB, SIZE_TAB, img4_o);

    display_ui8matrix(img4, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 4");
    printf("\n");

    display_ui8matrix(img4_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 4 - Dilatation Binaire 5");
    printf("\n");

    //============ DESALLOCATION MEMOIRE =============
    free_ui8matrix(img1, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img1_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
}

/**
 *  Test fonctions d'erosion binaire
 */
void f_test_erode_bin()
{
    int i, j;
    uint8_t** img1;
    uint8_t** img2;
    uint8_t** img3;
    uint8_t** img4;

    uint8_t** img1_o;
    uint8_t** img2_o;
    uint8_t** img3_o;
    uint8_t** img4_o;

    /*------ Allocation image test ------*/
    img1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img1_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    /*----- Initialisation image test -----*/
    for(i=-BORD_TAB; i<=SIZE_TAB-1+BORD_TAB; i++)
    {
        for(j=-BORD_TAB; j<=SIZE_TAB-1+BORD_TAB; j++)
        {
            img1[i][j] = 0;
            img2[i][j] = 0;
            img3[i][j] = 0;
            img4[i][j] = 0;
            img1_o[i][j] = 0;
            img2_o[i][j] = 0;
            img3_o[i][j] = 0;
            img4_o[i][j] = 0;
        }
    }

    /*------ Test fonctions ------*/
    //============= TEST 1 - Erosion binaire 3 ===============
    img1[2][2] = 1; img1[2][3] = 1; img1[2][4] = 1;
    img1[3][2] = 1; img1[3][3] = 1; img1[3][4] = 1;
    img1[4][2] = 1; img1[4][3] = 1; img1[4][4] = 1;

    display_ui8matrix(img1, -BORD_TAB, SIZE_TAB-1+BORD_TAB, -BORD_TAB, SIZE_TAB-1+BORD_TAB," %d ","Tableau 1");

    printf("\n======================\n");

    erode_bin3(img1, SIZE_TAB, SIZE_TAB, img1_o);

    display_ui8matrix(img1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1");
    printf("\n");

    display_ui8matrix(img1_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1 - Erosion Binaire 3");
    printf("\n");


    //============= TEST 2 - Erosion binaire 3 ===============
    for(i=1; i<5; i++){
        for(j=0; j< 4; j++){
            img2[i][j] = 1;
        }
    }

    for(i=3; i<7; i++){
        for(j=2; j< 5; j++){
            img2[i][j] = 1;
        }
    }

    erode_bin3(img2, SIZE_TAB, SIZE_TAB, img2_o);

    display_ui8matrix(img2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 2");
    printf("\n");

    display_ui8matrix(img2_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 2 - Erosion Binaire 3");
    printf("\n");

    //============= TEST 3 - Dilataion binaire 5 ===============
    for(i=0; i<=SIZE_TAB-1; i++)
    {
        for(j=0; j<=SIZE_TAB-1; j++)
        {
            img3[i][j] = 1;
        }
    }

    erode_bin5(img3, SIZE_TAB, SIZE_TAB, img3_o);

    display_ui8matrix(img3, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 3");
    printf("\n");

    display_ui8matrix(img3_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 3 - Erosion Binaire 5");
    printf("\n");

    //============= TEST 4 - Dilataion binaire 5 ===============
    for(i=0; i<=SIZE_TAB-1; i++)
    {
        for(j=0; j<=SIZE_TAB-1; j++)
        {
            img4[i][j] = 1;
        }
    }

    img4[2][4] = 0; img4[2][5] = 0; img4[2][6] = 0;
    img4[3][3] = 0; img4[2][4] = 0; img4[2][5] = 0;

    erode_bin5(img4, SIZE_TAB, SIZE_TAB, img4_o);

    display_ui8matrix(img4, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 4");
    printf("\n");

    display_ui8matrix(img4_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 4 - Erosion Binaire 5");
    printf("\n");


    //============ DESALLOCATION MEMOIRE =============
    free_ui8matrix(img1, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img1_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
}

/**
 *  Test fonctions d'ouverture binaire
 */
void f_test_open_bin()
{
    int i, j;
    uint8_t** img1;
    uint8_t** img2;
    uint8_t** img3;
    uint8_t** img4;

    uint8_t** img1_buf;
    uint8_t** img2_buf;
    uint8_t** img3_buf;
    uint8_t** img4_buf;

    uint8_t** img1_o;
    uint8_t** img2_o;
    uint8_t** img3_o;
    uint8_t** img4_o;

    /*------ Allocation image test ------*/
    img1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img1_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img1_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    /*----- Initialisation image test -----*/
    for(i=-BORD_TAB; i<=SIZE_TAB-1+BORD_TAB; i++)
    {
        for(j=-BORD_TAB; j<=SIZE_TAB-1+BORD_TAB; j++)
        {
            img1[i][j] = 0;
            img2[i][j] = 0;
            img3[i][j] = 0;
            img4[i][j] = 0;
            img1_buf[i][j] = 0;
            img2_buf[i][j] = 0;
            img3_buf[i][j] = 0;
            img4_buf[i][j] = 0;
            img1_o[i][j] = 0;
            img2_o[i][j] = 0;
            img3_o[i][j] = 0;
            img4_o[i][j] = 0;
        }
    }

    /*------ Test fonctions ------*/
    //============= TEST 1 - Ouverture binaire 3 ===============
    img1[0][0] = 0; img1[0][1] = 0; img1[0][2] = 1; img1[0][3] = 1; img1[0][4] = 1; img1[0][5] = 1; img1[0][6] = 0; img2[0][7] = 0;
    img1[1][0] = 0; img1[1][1] = 1; img1[1][2] = 1; img1[1][3] = 1; img1[1][4] = 1; img1[1][5] = 1; img1[1][6] = 1; img2[1][7] = 0;
    img1[2][0] = 0; img1[2][1] = 1; img1[2][2] = 1; img1[2][3] = 1; img1[2][4] = 1; img1[2][5] = 1; img1[2][6] = 1; img2[2][7] = 0;
    img1[3][0] = 0; img1[3][1] = 1; img1[3][2] = 1; img1[3][3] = 1; img1[3][4] = 1; img1[3][5] = 1; img1[3][6] = 1; img2[3][7] = 0;
    img1[4][0] = 0; img1[4][1] = 1; img1[4][2] = 1; img1[4][3] = 1; img1[4][4] = 1; img1[4][5] = 1; img1[4][6] = 1; img2[4][7] = 0;
    img1[5][0] = 0; img1[5][1] = 1; img1[5][2] = 1; img1[5][3] = 0; img1[5][4] = 0; img1[5][5] = 1; img1[5][6] = 1; img2[5][7] = 0;
    img1[6][0] = 0; img1[6][1] = 0; img1[6][2] = 1; img1[6][3] = 1; img1[6][4] = 1; img1[6][5] = 1; img1[6][6] = 0; img2[6][7] = 0;
    img2[7][0] = 0; img2[7][1] = 0; img2[7][2] = 0; img2[7][3] = 1; img2[7][4] = 0; img2[7][5] = 0; img2[7][6] = 0; img2[7][7] = 1;

    display_ui8matrix(img1, -BORD_TAB, SIZE_TAB-1+BORD_TAB, -BORD_TAB, SIZE_TAB-1+BORD_TAB," %d ","Tableau 1");
    printf("\n======================\n");

    open_bin3(img1, SIZE_TAB, SIZE_TAB, img1_o, img1_buf);

    display_ui8matrix(img1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1");
    printf("\n");

    display_ui8matrix(img1_buf, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1 - Temporaire (Erosion)");
    printf("\n");

    display_ui8matrix(img1_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1 - Ouverture Binaire 3 (Erosion + Dilatation)");
    printf("\n");

    //============= TEST 1 - Ouverture binaire 5 ===============
    img2[0][0] = 1; img2[0][1] = 1; img2[0][2] = 1; img2[0][3] = 1; img2[0][4] = 1; img2[0][5] = 1; img2[0][6] = 1; img2[0][7] = 0;
    img2[1][0] = 0; img2[1][1] = 1; img2[1][2] = 1; img2[1][3] = 1; img2[1][4] = 1; img2[1][5] = 1; img2[1][6] = 1; img2[1][7] = 0;
    img2[2][0] = 0; img2[2][1] = 1; img2[2][2] = 1; img2[2][3] = 1; img2[2][4] = 1; img2[2][5] = 1; img2[2][6] = 1; img2[2][7] = 0;
    img2[3][0] = 0; img2[3][1] = 1; img2[3][2] = 1; img2[3][3] = 1; img2[3][4] = 1; img2[3][5] = 1; img2[3][6] = 1; img2[3][7] = 0;
    img2[4][0] = 0; img2[4][1] = 1; img2[4][2] = 1; img2[4][3] = 1; img2[4][4] = 1; img2[4][5] = 1; img2[4][6] = 1; img2[4][7] = 0;
    img2[5][0] = 0; img2[5][1] = 1; img2[5][2] = 1; img2[5][3] = 0; img2[5][4] = 0; img2[5][5] = 1; img2[5][6] = 1; img2[5][7] = 0;
    img2[6][0] = 0; img2[6][1] = 1; img2[6][2] = 1; img2[6][3] = 1; img2[6][4] = 1; img2[6][5] = 1; img2[6][6] = 1; img2[6][7] = 0;
    img2[7][0] = 0; img2[7][1] = 1; img2[7][2] = 1; img2[7][3] = 1; img2[7][4] = 1; img2[7][5] = 1; img2[7][6] = 1; img2[7][7] = 0;

    printf("\n======================\n");

    open_bin5(img2, SIZE_TAB, SIZE_TAB, img2_o, img2_buf);

    display_ui8matrix(img2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 2");
    printf("\n");

    display_ui8matrix(img2_buf, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 2 - Temporaire (Erosion)");
    printf("\n");

    display_ui8matrix(img2_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 2 - Ouverture Binaire 5 (Erosion + Dilatation)");
    printf("\n");

    //============ DESALLOCATION MEMOIRE =============
    free_ui8matrix(img1, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img1_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img1_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

}

/**
 *  Test fonctions de fermeture binaire
 */
void f_test_close_bin()
{
    int i, j;
    uint8_t** img1;
    uint8_t** img2;
    uint8_t** img3;
    uint8_t** img4;

    uint8_t** img1_buf;
    uint8_t** img2_buf;
    uint8_t** img3_buf;
    uint8_t** img4_buf;

    uint8_t** img1_o;
    uint8_t** img2_o;
    uint8_t** img3_o;
    uint8_t** img4_o;

    /*------ Allocation image test ------*/
    img1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img1_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img1_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    /*----- Initialisation image test -----*/
    for(i=-BORD_TAB; i<=SIZE_TAB-1+BORD_TAB; i++)
    {
        for(j=-BORD_TAB; j<=SIZE_TAB-1+BORD_TAB; j++)
        {
            img1[i][j] = 0;
            img2[i][j] = 0;
            img3[i][j] = 0;
            img4[i][j] = 0;
            img1_buf[i][j] = 0;
            img2_buf[i][j] = 0;
            img3_buf[i][j] = 0;
            img4_buf[i][j] = 0;
            img1_o[i][j] = 0;
            img2_o[i][j] = 0;
            img3_o[i][j] = 0;
            img4_o[i][j] = 0;
        }
    }

    /*------ Test fonctions ------*/
    //============= TEST 1 - Ouverture binaire 3 ===============
    img1[0][0] = 0; img1[0][1] = 0; img1[0][2] = 0; img1[0][3] = 0; img1[0][4] = 0; img1[0][5] = 0; img1[0][6] = 0; img1[0][7] = 0;
    img1[1][0] = 0; img1[1][1] = 0; img1[1][2] = 0; img1[1][3] = 0; img1[1][4] = 0; img1[1][5] = 0; img1[1][6] = 0; img1[1][7] = 0;
    img1[2][0] = 0; img1[2][1] = 0; img1[2][2] = 0; img1[2][3] = 1; img1[2][4] = 1; img1[2][5] = 1; img1[2][6] = 0; img1[2][7] = 0;
    img1[3][0] = 0; img1[3][1] = 0; img1[3][2] = 1; img1[3][3] = 0; img1[3][4] = 0; img1[3][5] = 0; img1[3][6] = 1; img1[3][7] = 0;
    img1[4][0] = 0; img1[4][1] = 0; img1[4][2] = 1; img1[4][3] = 0; img1[4][4] = 0; img1[4][5] = 0; img1[4][6] = 1; img1[4][7] = 0;
    img1[5][0] = 0; img1[5][1] = 0; img1[5][2] = 1; img1[5][3] = 0; img1[5][4] = 0; img1[5][5] = 0; img1[5][6] = 0; img1[5][7] = 0;
    img1[6][0] = 0; img1[6][1] = 0; img1[6][2] = 0; img1[6][3] = 1; img1[6][4] = 1; img1[6][5] = 1; img1[6][6] = 0; img1[6][7] = 0;
    img1[7][0] = 0; img1[7][1] = 0; img1[7][2] = 0; img1[7][3] = 0; img1[7][4] = 0; img1[7][5] = 0; img1[7][6] = 0; img1[7][7] = 1;

    display_ui8matrix(img1, -BORD_TAB, SIZE_TAB-1+BORD_TAB, -BORD_TAB, SIZE_TAB-1+BORD_TAB," %d ","Tableau 1");
    printf("\n======================\n");

    close_bin3(img1, SIZE_TAB, SIZE_TAB, img1_o, img1_buf);

    display_ui8matrix(img1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1");
    printf("\n");

    display_ui8matrix(img1_buf, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1 - Temporaire (Dilatation)");
    printf("\n");

    display_ui8matrix(img1_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1 - Fermeture Binaire 3 (Dilatation + Erosion)");
    printf("\n");

    /*------ Test fonctions ------*/
    //============= TEST 2 - Fermeture binaire 3 ===============
    img2[0][0] = 1; img2[0][1] = 0; img2[0][2] = 0; img2[0][3] = 0; img2[0][4] = 0; img2[0][5] = 0; img2[0][6] = 0; img2[0][7] = 0;
    img2[1][0] = 0; img2[1][1] = 0; img2[1][2] = 0; img2[1][3] = 0; img2[1][4] = 0; img2[1][5] = 0; img2[1][6] = 0; img2[1][7] = 0;
    img2[2][0] = 0; img2[2][1] = 0; img2[2][2] = 0; img2[2][3] = 1; img2[2][4] = 1; img2[2][5] = 1; img2[2][6] = 0; img2[2][7] = 0;
    img2[3][0] = 0; img2[3][1] = 0; img2[3][2] = 1; img2[3][3] = 1; img2[3][4] = 0; img2[3][5] = 0; img2[3][6] = 1; img2[3][7] = 0;
    img2[4][0] = 0; img2[4][1] = 0; img2[4][2] = 1; img2[4][3] = 0; img2[4][4] = 0; img2[4][5] = 0; img2[4][6] = 1; img2[4][7] = 0;
    img2[5][0] = 0; img2[5][1] = 0; img2[5][2] = 1; img2[5][3] = 0; img2[5][4] = 1; img2[5][5] = 0; img2[5][6] = 0; img2[5][7] = 0;
    img2[6][0] = 0; img2[6][1] = 0; img2[6][2] = 0; img2[6][3] = 1; img2[6][4] = 1; img2[6][5] = 1; img2[6][6] = 0; img2[6][7] = 0;
    img2[7][0] = 0; img2[7][1] = 0; img2[7][2] = 0; img2[7][3] = 0; img2[7][4] = 0; img2[7][5] = 0; img2[7][6] = 0; img2[7][7] = 0;

    printf("\n======================\n");

    close_bin3(img2, SIZE_TAB, SIZE_TAB, img2_o, img2_buf);

    display_ui8matrix(img2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1");
    printf("\n");

    display_ui8matrix(img2_buf, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1 - Temporaire (Dilatation)");
    printf("\n");

    display_ui8matrix(img2_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 1 - Fermeture Binaire 3 (Dilatation + Erosion)");
    printf("\n");

    //============= TEST 3 - Fermeture binaire 5 ===============
    img3[0][0] = 0; img3[0][1] = 0; img3[0][2] = 0; img3[0][3] = 0; img3[0][4] = 0; img3[0][5] = 0; img3[0][6] = 0; img3[0][7] = 0;
    img3[1][0] = 0; img3[1][1] = 0; img3[1][2] = 0; img3[1][3] = 0; img3[1][4] = 0; img3[1][5] = 0; img3[1][6] = 0; img3[1][7] = 0;
    img3[2][0] = 0; img3[2][1] = 0; img3[2][2] = 0; img3[2][3] = 1; img3[2][4] = 1; img3[2][5] = 0; img3[2][6] = 0; img3[2][7] = 0;
    img3[3][0] = 0; img3[3][1] = 0; img3[3][2] = 1; img3[3][3] = 0; img3[3][4] = 0; img3[3][5] = 1; img3[3][6] = 0; img3[3][7] = 0;
    img3[4][0] = 0; img3[4][1] = 0; img3[4][2] = 1; img3[4][3] = 0; img3[4][4] = 0; img3[4][5] = 0; img3[4][6] = 0; img3[4][7] = 0;
    img3[5][0] = 0; img3[5][1] = 0; img3[5][2] = 0; img3[5][3] = 1; img3[5][4] = 1; img3[5][5] = 0; img3[5][6] = 0; img3[5][7] = 0;
    img3[6][0] = 0; img3[6][1] = 0; img3[6][2] = 0; img3[6][3] = 0; img3[6][4] = 0; img3[6][5] = 0; img3[6][6] = 0; img3[6][7] = 0;
    img3[7][0] = 0; img3[7][1] = 0; img3[7][2] = 0; img3[7][3] = 0; img3[7][4] = 0; img3[7][5] = 0; img3[7][6] = 0; img3[7][7] = 0;

    printf("\n======================\n");

    close_bin5(img3, SIZE_TAB, SIZE_TAB, img3_o, img3_buf);

    display_ui8matrix(img3, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 3");
    printf("\n");

    display_ui8matrix(img3_buf, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 3 - Temporaire (Dilatation)");
    printf("\n");

    display_ui8matrix(img3_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %d ","Tableau 3 - Fermeture Binaire 5 (Dilatation + Erosion)");
    printf("\n");

    //============ DESALLOCATION MEMOIRE =============
    free_ui8matrix(img1, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img1_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img1_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

}

/**
 *  Test fonctions de dilatation niveaux de gris
 */
void f_test_dilate()
{
    int i, j;
    uint8_t** img1;
    uint8_t** img2;
    uint8_t** img3;
    uint8_t** img4;

    uint8_t** img1_o;
    uint8_t** img2_o;
    uint8_t** img3_o;
    uint8_t** img4_o;

    /*------ Allocation image test ------*/
    img1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img1_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    /*----- Initialisation image test -----*/
    for(i=-BORD_TAB; i<=SIZE_TAB-1+BORD_TAB; i++)
    {
        for(j=-BORD_TAB; j<=SIZE_TAB-1+BORD_TAB; j++)
        {
            img1[i][j] = 0;
            img2[i][j] = 0;
            img3[i][j] = 0;
            img4[i][j] = 0;
            img1_o[i][j] = 0;
            img2_o[i][j] = 0;
            img3_o[i][j] = 0;
            img4_o[i][j] = 0;
        }
    }

    /*------ Test fonctions ------*/
    //============= TEST 1 - Dilataion 3 ===============
    img1[2][2] = 56; img1[2][3] = 25; img1[2][4] = 32;
    img1[3][2] = 155; img1[3][3] = 255; img1[3][4] = 45;
    img1[4][2] = 95; img1[4][3] = 10; img1[4][4] = 120;

    display_ui8matrix(img1, -BORD_TAB, SIZE_TAB-1+BORD_TAB, -BORD_TAB, SIZE_TAB-1+BORD_TAB," %d ","Tableau 1");
    printf("\n======================\n");

    dilate3(img1, SIZE_TAB, SIZE_TAB, img1_o);

    display_ui8matrix(img1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1");
    printf("\n");

    display_ui8matrix(img1_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1 - Dilatation 3");
    printf("\n");

    //============= TEST 2 - Dilataion binaire 5 ===============
    img2[2][2] = 56; img2[2][3] = 25; img2[2][4] = 32;
    img2[3][2] = 155; img2[3][3] = 134; img2[3][4] = 45;
    img2[4][2] = 95; img2[4][3] = 10; img2[4][4] = 120;
    img2[5][5] = 210;

    dilate5(img2, SIZE_TAB, SIZE_TAB, img2_o);

    display_ui8matrix(img2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 2");
    printf("\n");

    display_ui8matrix(img2_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 2 - Dilatation 5");
    printf("\n");


    //============ DESALLOCATION MEMOIRE =============
    free_ui8matrix(img1, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img1_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
}

/**
 *  Test fonctions d'erosion niveaux de gris
 */
void f_test_erode()
{
    int i, j;
    uint8_t** img1;
    uint8_t** img2;
    uint8_t** img3;
    uint8_t** img4;

    uint8_t** img1_o;
    uint8_t** img2_o;
    uint8_t** img3_o;
    uint8_t** img4_o;

    /*------ Allocation image test ------*/
    img1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img1_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    /*----- Initialisation image test -----*/
    for(i=-BORD_TAB; i<=SIZE_TAB-1+BORD_TAB; i++)
    {
        for(j=-BORD_TAB; j<=SIZE_TAB-1+BORD_TAB; j++)
        {
            img1[i][j] = 0;
            img2[i][j] = 0;
            img3[i][j] = 0;
            img4[i][j] = 0;
            img1_o[i][j] = 0;
            img2_o[i][j] = 0;
            img3_o[i][j] = 0;
            img4_o[i][j] = 0;
        }
    }

    /*------ Test fonctions ------*/
    //============= TEST 1 - Dilataion 3 ===============
    img1[1][1] = 2; img1[1][2] = 130; img1[1][3] = 12; img1[1][4] = 34; img1[1][5] = 75;
    img1[2][1] = 34; img1[2][2] = 56; img1[2][3] = 25; img1[2][4] = 32;  img1[2][5] = 72;
    img1[3][1] = 94; img1[3][2] = 155; img1[3][3] = 41; img1[3][4] = 45; img1[3][5] = 125;
    img1[4][1] = 223; img1[4][2] = 95; img1[4][3] = 10; img1[4][4] = 120; img1[4][5] = 215;
    img1[5][1] = 13; img1[5][2] = 180; img1[5][3] = 18; img1[5][4] = 38; img1[5][5] = 78;

    display_ui8matrix(img1, -BORD_TAB, SIZE_TAB-1+BORD_TAB, -BORD_TAB, SIZE_TAB-1+BORD_TAB," %3d ","Tableau 1");
    printf("\n======================\n");

    erode3(img1, SIZE_TAB, SIZE_TAB, img1_o);

    display_ui8matrix(img1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1");
    printf("\n");

    display_ui8matrix(img1_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1 - Dilatation 3");
    printf("\n");

    //============= TEST 2 - Dilataion binaire 5 ===============
    img2[1][1] = 2; img2[1][2] = 130; img2[1][3] = 12; img2[1][4] = 34; img2[1][5] = 75;
    img2[2][1] = 34; img2[2][2] = 56; img2[2][3] = 25; img2[2][4] = 32;  img2[2][5] = 72;
    img2[3][1] = 94; img2[3][2] = 155; img2[3][3] = 41; img2[3][4] = 45; img2[3][5] = 125;
    img2[4][1] = 223; img2[4][2] = 95; img2[4][3] = 10; img2[4][4] = 120; img2[4][5] = 215;
    img2[5][1] = 13; img2[5][2] = 180; img2[5][3] = 18; img2[5][4] = 38; img2[5][5] = 78;


    erode5(img2, SIZE_TAB, SIZE_TAB, img2_o);

    display_ui8matrix(img2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 2");
    printf("\n");

    display_ui8matrix(img2_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 2 - Dilatation 5");
    printf("\n");

    //============ DESALLOCATION MEMOIRE =============
    free_ui8matrix(img1, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img1_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
}

/**
 *  Test fonctions d'ouverture
 */
void f_test_open()
{
    int i, j;
    uint8_t** img1;
    uint8_t** img2;
    uint8_t** img3;
    uint8_t** img4;

    uint8_t** img1_buf;
    uint8_t** img2_buf;
    uint8_t** img3_buf;
    uint8_t** img4_buf;

    uint8_t** img1_o;
    uint8_t** img2_o;
    uint8_t** img3_o;
    uint8_t** img4_o;

    /*------ Allocation image test ------*/
    img1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img1_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img1_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    /*----- Initialisation image test -----*/
    for(i=-BORD_TAB; i<=SIZE_TAB-1+BORD_TAB; i++)
    {
        for(j=-BORD_TAB; j<=SIZE_TAB-1+BORD_TAB; j++)
        {
            img1[i][j] = 0;
            img2[i][j] = 0;
            img3[i][j] = 0;
            img4[i][j] = 0;
            img1_buf[i][j] = 0;
            img2_buf[i][j] = 0;
            img3_buf[i][j] = 0;
            img4_buf[i][j] = 0;
            img1_o[i][j] = 0;
            img2_o[i][j] = 0;
            img3_o[i][j] = 0;
            img4_o[i][j] = 0;
        }
    }

    /*------ Test fonctions ------*/
    //============= TEST 1 - Ouverture binaire 3 ===============
    img1[0][0] = 4;  img1[0][1] = 58;  img1[0][2] = 5;   img1[0][3] = 5;   img1[0][4] = 2;   img1[0][5] = 5;   img1[0][6] = 4;   img1[0][7] = 5;
    img1[1][0] = 5;  img1[1][1] = 5;   img1[1][2] = 246; img1[1][3] = 225; img1[1][4] = 245; img1[1][5] = 249; img1[1][6] = 5;   img1[1][7] = 5;
    img1[2][0] = 5;  img1[2][1] = 218; img1[2][2] = 215; img1[2][3] = 255; img1[2][4] = 234; img1[2][5] = 254; img1[2][6] = 255; img1[2][7] = 5;
    img1[3][0] = 5;  img1[3][1] = 230; img1[3][2] = 242; img1[3][3] = 234; img1[3][4] = 242; img1[3][5] = 5;   img1[3][6] = 242; img1[3][7] = 3;
    img1[4][0] = 5;  img1[4][1] = 228; img1[4][2] = 232; img1[4][3] = 245; img1[4][4] = 235; img1[4][5] = 5;   img1[4][6] = 242; img1[4][7] = 5;
    img1[5][0] = 5;  img1[5][1] = 240; img1[5][2] = 235; img1[5][3] = 255; img1[5][4] = 248; img1[5][5] = 238; img1[5][6] = 255; img1[5][7] = 6;
    img1[6][0] = 5;  img1[6][1] = 5;   img1[6][2] = 248; img1[6][3] = 245; img1[6][4] = 255; img1[6][5] = 243; img1[6][6] = 8;   img1[6][7] = 5;
    img1[7][0] = 5;  img1[7][1] = 3;   img1[7][2] = 5;   img1[7][3] = 5;   img1[7][4] = 5;   img1[7][5] = 5;   img1[7][6] = 5;   img1[7][7] = 5;

    display_ui8matrix(img1, -BORD_TAB, SIZE_TAB-1+BORD_TAB, -BORD_TAB, SIZE_TAB-1+BORD_TAB," %3d ","Tableau 1");
    printf("\n======================\n");

    open3(img1, SIZE_TAB, SIZE_TAB, img1_o, img1_buf);

    display_ui8matrix(img1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1");
    printf("\n");

    display_ui8matrix(img1_buf, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1 - Temporaire (Erosion)");
    printf("\n");

    display_ui8matrix(img1_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1 - Ouverture 3 (Erosion + Dilatation)");
    printf("\n");

    /*------ Test fonctions ------*/
    //============= TEST 2 - Ouverture binaire 3 ===============
    img2[0][0] = 4;   img2[0][1] = 5;   img2[0][2] = 5;   img2[0][3] = 5;   img2[0][4] = 5;   img2[0][5] = 5;   img2[0][6] = 5;   img2[0][7] = 5;
    img2[1][0] = 5;   img2[1][1] = 5;   img2[1][2] = 246; img2[1][3] = 225; img2[1][4] = 245; img2[1][5] = 249; img2[1][6] = 5;   img2[1][7] = 5;
    img2[2][0] = 5;   img2[2][1] = 218; img2[2][2] = 215; img2[2][3] = 255; img2[2][4] = 234; img2[2][5] = 254; img2[2][6] = 255; img2[2][7] = 5;
    img2[3][0] = 5;   img2[3][1] = 230; img2[3][2] = 242; img2[3][3] = 234; img2[3][4] = 242; img2[3][5] = 254; img2[3][6] = 242; img2[3][7] = 5;
    img2[4][0] = 5;   img2[4][1] = 228; img2[4][2] = 232; img2[4][3] = 245; img2[4][4] = 235; img2[4][5] = 248; img2[4][6] = 254; img2[4][7] = 225;
    img2[5][0] = 5;   img2[5][1] = 240; img2[5][2] = 235; img2[5][3] = 255; img2[5][4] = 248; img2[5][5] = 238; img2[5][6] = 255; img2[5][7] = 5;
    img2[6][0] = 5;   img2[6][1] = 5;   img2[6][2] = 248; img2[6][3] = 245; img2[6][4] = 255; img2[6][5] = 243; img2[6][6] = 5;   img2[6][7] = 5;
    img2[7][0] = 5;   img2[7][1] = 5;   img2[7][2] = 5;   img2[7][3] = 5;   img2[7][4] = 5;   img2[7][5] = 5;   img2[7][6] = 245; img2[7][7] = 5;

    printf("\n======================\n");

    open3(img2, SIZE_TAB, SIZE_TAB, img2_o, img2_buf);

    display_ui8matrix(img2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 2");
    printf("\n");

    display_ui8matrix(img2_buf, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 2 - Temporaire (Erosion)");
    printf("\n");

    display_ui8matrix(img2_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 2 - Ouverture 3 (Erosion + Dilatation)");
    printf("\n");

    //============= TEST 3 - Ouverture binaire 5 ===============
    img3[0][0] = 4;   img3[0][1] = 240; img3[0][2] = 238; img3[0][3] = 248; img3[0][4] = 244; img3[0][5] = 239; img3[0][6] = 5;   img3[0][7] = 5;
    img3[1][0] = 250; img3[1][1] = 253; img3[1][2] = 246; img3[1][3] = 225; img3[1][4] = 245; img3[1][5] = 249; img3[1][6] = 251; img3[1][7] = 5;
    img3[2][0] = 248; img3[2][1] = 218; img3[2][2] = 215; img3[2][3] = 255; img3[2][4] = 234; img3[2][5] = 14;  img3[2][6] = 255; img3[2][7] = 5;
    img3[3][0] = 243; img3[3][1] = 230; img3[3][2] = 242; img3[3][3] = 234; img3[3][4] = 242; img3[3][5] = 254; img3[3][6] = 242; img3[3][7] = 5;
    img3[4][0] = 242; img3[4][1] = 228; img3[4][2] = 232; img3[4][3] = 245; img3[4][4] = 235; img3[4][5] = 248; img3[4][6] = 17;  img3[4][7] = 5;
    img3[5][0] = 255; img3[5][1] = 240; img3[5][2] = 235; img3[5][3] = 255; img3[5][4] = 248; img3[5][5] = 238; img3[5][6] = 255; img3[5][7] = 5;
    img3[6][0] = 238; img3[6][1] = 254; img3[6][2] = 248; img3[6][3] = 245; img3[6][4] = 255; img3[6][5] = 243; img3[6][6] = 235; img3[6][7] = 5;
    img3[7][0] = 5;   img3[7][1] = 252; img3[7][2] = 235; img3[7][3] = 242; img3[7][4] = 233; img3[7][5] = 238; img3[7][6] = 5;   img3[7][7] = 5;

    printf("\n======================\n");

    open5(img3, SIZE_TAB, SIZE_TAB, img3_o, img3_buf);

    display_ui8matrix(img3, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 3");
    printf("\n");

    display_ui8matrix(img3_buf, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 3 - Temporaire (Erosion)");
    printf("\n");

    display_ui8matrix(img3_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 3 - Ouverture Binaire 5 (Erosion + Dilatation)");
    printf("\n");

    //============ DESALLOCATION MEMOIRE =============
    free_ui8matrix(img1, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img1_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img1_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

}

/**
 *  Test fonctions de fermeture
 */
void f_test_close()
{
    int i, j;
    uint8_t** img1;
    uint8_t** img2;
    uint8_t** img3;
    uint8_t** img4;

    uint8_t** img1_buf;
    uint8_t** img2_buf;
    uint8_t** img3_buf;
    uint8_t** img4_buf;

    uint8_t** img1_o;
    uint8_t** img2_o;
    uint8_t** img3_o;
    uint8_t** img4_o;

    /*------ Allocation image test ------*/
    img1 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4 = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img1_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4_buf = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    img1_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img2_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img3_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    img4_o = ui8matrix(0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    /*----- Initialisation image test -----*/
    for(i=-BORD_TAB; i<=SIZE_TAB-1+BORD_TAB; i++)
    {
        for(j=-BORD_TAB; j<=SIZE_TAB-1+BORD_TAB; j++)
        {
            img1[i][j] = 0;
            img2[i][j] = 0;
            img3[i][j] = 0;
            img4[i][j] = 0;
            img1_buf[i][j] = 0;
            img2_buf[i][j] = 0;
            img3_buf[i][j] = 0;
            img4_buf[i][j] = 0;
            img1_o[i][j] = 0;
            img2_o[i][j] = 0;
            img3_o[i][j] = 0;
            img4_o[i][j] = 0;
        }
    }

    /*------ Test fonctions ------*/
    //============= TEST 1 - Fermeture binaire 3 ===============
    img1[0][0] = 14; img1[0][1] = 15; img1[0][2] = 15; img1[0][3] = 15; img1[0][4] = 15; img1[0][5] = 15; img1[0][6] = 15; img1[0][7] = 15;
    img1[1][0] = 15; img1[1][1] = 15; img1[1][2] = 15; img1[1][3] = 22; img1[1][4] = 15; img1[1][5] = 15; img1[1][6] = 15; img1[1][7] = 15;
    img1[2][0] = 15; img1[2][1] = 13; img1[2][2] = 15; img1[2][3] = 255; img1[2][4] = 234; img1[2][5] = 254; img1[2][6] = 15; img1[2][7] = 15;
    img1[3][0] = 15; img1[3][1] = 15; img1[3][2] = 242; img1[3][3] = 15; img1[3][4] = 15; img1[3][5] = 15; img1[3][6] = 242; img1[3][7] = 15;
    img1[4][0] = 15; img1[4][1] = 15; img1[4][2] = 222; img1[4][3] = 17; img1[4][4] = 15; img1[4][5] = 15; img1[4][6] = 242; img1[4][7] = 15;
    img1[5][0] = 15; img1[5][1] = 15; img1[5][2] = 235; img1[5][3] = 15; img1[5][4] = 12; img1[5][5] = 15; img1[5][6] = 15; img1[5][7] = 15;
    img1[6][0] = 15; img1[6][1] = 15; img1[6][2] = 15; img1[6][3] = 245; img1[6][4] = 255; img1[6][5] = 243; img1[6][6] = 15; img1[6][7] = 15;
    img1[7][0] = 15; img1[7][1] = 15; img1[7][2] = 15; img1[7][3] = 15; img1[7][4] = 15; img1[7][5] = 15; img1[7][6] = 15; img1[7][7] = 15;

    display_ui8matrix(img1, -BORD_TAB, SIZE_TAB-1+BORD_TAB, -BORD_TAB, SIZE_TAB-1+BORD_TAB," %3d ","Tableau 1");
    printf("\n======================\n");

    close3(img1, SIZE_TAB, SIZE_TAB, img1_o, img1_buf);

    display_ui8matrix(img1, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1");
    printf("\n");

    display_ui8matrix(img1_buf, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1 - Temporaire (Dilatation)");
    printf("\n");

    display_ui8matrix(img1_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 1 - Fermeture 3 (Dilatation + Erosion)");
    printf("\n");

    /*------ Test fonctions ------*/
    //============= TEST 2 - Fermeture binaire 3 ===============
    img2[0][0] = 16; img2[0][1] = 16; img2[0][2] = 16; img2[0][3] = 16; img2[0][4] = 16; img2[0][5] = 16; img2[0][6] = 16; img2[0][7] = 16;
    img2[1][0] = 16; img2[1][1] = 16; img2[1][2] = 16; img2[1][3] = 16; img2[1][4] = 16; img2[1][5] = 16; img2[1][6] = 16; img2[1][7] = 16;
    img2[2][0] = 16; img2[2][1] = 16; img2[2][2] = 16; img2[2][3] = 234; img2[2][4] = 242; img2[2][5] = 254; img2[2][6] = 16; img2[2][7] = 16;
    img2[3][0] = 16; img2[3][1] = 16; img2[3][2] = 254; img2[3][3] = 244; img2[3][4] = 16; img2[3][5] = 16; img2[3][6] = 234; img2[3][7] = 16;
    img2[4][0] = 16; img2[4][1] = 16; img2[4][2] = 233; img2[4][3] = 16; img2[4][4] = 16; img2[4][5] = 16; img2[4][6] = 250; img2[4][7] = 16;
    img2[5][0] = 15; img2[5][1] = 16; img2[5][2] = 225; img2[5][3] = 16; img2[5][4] = 240; img2[5][5] = 16; img2[5][6] = 16; img2[5][7] = 16;
    img2[6][0] = 16; img2[6][1] = 16; img2[6][2] = 16; img2[6][3] = 255; img2[6][4] = 254; img2[6][5] = 236; img2[6][6] = 16; img2[6][7] = 16;
    img2[7][0] = 13; img2[7][1] = 16; img2[7][2] = 16; img2[7][3] = 16; img2[7][4] = 16; img2[7][5] = 16; img2[7][6] = 16; img2[7][7] = 16;

    printf("\n======================\n");

    close3(img2, SIZE_TAB, SIZE_TAB, img2_o, img2_buf);

    display_ui8matrix(img2, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 2");
    printf("\n");

    display_ui8matrix(img2_buf, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 2 - Temporaire (Dilatation)");
    printf("\n");

    display_ui8matrix(img2_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 2 - Fermeture 3 (Dilatation + Erosion)");
    printf("\n");

    //============= TEST 3 - Fermeture binaire 5 ===============
    img3[0][0] = 25; img3[0][1] = 23; img3[0][2] = 25; img3[0][3] = 25; img3[0][4] = 25; img3[0][5] = 21; img3[0][6] = 25; img3[0][7] = 25;
    img3[1][0] = 25; img3[1][1] = 25; img3[1][2] = 25; img3[1][3] = 25; img3[1][4] = 25; img3[1][5] = 24; img3[1][6] = 25; img3[1][7] = 25;
    img3[2][0] = 25; img3[2][1] = 23; img3[2][2] = 25; img3[2][3] = 242; img3[2][4] = 245; img3[2][5] = 25; img3[2][6] = 25; img3[2][7] = 25;
    img3[3][0] = 25; img3[3][1] = 25; img3[3][2] = 245; img3[3][3] = 25; img3[3][4] = 25; img3[3][5] = 245; img3[3][6] = 25; img3[3][7] = 25;
    img3[4][0] = 25; img3[4][1] = 25; img3[4][2] = 252; img3[4][3] = 25; img3[4][4] = 25; img3[4][5] = 32; img3[4][6] = 25; img3[4][7] = 25;
    img3[5][0] = 22; img3[5][1] = 25; img3[5][2] = 25; img3[5][3] = 241; img3[5][4] = 245; img3[5][5] = 25; img3[5][6] = 25; img3[5][7] = 25;
    img3[6][0] = 28; img3[6][1] = 25; img3[6][2] = 25; img3[6][3] = 25; img3[6][4] = 25; img3[6][5] = 24; img3[6][6] = 25; img3[6][7] = 25;
    img3[7][0] = 25; img3[7][1] = 25; img3[7][2] = 25; img3[7][3] = 25; img3[7][4] = 25; img3[7][5] = 25; img3[7][6] = 25; img3[7][7] = 25;

    printf("\n======================\n");

    close5(img3, SIZE_TAB, SIZE_TAB, img3_o, img3_buf);

    display_ui8matrix(img3, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 3");
    printf("\n");

    display_ui8matrix(img3_buf, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 3 - Temporaire (Dilatation)");
    printf("\n");

    display_ui8matrix(img3_o, 0, SIZE_TAB-1, 0, SIZE_TAB-1," %3d ","Tableau 3 - Fermeture Binaire 5 (Dilatation + Erosion)");
    printf("\n");

    //============ DESALLOCATION MEMOIRE =============
    free_ui8matrix(img1, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img1_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4_buf, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

    free_ui8matrix(img1_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img2_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img3_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);
    free_ui8matrix(img4_o, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB, 0-BORD_TAB, SIZE_TAB-1+BORD_TAB);

}

void f_test_morpho()
{
    // f_test_dilate_bin();
    // f_test_erode_bin();
    // f_test_open_bin();
    // f_test_close_bin();
    // f_test_dilate();
    // f_test_erode();
    f_test_open();
    // f_test_close();
}

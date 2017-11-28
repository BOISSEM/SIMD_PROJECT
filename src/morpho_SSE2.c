/*--------------------------------
    morpho_SSE2.c

    Fonctions de morphologie mathématique parallelises en SIMD

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Kevin Seng - 2017
 ----------------------------------*/

#include <stdio.h>
#include <stdint.h>

#include "nrdef.h"
#include "vnrdef.h"
#include "vnrutil.h"
#include "simd_macro.h"
#include "morpho_SSE2.h"

/**
 *  (SIMD) Dilataion binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate_bin3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest){
    int i, j, di, dj;
    vuint8 x1, x2, x3;
    vuint8 dilat;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            x1 = vec_left1(src[i][j], src[i][j+1]);

        }
    }
}

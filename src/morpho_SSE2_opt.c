/*--------------------------------
    morpho_SSE2.c

    Fonctions de morphologie mathématique parallelises en SIMD + optimisations

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Kevin Seng - 2017
 ----------------------------------*/

#include <stdio.h>
#include <stdint.h>

#include "debug_macro.h"

#include "nrdef.h"
#include "vnrdef.h"
#include "vnrutil.h"

#include "simd_macro.h"
#include "morpho_SSE2_opt.h"


/**
 *  (SIMD) Dilataion binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate_bin3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest)
{
    int i, j;
    vuint8 a, b, c;
    vuint8 b0, xr;
    vuint8 y_1, y0, y1;
    vuint8 y;
    vuint8 dilat;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        j=0;
        a  = _mm_load_si128(&src[i][j+0]);
        b  = _mm_load_si128(&src[i][j+0]);


        for(j = 0; j <= (size_l-1); j++)
        {
            
        }
    }
}

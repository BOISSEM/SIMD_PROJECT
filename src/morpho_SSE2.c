/*--------------------------------
    morpho_SSE2.c

    Fonctions de morphologie mathématique parallelises en SIMD

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
#include "morpho_SSE2.h"

/**
 *  (SIMD) Dilataion d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest)
{
    int i, j;
    vuint8 x_1, x0, x1;
    vuint8 xl, xr;
    vuint8 y_1, y0, y1;
    vuint8 y;
    vuint8 dilat;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            x_1 = _mm_load_si128(&src[i-1][j-1]);
            x0  = _mm_load_si128(&src[i-1][j+0]);
            x1  = _mm_load_si128(&src[i-1][j+1]);
            xl = vec_left1(x0, x1);
            xr = vec_right1(x_1, x0);

            y_1 = vec_max3(xl, x0, xr);

            x_1 = _mm_load_si128(&src[i][j-1]);
            x0  = _mm_load_si128(&src[i][j+0]);
            x1  = _mm_load_si128(&src[i][j+1]);
            xl = vec_left1(x0, x1);
            xr = vec_right1(x_1, x0);

            y0 = vec_max3(xl, x0, xr);

            x_1 = _mm_load_si128(&src[i+1][j-1]);
            x0  = _mm_load_si128(&src[i+1][j+0]);
            x1  = _mm_load_si128(&src[i+1][j+1]);
            xl = vec_left1(x0, x1);
            xr = vec_right1(x_1, x0);

            y1 = vec_max3(xl, x0, xr);

            DEBUG(display_vuint8(y_1, " %3d ", "y_1 = "));DEBUG(puts(""));
            DEBUG(display_vuint8(y0, " %3d ", " y0 = "));DEBUG(puts(""));
            DEBUG(display_vuint8(y1, " %3d ", " y1 = "));DEBUG(puts("\n"));

            y = vec_max3(y_1, y0, y1);
            DEBUG(display_vuint8(y, " %3d ", " y = "));DEBUG(puts("\n"));

            _mm_store_si128(&dest[i][j], y);
        }
    }
}

/**
 *  (SIMD) Erosion d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest)
{
    int i, j;
    vuint8 x_1, x0, x1;
    vuint8 xl, xr;
    vuint8 y_1, y0, y1;
    vuint8 y;
    vuint8 dilat;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            x_1 = _mm_load_si128(&src[i-1][j-1]);
            x0  = _mm_load_si128(&src[i-1][j+0]);
            x1  = _mm_load_si128(&src[i-1][j+1]);
            xl = vec_left1(x0, x1);
            xr = vec_right1(x_1, x0);

            y_1 = vec_min3(xl, x0, xr);

            x_1 = _mm_load_si128(&src[i][j-1]);
            x0  = _mm_load_si128(&src[i][j+0]);
            x1  = _mm_load_si128(&src[i][j+1]);
            xl = vec_left1(x0, x1);
            xr = vec_right1(x_1, x0);

            y0 = vec_min3(xl, x0, xr);

            x_1 = _mm_load_si128(&src[i+1][j-1]);
            x0  = _mm_load_si128(&src[i+1][j+0]);
            x1  = _mm_load_si128(&src[i+1][j+1]);
            xl = vec_left1(x0, x1);
            xr = vec_right1(x_1, x0);

            y1 = vec_min3(xl, x0, xr);

            DEBUG(display_vuint8(y_1, " %3d ", "y_1 = "));DEBUG(puts(""));
            DEBUG(display_vuint8(y0, " %3d ", " y0 = "));DEBUG(puts(""));
            DEBUG(display_vuint8(y1, " %3d ", " y1 = "));DEBUG(puts("\n"));

            y = vec_min3(y_1, y0, y1);
            DEBUG(display_vuint8(y, " %3d ", " y = "));DEBUG(puts("\n"));

            _mm_store_si128(&dest[i][j], y);
        }
    }
}

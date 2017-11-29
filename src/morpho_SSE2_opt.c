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
void dilate3_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest)
{
    int i, j;
    vuint8 x_1a, x_1b, x_1c;
    vuint8 x0a, x0b, x0c;
    vuint8 x1a, x1b, x1c;

    vuint8 x_1l, x_1, x_1r;
    vuint8 x0l, x0, x0r;
    vuint8 x1l, x1, x1r;

    vuint8 yl, ym, yr;
    vuint8 y;
    vuint8 dilat;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        x_1b = _mm_load_si128(&src[i-1][0]);
        x_1a = x_1b;
        x_1l = vec_dup_bord_l1(x_1b);

        x0b = _mm_load_si128(&src[i][0]);
        x0a = x0b;
        x0l = vec_dup_bord_l1(x0b);

        x1b = _mm_load_si128(&src[i+1][0]);
        x1a = x1b;
        x1l = vec_dup_bord_l1(x1b);

        yl = vec_max3(x_1l, x0l, x1l);
        ym = vec_max3(x_1b, x0b, x1b);
        DEBUG(printf("[%d]\n", i));
        DEBUG(display_vuint8(x_1l, "%3d", "x_1l = "));DEBUG(puts(""));
        DEBUG(display_vuint8(x0l, "%3d", " x0l = "));DEBUG(puts(""));
        DEBUG(display_vuint8(x1l, "%3d", " x1l = "));DEBUG(puts(""));
        DEBUG(puts("-----------------------------------------------------------"));
        DEBUG(display_vuint8(yl, "%3d", "  yl = "));DEBUG(puts("\n"));

        DEBUG(display_vuint8(x_1b, "%3d", "x_1b = "));DEBUG(puts(""));
        DEBUG(display_vuint8(x0b, "%3d", " x0b = "));DEBUG(puts(""));
        DEBUG(display_vuint8(x1b, "%3d", " x1b = "));DEBUG(puts(""));
        DEBUG(puts("-----------------------------------------------------------"));
        DEBUG(display_vuint8(ym, "%3d", "  ym = "));DEBUG(puts("\n"));

        for(j = 0; j <= (size_l-1)-1; j++)
        {

            x_1c = _mm_load_si128(&src[i-1][j+1]);
            x_1r = vec_left1(x_1b, x_1c);

            x0c = _mm_load_si128(&src[i][j+1]);
            x0r = vec_left1(x0b, x0c);

            x1c = _mm_load_si128(&src[i+1][j+1]);
            x1r = vec_left1(x1b, x1c);

            yr = vec_max3(x_1r, x0r, x1r);

            DEBUG(printf("[%d][%d]\n", i, j));
            DEBUG(display_vuint8(x_1r, "%3d", "x_1r = "));DEBUG(puts(""));
            DEBUG(display_vuint8(x0r, "%3d", " x0r = "));DEBUG(puts(""));
            DEBUG(display_vuint8(x1r, "%3d", " x1r = "));DEBUG(puts(""));
            DEBUG(puts("-----------------------------------------------------------"));
            DEBUG(display_vuint8(yr, "%3d", "  yr = "));DEBUG(puts("\n"));

            y = vec_max3(yl, ym, yr);
            _mm_store_si128(&dest[i][j], y);

            DEBUG(display_vuint8(yl, "%3d", " yl = "));DEBUG(puts(""));
            DEBUG(display_vuint8(ym, "%3d", " ym = "));DEBUG(puts(""));
            DEBUG(display_vuint8(yr, "%3d", " yr = "));DEBUG(puts(""));
            DEBUG(puts("-----------------------------------------------------------"));
            DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));

            ym = vec_max3(x_1c, x0c, x1c);

            x_1a = x_1b; x0a = x0b; x1a = x1b;
            x_1b = x_1c; x0b = x0c; x1b = x1c;

            x_1l = vec_right1(x_1a, x_1b);
            x0l = vec_right1(x0a, x0b);
            x1l = vec_right1(x1a, x1b);

            yl = vec_max3(x_1l, x0l, x1l);
        }

        x_1r = vec_dup_bord_r1(x_1c);
        x0r = vec_dup_bord_r1(x0c);
        x1r = vec_dup_bord_r1(x1c);
        yr = vec_max3(x_1r, x0r, x1r);

        y = vec_max3(yl, ym, yr);
        _mm_store_si128(&dest[i][j], y);

        DEBUG(display_vuint8(yl, "%3d", " yl = "));DEBUG(puts(""));
        DEBUG(display_vuint8(ym, "%3d", " ym = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr, "%3d", " yr = "));DEBUG(puts(""));
        DEBUG(puts("-----------------------------------------------------------"));
        DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));
    }
}

/*--------------------------------
    morpho_SSE2.c

    Fonctions de morphologie mathématique parallelises en SIMD

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Kevin Seng - 2017
 ----------------------------------*/

#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>

#include "debug_macro.h"

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
void dilate_bin3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest)
{
    int i, j;
    int di, dj;
    vuint8 x_1, x0, x1;
    vuint8 xl, xr;
    vuint8 y;
    vuint8 dilat;
    vuint8 bord_l;

    vuint8 buf1, buf2;
    // Parcours image

    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            dilat = _mm_set1_epi8((uint8_t)0);

            for(di = -1; di <= 1; di++)
            {
                x0  = _mm_load_si128(&src[i+di][j+0]);

                if(j == 0)
                {
                    xr = vec_dup_bord_l1(x0);
                }
                else
                {
                    x_1 = _mm_load_si128(&src[i+di][j-1]);
                    xr = vec_right1(x_1, x0);
                }

                if(j == (size_l-1))
                {
                    xl = vec_dup_bord_r1(x0);
                }
                else
                {
                    x1  = _mm_load_si128(&src[i+di][j+1]);
                    xl = vec_left1(x0, x1);
                }


                DEBUG(display_vuint8(xr, "%3d", " xr = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", " x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl, "%3d", " xl = "));DEBUG(puts("\n"));

                y = vec_or3(xl, x0, xr);
                dilat = _mm_or_si128(dilat, y);
            }
            DEBUG(display_vuint8(dilat, "%3d", " dilat = "));DEBUG(puts("\n"));
            _mm_store_si128(&dest[i][j], dilat);
        }
    }
}

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
    int di, dj;
    vuint8 x_1, x0, x1;
    vuint8 xl, xr;
    vuint8 y;
    vuint8 dilat;
    vuint8 bord_l;
    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            dilat = _mm_set1_epi8((uint8_t)0);

            for(di = -1; di <= 1; di++)
            {
                x0  = _mm_load_si128(&src[i+di][j+0]);

                if(j == 0)
                {
                    xr = vec_dup_bord_l1(x0);
                }
                else
                {
                    x_1 = _mm_load_si128(&src[i+di][j-1]);
                    xr = vec_right1(x_1, x0);
                }

                if(j == (size_l-1))
                {
                    xl = vec_dup_bord_r1(x0);
                }
                else
                {
                    x1  = _mm_load_si128(&src[i+di][j+1]);
                    xl = vec_left1(x0, x1);
                }
                DEBUG(display_vuint8(xr, "%3d", " xr = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", " x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl, "%3d", " xl = "));DEBUG(puts("\n"));

                y = vec_max3(xl, x0, xr);
                dilat = _mm_max_epu8(dilat, y);
            }
            DEBUG(display_vuint8(dilat, "%3d", " dilat = "));DEBUG(puts("\n"));
            _mm_store_si128(&dest[i][j], dilat);
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
    int di, dj;
    vuint8 x_1, x0, x1;
    vuint8 xl, xr;
    vuint8 y;
    vuint8 erod;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            erod = _mm_set1_epi8((uint8_t)0xFFFF);

            for(di = -1; di <= 1; di++)
            {
                x0  = _mm_load_si128(&src[i+di][j+0]);

                if(j == 0){
                    xr = vec_dup_bord_l1(x0);
                }
                else{
                    x_1 = _mm_load_si128(&src[i+di][j-1]);
                    xr = vec_right1(x_1, x0);
                }

                if(j == (size_l-1)){
                    xl = vec_dup_bord_r1(x0);
                }
                else{
                    x1  = _mm_load_si128(&src[i+di][j+1]);
                    xl = vec_left1(x0, x1);
                }
                DEBUG(display_vuint8(xr, "%3d", " xr = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", "  x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl, "%3d", " xl = "));DEBUG(puts(""));

                y = vec_min3(xl, x0, xr);
                erod = _mm_min_epu8(erod, y);
            }

            DEBUG(display_vuint8(erod, "%3d", " erod = "));DEBUG(puts("\n"));
            _mm_store_si128(&dest[i][j], erod);
        }
    }
}

/**
 *  (SIMD) Ouverture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer)
{
    int i, j;
    int di, dj;
    vuint8 x_1, x0, x1;
    vuint8 xl, xr;
    vuint8 y;
    vuint8 erod, dilat;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            erod = _mm_set1_epi8((uint8_t)0xFFFF);

            for(di = -1; di <= 1; di++)
            {
                x0  = _mm_load_si128(&src[i+di][j+0]);

                if(j == 0){
                    xr = vec_dup_bord_l1(x0);
                }
                else{
                    x_1 = _mm_load_si128(&src[i+di][j-1]);
                    xr = vec_right1(x_1, x0);
                }

                if(j == (size_l-1)){
                    xl = vec_dup_bord_r1(x0);
                }
                else{
                    x1  = _mm_load_si128(&src[i+di][j+1]);
                    xl = vec_left1(x0, x1);
                }
                DEBUG(display_vuint8(xr, "%3d", " xr = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", " x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl, "%3d", " xl = "));DEBUG(puts(""));

                y = vec_min3(xl, x0, xr);
                erod = _mm_min_epu8(erod, y);
            }
            DEBUG(puts(""));
            DEBUG(display_vuint8(erod, "%3d", " erod = "));DEBUG(puts("\n"));
            _mm_store_si128(&buffer[i][j], erod);
        }
    }
    DEBUG(puts("---------------------------------------------------------------"));

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            dilat = _mm_set1_epi8((uint8_t)0);

            for(di = -1; di <= 1; di++)
            {
                x0  = _mm_load_si128(&buffer[i+di][j+0]);

                if(j == 0){
                    xr = vec_dup_bord_l1(x0);
                }
                else{
                    x_1 = _mm_load_si128(&buffer[i+di][j-1]);
                    xr = vec_right1(x_1, x0);
                }

                if(j == (size_l-1)){
                    xl = vec_dup_bord_r1(x0);
                }
                else{
                    x1  = _mm_load_si128(&buffer[i+di][j+1]);
                    xl = vec_left1(x0, x1);
                }

                DEBUG(display_vuint8(xr, "%3d", " xr = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", " x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl, "%3d", " xl = "));DEBUG(puts("\n"));

                y = vec_max3(xl, x0, xr);
                dilat = _mm_max_epu8(dilat, y);
            }
            DEBUG(display_vuint8(dilat, "%3d", " dilat = "));DEBUG(puts("\n"));
            _mm_store_si128(&dest[i][j], dilat);
        }
        DEBUG(puts(""));
    }
    DEBUG(puts(""));
}


/**
 *  (SIMD) Fermeture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void close3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer)
{
    int i, j;
    int di, dj;
    vuint8 x_1, x0, x1;
    vuint8 xl, xr;
    vuint8 y;
    vuint8 erod, dilat;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            dilat = _mm_set1_epi8((uint8_t)0);

            for(di = -1; di <= 1; di++)
            {
                x0  = _mm_load_si128(&src[i+di][j+0]);

                if(j == 0){
                    xr = vec_dup_bord_l1(x0);
                }
                else{
                    x_1 = _mm_load_si128(&src[i+di][j-1]);
                    xr = vec_right1(x_1, x0);
                }

                if(j == (size_l-1)){
                    xl = vec_dup_bord_r1(x0);
                }
                else{
                    x1  = _mm_load_si128(&src[i+di][j+1]);
                    xl = vec_left1(x0, x1);
                }

                DEBUG(display_vuint8(xr, "%3d", " xr = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", "  x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl, "%3d", " xl = "));DEBUG(puts(""));

                y = vec_max3(xl, x0, xr);
                dilat = _mm_max_epu8(dilat, y);
            }
            DEBUG(display_vuint8(dilat, "%3d", " dilat = "));DEBUG(puts("\n"));
            _mm_store_si128(&buffer[i][j], dilat);
        }
    }

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            erod = _mm_set1_epi8((uint8_t)0xFFFF);

            for(di = -1; di <= 1; di++)
            {
                x0  = _mm_load_si128(&buffer[i+di][j+0]);

                if(j == 0){
                    xr = vec_dup_bord_l1(x0);
                }
                else{
                    x_1 = _mm_load_si128(&buffer[i+di][j-1]);
                    xr = vec_right1(x_1, x0);
                }

                if(j == (size_l-1)){
                    xl = vec_dup_bord_r1(x0);
                }
                else{
                    x1  = _mm_load_si128(&buffer[i+di][j+1]);
                    xl = vec_left1(x0, x1);
                }

                DEBUG(display_vuint8(xr, "%3d", " xr = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", "  x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl, "%3d", " xl = "));DEBUG(puts(""));

                y = vec_min3(xl, x0, xr);
                erod = _mm_min_epu8(erod, y);
            }
            DEBUG(display_vuint8(erod, "%3d", " erod = "));DEBUG(puts("\n"));
            _mm_store_si128(&dest[i][j], erod);
        }
    }
}

/**
 *  (SIMD) Dilataion d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate5_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest)
{
    int i, j;
    int di, dj;
    vuint8 x_1, x0, x1;
    vuint8 xr2, xr1, xl1, xl2;
    vuint8 y;
    vuint8 dilat;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            dilat = _mm_set1_epi8((uint8_t)0);

            for(di = -2; di <= 2; di++)
            {
                x0  = _mm_load_si128(&src[i+di][j+0]);

                if(j == 0){
                    xr2 = vec_dup_bord_l2(x0);
                    xr1 = vec_dup_bord_l1(x0);
                }
                else{
                    x_1 = _mm_load_si128(&src[i+di][j-1]);
                    xr2 = vec_right2(x_1, x0);
                    xr1 = vec_right1(x_1, x0);
                }

                if(j == (size_l-1)){
                    xl1 = vec_dup_bord_r1(x0);
                    xl2 = vec_dup_bord_r2(x0);
                }
                else{
                    x1  = _mm_load_si128(&src[i+di][j+1]);
                    xl1 = vec_left1(x0, x1);
                    xl2 = vec_left2(x0, x1);
                }

                DEBUG(display_vuint8(xr2, "%3d", " xr2 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xr1, "%3d", " xr1 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", "  x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl1, "%3d", " xl1 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl2, "%3d", " xl2 = "));DEBUG(puts("\n"));

                y = vec_max5(xr2, xr1, x0, xl1, xl2);
                dilat = _mm_max_epu8(dilat, y);
            }

            DEBUG(display_vuint8(dilat, "%3d", " dilat = "));DEBUG(puts("\n"));
            _mm_store_si128(&dest[i][j], dilat);
        }
    }
}

/**
 *  (SIMD) Erosion d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode5_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest)
{
    int i, j;
    int di, dj;
    vuint8 x_1, x0, x1;
    vuint8 xr2, xr1, xl1, xl2;
    vuint8 y;
    vuint8 erod;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            erod = _mm_set1_epi8((uint8_t)0xFFFF);

            for(di = -1; di <= 1; di++)
            {
                x0  = _mm_load_si128(&src[i+di][j+0]);

                if(j == 0){
                    xr2 = vec_dup_bord_l2(x0);
                    xr1 = vec_dup_bord_l1(x0);
                }
                else{
                    x_1 = _mm_load_si128(&src[i+di][j-1]);
                    xr2 = vec_right2(x_1, x0);
                    xr1 = vec_right1(x_1, x0);
                }

                if(j == (size_l-1)){
                    xl1 = vec_dup_bord_r1(x0);
                    xl2 = vec_dup_bord_r2(x0);
                }
                else{
                    x1  = _mm_load_si128(&src[i+di][j+1]);
                    xl1 = vec_left1(x0, x1);
                    xl2 = vec_left2(x0, x1);
                }

                DEBUG(display_vuint8(xr2, "%3d", " xr2 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xr1, "%3d", " xr1 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", "  x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl1, "%3d", " xl1 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl2, "%3d", " xl2 = "));DEBUG(puts("\n"));

                y = vec_min5(xr2, xr1, x0, xl1, xl2);
                erod = _mm_min_epu8(erod, y);
            }
            DEBUG(display_vuint8(erod, "%3d", " erod = "));DEBUG(puts("\n"));
            _mm_store_si128(&dest[i][j], erod);
        }
    }
}

/**
 *  (SIMD) Ouverture en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open5_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer)
{
    int i, j;
    int di, dj;
    vuint8 x_1, x0, x1;
    vuint8 xr2, xr1, xl1, xl2;
    vuint8 y;
    vuint8 erod, dilat;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            erod = _mm_set1_epi8((uint8_t)0xFFFF);

            for(di = -1; di <= 1; di++)
            {
                x0  = _mm_load_si128(&src[i+di][j+0]);

                if(j == 0){
                    xr2 = vec_dup_bord_l2(x0);
                    xr1 = vec_dup_bord_l1(x0);
                }
                else{
                    x_1 = _mm_load_si128(&src[i+di][j-1]);
                    xr2 = vec_right2(x_1, x0);
                    xr1 = vec_right1(x_1, x0);
                }

                if(j == (size_l-1)){
                    xl1 = vec_dup_bord_r1(x0);
                    xl2 = vec_dup_bord_r2(x0);
                }
                else{
                    x1  = _mm_load_si128(&src[i+di][j+1]);
                    xl1 = vec_left1(x0, x1);
                    xl2 = vec_left2(x0, x1);
                }

                DEBUG(display_vuint8(xr2, "%3d", " xr2 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xr1, "%3d", " xr1 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", "  x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl1, "%3d", " xl1 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl2, "%3d", " xl2 = "));DEBUG(puts("\n"));

                y = vec_min5(xr2, xr1, x0, xl1, xl2);
                erod = _mm_min_epu8(erod, y);
            }
            DEBUG(display_vuint8(erod, "%3d", " erod = "));DEBUG(puts(""));
            _mm_store_si128(&buffer[i][j], erod);
        }
        DEBUG(puts(""));
    }
    DEBUG(puts(""));

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            dilat = _mm_set1_epi8((uint8_t)0);

            for(di = -1; di <= 1; di++)
            {
                x0  = _mm_load_si128(&src[i+di][j+0]);

                if(j == 0){
                    xr2 = vec_dup_bord_l2(x0);
                    xr1 = vec_dup_bord_l1(x0);
                }
                else{
                    x_1 = _mm_load_si128(&src[i+di][j-1]);
                    xr2 = vec_right2(x_1, x0);
                    xr1 = vec_right1(x_1, x0);
                }

                if(j == (size_l-1)){
                    xl1 = vec_dup_bord_r1(x0);
                    xl2 = vec_dup_bord_r2(x0);
                }
                else{
                    x1  = _mm_load_si128(&src[i+di][j+1]);
                    xl1 = vec_left1(x0, x1);
                    xl2 = vec_left2(x0, x1);
                }

                DEBUG(display_vuint8(xr2, "%3d", " xr2 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xr1, "%3d", " xr1 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", "  x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl1, "%3d", " xl1 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl2, "%3d", " xl2 = "));DEBUG(puts("\n"));

                y = vec_max5(xr2, xr1, x0, xl1, xl2);
                dilat = _mm_max_epu8(dilat, y);
            }
            DEBUG(display_vuint8(dilat, "%3d", " dilat = "));DEBUG(puts(""));
            _mm_store_si128(&dest[i][j], dilat);
        }
        DEBUG(puts(""));
    }
    DEBUG(puts(""));
}


/**
 *  (SIMD) Fermeture en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void close5_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer)
{
    int i, j;
    int di, dj;
    vuint8 x_1, x0, x1;
    vuint8 xr2, xr1, xl1, xl2;
    vuint8 y;
    vuint8 erod, dilat;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            dilat = _mm_set1_epi8((uint8_t)0);

            for(di = -1; di <= 1; di++)
            {
                x0  = _mm_load_si128(&src[i+di][j+0]);

                if(j == 0){
                    xr2 = vec_dup_bord_l2(x0);
                    xr1 = vec_dup_bord_l1(x0);
                }
                else{
                    x_1 = _mm_load_si128(&src[i+di][j-1]);
                    xr2 = vec_right2(x_1, x0);
                    xr1 = vec_right1(x_1, x0);
                }

                if(j == (size_l-1)){
                    xl1 = vec_dup_bord_r1(x0);
                    xl2 = vec_dup_bord_r2(x0);
                }
                else{
                    x1  = _mm_load_si128(&src[i+di][j+1]);
                    xl1 = vec_left1(x0, x1);
                    xl2 = vec_left2(x0, x1);
                }

                DEBUG(display_vuint8(xr2, "%3d", " xr2 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xr1, "%3d", " xr1 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", "  x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl1, "%3d", " xl1 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl2, "%3d", " xl2 = "));DEBUG(puts("\n"));

                y = vec_max5(xr2, xr1, x0, xl1, xl2);
                dilat = _mm_max_epu8(dilat, y);
            }
            DEBUG(display_vuint8(dilat, "%3d", " dilat = "));DEBUG(puts("\n"));
            _mm_store_si128(&buffer[i][j], dilat);
        }
    }

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        for(j = 0; j <= (size_l-1); j++)
        {
            erod = _mm_set1_epi8((uint8_t)0xFFFF);

            for(di = -1; di <= 1; di++)
            {
                x0  = _mm_load_si128(&src[i+di][j+0]);

                if(j == 0){
                    xr2 = vec_dup_bord_l2(x0);
                    xr1 = vec_dup_bord_l1(x0);
                }
                else{
                    x_1 = _mm_load_si128(&src[i+di][j-1]);
                    xr2 = vec_right2(x_1, x0);
                    xr1 = vec_right1(x_1, x0);
                }

                if(j == (size_l-1)){
                    xl1 = vec_dup_bord_r1(x0);
                    xl2 = vec_dup_bord_r2(x0);
                }
                else{
                    x1  = _mm_load_si128(&src[i+di][j+1]);
                    xl1 = vec_left1(x0, x1);
                    xl2 = vec_left2(x0, x1);
                }

                DEBUG(display_vuint8(xr2, "%3d", " xr2 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xr1, "%3d", " xr1 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(x0, "%3d", "  x0 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl1, "%3d", " xl1 = "));DEBUG(puts(""));
                DEBUG(display_vuint8(xl2, "%3d", " xl2 = "));DEBUG(puts("\n"));

                y = vec_min5(xr2, xr1, x0, xl1, xl2);
                erod = _mm_min_epu8(erod, y);
            }
            DEBUG(display_vuint8(erod, "%3d", " erod = "));DEBUG(puts("\n"));
            _mm_store_si128(&dest[i][j], erod);
        }
    }
}

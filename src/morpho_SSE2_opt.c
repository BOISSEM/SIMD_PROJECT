/*--------------------------------
    morpho_SSE2_opt.c

    Fonctions de morphologie mathématique parallelises en SIMD + optimisations

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
#include "morpho_SSE2_opt.h"


/**
 *  (SIMD) Dilataion binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
 void dilate_bin3_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest)
 {
     int i, j;
     vuint8 x_1a, x_1b, x_1c;
     vuint8 x0a, x0b, x0c;
     vuint8 x1a, x1b, x1c;

     vuint8 xa, xb, xc;

     vuint8 yl, yr;
     vuint8 y;

     // Parcours image
     for(i = 0; i <= (size_h-1); i++)
     {
         x_1b = _mm_load_si128(&src[i-1][0]);
         x0b = _mm_load_si128(&src[i][0]);
         x1b = _mm_load_si128(&src[i+1][0]);

         // Operation sur colonne (entre les lignes de vecteurs)
         // Factorisation d'operateurs sur 1D
         xb = vec_or3(x_1b, x0b, x1b);
         xa = vec_bord_g1(xb);

         for(j = 0; j <= (size_l-1)-1; j++)
         {
             // Operations sur le vecteur de droite
             x_1c = _mm_load_si128(&src[i-1][j+1]);
             x0c = _mm_load_si128(&src[i][j+1]);
             x1c = _mm_load_si128(&src[i+1][j+1]);
             xc = vec_or3(x_1c, x0c, x1c);

             yl = vec_right1(xa, xb);
             yr = vec_left1(xb, xc);

             // Operation finale
             y = vec_or3(yl, xb, yr);   // operations entre colonnes
             _mm_store_si128(&dest[i][j], y);

             DEBUG(display_vuint8(yl, "%3d", " yl = "));DEBUG(puts(""));
             DEBUG(display_vuint8(xb, "%3d", " xb = "));DEBUG(puts(""));
             DEBUG(display_vuint8(yr, "%3d", " yr = "));DEBUG(puts(""));
             DEBUG(puts("-----------------------------------------------------------"));
             DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));

             xa = xb;
             xb = xc;
         }

         /* Prologue */

         // Gestion bords droits
         xc = vec_bord_d1(xb);
         yl = vec_right1(xa, xb);
         yr = vec_left1(xb, xc);

         y = vec_or3(yl, xb, yr);
         _mm_store_si128(&dest[i][j], y);

         DEBUG(display_vuint8(yl, "%3d", " yl = "));DEBUG(puts(""));
         DEBUG(display_vuint8(xb, "%3d", " xb = "));DEBUG(puts(""));
         DEBUG(display_vuint8(yr, "%3d", " yr = "));DEBUG(puts(""));
         DEBUG(puts("-----------------------------------------------------------"));
         DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));
     }
 }

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

    vuint8 xa, xb, xc;

    vuint8 yl, yr;
    vuint8 y;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        x_1b = _mm_load_si128(&src[i-1][0]);
        x0b = _mm_load_si128(&src[i][0]);
        x1b = _mm_load_si128(&src[i+1][0]);

        // Operation sur colonne (entre les lignes de vecteurs)
        // Factorisation d'operateurs sur 1D
        xb = vec_max3(x_1b, x0b, x1b);
        xa = vec_bord_g1(xb);

        for(j = 0; j <= (size_l-1)-1; j++)
        {
            // Operations sur le vecteur de droite
            x_1c = _mm_load_si128(&src[i-1][j+1]);
            x0c = _mm_load_si128(&src[i][j+1]);
            x1c = _mm_load_si128(&src[i+1][j+1]);
            xc = vec_max3(x_1c, x0c, x1c);

            yl = vec_right1(xa, xb);
            yr = vec_left1(xb, xc);

            // Operation finale
            y = vec_max3(yl, xb, yr);   // operations entre colonnes
            _mm_store_si128(&dest[i][j], y);

            DEBUG(display_vuint8(yl, "%3d", " yl = "));DEBUG(puts(""));
            DEBUG(display_vuint8(xb, "%3d", " xb = "));DEBUG(puts(""));
            DEBUG(display_vuint8(yr, "%3d", " yr = "));DEBUG(puts(""));
            DEBUG(puts("-----------------------------------------------------------"));
            DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));

            xa = xb;
            xb = xc;
        }

        /* Prologue */

        // Gestion bords droits
        xc = vec_bord_d1(xb);
        yl = vec_right1(xa, xb);
        yr = vec_left1(xb, xc);

        y = vec_max3(yl, xb, yr);
        _mm_store_si128(&dest[i][j], y);

        DEBUG(display_vuint8(yl, "%3d", " yl = "));DEBUG(puts(""));
        DEBUG(display_vuint8(xb, "%3d", " xb = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr, "%3d", " yr = "));DEBUG(puts(""));
        DEBUG(puts("-----------------------------------------------------------"));
        DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));
    }
}

/**
 *  (SIMD) Dilataion binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate5_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest)
{
    int i, j;
    vuint8 x_2a, x_2b, x_2c;
    vuint8 x_1a, x_1b, x_1c;
    vuint8 x0a, x0b, x0c;
    vuint8 x1a, x1b, x1c;
    vuint8 x2a, x2b, x2c;

    vuint8 xa, xb, xc;

    vuint8 yl2, yl1, yr1, yr2;
    vuint8 y;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        x_2b = _mm_load_si128(&src[i-2][0]);
        x_1b = _mm_load_si128(&src[i-1][0]);
        x0b = _mm_load_si128(&src[i][0]);
        x1b = _mm_load_si128(&src[i+1][0]);
        x2b = _mm_load_si128(&src[i+2][0]);

        // Operation sur colonne (entre les lignes de vecteurs)
        // Factorisation d'operateurs sur 1D
        xb = vec_max5(x_2b, x_1b, x0b, x1b, x2b);
        xa = vec_bord_g2(xb);

        for(j = 0; j <= (size_l-1)-1; j++)
        {
            // Operations sur le vecteur de droite
            x_2c = _mm_load_si128(&src[i-2][j+1]);
            x_1c = _mm_load_si128(&src[i-1][j+1]);
            x0c = _mm_load_si128(&src[i][j+1]);
            x1c = _mm_load_si128(&src[i+1][j+1]);
            x2c = _mm_load_si128(&src[i+2][j+1]);
            xc = vec_max5(x_2c, x_1c, x0c, x1c, x2c);

            yl2 = vec_right2(xa, xb);
            yl1 = vec_right1(xa, xb);
            yr1 = vec_left1(xb, xc);
            yr2 = vec_left2(xb, xc);

            // Operation finale
            y = vec_max5(yl2, yl1, xb, yr1, yr2);   // operations entre colonnes
            _mm_store_si128(&dest[i][j], y);

            DEBUG(display_vuint8(yl2, "%3d", " yl2 = "));DEBUG(puts(""));
            DEBUG(display_vuint8(yl1, "%3d", " yl1 = "));DEBUG(puts(""));
            DEBUG(display_vuint8(xb, "%3d", "  xb = "));DEBUG(puts(""));
            DEBUG(display_vuint8(yr1, "%3d", " yr1 = "));DEBUG(puts(""));
            DEBUG(display_vuint8(yr2, "%3d", " yr2 = "));DEBUG(puts(""));
            DEBUG(puts("-----------------------------------------------------------"));
            DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));

            xa = xb;
            xb = xc;
        }

        /* Prologue */

        // Gestion bords droits
        yl2 = vec_right2(xa, xb);
        yl1 = vec_right1(xa, xb);
        yr1 = vec_left1(xb, xc);
        yr2 = vec_left2(xb, xc);

        y = vec_max5(yl2, yl1, xb, yr1, yr2);   // operations entre colonnes
        _mm_store_si128(&dest[i][j], y);

        DEBUG(display_vuint8(yl2, "%3d", " yl2 = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yl1, "%3d", " yl1 = "));DEBUG(puts(""));
        DEBUG(display_vuint8(xb, "%3d", "  xb = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr1, "%3d", " yr1 = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr2, "%3d", " yr2 = "));DEBUG(puts(""));
        DEBUG(puts("-----------------------------------------------------------"));
        DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));
    }
}

/**
 *  (SIMD) Erosion en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode3_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest)
{
    int i, j;
    vuint8 x_1a, x_1b, x_1c;
    vuint8 x0a, x0b, x0c;
    vuint8 x1a, x1b, x1c;

    vuint8 xa, xb, xc;

    vuint8 yl, yr;
    vuint8 y;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        x_1b = _mm_load_si128(&src[i-1][0]);
        x0b = _mm_load_si128(&src[i][0]);
        x1b = _mm_load_si128(&src[i+1][0]);

        // Operation sur colonne (entre les lignes de vecteurs)
        // Factorisation d'operateurs sur 1D
        xb = vec_min3(x_1b, x0b, x1b);
        xa = vec_bord_g1(xb);

        for(j = 0; j <= (size_l-1)-1; j++)
        {
            // Operations sur le vecteur de droite
            x_1c = _mm_load_si128(&src[i-1][j+1]);
            x0c = _mm_load_si128(&src[i][j+1]);
            x1c = _mm_load_si128(&src[i+1][j+1]);
            xc = vec_min3(x_1c, x0c, x1c);

            yl = vec_right1(xa, xb);
            yr = vec_left1(xb, xc);

            // Operation finale
            y = vec_min3(yl, xb, yr);   // operations entre colonnes
            _mm_store_si128(&dest[i][j], y);

            DEBUG(display_vuint8(yl, "%3d", " yl = "));DEBUG(puts(""));
            DEBUG(display_vuint8(xb, "%3d", " xb = "));DEBUG(puts(""));
            DEBUG(display_vuint8(yr, "%3d", " yr = "));DEBUG(puts(""));
            DEBUG(puts("-----------------------------------------------------------"));
            DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));

            xa = xb;
            xb = xc;
        }

        /* Prologue */

        // Gestion bords droits
        xc = vec_bord_d1(xb);
        yl = vec_right1(xa, xb);
        yr = vec_left1(xb, xc);

        y = vec_min3(yl, xb, yr);
        _mm_store_si128(&dest[i][j], y);

        DEBUG(display_vuint8(yl, "%3d", " yl = "));DEBUG(puts(""));
        DEBUG(display_vuint8(xb, "%3d", " xb = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr, "%3d", " yr = "));DEBUG(puts(""));
        DEBUG(puts("-----------------------------------------------------------"));
        DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));
    }
}

/**
 *  (SIMD) Erosion en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode5_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest)
{
    int i, j;
    vuint8 x_2a, x_2b, x_2c;
    vuint8 x_1a, x_1b, x_1c;
    vuint8 x0a, x0b, x0c;
    vuint8 x1a, x1b, x1c;
    vuint8 x2a, x2b, x2c;

    vuint8 xa, xb, xc;

    vuint8 yl2, yl1, yr1, yr2;
    vuint8 y;

    // Parcours image
    for(i = 0; i <= (size_h-1); i++)
    {
        x_2b = _mm_load_si128(&src[i-2][0]);
        x_1b = _mm_load_si128(&src[i-1][0]);
        x0b = _mm_load_si128(&src[i][0]);
        x1b = _mm_load_si128(&src[i+1][0]);
        x2b = _mm_load_si128(&src[i+2][0]);

        // Operation sur colonne (entre les lignes de vecteurs)
        // Factorisation d'operateurs sur 1D
        xb = vec_min5(x_2b, x_1b, x0b, x1b, x2b);
        xa = vec_bord_g2(xb);

        for(j = 0; j <= (size_l-1)-1; j++)
        {
            // Operations sur le vecteur de droite
            x_2c = _mm_load_si128(&src[i-2][j+1]);
            x_1c = _mm_load_si128(&src[i-1][j+1]);
            x0c = _mm_load_si128(&src[i][j+1]);
            x1c = _mm_load_si128(&src[i+1][j+1]);
            x2c = _mm_load_si128(&src[i+2][j+1]);
            xc = vec_min5(x_2c, x_1c, x0c, x1c, x2c);

            yl2 = vec_right2(xa, xb);
            yl1 = vec_right1(xa, xb);
            yr1 = vec_left1(xb, xc);
            yr2 = vec_left2(xb, xc);

            // Operation finale
            y = vec_min5(yl2, yl1, xb, yr1, yr2);   // operations entre colonnes
            _mm_store_si128(&dest[i][j], y);

            DEBUG(display_vuint8(yl2, "%3d", " yl2 = "));DEBUG(puts(""));
            DEBUG(display_vuint8(yl1, "%3d", " yl1 = "));DEBUG(puts(""));
            DEBUG(display_vuint8(xb, "%3d", "  xb = "));DEBUG(puts(""));
            DEBUG(display_vuint8(yr1, "%3d", " yr1 = "));DEBUG(puts(""));
            DEBUG(display_vuint8(yr2, "%3d", " yr2 = "));DEBUG(puts(""));
            DEBUG(puts("-----------------------------------------------------------"));
            DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));

            xa = xb;
            xb = xc;
        }

        /* Prologue */

        // Gestion bords droits
        yl2 = vec_right2(xa, xb);
        yl1 = vec_right1(xa, xb);
        yr1 = vec_left1(xb, xc);
        yr2 = vec_left2(xb, xc);

        y = vec_min5(yl2, yl1, xb, yr1, yr2);   // operations entre colonnes
        _mm_store_si128(&dest[i][j], y);

        DEBUG(display_vuint8(yl2, "%3d", " yl2 = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yl1, "%3d", " yl1 = "));DEBUG(puts(""));
        DEBUG(display_vuint8(xb, "%3d", "  xb = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr1, "%3d", " yr1 = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr2, "%3d", " yr2 = "));DEBUG(puts(""));
        DEBUG(puts("-----------------------------------------------------------"));
        DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));
    }
}

/**
 *  (SIMD) Dilatation en niveau de gris d'une ligne d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 *  @param  i       Numero de ligne
 */
inline void dilate3_vector_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest, int i)
{
    int j;
    vuint8 x_1a, x_1b, x_1c;
    vuint8 x0a, x0b, x0c;
    vuint8 x1a, x1b, x1c;

    vuint8 xa, xb, xc;

    vuint8 yl, yr;
    vuint8 y;

    // Parcours image
    x_1b = _mm_load_si128(&src[i-1][0]);
    x0b = _mm_load_si128(&src[i][0]);
    x1b = _mm_load_si128(&src[i+1][0]);

    // Operation sur colonne (entre les lignes de vecteurs)
    // Factorisation d'operateurs sur 1D
    xb = vec_max3(x_1b, x0b, x1b);
    xa = vec_bord_g1(xb);

    for(j = 0; j <= (size_l-1)-1; j++)
    {
        // Operations sur le vecteur de droite
        x_1c = _mm_load_si128(&src[i-1][j+1]);
        x0c = _mm_load_si128(&src[i][j+1]);
        x1c = _mm_load_si128(&src[i+1][j+1]);
        xc = vec_max3(x_1c, x0c, x1c);

        yl = vec_right1(xa, xb);
        yr = vec_left1(xb, xc);

        // Operation finale
        y = vec_max3(yl, xb, yr);   // operations entre colonnes
        _mm_store_si128(&dest[i][j], y);

        DEBUG(display_vuint8(yl, "%3d", " yl = "));DEBUG(puts(""));
        DEBUG(display_vuint8(xb, "%3d", " xb = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr, "%3d", " yr = "));DEBUG(puts(""));
        DEBUG(puts("-----------------------------------------------------------"));
        DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));

        xa = xb;
        xb = xc;
    }

    /* Prologue */

    // Gestion bords droits
    xc = vec_bord_d1(xb);
    yl = vec_right1(xa, xb);
    yr = vec_left1(xb, xc);

    y = vec_max3(yl, xb, yr);
    _mm_store_si128(&dest[i][j], y);

    DEBUG(display_vuint8(yl, "%3d", " yl = "));DEBUG(puts(""));
    DEBUG(display_vuint8(xb, "%3d", " xb = "));DEBUG(puts(""));
    DEBUG(display_vuint8(yr, "%3d", " yr = "));DEBUG(puts(""));
    DEBUG(puts("-----------------------------------------------------------"));
    DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));
}

/**
 *  (SIMD) Dilatation en niveau de gris d'une ligne d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 *  @param  i       Numero de ligne
 */
inline void dilate5_vector_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest, int i)
{
    int j;
    vuint8 x_2a, x_2b, x_2c;
    vuint8 x_1a, x_1b, x_1c;
    vuint8 x0a, x0b, x0c;
    vuint8 x1a, x1b, x1c;
    vuint8 x2a, x2b, x2c;

    vuint8 xa, xb, xc;

    vuint8 yl2, yl1, yr1, yr2;
    vuint8 y;

    // Parcours image
    x_2b = _mm_load_si128(&src[i-2][0]);
    x_1b = _mm_load_si128(&src[i-1][0]);
    x0b = _mm_load_si128(&src[i][0]);
    x1b = _mm_load_si128(&src[i+1][0]);
    x2b = _mm_load_si128(&src[i+2][0]);

    // Operation sur colonne (entre les lignes de vecteurs)
    // Factorisation d'operateurs sur 1D
    xb = vec_max5(x_2b, x_1b, x0b, x1b, x2b);
    xa = vec_bord_g2(xb);

    for(j = 0; j <= (size_l-1)-1; j++)
    {
        // Operations sur le vecteur de droite
        x_2c = _mm_load_si128(&src[i-2][j+1]);
        x_1c = _mm_load_si128(&src[i-1][j+1]);
        x0c = _mm_load_si128(&src[i][j+1]);
        x1c = _mm_load_si128(&src[i+1][j+1]);
        x2c = _mm_load_si128(&src[i+2][j+1]);
        xc = vec_max5(x_2c, x_1c, x0c, x1c, x2c);

        yl2 = vec_right2(xa, xb);
        yl1 = vec_right1(xa, xb);
        yr1 = vec_left1(xb, xc);
        yr2 = vec_left2(xb, xc);

        // Operation finale
        y = vec_max5(yl2, yl1, xb, yr1, yr2);   // operations entre colonnes
        _mm_store_si128(&dest[i][j], y);

        DEBUG(display_vuint8(yl2, "%3d", " yl2 = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yl1, "%3d", " yl1 = "));DEBUG(puts(""));
        DEBUG(display_vuint8(xb, "%3d", "  xb = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr1, "%3d", " yr1 = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr2, "%3d", " yr2 = "));DEBUG(puts(""));
        DEBUG(puts("-----------------------------------------------------------"));
        DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));

        xa = xb;
        xb = xc;
    }

    /* Prologue */

    // Gestion bords droits
    yl2 = vec_right2(xa, xb);
    yl1 = vec_right1(xa, xb);
    yr1 = vec_left1(xb, xc);
    yr2 = vec_left2(xb, xc);

    y = vec_max5(yl2, yl1, xb, yr1, yr2);   // operations entre colonnes
    _mm_store_si128(&dest[i][j], y);

    DEBUG(display_vuint8(yl2, "%3d", " yl2 = "));DEBUG(puts(""));
    DEBUG(display_vuint8(yl1, "%3d", " yl1 = "));DEBUG(puts(""));
    DEBUG(display_vuint8(xb, "%3d", "  xb = "));DEBUG(puts(""));
    DEBUG(display_vuint8(yr1, "%3d", " yr1 = "));DEBUG(puts(""));
    DEBUG(display_vuint8(yr2, "%3d", " yr2 = "));DEBUG(puts(""));
    DEBUG(puts("-----------------------------------------------------------"));
    DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));
}

/**
 *  (SIMD) Erosion en niveau de gris d'une ligne d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 *  @param  i       Numero de ligne
 */
inline void erode3_vector_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest, int i)
{
    int j;
    vuint8 x_1a, x_1b, x_1c;
    vuint8 x0a, x0b, x0c;
    vuint8 x1a, x1b, x1c;

    vuint8 xa, xb, xc;

    vuint8 yl, yr;
    vuint8 y;

    // Parcours image
    x_1b = _mm_load_si128(&src[i-1][0]);
    x0b = _mm_load_si128(&src[i][0]);
    x1b = _mm_load_si128(&src[i+1][0]);

    // Operation sur colonne (entre les lignes de vecteurs)
    // Factorisation d'operateurs sur 1D
    xb = vec_min3(x_1b, x0b, x1b);
    xa = vec_bord_g1(xb);

    for(j = 0; j <= (size_l-1)-1; j++)
    {
        // Operations sur le vecteur de droite
        x_1c = _mm_load_si128(&src[i-1][j+1]);
        x0c = _mm_load_si128(&src[i][j+1]);
        x1c = _mm_load_si128(&src[i+1][j+1]);
        xc = vec_min3(x_1c, x0c, x1c);

        yl = vec_right1(xa, xb);
        yr = vec_left1(xb, xc);

        // Operation finale
        y = vec_min3(yl, xb, yr);   // operations entre colonnes
        _mm_store_si128(&dest[i][j], y);

        DEBUG(display_vuint8(yl, "%3d", " yl = "));DEBUG(puts(""));
        DEBUG(display_vuint8(xb, "%3d", " xb = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr, "%3d", " yr = "));DEBUG(puts(""));
        DEBUG(puts("-----------------------------------------------------------"));
        DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));

        xa = xb;
        xb = xc;
    }

    /* Prologue */

    // Gestion bords droits
    xc = vec_bord_d1(xb);
    yl = vec_right1(xa, xb);
    yr = vec_left1(xb, xc);

    y = vec_min3(yl, xb, yr);
    _mm_store_si128(&dest[i][j], y);

    DEBUG(display_vuint8(yl, "%3d", " yl = "));DEBUG(puts(""));
    DEBUG(display_vuint8(xb, "%3d", " xb = "));DEBUG(puts(""));
    DEBUG(display_vuint8(yr, "%3d", " yr = "));DEBUG(puts(""));
    DEBUG(puts("-----------------------------------------------------------"));
    DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));
}


/**
 *  (SIMD) Erosion en niveau de gris d'une ligne d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 *  @param  i       Numero de ligne
 */
inline void erode5_vector_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest, int i)
{
    int j;
    vuint8 x_2a, x_2b, x_2c;
    vuint8 x_1a, x_1b, x_1c;
    vuint8 x0a, x0b, x0c;
    vuint8 x1a, x1b, x1c;
    vuint8 x2a, x2b, x2c;

    vuint8 xa, xb, xc;

    vuint8 yl2, yl1, yr1, yr2;
    vuint8 y;

    // Parcours image
    x_2b = _mm_load_si128(&src[i-2][0]);
    x_1b = _mm_load_si128(&src[i-1][0]);
    x0b = _mm_load_si128(&src[i][0]);
    x1b = _mm_load_si128(&src[i+1][0]);
    x2b = _mm_load_si128(&src[i+2][0]);

    // Operation sur colonne (entre les lignes de vecteurs)
    // Factorisation d'operateurs sur 1D
    xb = vec_min5(x_2b, x_1b, x0b, x1b, x2b);
    xa = vec_bord_g2(xb);

    for(j = 0; j <= (size_l-1)-1; j++)
    {
        // Operations sur le vecteur de droite
        x_2c = _mm_load_si128(&src[i-2][j+1]);
        x_1c = _mm_load_si128(&src[i-1][j+1]);
        x0c = _mm_load_si128(&src[i][j+1]);
        x1c = _mm_load_si128(&src[i+1][j+1]);
        x2c = _mm_load_si128(&src[i+2][j+1]);
        xc = vec_min5(x_2c, x_1c, x0c, x1c, x2c);

        yl2 = vec_right2(xa, xb);
        yl1 = vec_right1(xa, xb);
        yr1 = vec_left1(xb, xc);
        yr2 = vec_left2(xb, xc);

        // Operation finale
        y = vec_min5(yl2, yl1, xb, yr1, yr2);   // operations entre colonnes
        _mm_store_si128(&dest[i][j], y);

        DEBUG(display_vuint8(yl2, "%3d", " yl2 = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yl1, "%3d", " yl1 = "));DEBUG(puts(""));
        DEBUG(display_vuint8(xb, "%3d", "  xb = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr1, "%3d", " yr1 = "));DEBUG(puts(""));
        DEBUG(display_vuint8(yr2, "%3d", " yr2 = "));DEBUG(puts(""));
        DEBUG(puts("-----------------------------------------------------------"));
        DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));

        xa = xb;
        xb = xc;
    }

    /* Prologue */

    // Gestion bords droits
    yl2 = vec_right2(xa, xb);
    yl1 = vec_right1(xa, xb);
    yr1 = vec_left1(xb, xc);
    yr2 = vec_left2(xb, xc);

    y = vec_min5(yl2, yl1, xb, yr1, yr2);   // operations entre colonnes
    _mm_store_si128(&dest[i][j], y);

    DEBUG(display_vuint8(yl2, "%3d", " yl2 = "));DEBUG(puts(""));
    DEBUG(display_vuint8(yl1, "%3d", " yl1 = "));DEBUG(puts(""));
    DEBUG(display_vuint8(xb, "%3d", "  xb = "));DEBUG(puts(""));
    DEBUG(display_vuint8(yr1, "%3d", " yr1 = "));DEBUG(puts(""));
    DEBUG(display_vuint8(yr2, "%3d", " yr2 = "));DEBUG(puts(""));
    DEBUG(puts("-----------------------------------------------------------"));
    DEBUG(display_vuint8(y, "%3d", "  y = "));DEBUG(puts("\n"));
}

/**
 *  (SIMD) Ouverture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *  avec pipeline d'operateur
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open3_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer)
{
    int i;

    for(i=0; i<2; i++){
        erode3_vector_SSE2_opt(src, size_h, size_l, buffer, i);
    }
    for(i=0; i+2 < size_h; i++){
        dilate3_vector_SSE2_opt(buffer, size_h, size_l, dest, i);
        erode3_vector_SSE2_opt(src, size_h, size_l, buffer, i+2);
    }
    dilate3_vector_SSE2_opt(buffer, size_h, size_l, dest, size_h-2);
    dilate3_vector_SSE2_opt(buffer, size_h, size_l, dest, size_h-1);
}

/**
 *  (SIMD) Ouverture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *  sans pipeline d'operateur
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open3_SSE2_opt_no_pipe(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer)
{
    erode3_SSE2_opt(src, size_h, size_l, buffer);
    dilate3_SSE2_opt(buffer, size_h, size_l, dest);
}

/**
 *  (SIMD) Fermeture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void close3_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer)
{
    int i;

    for(i=0; i<2; i++){
        erode3_vector_SSE2_opt(src, size_h, size_l, buffer, i);
    }
    for(i=0; i+2 < size_h; i++){
        dilate3_vector_SSE2_opt(buffer, size_h, size_l, dest, i);
        erode3_vector_SSE2_opt(src, size_h, size_l, buffer, i+2);
    }
    dilate3_vector_SSE2_opt(buffer, size_h, size_l, dest, size_h-2);
    dilate3_vector_SSE2_opt(buffer, size_h, size_l, dest, size_h-1);
}

/**
 *  (SIMD) Fermeture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void close3_SSE2_opt_no_pipe(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer)
{
    dilate3_SSE2_opt(src, size_h, size_l, buffer);
    erode3_SSE2_opt(buffer, size_h, size_l, dest);
}

/**
 *  (SIMD) Ouverture en niveau de gris d'une image avec un élément structurant de taille 5x5
 *  avec pipeline d'operateur
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open5_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer)
{
    int i;

    for(i=0; i<3; i++){
        erode5_vector_SSE2_opt(src, size_h, size_l, buffer, i);
    }
    for(i=0; i+3 < size_h; i++){
        dilate5_vector_SSE2_opt(buffer, size_h, size_l, dest, i);
        erode5_vector_SSE2_opt(src, size_h, size_l, buffer, i+3);
    }
    dilate5_vector_SSE2_opt(buffer, size_h, size_l, dest, size_h-3);
    dilate5_vector_SSE2_opt(buffer, size_h, size_l, dest, size_h-2);
    dilate5_vector_SSE2_opt(buffer, size_h, size_l, dest, size_h-1);
}

/**
 *  (SIMD) Ouverture en niveau de gris d'une image avec un élément structurant de taille 5x5
 *  avec pipeline d'operateur
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open5_SSE2_opt_no_pipe(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer)
{
    erode5_SSE2_opt(src, size_h, size_l, buffer);
    dilate5_SSE2_opt(buffer, size_h, size_l, dest);
}

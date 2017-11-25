/*--------------------------------
    morpho.c

    Fonctions de morphologie mathématique

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Kevin Seng - 2017
 ----------------------------------*/

#include <stdio.h>
#include <stdint.h>

#include "morpho.h"

/**
 *  Dilataion binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate_bin3(uint8_t** src, int size_h, int size_l, uint8_t** dest)
{
    int i, j, di, dj;
    uint8_t dilat = 0;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-1; di <= i+1; di++)
            {
                for(dj = j-1; dj <= j+1; dj++)
                {
                    dilat = dilat | src[di][dj];
                }
            }
            dest[i][j] = dilat;
            dilat = 0;
        }
    }
}

/**
 *  Erosion binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode_bin3(uint8_t** src, int size_h, int size_l, uint8_t** dest)
{
    int i, j, di, dj;
    uint8_t erod = 1;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-1; di <= i+1; di++)
            {
                for(dj = j-1; dj <= j+1; dj++)
                {
                    erod = erod & src[di][dj];
                }
            }
            dest[i][j] = erod;
            erod = 1;
        }
    }
}

/**
 *  Fermeture binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image filtree
 *  @param  buffer  Tableau temporaire pour le filtrage
 */
void close_bin3(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer)
{
    int i, j, di, dj;
    uint8_t dilat = 0;
    uint8_t erod = 1;
    uint8_t** temp_mat;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-1; di <= i+1; di++)
            {
                for(dj = j-1; dj <= j+1; dj++)
                {
                    dilat = dilat | src[di][dj];
                }
            }
            buffer[i][j] = dilat;
            dilat = 0;
        }
    }

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-1; di <= i+1; di++)
            {
                for(dj = j-1; dj <= j+1; dj++)
                {
                    erod = erod & buffer[di][dj];
                }
            }
            dest[i][j] = erod;
            erod = 1;
        }
    }
}

/**
 *  Ouverture binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image filtree
 *  @param  buffer  Tableau temporaire pour le filtrage
 */
void open_bin3(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer)
{
    int i, j, di, dj;
    uint8_t dilat = 0;
    uint8_t erod = 1;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-1; di <= i+1; di++)
            {
                for(dj = j-1; dj <= j+1; dj++)
                {
                    erod = erod & src[di][dj];
                }
            }
            buffer[i][j] = erod;
            erod = 1;
        }
    }

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-1; di <= i+1; di++)
            {
                for(dj = j-1; dj <= j+1; dj++)
                {
                    dilat = dilat | buffer[di][dj];
                }
            }
            dest[i][j] = dilat;
            dilat = 0;
        }
    }
}

/**
 *  Dilataion binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate_bin5(uint8_t** src, int size_h, int size_l, uint8_t** dest)
{
    int i, j, di, dj;
    uint8_t dilat = 0;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-2; di <= i+2; di++)
            {
                for(dj = j-2; dj <= j+2; dj++)
                {
                    dilat = dilat | src[di][dj];
                }
            }
            dest[i][j] = dilat;
            dilat = 0;
        }
    }
}

/**
 *  Erosion binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode_bin5(uint8_t** src, int size_h, int size_l, uint8_t** dest)
{
    int i, j, di, dj;
    uint8_t erod = 1;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-2; di <= i+2; di++)
            {
                for(dj = j-2; dj <= j+2; dj++)
                {
                    erod = erod & src[di][dj];
                }
            }
            dest[i][j] = erod;
            erod = 1;
        }
    }
}

/**
 *  Ouverture binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image filtree
 *  @param  buffer  Tableau temporaire pour le filtrage
 */
void open_bin5(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer)
{
    int i, j, di, dj;
    uint8_t dilat = 0;
    uint8_t erod = 1;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-2; di <= i+2; di++)
            {
                for(dj = j-2; dj <= j+2; dj++)
                {
                    erod = erod & src[di][dj];
                }
            }
            buffer[i][j] = erod;
            erod = 1;
        }
    }

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-2; di <= i+2; di++)
            {
                for(dj = j-2; dj <= j+2; dj++)
                {
                    dilat = dilat | buffer[di][dj];
                }
            }
            dest[i][j] = dilat;
            dilat = 0;
        }
    }
}

/**
 *  Fermeture binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image filtree
 *  @param  buffer  Tableau temporaire pour le filtrage
 */
void close_bin5(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer)
{
    int i, j, di, dj;
    uint8_t dilat = 0;
    uint8_t erod = 1;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-2; di <= i+2; di++)
            {
                for(dj = j-2; dj <= j+2; dj++)
                {
                    dilat = dilat | src[di][dj];
                }
            }
            buffer[i][j] = dilat;
            dilat = 0;
        }
    }

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-2; di <= i+2; di++)
            {
                for(dj = j-2; dj <= j+2; dj++)
                {
                    erod = erod & buffer[di][dj];
                }
            }
            dest[i][j] = erod;
            erod = 1;
        }
    }
}

/**
 *  Dilataion en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate3(uint8_t** src, int size_h, int size_l, uint8_t** dest)
{
    int i, j, di, dj;
    uint8_t dilat = 0;
    uint8_t temp;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-1; di <= i+1; di++)
            {
                for(dj = j-1; dj <= j+1; dj++)
                {
                    // Max de l'element structurant
                    temp = src[di][dj];
                    if(dilat<temp)
                        dilat = temp;
                }
            }
            dest[i][j] = dilat;
            dilat = 0;
        }
    }
}

/**
 *  Erosion en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source</stdint>
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode3(uint8_t** src, int size_h, int size_l, uint8_t** dest)
{
    int i, j, di, dj;
    uint8_t erod = 255;
    uint8_t temp;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-1; di <= i+1; di++)
            {
                for(dj = j-1; dj <= j+1; dj++)
                {
                    // Min de l'element structurant
                    temp = src[di][dj];
                    if(erod>temp)
                        erod = temp;
                }
            }
            dest[i][j] = erod;
            erod = 255;
        }
    }
}

/**
 *  Ouverture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image filtree
 *  @param  buffer  Tableau temporaire pour le filtrage
 */
void open3(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer)
{
    int i, j, di, dj;
    uint8_t dilat = 0;
    uint8_t erod = 255;
    uint8_t temp;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-1; di <= i+1; di++)
            {
                for(dj = j-1; dj <= j+1; dj++)
                {
                    // Min de l'element structurant
                    temp = src[di][dj];
                    if(erod>temp)
                        erod = temp;
                }
            }
            buffer[i][j] = erod;
            erod = 255;
        }
    }

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-1; di <= i+1; di++)
            {
                for(dj = j-1; dj <= j+1; dj++)
                {
                    // Max de l'element structurant
                    temp = buffer[di][dj];
                    if(dilat<temp)
                        dilat = temp;
                }
            }
            dest[i][j] = dilat;
            dilat = 0;
        }
    }
}

/**
 *  Fermeture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image filtree
 *  @param  buffer  Tableau temporaire pour le filtrage
 */
void close3(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer)
{
    int i, j, di, dj;
    uint8_t dilat = 0;
    uint8_t erod = 255;
    uint8_t temp;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-1; di <= i+1; di++)
            {
                for(dj = j-1; dj <= j+1; dj++)
                {
                    // Max de l'element structurant
                    temp = src[di][dj];
                    if(dilat<temp)
                        dilat = temp;
                }
            }
            buffer[i][j] = dilat;
            dilat = 0;
        }
    }

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-1; di <= i+1; di++)
            {
                for(dj = j-1; dj <= j+1; dj++)
                {
                    // Min de l'element structurant
                    temp = buffer[di][dj];
                    if(erod>temp)
                        erod = temp;
                }
            }
            dest[i][j] = erod;
            erod = 255;
        }
    }
}

/**
 *  Dilataion en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate5(uint8_t** src, int size_h, int size_l, uint8_t** dest)
{
    int i, j, di, dj;
    uint8_t dilat = 0;
    uint8_t temp;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-2; di <= i+2; di++)
            {
                for(dj = j-2; dj <= j+2; dj++)
                {
                    // Max de l'element structurant
                    temp = src[di][dj];
                    if(dilat<temp)
                        dilat = temp;
                }
            }
            dest[i][j] = dilat;
            dilat = 0;
        }
    }
}

/**
 *  Erosion en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode5(uint8_t** src, int size_h, int size_l, uint8_t** dest)
{
    int i, j, di, dj;
    uint8_t erod = 255;
    uint8_t temp;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-2; di <= i+2; di++)
            {
                for(dj = j-2; dj <= j+2; dj++)
                {
                    // Min de l'element structurant
                    temp = src[di][dj];
                    if(erod>temp)
                        erod = temp;
                }
            }
            dest[i][j] = erod;
            erod = 255;
        }
    }
}

/**
 *  Ouverture en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image filtree
 *  @param  buffer  Tableau temporaire pour le filtrage
 */
void open5(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer)
{
    int i, j, di, dj;
    uint8_t dilat = 0;
    uint8_t erod = 255;
    uint8_t temp;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-2; di <= i+2; di++)
            {
                for(dj = j-2; dj <= j+2; dj++)
                {
                    // Min de l'element structurantsrc
                    temp = src[di][dj];
                    if(erod>temp)
                        erod = temp;
                }
            }
            buffer[i][j] = erod;
            erod = 255;
        }
    }

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-2; di <= i+2; di++)
            {
                for(dj = j-2; dj <= j+2; dj++)
                {
                    // Max de l'element structurant
                    temp = buffer[di][dj];
                    if(dilat<temp)
                        dilat = temp;
                }
            }
            dest[i][j] = dilat;
            dilat = 0;
        }
    }
}

/**
 *  Fermeture en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image filtree
 *  @param  buffer  Tableau temporaire pour le filtrage
 */
void close5(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer)
{
    int i, j, di, dj;
    uint8_t dilat = 0;
    uint8_t erod = 255;
    uint8_t temp;

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-2; di <= i+2; di++)
            {
                for(dj = j-2; dj <= j+2; dj++)
                {
                    // Max de l'element structurant
                    temp = src[di][dj];
                    if(dilat<temp)
                        dilat = temp;
                }
            }
            buffer[i][j] = dilat;
            dilat = 0;
        }
    }

    // Parcours image
    for(i = 0; i < size_h; i++)
    {
        for(j = 0; j < size_l; j++)
        {
            // Parcours Element structurant
            for(di = i-2; di <= i+2; di++)
            {
                for(dj = j-2; dj <= j+2; dj++)
                {
                    // Min de l'element structurant
                    temp = buffer[di][dj];
                    if(erod>temp)
                        erod = temp;
                }
            }
            dest[i][j] = erod;
            erod = 255;
        }
    }
}

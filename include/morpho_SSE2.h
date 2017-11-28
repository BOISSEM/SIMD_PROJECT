/*---------------------------------
    morpho_SSE2.h

    Fonctions de morphologie mathématique parallelises en SIMD

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Kevin Seng - 2017
 ----------------------------------*/
#ifndef __MORPHO_SSE2_H__
#define __MORPHO_SSE2_H__

/**
 *  (SIMD) Dilataion binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate_bin3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest);

/**
 *  (SIMD) Erosion binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode_bin3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest);

/**
 *  (SIMD) Fermeture binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void close_bin3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer);

/**
 *  (SIMD) Ouverture binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open_bin3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer);

/**
 *  (SIMD) Dilataion binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate_bin5_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest);

/**
 *  (SIMD) Erosion binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode_bin5_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest);

/**
 *  (SIMD) Ouverture binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open_bin5_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer);

/**
 *  (SIMD) Fermeture binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void close_bin5_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer);

/**
 *  (SIMD) Dilataion en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest);

/**
 *  (SIMD) Erosion en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest);

/**
 *  (SIMD) Ouverture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer);

/**
 *  (SIMD) Fermeture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void close3_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer);

/**
 *  (SIMD) Dilataion en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate5_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest);

/**
 *  (SIMD) Erosion en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode5_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest);

/**
 *  (SIMD) Ouverture en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image filtree
 *  @param  buffer  Tableau temporaire pour le filtrage
 */
void open5_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer);

/**
 *  (SIMD) Fermeture en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image filtree
 *  @param  buffer  Tableau temporaire pour le filtrage
 */
void close5_SSE2(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer);

#endif  // __MORPHO_SSE2_H__

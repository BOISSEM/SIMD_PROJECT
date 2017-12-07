/*---------------------------------
    morpho_SSE2_opt.h

    Fonctions de morphologie mathématique parallelises en SIMD

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Kevin Seng - 2017
 ----------------------------------*/
#ifndef __MORPHO_SSE2_OPT_H__
#define __MORPHO_SSE2_OPT_H__


/**
 *  (SIMD) Dilataion binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate_bin3_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest);

/**
 *  (SIMD) Dilataion d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate3_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest);

/**
 *  (SIMD) Erosion en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode3_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest);

/**
 *  (SIMD) Ouverture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *  avec pipeline d'operateur
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open3_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer);

/**
 *  (SIMD) Ouverture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *  sans pipeline d'operateur
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open3_SSE2_opt_no_pipe(vuint8** src, int size_h, int size_l, vuint8** dest, vuint8** buffer);

#endif  // __MORPHO_SSE2_OPT_H__

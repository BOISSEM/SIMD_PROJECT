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
 *  (SIMD) Dilataion d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate3_SSE2_opt(vuint8** src, int size_h, int size_l, vuint8** dest);

#endif  // __MORPHO_SSE2_OPT_H__

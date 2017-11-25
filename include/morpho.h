/*---------------------------------
    morpho.h

    Fonctions de morphologie mathématique

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Kevin Seng - 2017
 ----------------------------------*/
#ifndef __MORPHO_H__
#define __MORPHO_H__

/**
 *  Dilataion binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate_bin3(uint8_t** src, int size_h, int size_l, uint8_t** dest);

/**
 *  Erosion binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode_bin3(uint8_t** src, int size_h, int size_l, uint8_t** dest);

/**
 *  Fermeture binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void close_bin3(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer);

/**
 *  Ouverture binaire d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open_bin3(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer);

/**
 *  Dilataion binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate_bin5(uint8_t** src, int size_h, int size_l, uint8_t** dest);

/**
 *  Erosion binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode_bin5(uint8_t** src, int size_h, int size_l, uint8_t** dest);

/**
 *  Ouverture binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open_bin5(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer);

/**
 *  Fermeture binaire d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void close_bin5(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer);

/**
 *  Dilataion en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate3(uint8_t** src, int size_h, int size_l, uint8_t** dest);

/**
 *  Erosion en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode3(uint8_t** src, int size_h, int size_l, uint8_t** dest);

/**
 *  Ouverture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void open3(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer);

/**
 *  Fermeture en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void close3(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer);

/**
 *  Dilataion en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image dilatee
 */
void dilate5(uint8_t** src, int size_h, int size_l, uint8_t** dest);

/**
 *  Erosion en niveau de gris d'une image avec un élément structurant de taille 3x3
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image erodee
 */
void erode5(uint8_t** src, int size_h, int size_l, uint8_t** dest);

/**
 *  Ouverture en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image filtree
 *  @param  buffer  Tableau temporaire pour le filtrage
 */
void open5(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer);

/**
 *  Fermeture en niveau de gris d'une image avec un élément structurant de taille 5x5
 *
 *  @param  src     Image source
 *  @param  size_h  Hauteur de l'image
 *  @param  size_l  Largeur de l'image
 *  @param  dest    Image filtree
 *  @param  buffer  Tableau temporaire pour le filtrage
 */
void close5(uint8_t** src, int size_h, int size_l, uint8_t** dest, uint8_t** buffer);

#endif  // __MORPHO_H__

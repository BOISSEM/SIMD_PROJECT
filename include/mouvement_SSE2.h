/* -----------------------------------------------
	mouvement.h
	Edité par Martin Boisse
	Le 20 Octobre 2018

	Projet SIMD
	Prototype des algorithmes SIMD
	de detection de mouvement (non optimisés)
----------------------------------------------- */
#ifndef __MOUVEMENT_H__
#define __MOUVEMENT_H__

#define NB_IMAGE 200
#define THETA 25
#define N 2
#define VMAX 50
#define VMIN 18

/**
 *	Routine de l'algorithme de Frame Difference
 *
 *	@param It		Image au temps t
 *	@param It_1		Image au temps t+1
 *	@param size_l		Largeur de l'image
 *	@param size_h		Hauteur de l'iamge
 *	@param Ot	Table de difference
 *	@param Et	Tableau d'etiquettes binaires de sortie
 *	@return				pointeur vers le tableau d'etiquettes binaires
 */
vuint8** routine_FrameDifference_SSE2(vuint8** It, vuint8** It_1,
	int size_h, int size_l, vuint8** Ot, vuint8** Et);

/**
 *	Etape prologue de l'algorithme Sigma Delta
 *
 *	@param V		Tableau de V
 *	@param M		Tableau de M
 *	@param It		Image au temps t0
 *	@param size_l		Largeur de l'image
 *	@param size_h		Hauteur de l'iamge
 * 	@return				Pointeur vers le tableau de Ms
 */
vuint8** SigmaDelta_step0_SSE2(vuint8** V, vuint8** M, vuint8** It,
	int size_h, int size_l);

/**
 *	Etape de routine de l'algorithme Sigma Delta
 *
 *	@param It_1		Image au temps t
 *	@param Ot	Tableau de difference
 *	@param size_l		Largeur de l'image
 *	@param size_h		Hauteur de l'iamge
 *	@param M		Tableau de M
 *	@param V		Tableau de V
 *	@param Et	Etiquette binaire de sortie
 *	@return 			Pointeur vers tableau d'etiquettes binaires
 */
vuint8** SigmaDelta_1step_SSE2(vuint8** It_1, vuint8** Ot,
	int size_h, int size_l, vuint8** M, vuint8** V, vuint8** Et);

/**
 *	Routine de l'algorithme de Frame Difference
 *	Architecture améliorée
 *
 *	@param It			Image au temps t
 *	@param It_1			Image au temps t+1
 *	@param size_h		Hauteur de l'image
 *	@param size_l		Largeur de l'image
 *	@param Ot			Table de difference
 *	@param Et			Tableau d'etiquettes binaires de sortie
 *	@return				pointeur vers le tableau d'etiquettes binaires
 */

vuint8** routine_FrameDifference_SSE2_Archi(vuint8** It, vuint8** It_1,
	int size_h, int size_l, vuint8** Ot, vuint8** Et);

/**
 *	Etape de routine de l'algorithme Sigma Delta
 *	Architecture améliorée 
 *
 *	@param It_1			Image au temps t
 *	@param Ot			Tableau de difference
 *	@param size_h		Hauteur de l'image
 *	@param size_l		Largeur de l'image
 *	@param M			Tableau de M
 *	@param V			Tableau de V
 *	@param Et			Etiquette binaire de sortie
 *	@return 			Pointeur vers tableau d'etiquettes binaires
 */
vuint8** SigmaDelta_1step_SSE2_Archi(vuint8** It_1, vuint8** Ot,
	int size_h, int size_l, vuint8** M, vuint8** V, vuint8** Et);

#endif //__MOUVEMENT_H__

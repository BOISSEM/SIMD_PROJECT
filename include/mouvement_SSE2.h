/* -----------------------------------------------
	mouvement.h
	Edité par Martin Boisse
	Le 20 Octobre 2018

	Projet SIMD
	Prototype des algorithmes SIMD
	de detection de mouvement (non optimisés)
----------------------------------------------- */
#ifndef __MOUVEMENT_SSE2_H__
#define __MOUVEMENT_SSE2_H__

#define NB_IMAGE 200
#define THETA 10
#define N 3
#define VMAX 40
#define VMIN 20

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
vuint8** routine_FrameDifference(vuint8** It, vuint8** It_1,
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
vuint8** SigmaDelta_step0(vuint8** V, vuint8** M, vuint8** It,
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
vuint8** SigmaDelta_1step(vuint8** It_1, vuint8** Ot,
	int size_h, int size_l, vuint8** M, vuint8** V, vuint8** Et);

#endif //__MOUVEMENT_SSE2_H__

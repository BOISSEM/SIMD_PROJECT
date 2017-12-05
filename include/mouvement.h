/* -----------------------------------------------
	mouvement.h
	Edité par Martin Boisse
	Le 20 Octobre 2018

	Projet SIMD
	Prototype des algorithmes scalaires
	de detection de mouvement (non optimisés)
----------------------------------------------- */
#ifndef __MOUVEMENT_H__
#define __MOUVEMENT_H__

#define NB_IMAGE 200
#define THETA 20
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
uint8_t** routine_FrameDifference(uint8_t** It, uint8_t** It_1,
	int size_h, int size_l, uint8_t** Ot, uint8_t** Et);

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
uint8_t** SigmaDelta_step0(uint8_t** V, uint8_t** M, uint8_t** It,
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
uint8_t** SigmaDelta_1step(uint8_t** It_1, uint8_t** Ot,
	int size_h, int size_l, uint8_t** M, uint8_t** V, uint8_t** Et);

int min(int a, int b);
int max(int a, int b);

#endif //__MOUVEMENT_H__

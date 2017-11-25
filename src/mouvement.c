/* -----------------------------------------------
	mouvement.c
	Edité par Martin Boisse
	Le 20 Octobre 2018

	Projet SIMD
	Algorithmes scalaires de detection
	de mouvement (non optimisés)
----------------------------------------------- */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "mouvement.h"

/**
 *	Routine de l'algorithme de Frame Difference
 *
 *	@param It			Image au temps t
 *	@param It_1			Image au temps t+1
 *	@param size_h		Hauteur de l'image
 *	@param size_l		Largeur de l'image
 *	@param Ot			Table de difference
 *	@param Et			Tableau d'etiquettes binaires de sortie
 *	@return				pointeur vers le tableau d'etiquettes binaires
 */
uint8_t** routine_FrameDifference(uint8_t** It, uint8_t** It_1,
			int size_h, int size_l, uint8_t** Ot, uint8_t** Et)
{
	int i, j;

	// Step#1: Ot Computation
	for(i = 0; i < size_h; i++)	{
		for (j = 0; j < size_l; j++)	{
			Ot[i][j] = abs(It_1[i][j] - It[i][j]);
			// Step#2: thresholding and Et estimation
			if(Ot[i][j] < THETA)
				Et[i][j] = 0;
			else
				Et[i][j] = 255;
		}
	}

	return Et;
}

/**
 *	Etape prologue de l'algorithme Sigma Delta
 *
 *	@param V			Tableau de V
 *	@param M			Tableau de M
 *	@param It			Image au temps t0
 *	@param size_l		Largeur de l'image
 *	@param size_h		Hauteur de l'iamge
 * 	@return				Pointeur vers le tableau de Ms
 */
uint8_t** SigmaDelta_step0(uint8_t** V, uint8_t** M, uint8_t** It, int size_h, int size_l)
{
	int i, j;
	for(i = 0; i < size_h; i++)	{
		for(j = 0; j < size_l; j++)	{
			V[i][j] = VMIN;
			M[i][j] = It[i][j];
		}
	}

	return M;
}

/**
 *	Etape de routine de l'algorithme Sigma Delta
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
uint8_t** SigmaDelta_1step(uint8_t** It_1, uint8_t** Ot, int size_h, int size_l,
			uint8_t** M, uint8_t** V, uint8_t** Et)	{
	int i, j;

	// Step#1: Mt estimation
	for(i = 0; i < size_h; i++)	{
		for(j = 0; j < size_l; j++)	{
			if(M[i][j] < It_1[i][j])
				M[i][j] = M[i][j] + 1;
			else if(M[i][j] > It_1[i][j])
				M[i][j] = M[i][j] - 1;
		}
	}

	// Step#2: Difference Computation
	for(i = 0; i < size_h; i++)
		for(j = 0; j < size_l; j++)
			Ot[i][j] = abs(M[i][j] - It_1[i][j]);

	// Step#3: Vt update and clamping
	for(i = 0; i < size_h; i++)	{
		for(j = 0; j < size_l; j++)	{
			if(V[i][j] < N*It_1[i][j])
				V[i][j] = V[i][j] + 1;
			else if(V[i][j] > N*It_1[i][j])
				V[i][j] = V[i][j] - 1;
			// Clamp to [VMIN, VMAX]
			V[i][j] = max(min(V[i][j], VMAX), VMIN);
		}
	}

	// Step#4: Et estimation
	for(i = 0; i < size_h; i++)	{
		for(j = 0; j < size_l; j++)	{
			if(Ot[i][j] < V[i][j])
				Et[i][j] = 0;
			else
				Et[i][j] = 255;
		}
	}

	return Et;
}

int min(int a, int b)	{
	if(a < b)
		return a;
	else
		return b;
}
int max(int a, int b)	{
	if(a > b)
		return a;
	else
		return b;
}

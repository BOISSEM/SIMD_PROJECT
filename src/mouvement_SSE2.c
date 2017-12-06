/* -----------------------------------------------
	mouvement.c
	Edité par Martin Boisse
	Le 20 Octobre 2018

	Projet SIMD
	Algorithmes SIMD de detection
	de mouvement (non optimisés)
----------------------------------------------- */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "vnrdef.h"
#include "nrdef.h"
#include "mouvement_SSE2.h"
#include "vnrutil.h"

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

vuint8** routine_FrameDifference_SSE2(vuint8** It, vuint8** It_1,
	int size_h, int size_l, vuint8** Ot, vuint8** Et)
{
	int i, j;
 	vuint8 v_theta = init_vuint8(THETA);
	vuint8 v_255 = init_vuint8(255);
	vuint8 v_128 = init_vuint8(128);

	vuint8 a_0;
	vuint8 b_0;

	vuint8 v_it;
	vuint8 v_it_1;

 	// Step#1: Ot Computation
 	for(i = 0; i < size_h; i++)	{
 		for(j = 0; j <= size_l; j++)	{
 			// Load
 			v_it = _mm_load_si128(&It[i][j]);
 			v_it_1 = _mm_load_si128(&It_1[i][j]);

 			// a_0 <- abs(It_1, It)
 			a_0 = _mm_min_epu8(v_it_1, v_it);
 			b_0 = _mm_max_epu8(v_it_1, v_it);
 			a_0 = _mm_sub_epi8(b_0, a_0);
 			// Ot <- a_0
 			_mm_store_si128(&Ot[i][j], a_0);
 		}
 	}

	// Step#2: thresholding and Et estimation
 	for(i = 0; i < size_h; i++)	{
 		for(j = 0; j <= size_l; j++)	{
 			// a_0 <- 255 si Ot < THETA
			//		  0	sinon 
			a_0 = _mm_sub_epi8(Ot[i][j], v_128);
			b_0 = _mm_sub_epi8(v_theta, v_128);
			a_0 = _mm_cmplt_epi8(a_0, b_0);
			// b_0 <- 255 si a_0 == 0
			b_0 = _mm_andnot_si128(a_0, v_255);
			// Et <- b_0
			_mm_store_si128(&Et[i][j], b_0);
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
vuint8** SigmaDelta_step0_SSE2(vuint8** V, vuint8** M, vuint8** It,
	int size_h, int size_l)
{
	int i, j;

	vuint8 v_vmin = init_vuint8(VMIN);

	for(i = 0; i < size_h; i++)	{
		for(j = 0; j <= size_l; j++)	{
			// V <- VMIN
			_mm_store_si128(&V[i][j], v_vmin);	
			// M <- It
			_mm_store_si128(&M[i][j], It[i][j]);
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
vuint8** SigmaDelta_1step_SSE2(vuint8** It_1, vuint8** Ot,
	int size_h, int size_l, vuint8** M, vuint8** V, vuint8** Et)
{
	int i, j, k;
	vuint8 v_0x01 = _mm_set1_epi8(0x01);
	vuint8 v_255 = init_vuint8(255);
	vuint8 v_128 = init_vuint8(128);

	vuint8 a;
	vuint8 b;

	vuint8 v_var;
	// Variance signée
	vuint8 v_varS;
	vuint8 v_it_1;
	// Image signée
	vuint8 v_it_1S;
	vuint8 v_m;
	vuint8 v_ot;

	vuint8 v_vmax = init_vuint8(VMAX);
	vuint8 v_vmin = init_vuint8(VMIN);

	// Step#1: Mt Estimation
	for (i = 0; i < size_h; i++)	{
		for (j = 0; j <= size_l; j++)	{
			// Load
			v_m = _mm_load_si128(&M[i][j]);
			v_it_1 = _mm_load_si128(&It_1[i][j]);
			// non signés -> signés 
			// a <- 255 si M < It_1
			//		0	sinon
			a = _mm_cmplt_epi8(_mm_sub_epi8(v_m, v_128), _mm_sub_epi8(v_it_1, v_128));
			// a <- 1 si a == 255
			//		0 sinon
			a = _mm_and_si128(a, v_0x01);
			// a <- M+1 si a == 1
			// 		M	sinon
			v_m = _mm_adds_epu8(v_m, a);

			// b <- 255 si M < It_1
			//		0	sinon
			b = _mm_cmpgt_epi8(_mm_sub_epi8(v_m, v_128), _mm_sub_epi8(v_it_1, v_128));
			// b <- 1 si b == 255
			//		0 sinon
			b = _mm_and_si128(b, v_0x01);
			// b <- M-1 si b == 1
			// 		M   sinon
			v_m = _mm_sub_epi8(v_m, b);
			// M <- b
			_mm_store_si128(&M[i][j], v_m);
		}
	}

	// Step#2: Difference Computation
	for(i = 0; i < size_h; i++)	{
		for(j = 0; j <= size_l; j++)	{
			// Load
			v_m = _mm_load_si128(&M[i][j]);
			v_it_1 = _mm_load_si128(&It_1[i][j]);
			// a <- abs(M, It_1)
			a = _mm_min_epu8(v_m, v_it_1);
			b = _mm_max_epu8(v_it_1, v_m);
			a = _mm_sub_epi8(b, a);
			// Ot <- a
			_mm_store_si128(&Ot[i][j], a);
		}
	}

	// Step#3: Vt update and clamping
	for(i = 0; i < size_h; i++)	{
		for(j = 0; j <= size_l; j++)	{
			//Load
			v_ot = _mm_load_si128(&Ot[i][j]);
			v_var = _mm_load_si128(&V[i][j]);

			// a <- N x It_1
			a = v_ot;
			for(k = 0; k < N; k++)	{
				v_ot = _mm_adds_epu8(v_ot, a);
			}
			// non signés -> signés (à quoi ça sert de signer V puisqu'il depasse pas VMAX < 128 ?)
			v_varS = _mm_sub_epi8(v_var, v_128);
			v_it_1S = _mm_sub_epi8(v_ot, v_128);

			// a <- 255 si V < NxIt_1
			//		0	sinon 
			a = _mm_cmplt_epi8(v_varS, v_it_1S);
			// a <- 1	si a == 255
			//		0	sinon
			a = _mm_and_si128(a, v_0x01);
			// a <- V+1	si a == 1
			//		V 	sinon
			v_var = _mm_add_epi8(v_var, a);

			// b <- 255	si V > NxIt_1
			// 		0	sinon
			b = _mm_cmpgt_epi8(v_varS, v_it_1S);
			// b <- 1 	si b == 255
			//		0	sinon
			b = _mm_and_si128(b, v_0x01);
			// b <- V-1	si b == 1
			//		V 	sinon	
			v_var = _mm_sub_epi8(v_var, b);

			// Clamp to [VMIN, VMAX]
			// a <- min(V, VMAX)
			a = _mm_min_epu8(v_var, v_vmax);
			// a <- max(a, VMIN)
			a = _mm_max_epu8(a, v_vmin);
			// V <- a
			_mm_store_si128(&V[i][j], a); 
		}
	}

	// Step#4: Et estimation
	for(i = 0; i < size_h; i++)	{
		for(j = 0; j <= size_l; j++)	{ 
			//Load
			v_ot = _mm_load_si128(&Ot[i][j]);
			v_var = _mm_load_si128(&V[i][j]);
			// non signés -> signés
			// a <-	255	si Ot < V
			//		0	sinon 
			a = _mm_cmplt_epi8(_mm_sub_epi8(v_ot, v_128), _mm_sub_epi8(v_var, v_128));
			// a <- 255	si a == 0
			//		0	sinon
			a = _mm_andnot_si128(a, v_255);
			// Et <- a
			_mm_store_si128(&Et[i][j], a);
		}
	}

	return Et;
}

/* --------------------------------------------- Amélioration architecture ------------------------------------------ */

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
	int size_h, int size_l, vuint8** Ot, vuint8** Et)
{
	int i, j;
 	vuint8 v_theta = init_vuint8(THETA);
	vuint8 v_255 = init_vuint8(255);
	vuint8 v_128 = init_vuint8(128);

	vuint8 a_0;
	vuint8 b_0;

	vuint8 v_it;
	vuint8 v_it_1;

 	// Step#1: Ot Computation
 	for(i = 0; i < size_h; i++)	{
 		for(j = 0; j <= size_l; j++)	{
 			// Load
 			v_it = _mm_load_si128(&It[i][j]);
 			v_it_1 = _mm_load_si128(&It_1[i][j]);

 			// a_0 <- abs(It_1, It)
 			a_0 = _mm_min_epu8(v_it_1, v_it);
 			b_0 = _mm_max_epu8(v_it_1, v_it);
 			a_0 = _mm_sub_epi8(b_0, a_0);
 			// Ot <- a_0
 			_mm_store_si128(&Ot[i][j], a_0);

			// Step#2: thresholding and Et estimation
			//Pourquoi ça marche pas quand on le met pas dans le test directemetn ? 
			// a_0 <- 255 si Ot < THETA
			//		  0	sinon 
			a_0 = _mm_sub_epi8(Ot[i][j], v_128);
			b_0 = _mm_sub_epi8(v_theta, v_128);
			a_0 = _mm_cmplt_epi8(a_0, b_0);
			// b_0 <- 255 si a_0 == 0
			b_0 = _mm_andnot_si128(a_0, v_255);
			// Et <- b_0
			_mm_store_si128(&Et[i][j], b_0);
 		}
 	}

 	return Et;
}

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
	int size_h, int size_l, vuint8** M, vuint8** V, vuint8** Et)
{
	int i, j, k;
	vuint8 v_0x01 = _mm_set1_epi8(0x01);
	vuint8 v_255 = init_vuint8(255);
	vuint8 v_128 = init_vuint8(128);

	vuint8 a;
	vuint8 b;

	vuint8 v_var;
	// Variance signée
	vuint8 v_varS;
	vuint8 v_it_1;
	// Image signée
	vuint8 v_it_1S;
	vuint8 v_m;
	vuint8 v_ot;

	vuint8 v_vmax = init_vuint8(VMAX);
	vuint8 v_vmin = init_vuint8(VMIN);

	// Step#1: Mt Estimation
	for (i = 0; i < size_h; i++)	{
		for (j = 0; j <= size_l; j++)	{
			// Load
			v_m = _mm_load_si128(&M[i][j]);
			v_it_1 = _mm_load_si128(&It_1[i][j]);
			// non signés -> signés 
			// a <- 255 si M < It_1
			//		0	sinon
			a = _mm_cmplt_epi8(_mm_sub_epi8(v_m, v_128), _mm_sub_epi8(v_it_1, v_128));
			// a <- 1 si a == 255
			//		0 sinon
			a = _mm_and_si128(a, v_0x01);
			// a <- M+1 si a == 1
			// 		M	sinon
			a = _mm_adds_epu8(v_m, a);
			// M <- a
			_mm_store_si128(&M[i][j], a);

			// b <- 255 si M < It_1
			//		0	sinon
			b = _mm_cmpgt_epi8(_mm_sub_epi8(v_m, v_128), _mm_sub_epi8(v_it_1, v_128));
			// b <- 1 si b == 255
			//		0 sinon
			b = _mm_and_si128(b, v_0x01);
			// b <- M-1 si b == 1
			// 		M   sinon
			b = _mm_sub_epi8(v_m, b);
			// M <- b
			_mm_store_si128(&M[i][j], b);


			// Step#2: Difference Computation
			// a <- abs(M, It_1)
			// Load
			v_m = _mm_load_si128(&M[i][j]);
			v_it_1 = _mm_load_si128(&It_1[i][j]);
			// a <- abs(M, It_1)
			a = _mm_min_epu8(v_m, v_it_1);
			b = _mm_max_epu8(v_it_1, v_m);
			a = _mm_sub_epi8(b, a);
			// Ot <- a
			_mm_store_si128(&Ot[i][j], a);


			// Step#3: Vt update and clamping
			// a <- N x It_1
			//Load
			v_it_1 = _mm_load_si128(&It_1[i][j]);
			v_var = _mm_load_si128(&V[i][j]);

			// a <- N x It_1
			a = v_it_1;
			for(k = 0; k < N; k++)	{
				v_it_1 = _mm_adds_epu8(v_it_1, a);
			}
			// non signés -> signés (à quoi ça sert de signer V puisqu'il depasse pas VMAX < 128 ?)
			v_varS = _mm_sub_epi8(v_var, v_128);
			v_it_1S = _mm_sub_epi8(v_it_1, v_128);

			// a <- 255 si V < NxIt_1
			//		0	sinon 
			a = _mm_cmplt_epi8(v_varS, v_it_1S);
			// a <- 1	si a == 255
			//		0	sinon
			a = _mm_and_si128(a, v_0x01);
			// a <- V+1	si a == 1
			//		V 	sinon
			a = _mm_add_epi8(v_var, a);
			// V <- a 
			_mm_store_si128(&V[i][j], a);

			// b <- 255	si V > NxIt_1
			// 		0	sinon
			b = _mm_cmpgt_epi8(v_varS, v_it_1S);
			// b <- 1 	si b == 255
			//		0	sinon
			b = _mm_and_si128(b, v_0x01);
			// b <- V-1	si b == 1
			//		V 	sinon	
			b = _mm_sub_epi8(v_var, b);
			// V <- b
			_mm_store_si128(&V[i][j], b); 

			// Clamp to [VMIN, VMAX]
			// a <- min(V, VMAX)
			a = _mm_min_epu8(v_var, v_vmax);
			// a <- max(a, VMIN)
			a = _mm_max_epu8(a, v_vmin);
			// V <- a
			_mm_store_si128(&V[i][j], a); 


			// Step#4: Et estimation
			//Load
			v_ot = _mm_load_si128(&Ot[i][j]);
			v_var = _mm_load_si128(&V[i][j]);
			// non signés -> signés
			// a <-	255	si Ot < V
			//		0	sinon 
			a = _mm_cmplt_epi8(_mm_sub_epi8(v_ot, v_128), _mm_sub_epi8(v_var, v_128));
			// a <- 255	si a == 0
			//		0	sinon
			a = _mm_andnot_si128(a, v_255);
			// Et <- a
			_mm_store_si128(&Et[i][j], a);
		}
	}

	return Et;
}



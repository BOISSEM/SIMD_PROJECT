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
	vuint8 a_1;
	vuint8 b_1;

 	// Step#1: Ot Computation
 	for(i = 0; i < size_h; i++)	{
 		for(j = 0; j < size_l; j++)	{
 			// a_0 <- abs(It_1, It)
 			a_0 = _mm_min_epu8(It_1[i][j], It[i][j]);
 			b_0 = _mm_max_epu8(It_1[i][j], It[i][j]);
 			a_0 = _mm_sub_epi8(b_0, a_0);
 			// Ot <- a_0
 			_mm_store_si128(&Ot[i][j], a_0);

 			a_1 = _mm_min_epu8(It_1[i][j+1], It[i][j+1]);
 			b_1 = _mm_max_epu8(It_1[i][j+1], It[i][j+1]);
 			a_1 = _mm_sub_epi8(b_1, a_1);
 			_mm_store_si128(&Ot[i][j+1], a_1);

			// Step#2: thresholding and Et estimation
			//Pourquoi ça marche pas quand on le met pas dans le test directemetn ? 
			// a_0 <- 255 si Ot < THETA
			//		  0	sinon 
			a_0 = _mm_cmplt_epi8(_mm_sub_epi8(Ot[i][j], v_128), _mm_sub_epi8(v_theta, v_128));
			// b_0 <- 255 si a_0 == 0
			b_0 = _mm_andnot_si128(a_0, v_255);
			// Et <- b_0
			_mm_store_si128(&Et[i][j], b_0);

			a_1 = _mm_cmplt_epi8(_mm_sub_epi8(Ot[i][j+1], v_128), _mm_sub_epi8(v_theta, v_128));
			b_1 = _mm_andnot_si128(a_1, v_255);
			_mm_store_si128(&Et[i][j+1], b_1);
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
		for(j = 0; j < size_l; j++)	{
			// V <- VMIN
			_mm_store_si128(&V[i][j], v_vmin);	
			// M <- It
			_mm_store_si128(&M[i][j], It[i][j]);

			_mm_store_si128(&V[i][j+1], v_vmin);
			_mm_store_si128(&M[i][j+1], It[i][j+1]);
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

	vuint8 v_vmax = init_vuint8(VMAX);
	vuint8 v_vmin = init_vuint8(VMIN);


	// Step#1: Mt Estimation
	for (i = 0; i < size_h; i++)	{
		for (j = 0; j < size_l; j++)	{
			// Si M < I alors M<-M+1
			// a <- 255 si M < It_1
			//		0	sinon
			a = _mm_cmplt_epi8(_mm_sub_epi8(M[i][j], v_128), _mm_sub_epi8(It_1[i][j], v_128));
			// a <- 1 si a == 255
			//		0 sinon
			a = _mm_and_si128(a, v_0x01);
			// a <- M+1 si a == 1
			// 		M	sinon
			a = _mm_add_epi8(M[i][j], a);
			// M <- a
			_mm_store_si128(&M[i][j], a);

			b = _mm_cmplt_epi8(_mm_sub_epi8(M[i][j+1], v_128), _mm_sub_epi8(It_1[i][j+1], v_128));
			b = _mm_and_si128(b, v_0x01);
			b = _mm_add_epi8(M[i][j+1], b);
			_mm_store_si128(&M[i][j+1], b);

			// Si M > I alors M<-M-1
			// a <- 255 si It_1 < M
			//		0	sinon
			a = _mm_cmplt_epi8(_mm_sub_epi8(It_1[i][j], v_128), _mm_sub_epi8(M[i][j], v_128));
			// a <- 1 si a == 255
			//		0 sinon
			a = _mm_and_si128(a, v_0x01);
			// a <- M-1 si a == 1
			// 		M   sinon
			a = _mm_sub_epi8(M[i][j], a);
			// M <- a
			_mm_store_si128(&M[i][j], a);

			b = _mm_cmplt_epi8(_mm_sub_epi8(It_1[i][j+1], v_128), _mm_sub_epi8(M[i][j+1], v_128));
			b = _mm_and_si128(b, v_0x01);
			b = _mm_sub_epi8(M[i][j+1], b);
			_mm_store_si128(&M[i][j+1], b);
			// Sinon M<-M (on ne touche à rien)
		}
	}

	// Step#2: Difference Computation
	for(i = 0; i < size_h; i++)	{
		for(j = 0; j < size_l; j++)	{
			// a <- abs(M, It_1)
			a = _mm_min_epu8(M[i][j], It_1[i][j]);
			b = _mm_max_epu8(It_1[i][j], M[i][j]);
			a = _mm_sub_epi8(b, a);
			// Ot <- a
			_mm_store_si128(&Ot[i][j], a);

			a = _mm_min_epu8(M[i][j+1], It_1[i][j+1]);
			b = _mm_max_epu8(It_1[i][j+1], M[i][j+1]);
			a = _mm_sub_epi8(b, a);
			_mm_store_si128(&Ot[i][j+1], a);
		}
	}

	// Step#3: Vt update and clamping
	for(i = 0; i < size_h; i++)	{
		for(j = 0; j < size_l; j++)	{
			// a <- N x It_1
			a = It_1[i][j];
			for(k = 0; k < N; k++)	{
				It_1[i][j] = _mm_add_epi8(It_1[i][j], a);
			}
			// Si V < NxIt_1
			// a <- 255 si V < NxIt_1
			//		0	sinon
			a = _mm_cmplt_epi8(_mm_sub_epi8(V[i][j], v_128), _mm_sub_epi8(It_1[i][j], v_128));
			// a <- 1	si a == 255
			//		0	sinon
			a = _mm_and_si128(a, v_0x01);
			// a <- v+1	si a == 1
			//		v 	sinon
			a = _mm_add_epi8(V[i][j], a);
			// V <- a
			_mm_store_si128(&V[i][j], a); 

			b = _mm_cmplt_epi8(_mm_sub_epi8(V[i][j+1], v_128), _mm_sub_epi8(It_1[i][j+1], v_128));
			b = _mm_and_si128(b, v_0x01);
			b = _mm_add_epi8(V[i][j+1], b);
			_mm_store_si128(&V[i][j+1], b); 

			// Si V > NxIt_1
			// a <- 255 si V > NxIt_1
			//		0	sinon
			a = _mm_cmplt_epi8(_mm_sub_epi8(It_1[i][j], v_128), _mm_sub_epi8(V[i][j], v_128));
			// a <- 1 	si a == 255
			//		0	sinon
			a = _mm_and_si128(a, v_0x01);
			// a <- V-1	si a == 1
			//		V 	sinon	
			a = _mm_sub_epi8(V[i][j], a);
			// V <- a
			_mm_store_si128(&V[i][j], a); 

			b = _mm_cmplt_epi8(_mm_sub_epi8(It_1[i][j+1], v_128), _mm_sub_epi8(V[i][j+1], v_128));
			b = _mm_and_si128(b, v_0x01);
			b = _mm_sub_epi8(V[i][j+1], b);
			_mm_store_si128(&V[i][j+1], b); 

			// Clamp to [VMIN, VMAX]
			// a <- min(V, VMAX)
			a = _mm_min_epu8(V[i][j], v_vmax);
			// a <- max(a, VMIN)
			a = _mm_max_epu8(a, v_vmin);
			// V <- a
			_mm_store_si128(&V[i][j], a); 

			b = _mm_min_epu8(V[i][j+1], v_vmax);
			b = _mm_max_epu8(b, v_vmin);
			_mm_store_si128(&V[i][j+1], b);
		}
	}

	// Step#4: Et estimation
	for(i = 0; i < size_h; i++)	{
		for(j = 0; j < size_l; j++)	{
			// Si Ot < V 
			// a <-	255	si Ot < V
			//		0	sinon 
			a = _mm_cmplt_epi8(_mm_sub_epi8(Ot[i][j], v_128), _mm_sub_epi8(V[i][j], v_128));
			// a <- 255	si a == 0
			//		0	sinon
			a = _mm_andnot_si128(a, v_255);
			// Et <- a
			_mm_store_si128(&Et[i][j], a);

			b = _mm_cmplt_epi8(_mm_sub_epi8(Ot[i][j+1], v_128), _mm_sub_epi8(V[i][j+1], v_128));
			b = _mm_andnot_si128(b, v_255);
			_mm_store_si128(&Et[i][j+1], b);
		}
	}

	return Et;
}
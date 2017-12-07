/* -----------------------------------------------
	test_car3.h
	Edité par Martin Boisse
	Le 20 Octobre 2018

	Projet SIMD
	Prototype des algorithmes scalaires
	de detection de mouvement (non optimisés)
----------------------------------------------- */
#ifndef __TEST_CAR3_H__
#define __TEST_CAR3_H__

void f_test_mouvement_car3(int nb_images);

uint8_t** copy_pgm_matrix(char* fname, uint8_t** image, int size_h, int size_l);

#endif //__CAR3_H__

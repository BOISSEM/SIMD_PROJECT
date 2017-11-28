/*--------------------------------
    test_morpho_SSE2.c

    Fonctions de tests unitaires et d'intégration des fonctions de
    morphologie mathématique en SIMD

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Kevin Seng - 2017
 ----------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "nrdef.h"
#include "vnrdef.h"
#include "vnrutil.h"

#include "morpho_SSE2.h"
#include "test_morpho_SSE2.h"

void f_test_morpho_sse2()
{
    int card; // cardinal of vector type
    int si0, si1, sj0, sj1;
    int vi0, vi1, vj0, vj1;
    int mi0, mi1;
    vuint8 **img1, **img2;

    int n = 16*4;

    card = card_vuint8();

    si0 = 0 - 2;
    si1 = n-1 + 2;
    s2v(si0, si1, card, &vi0, &vi1);
    v2m(vi0, vi1, card, &mi0, &mi1);

    vX  = vui8matrix(vi0, vi1, vi0, vi1);

    init

}

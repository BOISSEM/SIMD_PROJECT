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

#include "simd_macro.h"
#include "morpho_SSE2.h"
#include "test_morpho_SSE2.h"


void f_test_macro(void)
{
    vuint8 a, b, c, d, e;
    vuint8 au, cu; // unaligned vectorvec_left1
    vuint8 a3, a5; // add3 add5
    puts("------------------");
    puts("--- test_macro ---");
    puts("------------------"); puts("");

    puts("vec_left et vec_right");

    // setr simule le fonctionnement d'un load avec permutation des blocs grace au "r" = reverse
    a = init_vuint8_param(0, 1);
    b = init_vuint8_param(16, 1);
    c = init_vuint8_param(32, 1);
    d = init_vuint8_param(48, 1);
    e = init_vuint8_param(64, 1);

    display_vuint8(a, " %3d ", "a "); puts("");
    display_vuint8(b, " %3d ", "b "); puts("");
    display_vuint8(c, " %3d ", "c "); puts("");
    display_vuint8(d, " %3d ", "d "); puts("");
    display_vuint8(e, " %3d ", "e "); puts("\n");

    au = vec_left1(a, b);
    cu = vec_right1(b, c);
    display_vuint8(au, " %3d ", "au"); puts("");
    display_vuint8(cu, " %3d ", "cu"); puts("\n");

    puts("vec_add3 et vec_add5");
    a3 = vec_add3(a, b, c);
    a5 = vec_add5(a, b, c, d, e);

    display_vuint8(a3, " %3d ", "a3"); puts("");
    display_vuint8(a5, " %3d ", "a5"); puts("\n");
}

void f_test_dilate_bin3_SSE2()
{
    int card; // cardinal of vector type
    int si0, si1, sj0, sj1;
    int si0b, si1b, sj0b, sj1b;
    int vi0, vi1, vj0, vj1;
    int vi0b, vi1b, vj0b, vj1b;
    int mi0, mi1, mj0, mj1;
    vuint8 **img1, **img2;

    int l = 16*2;
    int h = 4;
    int bord = 2;

    card = card_vuint8();

    si0 = 0;        si0b = si0 - bord;
    si1 = h-1;      si1b = si1 + bord;
    sj0 = 0;        sj0b = sj0 - bord;
    sj1 = l-1;      sj1b = sj1 + bord;

    s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
    s2v(si0b, si1b, sj0b, sj1b, card, &vi0b, &vi1b, &vj0b, &vj1b);

    // printf("v : %d %d %d", vi0, vi1, vi0b);
    img1 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    img2 = vui8matrix(vi0b, vi1b, vj0b, vj1b);

    zero_vsi8matrix(img1, vi0b, vi1b, vj0b, vj1b);
    zero_vsi8matrix(img2, vi0b, vi1b, vj0b, vj1b);
    init_vui8matrix_param(img1, vi0, vi1, vj0, vj1, 1, 1, l);

    display_vui8matrix(img1, vi0, vi1, vj0, vj1, " %3d ", "img1 = ");

    dilate_bin3_SSE2(img1, vi1+1, vj1+1, img2);
}

void f_test_morpho_SSE2()
{
    // f_test_macro();
    f_test_dilate_bin3_SSE2();
}

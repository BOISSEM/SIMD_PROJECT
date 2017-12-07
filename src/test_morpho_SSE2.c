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
#include <x86intrin.h>

#include "debug_macro.h"

#include "nrdef.h"
#include "vnrdef.h"
#include "vnrutil.h"

#include "simd_macro.h"
#include "morpho_SSE2.h"
#include "morpho_SSE2_opt.h"
#include "test_morpho_SSE2.h"

void f_test_macro(void)
{
    vuint8 a, b, c, d, e;
    vuint8 au, cu; // unaligned vectorvec_left1
    vuint8 a3, a5; // add3 add5
    vuint8 am3, am5;
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

void f_test_dilate3_SSE2()
{
    int i0, i1;
    int card; // cardinal of vector type
    int si0, si1, sj0, sj1;
    int si0b, si1b, sj0b, sj1b;
    int vi0, vi1, vj0, vj1;
    int vi0b, vi1b, vj0b, vj1b;
    int mi0, mi1, mj0, mj1;
    vuint8 **img1, **img2;

    card = card_vuint8();
    int l = card * 3;
    int h = 4;
    int bord_i = 1;
    int bord_j = 0;

    si0 = 0;        si0b = si0 - bord_i;
    si1 = h-1;      si1b = si1 + bord_i;
    sj0 = 0;        sj0b = sj0 - bord_j;
    sj1 = l-1;      sj1b = sj1 + bord_j;

    s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
    s2v(si0b, si1b, sj0b, sj1b, card, &vi0b, &vi1b, &vj0b, &vj1b);

    // printf("v : %d %d %d", vi0, vi1, vi0b);
    img1 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    img2 = vui8matrix(vi0b, vi1b, vj0b, vj1b);

    /* Bords haut et bas */
    i1 = vi1b;
    for(i0 = vi0b; i0<vi0; i0++){
        img1[i0] = img1[vi0];
        img2[i0] = img2[vi0];
        img1[i1] = img1[vi1];
        img2[i1] = img2[vi1];
        i1--;
    }

    zero_vui8matrix(img1, vi0, vi1, vj0b, vj1b);
    zero_vui8matrix(img2, vi0b, vi1b, vj0b, vj1b);
    init_vui8matrix_param(img1, vi0, vi1, vj0, vj1, 1, 1, 2);

    DEBUG(display_vui8matrix(img1, vi0b, vi1b, vj0b, vj1b, "%3d", "img1 (+bords) = "));
    DEBUG(display_vui8matrix(img1, vi0, vi1, vj0, vj1, "%3d", "img1 = "));


    // printf("Dilate SSE2 : \n"); dilate3_SSE2(img1, vi1+1, vj1+1, img2);
    printf("Dilate SSE2 optimisé : \n"); dilate3_SSE2_opt(img1, vi1+1, vj1+1, img2);

    DEBUG(display_vui8matrix(img2, vi0, vi1, vj0, vj1, "%3d", "img2 = "));


}

void f_test_erode3_SSE2()
{
    int i0, i1;
    int card; // cardinal of vector type
    int si0, si1, sj0, sj1;
    int si0b, si1b, sj0b, sj1b;
    int vi0, vi1, vj0, vj1;
    int vi0b, vi1b, vj0b, vj1b;
    int mi0, mi1, mj0, mj1;
    vuint8 **img1, **img2;

    card = card_vuint8();
    int l = card * 3;
    int h = 4;
    int bord_i = 1;
    int bord_j = 0;

    si0 = 0;        si0b = si0 - bord_i;
    si1 = h-1;      si1b = si1 + bord_i;
    sj0 = 0;        sj0b = sj0 - bord_j;
    sj1 = l-1;      sj1b = sj1 + bord_j;

    s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
    s2v(si0b, si1b, sj0b, sj1b, card, &vi0b, &vi1b, &vj0b, &vj1b);

    // printf("v : %d %d %d", vi0, vi1, vi0b);
    img1 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    img2 = vui8matrix(vi0b, vi1b, vj0b, vj1b);

    /* Bords haut et bas */
    i1 = vi1b;
    for(i0 = vi0b; i0<vi0; i0++){
        img1[i0] = img1[vi0];
        img2[i0] = img2[vi0];
        img1[i1] = img1[vi1];
        img2[i1] = img2[vi1];
        i1--;
    }

    zero_vui8matrix(img1, vi0, vi1, vj0b, vj1b);
    zero_vui8matrix(img2, vi0b, vi1b, vj0b, vj1b);
    init_vui8matrix_param(img1, vi0, vi1, vj0, vj1, 1, 1, 2);

    DEBUG(display_vui8matrix(img1, vi0b, vi1b, vj0b, vj1b, "%3d", "img1 (+bords) = "));
    DEBUG(display_vui8matrix(img1, vi0, vi1, vj0, vj1, "%3d", "img1 = "));

    printf("Erode SSE2 : \n"); erode3_SSE2(img1, vi1+1, vj1+1, img2);
    // printf("Erode SSE2 optimisé : \n"); erode3_SSE2_opt(img1, vi1+1, vj1+1, img2);

    display_vui8matrix(img2, vi0, vi1, vj0, vj1, "%3d", "img2 = ");
}

void f_test_open3_SSE2()
{
    int i0, i1;
    int card; // cardinal of vector type
    int si0, si1, sj0, sj1;
    int si0b, si1b, sj0b, sj1b;
    int vi0, vi1, vj0, vj1;
    int vi0b, vi1b, vj0b, vj1b;
    int mi0, mi1, mj0, mj1;
    vuint8 **img1, **img2, **buffer;

    // char *format     = "%6.2f ";
    // int iter, niter = 100;
    // int run, nrun = 100;
    // double t0, t1, dt, tmin, t;
    // double cycles;

    card = card_vuint8();
    int l = card * 3;
    int h = 8;
    int bord_i = 1;
    int bord_j = 0;

    si0 = 0;        si0b = si0 - bord_i;
    si1 = h-1;      si1b = si1 + bord_i;
    sj0 = 0;        sj0b = sj0 - bord_j;
    sj1 = l-1;      sj1b = sj1 + bord_j;

    s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
    s2v(si0b, si1b, sj0b, sj1b, card, &vi0b, &vi1b, &vj0b, &vj1b);

    // printf("v : %d %d %d", vi0, vi1, vi0b);
    img1 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    img2 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    buffer = vui8matrix(vi0b, vi1b, vj0b, vj1b);


    /* Bords haut (i0) et bas (i1) */
    i1 = vi1b;
    for(i0 = vi0b; i0<vi0; i0++){
        img1[i0] = img1[vi0];
        img2[i0] = img2[vi0];
        img1[i1] = img1[vi1];
        img2[i1] = img2[vi1];
        buffer[i0] = buffer[vi0];
        buffer[i1] = buffer[vj0];
        i1--;
    }

    zero_vui8matrix(img1, vi0, vi1, vj0b, vj1b);
    zero_vui8matrix(img2, vi0b, vi1b, vj0b, vj1b);
    init_vui8matrix_param(img1, vi0, (vi1/2), vj0, vj1, 1, 1, 2);
    init_vui8matrix_param(img1, (vi1/2)+1, vi1, vj0, vj1, 0, 2, 1);

    DEBUG(display_vui8matrix(img1, vi0b, vi1b, vj0b, vj1b, "%3d", "img1 (+bords) = "));
    DEBUG(display_vui8matrix(img1, vi0, vi1, vj0, vj1, "%3d", "img1 = "));

    // printf("Open SSE2 : \n"); open3_SSE2(img1, vi1+1, vj1+1, img2, buffer);
    // printf("Open SSE2 optimisé : \n"); open3_SSE2_opt(img1, vi1+1, vj1+1, img2, buffer);
    printf("Open SSE2 No pipe : \n"); open3_SSE2_opt_no_pipe(img1, vi1+1, vj1+1, img2, buffer);

    DEBUG(display_vui8matrix(buffer, vi0, vi1, vj0, vj1, "%3d", "buffer = "));
    DEBUG(display_vui8matrix(img2, vi0, vi1, vj0, vj1, "%3d", "img2 = "));
}

void f_test_close3_SSE2()
{
    int i0, i1;
    int card; // cardinal of vector type
    int si0, si1, sj0, sj1;
    int si0b, si1b, sj0b, sj1b;
    int vi0, vi1, vj0, vj1;
    int vi0b, vi1b, vj0b, vj1b;
    int mi0, mi1, mj0, mj1;
    vuint8 **img1, **img2, **buffer;

    char *format     = "%6.2f ";

    // int iter, niter = 100;
    // int run, nrun = 100;
    // double t0, t1, dt, tmin, t;
    // double cycles;

    card = card_vuint8();
    int l = card * 2;
    int h = 8;
    int bord_i = 1;
    int bord_j = 0;

    si0 = 0;        si0b = si0 - bord_i;
    si1 = h-1;      si1b = si1 + bord_i;
    sj0 = 0;        sj0b = sj0 - bord_j;
    sj1 = l-1;      sj1b = sj1 + bord_j;

    s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
    s2v(si0b, si1b, sj0b, sj1b, card, &vi0b, &vi1b, &vj0b, &vj1b);

    // printf("v : %d %d %d", vi0, vi1, vi0b);
    img1 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    img2 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    buffer = vui8matrix(vi0b, vi1b, vj0b, vj1b);

    /* Bords haut et bas */
    i1 = vi1b;
    for(i0 = vi0b; i0<vi0; i0++){
        img1[i0] = img1[vi0];
        img2[i0] = img2[vi0];
        img1[i1] = img1[vi1];
        img2[i1] = img2[vi1];
        buffer[i0] = buffer[vi0];
        buffer[i1] = buffer[vj0];
        i1--;
    }

    zero_vui8matrix(img1, vi0, vi1, vj0b, vj1b);
    zero_vui8matrix(img2, vi0b, vi1b, vj0b, vj1b);
    init_vui8matrix_param(img1, vi0, (vi1/2), vj0, vj1, 1, 1, 2);
    init_vui8matrix_param(img1, (vi1/2)+1, vi1, vj0, vj1, 0, 2, 1);

    DEBUG(display_vui8matrix(img1, vi0b, vi1b, vj0b, vj1b, "%3d", "img1 (+bords) = "));
    DEBUG(display_vui8matrix(img1, vi0, vi1, vj0, vj1, "%3d", "img1 = "));

    printf("Close SSE2 : \n"); close3_SSE2(img1, vi1+1, vj1+1, img2, buffer);
    // printf("Close SSE2 optimisé : \n"); close3_SSE2_opt(img1, vi1+1, vj1+1, img2, buffer);

    display_vui8matrix(img2, vi0, vi1, vj0, vj1, "%3d", "img2 = ");
}

void f_test_dilate5_SSE2()
{
    int i0, i1;
    int card; // cardinal of vector type
    int si0, si1, sj0, sj1;
    int si0b, si1b, sj0b, sj1b;
    int vi0, vi1, vj0, vj1;
    int vi0b, vi1b, vj0b, vj1b;
    int mi0, mi1, mj0, mj1;
    vuint8 **img1, **img2;

    card = card_vuint8();
    int l = card * 2;
    int h = 6;
    int bord_i = 2;
    int bord_j = 1;

    si0 = 0;        si0b = si0 - bord_i;
    si1 = h-1;      si1b = si1 + bord_i;
    sj0 = 0;        sj0b = sj0 - bord_j;
    sj1 = l-1;      sj1b = sj1 + bord_j;

    s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
    s2v(si0b, si1b, sj0b, sj1b, card, &vi0b, &vi1b, &vj0b, &vj1b);

    // printf("v : %d %d %d", vi0, vi1, vi0b);
    img1 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    img2 = vui8matrix(vi0b, vi1b, vj0b, vj1b);

    /* Bords haut et bas */
    i1 = vi1b;
    for(i0 = vi0b; i0<vi0; i0++){
        img1[i0] = img1[vi0];
        img2[i0] = img2[vi0];
        img1[i1] = img1[vi1];
        img2[i1] = img2[vi1];
        i1--;
    }

    zero_vui8matrix(img1, vi0, vi1, vj0b, vj1b);
    zero_vui8matrix(img2, vi0b, vi1b, vj0b, vj1b);
    init_vui8matrix_param(img1, vi0, vi1, vj0, vj1, 1, 1, 2);

    DEBUG(display_vui8matrix(img1, vi0b, vi1b, vj0b, vj1b, "%3d", "img1 (+bords) = "));
    DEBUG(display_vui8matrix(img1, vi0, vi1, vj0, vj1, "%3d", "img1 = "));


    // printf("Dilate5 SSE2 : \n"); dilate5_SSE2(img1, vi1+1, vj1+1, img2);
    printf("Dilate5 SSE2 optimisé : \n"); dilate5_SSE2_opt(img1, vi1+1, vj1+1, img2);

    display_vui8matrix(img2, vi0, vi1, vj0, vj1, "%3d", "img2 = ");
}

void f_test_erode5_SSE2()
{
    int i0, i1;
    int card; // cardinal of vector type
    int si0, si1, sj0, sj1;
    int si0b, si1b, sj0b, sj1b;
    int vi0, vi1, vj0, vj1;
    int vi0b, vi1b, vj0b, vj1b;
    int mi0, mi1, mj0, mj1;
    vuint8 **img1, **img2;

    card = card_vuint8();
    int l = card * 2;
    int h = 6;
    int bord_i = 2;
    int bord_j = 1;

    si0 = 0;        si0b = si0 - bord_i;
    si1 = h-1;      si1b = si1 + bord_i;
    sj0 = 0;        sj0b = sj0 - bord_j;
    sj1 = l-1;      sj1b = sj1 + bord_j;

    s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
    s2v(si0b, si1b, sj0b, sj1b, card, &vi0b, &vi1b, &vj0b, &vj1b);

    // printf("v : %d %d %d", vi0, vi1, vi0b);
    img1 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    img2 = vui8matrix(vi0b, vi1b, vj0b, vj1b);

    /* Bords haut et bas */
    i1 = vi1b;
    for(i0 = vi0b; i0<vi0; i0++){
        img1[i0] = img1[vi0];
        img2[i0] = img2[vi0];
        img1[i1] = img1[vi1];
        img2[i1] = img2[vi1];
        i1--;
    }

    zero_vui8matrix(img1, vi0, vi1, vj0b, vj1b);
    zero_vui8matrix(img2, vi0b, vi1b, vj0b, vj1b);
    init_vui8matrix_param(img1, vi0, vi1, vj0, vj1, 1, 1, 2);

    DEBUG(display_vui8matrix(img1, vi0b, vi1b, vj0b, vj1b, "%3d", "img1 (+bords) = "));
    DEBUG(display_vui8matrix(img1, vi0, vi1, vj0, vj1, "%3d", "img1 = "));


    printf("Erode5 SSE2 : \n"); erode5_SSE2(img1, vi1+1, vj1+1, img2);
    // printf("Erode5 SSE2 optimisé : \n"); erode5_SSE2_opt(img1, vi1+1, vj1+1, img2);

    display_vui8matrix(img2, vi0, vi1, vj0, vj1, "%3d", "img2 = ");
}

void f_test_open5_SSE2()
{
    int i0, i1;
    int card; // cardinal of vector type
    int si0, si1, sj0, sj1;
    int si0b, si1b, sj0b, sj1b;
    int vi0, vi1, vj0, vj1;
    int vi0b, vi1b, vj0b, vj1b;
    int mi0, mi1, mj0, mj1;
    vuint8 **img1, **img2, **buffer;

    card = card_vuint8();
    int l = card * 2;
    int h = 8;
    int bord_i = 2;
    int bord_j = 1;

    si0 = 0;        si0b = si0 - bord_i;
    si1 = h-1;      si1b = si1 + bord_i;
    sj0 = 0;        sj0b = sj0 - bord_j;
    sj1 = l-1;      sj1b = sj1 + bord_j;

    s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
    s2v(si0b, si1b, sj0b, sj1b, card, &vi0b, &vi1b, &vj0b, &vj1b);

    // printf("v : %d %d %d", vi0, vi1, vi0b);
    img1 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    img2 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    buffer = vui8matrix(vi0b, vi1b, vj0b, vj1b);

    /* Bords haut et bas */
    i1 = vi1b;
    for(i0 = vi0b; i0<vi0; i0++){
        img1[i0] = img1[vi0];
        img2[i0] = img2[vi0];
        img1[i1] = img1[vi1];
        img2[i1] = img2[vi1];
        buffer[i0] = buffer[vi0];
        buffer[i1] = buffer[vj0];
        i1--;
    }

    zero_vui8matrix(img1, vi0, vi1, vj0b, vj1b);
    zero_vui8matrix(img2, vi0b, vi1b, vj0b, vj1b);
    init_vui8matrix_param(img1, vi0, (vi1/2), vj0, vj1, 1, 1, 2);
    init_vui8matrix_param(img1, (vi1/2)+1, vi1, vj0, vj1, 0, 2, 1);

    DEBUG(display_vui8matrix(img1, vi0b, vi1b, vj0b, vj1b, "%3d", "img1 (+bords) = "));
    DEBUG(display_vui8matrix(img1, vi0, vi1, vj0, vj1, "%3d", "img1 = "));

    printf("Open5 SSE2 : \n"); open5_SSE2(img1, vi1+1, vj1+1, img2, buffer);
    // printf("Open5 SSE2 optimisé : \n"); open5_SSE2_opt(img1, vi1+1, vj1+1, img2, buffer);

    display_vui8matrix(img2, vi0, vi1, vj0, vj1, "%3d", "img2 = ");
}

void f_test_close5_SSE2()
{
    int i0, i1;
    int card; // cardinal of vector type
    int si0, si1, sj0, sj1;
    int si0b, si1b, sj0b, sj1b;
    int vi0, vi1, vj0, vj1;
    int vi0b, vi1b, vj0b, vj1b;
    int mi0, mi1, mj0, mj1;
    vuint8 **img1, **img2, **buffer;

    card = card_vuint8();
    int l = card * 2;
    int h = 8;
    int bord_i = 2;
    int bord_j = 1;

    si0 = 0;        si0b = si0 - bord_i;
    si1 = h-1;      si1b = si1 + bord_i;
    sj0 = 0;        sj0b = sj0 - bord_j;
    sj1 = l-1;      sj1b = sj1 + bord_j;

    s2v(si0, si1, sj0, sj1, card, &vi0, &vi1, &vj0, &vj1);
    s2v(si0b, si1b, sj0b, sj1b, card, &vi0b, &vi1b, &vj0b, &vj1b);

    // printf("v : %d %d %d", vi0, vi1, vi0b);
    img1 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    img2 = vui8matrix(vi0b, vi1b, vj0b, vj1b);
    buffer = vui8matrix(vi0b, vi1b, vj0b, vj1b);

    /* Bords haut et bas */
    i1 = vi1b;
    for(i0 = vi0b; i0<vi0; i0++){
        img1[i0] = img1[vi0];
        img2[i0] = img2[vi0];
        img1[i1] = img1[vi1];
        img2[i1] = img2[vi1];
        buffer[i0] = buffer[vi0];
        buffer[i1] = buffer[vj0];
        i1--;
    }

    zero_vui8matrix(img1, vi0, vi1, vj0b, vj1b);
    zero_vui8matrix(img2, vi0b, vi1b, vj0b, vj1b);
    init_vui8matrix_param(img1, vi0, (vi1/2), vj0, vj1, 1, 1, 2);
    init_vui8matrix_param(img1, (vi1/2)+1, vi1, vj0, vj1, 0, 2, 1);

    DEBUG(display_vui8matrix(img1, vi0b, vi1b, vj0b, vj1b, "%3d", "img1 (+bords) = "));
    DEBUG(display_vui8matrix(img1, vi0, vi1, vj0, vj1, "%3d", "img1 = "));

    // printf("Close5 SSE2 : \n"); close5_SSE2(img1, vi1+1, vj1+1, img2, buffer);
    // printf("Close5 SSE2 optimisé : \n"); close5_SSE2_opt(img1, vi1+1, vj1+1, img2, buffer);

    display_vui8matrix(img2, vi0, vi1, vj0, vj1, "%3d", "img2 = ");
}

void f_test_morpho_SSE2()
{
    /* Fonction test de macros SIMD */
    // f_test_macro();

    /* Tests 3x3 */
    // f_test_dilate3_SSE2();
    // f_test_erode3_SSE2();
    f_test_open3_SSE2();
    // f_test_close3_SSE2();

<<<<<<< HEAD
}
=======
    /* Tests 5x5 */
    // f_test_dilate5_SSE2();
    // f_test_erode5_SSE2();
    // f_test_open5_SSE2();
    // f_test_close5_SSE2();
}
>>>>>>> morpho_1

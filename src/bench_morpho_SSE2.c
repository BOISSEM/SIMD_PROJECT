/*--------------------------------
    bench_morpho_SSE2.c

    Evaluation des performances des fonctions de morphologie mathematiques
    SIMD

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Kevin Seng - 2017
 ----------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>
#include <time.h>

#include "debug_macro.h"

#include "nrdef.h"
#include "nrutil.h"
#include "vnrdef.h"
#include "vnrutil.h"

#include "morpho_SSE2.h"
#include "morpho_SSE2_opt.h"
#include "bench_morpho_SSE2.h"


void f_bench_dilate3_SSE2(int nb_images)
{
    int i, i0, i1;

    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD/";
    char* path_file_out = "img/car3_SD_dilate3_SSE2/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord_i = 1, bord_j = 0;
    uint8_t **img_0, **img_out;

    int card;
    int nrl, nrh, ncl, nch;
    int vnrl, vnrh, vncl, vnch;
    int vnrl_b, vnrh_b, vncl_b, vnch_b;
    vuint8 **v_img_0, **v_img_out;

    card = card_vuint8();

    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    img_in_name = (char*) calloc(80, sizeof(char));
    img_out_name = (char*) calloc(80, sizeof(char));

    generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb, 4, extension, img_in_name);
    LoadPGM_ui8matrix(img_in_name, (long*)&nrl, (long*)&nrh, (long*)&ncl, (long*)&nch);

    s2v(nrl, nrh, ncl, nch, card, &vnrl, &vnrh, &vncl, &vnch);
    s2v(nrl-bord_i, nrh+bord_i, ncl-bord_j, nch+bord_j, card, &vnrl_b, &vnrh_b, &vncl_b, &vnch_b);

    v_img_0 = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_img_out = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);

    /* Bords haut et bas */
    i1 = vnrh;
    for(i0 = vnrl-bord_i; i0<vnrl; i0++){
        v_img_0[i0] = v_img_0[vnrl];
        v_img_out[i0] = v_img_out[vnrl];
        v_img_0[i1] = v_img_0[vnrh];
        v_img_out[i1] = v_img_out[vnrh];
        i1--;
    }

    img_0 = (uint8**)v_img_0;
    img_out = (uint8**)v_img_out;

    // i = 0;
    for(i=0; i<=nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        BENCH(printf("Dilatation3 SSE2: "));
        CHRONO(dilate3_SSE2(v_img_0, vnrh, vnch, v_img_out),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));
        // CHRONO(dilate_bin3_SSE2(v_img_0, vnrh, vnch, v_img_out),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}

void f_bench_dilate5_SSE2(int nb_images)
{
    int i, i0, i1;

    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD/";
    char* path_file_out = "img/car3_SD_dilate5_SSE2/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord_i = 2, bord_j = 0;
    uint8_t **img_0, **img_out;

    int card;
    int nrl, nrh, ncl, nch;
    int vnrl, vnrh, vncl, vnch;
    int vnrl_b, vnrh_b, vncl_b, vnch_b;
    vuint8 **v_img_0, **v_img_out;

    card = card_vuint8();

    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    img_in_name = (char*) calloc(80, sizeof(char));
    img_out_name = (char*) calloc(80, sizeof(char));

    generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb, 4, extension, img_in_name);
    LoadPGM_ui8matrix(img_in_name, (long*)&nrl, (long*)&nrh, (long*)&ncl, (long*)&nch);

    s2v(nrl, nrh, ncl, nch, card, &vnrl, &vnrh, &vncl, &vnch);
    s2v(nrl-bord_i, nrh+bord_i, ncl-bord_j, nch+bord_j, card, &vnrl_b, &vnrh_b, &vncl_b, &vnch_b);

    v_img_0 = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_img_out = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);

    /* Bords haut et bas */
    i1 = vnrh;
    for(i0 = vnrl-bord_i; i0<vnrl; i0++){
        v_img_0[i0] = v_img_0[vnrl];
        v_img_out[i0] = v_img_out[vnrl];
        v_img_0[i1] = v_img_0[vnrh];
        v_img_out[i1] = v_img_out[vnrh];
        i1--;
    }

    img_0 = (uint8**)v_img_0;
    img_out = (uint8**)v_img_out;

    // i = 0;
    for(i=0; i<=nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        BENCH(printf("Dilatation5 SSE2: "));
        CHRONO(dilate5_SSE2(v_img_0, vnrh, vnch, v_img_out),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));
        // CHRONO(dilate_bin5_SSE2(v_img_0, vnrh, vnch, v_img_out),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}

void f_bench_dilate3_SSE2_opt(int nb_images)
{
    int i, i0, i1;

    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD/";
    char* path_file_out = "img/car3_SD_dilate3_SSE2_opt/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord_i = 1, bord_j = 0;
    uint8_t **img_0, **img_out;

    int card;
    int nrl, nrh, ncl, nch;
    int vnrl, vnrh, vncl, vnch;
    int vnrl_b, vnrh_b, vncl_b, vnch_b;
    vuint8 **v_img_0, **v_img_out;

    card = card_vuint8();

    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    img_in_name = (char*) calloc(80, sizeof(char));
    img_out_name = (char*) calloc(80, sizeof(char));

    generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb, 4, extension, img_in_name);
    LoadPGM_ui8matrix(img_in_name, (long*)&nrl, (long*)&nrh, (long*)&ncl, (long*)&nch);

    s2v(nrl, nrh, ncl, nch, card, &vnrl, &vnrh, &vncl, &vnch);
    s2v(nrl-bord_i, nrh+bord_i, ncl-bord_j, nch+bord_j, card, &vnrl_b, &vnrh_b, &vncl_b, &vnch_b);

    v_img_0 = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_img_out = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);

    /* Bords haut et bas */
    i1 = vnrh;
    for(i0 = vnrl-bord_i; i0<vnrl; i0++){
        v_img_0[i0] = v_img_0[vnrl];
        v_img_out[i0] = v_img_out[vnrl];
        v_img_0[i1] = v_img_0[vnrh];
        v_img_out[i1] = v_img_out[vnrh];
        i1--;
    }

    img_0 = (uint8**)v_img_0;
    img_out = (uint8**)v_img_out;

    // i = 0;
    for(i=0; i<=nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        BENCH(printf("Dilatation3 SSE2 optimise: "));
        CHRONO(dilate3_SSE2_opt(v_img_0, vnrh, vnch, v_img_out),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));
        // CHRONO(dilate_bin3_SSE2_opt(v_img_0, vnrh, vnch, v_img_out),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}

void f_bench_dilate5_SSE2_opt(int nb_images)
{
    int i, i0, i1;

    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD/";
    char* path_file_out = "img/car3_SD_dilate5_SSE2_opt/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord_i = 2, bord_j = 0;
    uint8_t **img_0, **img_out;

    int card;
    int nrl, nrh, ncl, nch;
    int vnrl, vnrh, vncl, vnch;
    int vnrl_b, vnrh_b, vncl_b, vnch_b;
    vuint8 **v_img_0, **v_img_out;

    card = card_vuint8();

    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    img_in_name = (char*) calloc(80, sizeof(char));
    img_out_name = (char*) calloc(80, sizeof(char));

    generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb, 4, extension, img_in_name);
    LoadPGM_ui8matrix(img_in_name, (long*)&nrl, (long*)&nrh, (long*)&ncl, (long*)&nch);

    s2v(nrl, nrh, ncl, nch, card, &vnrl, &vnrh, &vncl, &vnch);
    s2v(nrl-bord_i, nrh+bord_i, ncl-bord_j, nch+bord_j, card, &vnrl_b, &vnrh_b, &vncl_b, &vnch_b);

    v_img_0 = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_img_out = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);

    /* Bords haut et bas */
    i1 = vnrh;
    for(i0 = vnrl-bord_i; i0<vnrl; i0++){
        v_img_0[i0] = v_img_0[vnrl];
        v_img_out[i0] = v_img_out[vnrl];
        v_img_0[i1] = v_img_0[vnrh];
        v_img_out[i1] = v_img_out[vnrh];
        i1--;
    }

    img_0 = (uint8**)v_img_0;
    img_out = (uint8**)v_img_out;

    // i = 0;
    for(i=0; i<=nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        BENCH(printf("Dilatation5 SSE2 optimise: "));
        CHRONO(dilate5_SSE2_opt(v_img_0, vnrh, vnch, v_img_out),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));
        // CHRONO(dilate_bin5_SSE2_opt(v_img_0, vnrh, vnch, v_img_out),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}

void f_bench_open3_SSE2(int nb_images)
{
    int i, i0, i1;

    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD/";
    char* path_file_out = "img/car3_SD_open3_SSE2/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord_i = 1, bord_j = 0;
    uint8_t **img_0, **img_out;

    int card;
    int nrl, nrh, ncl, nch;
    int vnrl, vnrh, vncl, vnch;
    int vnrl_b, vnrh_b, vncl_b, vnch_b;
    vuint8 **v_img_0, **v_img_out, **v_buffer;

    card = card_vuint8();

    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    img_in_name = (char*) calloc(80, sizeof(char));
    img_out_name = (char*) calloc(80, sizeof(char));

    generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb, 4, extension, img_in_name);
    LoadPGM_ui8matrix(img_in_name, (long*)&nrl, (long*)&nrh, (long*)&ncl, (long*)&nch);

    s2v(nrl, nrh, ncl, nch, card, &vnrl, &vnrh, &vncl, &vnch);
    s2v(nrl-bord_i, nrh+bord_i, ncl-bord_j, nch+bord_j, card, &vnrl_b, &vnrh_b, &vncl_b, &vnch_b);

    v_img_0 = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_img_out = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_buffer = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);

    /* Bords haut et bas */
    i1 = vnrh;
    for(i0 = vnrl_b; i0<vnrl; i0++){
        v_img_0[i0] = v_img_0[vnrl];
        v_img_out[i0] = v_img_out[vnrl];
        v_img_0[i1] = v_img_0[vnrh];
        v_img_out[i1] = v_img_out[vnrh];
        i1--;
    }

    img_0 = (uint8**)v_img_0;
    img_out = (uint8**)v_img_out;

    // i = 0;
    for(i=0; i<=nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        BENCH(printf("Ouverture3 SSE2: "));
        CHRONO(open3_SSE2(v_img_0, vnrh, vnch, v_img_out, v_buffer),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));
        // CHRONO(open_bin3_SSE2(v_img_0, vnrh, vnch, v_img_out, v_buffer),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}

void f_bench_open3_SSE2_opt(int nb_images)
{
    int i, i0, i1;

    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD/";
    char* path_file_out = "img/car3_SD_open3_SSE2_opt/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord_i = 1, bord_j = 0;
    uint8_t **img_0, **img_out;

    int card;
    int nrl, nrh, ncl, nch;
    int vnrl, vnrh, vncl, vnch;
    int vnrl_b, vnrh_b, vncl_b, vnch_b;
    vuint8 **v_img_0, **v_img_out, **v_buffer;

    card = card_vuint8();

    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    img_in_name = (char*) calloc(80, sizeof(char));
    img_out_name = (char*) calloc(80, sizeof(char));

    generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb, 4, extension, img_in_name);
    LoadPGM_ui8matrix(img_in_name, (long*)&nrl, (long*)&nrh, (long*)&ncl, (long*)&nch);

    s2v(nrl, nrh, ncl, nch, card, &vnrl, &vnrh, &vncl, &vnch);
    s2v(nrl-bord_i, nrh+bord_i, ncl-bord_j, nch+bord_j, card, &vnrl_b, &vnrh_b, &vncl_b, &vnch_b);

    v_img_0 = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_img_out = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_buffer = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);

    /* Bords haut et bas */
    i1 = vnrh;
    for(i0 = vnrl_b; i0<vnrl; i0++){
        v_img_0[i0] = v_img_0[vnrl];
        v_img_out[i0] = v_img_out[vnrl];
        v_img_0[i1] = v_img_0[vnrh];
        v_img_out[i1] = v_img_out[vnrh];
        i1--;
    }

    img_0 = (uint8**)v_img_0;
    img_out = (uint8**)v_img_out;

    // i = 0;
    for(i=0; i<=nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        BENCH(printf("Ouverture3 SSE2 optimise: "));
        CHRONO(open3_SSE2_opt(v_img_0, vnrh, vnch, v_img_out,v_buffer),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));
        // CHRONO(open_bin3_SSE2_opt(v_img_0, vnrh, vnch, v_img_out, v_buffer),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}

void f_bench_open3_SSE2_opt_no_pipe(int nb_images)
{
    int i, i0, i1;

    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD/";
    char* path_file_out = "img/car3_SD_open3_SSE2_opt_no_pipe/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord_i = 1, bord_j = 0;
    uint8_t **img_0, **img_out;

    int card;
    int nrl, nrh, ncl, nch;
    int vnrl, vnrh, vncl, vnch;
    int vnrl_b, vnrh_b, vncl_b, vnch_b;
    vuint8 **v_img_0, **v_img_out, **v_buffer;

    card = card_vuint8();

    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    img_in_name = (char*) calloc(80, sizeof(char));
    img_out_name = (char*) calloc(80, sizeof(char));

    generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb, 4, extension, img_in_name);
    LoadPGM_ui8matrix(img_in_name, (long*)&nrl, (long*)&nrh, (long*)&ncl, (long*)&nch);

    s2v(nrl, nrh, ncl, nch, card, &vnrl, &vnrh, &vncl, &vnch);
    s2v(nrl-bord_i, nrh+bord_i, ncl-bord_j, nch+bord_j, card, &vnrl_b, &vnrh_b, &vncl_b, &vnch_b);

    v_img_0 = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_img_out = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_buffer = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);

    /* Bords haut et bas */
    i1 = vnrh;
    for(i0 = vnrl_b; i0<vnrl; i0++){
        v_img_0[i0] = v_img_0[vnrl];
        v_img_out[i0] = v_img_out[vnrl];
        v_img_0[i1] = v_img_0[vnrh];
        v_img_out[i1] = v_img_out[vnrh];
        i1--;
    }

    img_0 = (uint8**)v_img_0;
    img_out = (uint8**)v_img_out;

    // i = 0;
    for(i=0; i<=nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        BENCH(printf("Ouverture3 SSE2 optimise (sans pipeline): "));
        CHRONO(open3_SSE2_opt_no_pipe(v_img_0, vnrh, vnch, v_img_out,v_buffer),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));
        // CHRONO(open_bin3_SSE2_opt_no_pipe(v_img_0, vnrh, vnch, v_img_out, v_buffer),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}

void f_bench_open5_SSE2(int nb_images)
{
    int i, i0, i1;

    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD/";
    char* path_file_out = "img/car3_SD_open5_SSE2/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord_i = 2, bord_j = 0;
    uint8_t **img_0, **img_out;

    int card;
    int nrl, nrh, ncl, nch;
    int vnrl, vnrh, vncl, vnch;
    int vnrl_b, vnrh_b, vncl_b, vnch_b;
    vuint8 **v_img_0, **v_img_out, **v_buffer;

    card = card_vuint8();

    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    img_in_name = (char*) calloc(80, sizeof(char));
    img_out_name = (char*) calloc(80, sizeof(char));

    generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb, 4, extension, img_in_name);
    LoadPGM_ui8matrix(img_in_name, (long*)&nrl, (long*)&nrh, (long*)&ncl, (long*)&nch);

    s2v(nrl, nrh, ncl, nch, card, &vnrl, &vnrh, &vncl, &vnch);
    s2v(nrl-bord_i, nrh+bord_i, ncl-bord_j, nch+bord_j, card, &vnrl_b, &vnrh_b, &vncl_b, &vnch_b);

    v_img_0 = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_img_out = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_buffer = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);

    /* Bords haut et bas */
    i1 = vnrh;
    for(i0 = vnrl_b; i0<vnrl; i0++){
        v_img_0[i0] = v_img_0[vnrl];
        v_img_out[i0] = v_img_out[vnrl];
        v_img_0[i1] = v_img_0[vnrh];
        v_img_out[i1] = v_img_out[vnrh];
        i1--;
    }

    img_0 = (uint8**)v_img_0;
    img_out = (uint8**)v_img_out;

    // i = 0;
    for(i=0; i<=nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        BENCH(printf("Ouverture5 SSE2: "));
        CHRONO(open5_SSE2(v_img_0, vnrh, vnch, v_img_out, v_buffer),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));
        // CHRONO(open_bin3_SSE2(v_img_0, vnrh, vnch, v_img_out, v_buffer),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}


void f_bench_open5_SSE2_opt(int nb_images)
{
    int i, i0, i1;

    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD/";
    char* path_file_out = "img/car3_SD_open5_SSE2_opt/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord_i = 2, bord_j = 0;
    uint8_t **img_0, **img_out;

    int card;
    int nrl, nrh, ncl, nch;
    int vnrl, vnrh, vncl, vnch;
    int vnrl_b, vnrh_b, vncl_b, vnch_b;
    vuint8 **v_img_0, **v_img_out, **v_buffer;

    card = card_vuint8();

    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    img_in_name = (char*) calloc(80, sizeof(char));
    img_out_name = (char*) calloc(80, sizeof(char));

    generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb, 4, extension, img_in_name);
    LoadPGM_ui8matrix(img_in_name, (long*)&nrl, (long*)&nrh, (long*)&ncl, (long*)&nch);

    s2v(nrl, nrh, ncl, nch, card, &vnrl, &vnrh, &vncl, &vnch);
    s2v(nrl-bord_i, nrh+bord_i, ncl-bord_j, nch+bord_j, card, &vnrl_b, &vnrh_b, &vncl_b, &vnch_b);

    v_img_0 = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_img_out = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_buffer = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);

    /* Bords haut et bas */
    i1 = vnrh;
    for(i0 = vnrl_b; i0<vnrl; i0++){
        v_img_0[i0] = v_img_0[vnrl];
        v_img_out[i0] = v_img_out[vnrl];
        v_img_0[i1] = v_img_0[vnrh];
        v_img_out[i1] = v_img_out[vnrh];
        i1--;
    }

    img_0 = (uint8**)v_img_0;
    img_out = (uint8**)v_img_out;

    // i = 0;
    for(i=0; i<=nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        BENCH(printf("Ouverture5 SSE2 optimise: "));
        CHRONO(open5_SSE2_opt(v_img_0, vnrh, vnch, v_img_out,v_buffer),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));
        // CHRONO(open_bin5_SSE2_opt(v_img_0, vnrh, vnch, v_img_out, v_buffer),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}

void f_bench_open5_SSE2_opt_no_pipe(int nb_images)
{
    int i, i0, i1;

    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD/";
    char* path_file_out = "img/car3_SD_open5_SSE2_opt_no_pipe/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord_i = 2, bord_j = 0;
    uint8_t **img_0, **img_out;

    int card;
    int nrl, nrh, ncl, nch;
    int vnrl, vnrh, vncl, vnch;
    int vnrl_b, vnrh_b, vncl_b, vnch_b;
    vuint8 **v_img_0, **v_img_out, **v_buffer;

    card = card_vuint8();

    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    img_in_name = (char*) calloc(80, sizeof(char));
    img_out_name = (char*) calloc(80, sizeof(char));

    generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb, 4, extension, img_in_name);
    LoadPGM_ui8matrix(img_in_name, (long*)&nrl, (long*)&nrh, (long*)&ncl, (long*)&nch);

    s2v(nrl, nrh, ncl, nch, card, &vnrl, &vnrh, &vncl, &vnch);
    s2v(nrl-bord_i, nrh+bord_i, ncl-bord_j, nch+bord_j, card, &vnrl_b, &vnrh_b, &vncl_b, &vnch_b);

    v_img_0 = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_img_out = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_buffer = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);

    /* Bords haut et bas */
    i1 = vnrh;
    for(i0 = vnrl_b; i0<vnrl; i0++){
        v_img_0[i0] = v_img_0[vnrl];
        v_img_out[i0] = v_img_out[vnrl];
        v_img_0[i1] = v_img_0[vnrh];
        v_img_out[i1] = v_img_out[vnrh];
        i1--;
    }

    img_0 = (uint8**)v_img_0;
    img_out = (uint8**)v_img_out;

    // i = 0;
    for(i=0; i<=nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        BENCH(printf("Ouverture5 SSE2 optimise (sans pipeline): "));
        CHRONO(open5_SSE2_opt_no_pipe(v_img_0, vnrh, vnch, v_img_out,v_buffer),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));
        // CHRONO(open_bin5_SSE2_opt_no_pipe(v_img_0, vnrh, vnch, v_img_out, v_buffer),cycles);BENCH(printf(format, cycles/((nrh+1-nrl)*(nch+1-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}

void f_bench_morpho_SSE2(int nb_images){
    char *format = "%6.2f ";
    int iter, niter = 2;
    int run, nrun = 5;
    double t0, t1, dt, tmin, t;
    double cycles;

    // CHRONO(f_bench_dilate3_SSE2_full(nb_images),cycles); BENCH(printf(format, cycles/(198*320*240))); BENCH(puts(""));
    f_bench_dilate3_SSE2(nb_images);
    f_bench_dilate3_SSE2_opt(nb_images);
    f_bench_dilate5_SSE2(nb_images);
    f_bench_dilate5_SSE2_opt(nb_images);

    f_bench_open3_SSE2(nb_images);
    f_bench_open3_SSE2_opt(nb_images);
    f_bench_open3_SSE2_opt_no_pipe(nb_images);

    f_bench_open5_SSE2(nb_images);
    f_bench_open5_SSE2_opt(nb_images);
    f_bench_open5_SSE2_opt_no_pipe(nb_images);
}

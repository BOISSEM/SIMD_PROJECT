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
    int bord = 1;
    uint8_t **img_0, **img_out;
    long nrl, nrh, ncl, nch;
    vuint8 **v_img_0, **v_img_out;

    char *format_f32= "%4.0f ";
    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    img_in_name = (char*) calloc(80, sizeof(char));
    img_out_name = (char*) calloc(80, sizeof(char));

    generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb, 4, extension, img_in_name);
    LoadPGM_ui8matrix(img_in_name, &nrl, &nrh, &ncl, &nch);

    img_0 = ui8matrix(nrl-bord, nrh+bord, ncl-bord, nch+bord);
    img_out = ui8matrix(nrl-bord, nrh+bord, ncl-bord, nch+bord);

    v_img_0 = vui8matrix(nrl-bord, nrh+bord, ncl-bord, nch+bord);
    v_img_out = vui8matrix(nrl-bord, nrh+bord, ncl-bord, nch+bord);

    /* Bords haut et bas */
    i1 = nrh;
    for(i0 = nrl-bord; i0<nrl; i0++){
        v_img_0[i0] = v_img_0[nrl];
        v_img_out[i0] = v_img_out[nrl];
        v_img_0[i1] = v_img_0[nrh];
        v_img_out[i1] = v_img_out[nrh];
        i1--;
    }

    img_0 = (uint8**)v_img_0;
    img_out = (uint8**)v_img_out;

    i = 0;
    // for(i=0; i<nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        CHRONO(dilate3_SSE2(v_img_0, nrh, nch, v_img_out),cycles);BENCH(printf(format, cycles/((nrh-nrl)*(nch-ncl)))); BENCH(puts(""));

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
    int bord = 1;
    uint8_t **img_0, **img_out;
    long nrl, nrh, ncl, nch;
    vuint8 **v_img_0, **v_img_out;

    char *format    = "%6.2f ";
    int iter, niter = 10;
    int run, nrun = 20;
    double t0, t1, dt, tmin, t;
    double cycles;

    img_in_name = (char*) calloc(80, sizeof(char));
    img_out_name = (char*) calloc(80, sizeof(char));

    generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb, 4, extension, img_in_name);
    LoadPGM_ui8matrix(img_in_name, &nrl, &nrh, &ncl, &nch);

    img_0 = ui8matrix(nrl-bord, nrh+bord, ncl-bord, nch+bord);
    img_out = ui8matrix(nrl-bord, nrh+bord, ncl-bord, nch+bord);

    v_img_0 = vui8matrix(nrl-bord, nrh+bord, ncl-bord, nch+bord);
    v_img_out = vui8matrix(nrl-bord, nrh+bord, ncl-bord, nch+bord);

    /* Bords haut et bas */
    i1 = nrh;
    for(i0 = nrl-bord; i0<nrl; i0++){
        v_img_0[i0] = v_img_0[nrl];
        v_img_out[i0] = v_img_out[nrl];
        v_img_0[i1] = v_img_0[nrh];
        v_img_out[i1] = v_img_out[nrh];
        i1--;
    }

    img_0 = (uint8**)v_img_0;
    img_out = (uint8**)v_img_out;

    for(i=0; i<nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        CHRONO(dilate3_SSE2_opt(v_img_0, nrh, nch, v_img_out),cycles);BENCH(printf(format, cycles/((nrh-nrl)*(nch-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}


void f_bench_morpho_SSE2(){
    // char *format = "%6.2f ";
    // int iter, niter = 2;
    // int run, nrun = 5;
    // double t0, t1, dt, tmin, t;
    // double cycles;

    // CHRONO(f_bench_dilate3(198),cycles); BENCH(printf(format, cycles/(198*320*240))); BENCH(puts(""));
    f_bench_dilate3_SSE2(198);
    f_bench_dilate3_SSE2_opt(198);
    // f_bench_dilate5_SSE2(198);
}

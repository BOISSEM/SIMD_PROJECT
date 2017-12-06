/*--------------------------------
    bench_morpho.c

    Evaluation des performances des fonctions de morphologie mathematiques
    scalaires

    Projet SIMD - Implementation d'une chaine de detection de mouvement
    temps-reel sur un processeur multi-coeurs SIMD

    Kevin Seng - 2017
 ----------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "debug_macro.h"

#include "nrdef.h"
#include "nrutil.h"

#include "morpho.h"
#include "bench_morpho.h"

void f_bench_dilate3(int nb_images)
{
    int i, i0, i1;
    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD/";
    char* path_file_out = "img/car3_SD_dilate3/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord = 1;
    uint8_t **img_0, **img_out;
    long nrl, nrh, ncl, nch;

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

    /* Bords haut et bas */
    i1 = nrh;
    for(i0 = nrl-bord; i0<nrl; i0++){
        img_0[i0] = img_0[nrl];
        img_out[i0] = img_out[nrl];
        img_0[i1] = img_0[nrh];
        img_out[i1] = img_out[nrh];
        i1--;
    }

    for(i=0; i<nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        CHRONO(dilate3(img_0, nrh, nch, img_out),cycles);BENCH(printf(format, cycles/((nrh-nrl)*(nch-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}

void f_bench_dilate5(int nb_images)
{
    int i, i0, i1;
    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD/";
    char* path_file_out = "img/car3_SD_dilate5/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord = 2;
    uint8_t **img_0, **img_out;
    long nrl, nrh, ncl, nch;

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

    /* Bords haut et bas */
    i1 = nrh;
    for(i0 = nrl-bord; i0<nrl; i0++){
        img_0[i0] = img_0[nrl];
        img_out[i0] = img_out[nrl];
        img_0[i1] = img_0[nrh];
        img_out[i1] = img_out[nrh];
        i1--;
    }

    for(i=0; i<nb_images-1; i++)
    {
        generate_path_filename_k_ndigit_extension(path_file_in, filename, file_nb+i, 4, extension, img_in_name);

        MLoadPGM_ui8matrix(img_in_name, nrl, nrh, ncl, nch, img_0);

        CHRONO(dilate5(img_0, nrh, nch, img_out),cycles);BENCH(printf(format, cycles/((nrh-nrl)*(nch-ncl)))); BENCH(puts(""));

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}


void f_bench_morpho(){
    // char *format = "%6.2f ";
    // int iter, niter = 2;
    // int run, nrun = 5;
    // double t0, t1, dt, tmin, t;
    // double cycles;

    // CHRONO(f_bench_dilate3(198),cycles); BENCH(printf(format, cycles/(198*320*240))); BENCH(puts(""));
    f_bench_dilate3(198);
    // f_bench_dilate5(198);
}

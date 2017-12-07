/* -----------------------------------------------
	test_car3.c
	Edité par Martin Boisse
	Le 22 Octobre 2018

	Projet SIMD
	test detection de mouvement sur image
	(verification des fonctions presente dans
	mouvement.c)
----------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "nrdef.h"
#include "vnrdef.h"
#include "nrutil.h"
#include "vnrutil.h"
#include "mouvement.h"
#include "morpho.h"
#include "morpho_SSE2.h"
#include "morpho_SSE2_opt.h"

void f_test_sd_morpho_car3(int nb_images)
{
    int i, i0, i1;

    char *img_in_name, *img_out_name;
    char* path_file_in = "img/car3_SD_SSE2/";
    char* path_file_out = "img/car3_SD+morpho_2/";
    char* filename = "car_";
    char* extension= "pgm";

    int file_nb = 3000;
    int bord_i = 2, bord_j = 0;
    uint8_t **img_0, **img_out;

    int card;
    int nrl, nrh, ncl, nch;
    int vnrl, vnrh, vncl, vnch;
    int vnrl_b, vnrh_b, vncl_b, vnch_b;
    vuint8 **v_img_0, **v_img_out, **v_img_buff1, **v_img_buff2, **v_buffer;

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
    v_img_buff1 = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);
    v_img_buff2 = vui8matrix(vnrl_b, vnrh_b, vncl_b, vnch_b);

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

        close5_SSE2_opt(v_img_0, vnrh, vnch, v_img_buff1,v_buffer);
        open3_SSE2_opt(v_img_buff1, vnrh, vnch, v_img_buff2, v_buffer);
        open5_SSE2_opt(v_img_buff2, vnrh, vnch, v_img_buff1, v_buffer);
        close5_SSE2_opt(v_img_buff1, vnrh, vnch, v_img_out, v_buffer);

        generate_path_filename_k_ndigit_extension(path_file_out, filename, file_nb+i, 4, extension, img_out_name);
        SavePGM_ui8matrix(img_out, nrl, nrh, ncl, nch, img_out_name);
    }
}

void f_test_mouvement_car3(int nb_images){
    f_test_sd_morpho_car3(nb_images);
}

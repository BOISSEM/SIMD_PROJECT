/* -------------------- */
/* --- simd_macro.h --- */
/* -------------------- */


#ifndef __SIMD_MACRO_H__
#define __SIMD_MACRO_H__

#pragma message("  include  simd_macro.h")

// -----------------------
// melanges / permutations
// -----------------------

#define vec_left1(v0, v1)  (_mm_or_si128(_mm_srli_si128(v0, 1),_mm_slli_si128(v1, 15)))
#define vec_left2(v0, v1)  (_mm_or_si128(_mm_srli_si128(v0, 2),_mm_slli_si128(v1, 14)))
#define vec_left3(v0, v1)  (_mm_or_si128(_mm_srli_si128(v0, 3),_mm_slli_si128(v1, 13)))
#define vec_left4(v0, v1)  (_mm_or_si128(_mm_srli_si128(v0, 4),_mm_slli_si128(v1, 12)))

#define vec_right1(v1, v2) (_mm_or_si128(_mm_srli_si128(v1, 15),_mm_slli_si128(v2, 1)))
#define vec_right2(v1, v2) (_mm_or_si128(_mm_srli_si128(v1, 14),_mm_slli_si128(v2, 2)))
#define vec_right3(v1, v2) (_mm_or_si128(_mm_srli_si128(v1, 13),_mm_slli_si128(v2, 3)))
#define vec_right4(v1, v2) (_mm_or_si128(_mm_srli_si128(v1, 12),_mm_slli_si128(v2, 4)))

/*--------------------------------------------------------
    Duplication des bords :

    b = vec_left1(a,a) :    [ 1  2  3  4 ][ 1  2  3  4 ]
                      --> 1 [ 2  3  4  1 ] 2  3  4


    vec_left1(b, a) :       [ 2  3  4  1 ][ 1  2  3  4 ]
                      --> 2 [ 3  4  1  1 ] 2  3  4
----------------------------------------------------------*/
#define vec_bord_g1(a)  vec_left1(a, a)
#define vec_bord_g2(a)  vec_left1(vec_left1(a, a), a)

/*--------------------------------------------------------
    b = vec_right1(a,a) :    [ 1  2  3  4 ][ 1  2  3  4 ]
                      -->          1  2  3 [ 4  1  2  3 ] 4


    vec_right1(a, b) :       [ 1  2  3  4 ][ 4  1  2  3 ]
                      -->          1  2  3 [ 4  4  1  2 ] 3
----------------------------------------------------------*/
#define vec_bord_d1(a)  vec_right1(a, a)
#define vec_bord_d2(a)  vec_right1(a, vec_bord_d1(a, a)))

// -------
// calculs
// -------

#define vec_add3(x0, x1, x2) (_mm_add_epi8(_mm_add_epi8(x0, x1), x2))
#define vec_add5(x0, x1, x2, x3, x4) (_mm_add_epi8(_mm_add_epi8(_mm_add_epi8(_mm_add_epi8(x0, x1), x2), x3), x4))

#define vec_or3(x0, x1, x2) (_mm_or_si128(_mm_or_si128(x0, x1), x2))

#define vec_min3(x0, x1, x2) (_mm_min_epu8(_mm_min_epu8(x0, x1), x2))
#define vec_min5(x0, x1, x2, x3, x4) (_mm_min_epu8(_mm_min_epu8(_mm_min_epu8(_mm_min_epu8(x0, x1), x2), x3), x4))

#define vec_max3(x0, x1, x2) (_mm_max_epu8(_mm_max_epu8(x0, x1), x2))
#define vec_max5(x0, x1, x2, x3, x4) (_mm_max_epu8(_mm_max_epu8(_mm_max_epu8(_mm_max_epu8(x0, x1), x2), x3), x4))

#endif // __SIMD_MACRO_H__

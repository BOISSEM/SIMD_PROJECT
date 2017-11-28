/* -------------------- */
/* --- simd_macro.h --- */
/* -------------------- */


#ifndef __SIMD_MACRO_H__
#define __SIMD_MACRO_H__

#pragma message("  include  simd_macro.h")

// -----------------------
// melanges / permutations
// -----------------------

#define vec_border(a,b) a
#define vec_middle(a,b) a

#define vec_left1(v0, v1)  (_mm_or_si128(_mm_slli_si128(v0, 1),_mm_srli_si128(v1, 15)))
#define vec_left2(v0, v1)  v0
#define vec_left3(v0, v1)  v0
#define vec_left4(v0, v1)  v0

#define vec_right1(v1, v2) v1
#define vec_right2(v1, v2) v1
#define vec_right3(v1, v2) v1
#define vec_right4(v1, v2) v1


// -------
// calculs
// -------

#define vec_add3(x0, x1, x2) x0
#define vec_add5(x0, x1, x2, x3, x4) x0

#define vec_min3(x0, x1, x2) x0
#define vec_min5(x0, x1, x2, x3, x4) x0

// division neutralisee pour verifier la somme
#define vec_div3(x) x
#define vec_div5(x) x

#define vec_avg3(x0,x1,x2) x0
#define vec_avg5(x0,x1,x2,x3,x4) x0

#endif // __SIMD_MACRO_H__

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.15-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-8.15-C11: All declarations of an object with an explicit alignment
 *                specification shall specify the same alignment
 *
 * Enforced by message(s):
 *   1166   Using inconsistent alignment specification for object '${name}'
 *          with external linkage.
 *
 *   1167   Using inconsistent alignment specification for object '${name}'
 *          with internal linkage.
 *
 *
 *//* PRQA S 1166,1167 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"


_Alignas (4) extern int r0815_xa;
_Alignas (4) extern int r0815_xa;     /* c11_expect: !1166 */

_Alignas (4) extern int r0815_xb;
             extern int r0815_xb;     /* c11_expect:  1166 */

_Alignas (4) extern int r0815_xc;
_Alignas (8) extern int r0815_xc;     /* c11_expect:  1166 */

_Alignas (int) extern int r0815_xd;
_Alignas (4)   extern int r0815_xd;   /* c11_expect:  1166 */

typedef int Num;
_Alignas (int) extern int r0815_xe;
_Alignas (Num) extern int r0815_xe;   /* c11_expect:  1166 */

_Alignas (float) extern int r0815_xe; /* c11_expect:  1166 */


_Alignas (4) static int r0815_sa;
_Alignas (4) static int r0815_sa;     /* c11_expect: !1167 */

_Alignas (4) static int r0815_sb;
             static int r0815_sb;     /* c11_expect:  1167 */

_Alignas (4) static int r0815_sc;
_Alignas (8) static int r0815_sc;     /* c11_expect:  1167 */

_Alignas (int) static int r0815_sd;
_Alignas (4)   static int r0815_sd;   /* c11_expect:  1167 */

typedef int Num;
_Alignas (int) static int r0815_se;
_Alignas (Num) static int r0815_se;   /* c11_expect:  1167 */

_Alignas (float) static int r0815_se; /* c11_expect:  1167 */


extern int16_t rule_0815(void)
{
  return 0;
}

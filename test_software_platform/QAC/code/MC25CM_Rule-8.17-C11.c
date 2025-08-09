/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.17-C11.c
 *
 * MISRA Advisory - C11 Specific Rules
 *
 * Rule-8.17-C11: At most one explicit alignment specifier should appear in an
 *                object declaration
 *
 * Enforced by message(s):
 *   1164   Specifier list contains more than one alignment specifier.
 *
 *
 *//* PRQA S 1164 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_0817(void)
{
  _Alignas (4) char a;              /* c11_expect: !1164 */

  _Alignas (4) _Alignas (8) char b; /* c11_expect:  1164 */


  #define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
  _Alignas (MAX (4, 8)) char c;     /* c11_expect: !1164 */


  // Hidden alignment specifier
  #define SIMD _Alignas (8)
  SIMD _Alignas (4) char d;         /* c11_expect:  1164 */

  return 0;
}

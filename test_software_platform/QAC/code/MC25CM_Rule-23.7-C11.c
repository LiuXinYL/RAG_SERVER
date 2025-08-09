/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-23.7-C11.c
 *
 * MISRA Advisory - C11 Specific Rules
 *
 * Rule-23.7-C11: A generic selection that is expanded from a macro should evaluate
 *                its argument only once
 *
 * Enforced by message(s):
 *   1176   This generic argument is not consistently evaluated.
 *
 *
 *//* PRQA S 1176 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

#include <stdlib.h>


extern int16_t rule_2307 (void)
{
  #define use_twice(X) _Generic((X)       \
    , int : (X) + (X)                     \
    , default: (X))

  #define no_uses(X) _Generic((X)         \
    , int: 1                              \
    , default: 2)

  #define use_outside(X) (_Generic((X)    \
    , int : 4                             \
    , default: 5) + (X))

  #define with_ternary(B, X) _Generic((X) \
    , int : (B) ? (X) : (X)               \
    , default: (X))

  #define with_sizeof(X) _Generic((X)     \
    , int (*) [sizeof (X)] : (X)          \
    , int : sizeof (X) + (X))

  int b, x;
  use_twice (x);                       /* c11_expect:  1176 */
  with_sizeof (x);                     /* c11_expect: !1176 */
  no_uses (x);                         /* c11_expect:  1176 */
  use_outside (x);                     /* c11_expect: !1176 */
  with_ternary (b, x);                 /* c11_expect: !1176 */

  int z;
  // still from an argument, just not from outermost
  #define USE_Z_TWICE (use_twice (z))
  USE_Z_TWICE;                         /* c11_expect: !1172  1176 */

  return 0;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-23.1-C11.c
 *
 * MISRA Advisory - C11 Specific Rules
 *
 * Rule-23.1-C11: A generic selection should only be expanded from a macro
 *
 * Enforced by message(s):
 *   1177   This generic selection was not expanded from a macro.
 *
 *
 *//* PRQA S 1177 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

#include <stdlib.h>


extern int16_t rule_2301 (void)
{
  /* Non-compliant: type of x is locally visible */
  int32_t x = 0;

  int32_t y =_Generic (x   /* c11_expect:  1177 */
    , int32_t : 1
    , float : 2);

  /* Compliant: used to implement a generic function */
  #define arith(X) _Generic((X) \
    , int32_t : handle_int32    \
    , float : handle_float      \
    , default: handle_double) ((X))

  extern void handle_int32 (double);
  extern void handle_float (double);
  extern void handle_double (double);

  arith (x);               /* c11_expect: !1177 */
  arith (y);               /* c11_expect: !1177 */

  return 0;
}

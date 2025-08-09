/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-23.2-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-23.2-C11: A generic selection that is not expanded from a macro shall not
 *                contain potential side effects in the controlling expression
 *
 * Enforced by message(s):
 *   1172   This generic controlling expression has a side effect but does
 *          not originate from a macro argument.
 *
 *
 *//* PRQA S 1172 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

#include <stdlib.h>


extern int16_t rule_2302 (void)
{
  static int z;
  #define increment() _Generic (++ z  \
    , int : 1                         \
    , float : 2)
  increment ();                        /* c11_expect: 1172  */

  return 0;
}
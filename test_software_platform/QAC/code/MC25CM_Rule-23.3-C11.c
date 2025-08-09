/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-23.3-C11.c
 *
 * MISRA Advisory - C11 Specific Rules
 *
 * Rule-23.3-C11: A generic selection should contain at least one non-default
 *                association
 *
 * Enforced by message(s):
 *   1171   This generic selection only contains a default association.
 *
 *
 *//* PRQA S 1171 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

#include <stdlib.h>


void r2303_handle_int (unsigned int);
void r2303_handle_numeric (double);

#define no_op(X) _Generic ((X), default: (X))

#define filter_ints(X) (_Generic((X)  \
  , signed int: r2303_handle_int      \
  , unsigned int: r2303_handle_int    \
  , default: r2303_handle_numeric) (X))

#define only_ints(X) (_Generic((X)  \
  , signed int: r2303_handle_int    \
  , unsigned int: r2303_handle_int) (X))


extern int16_t rule_2303 (void)
{
  int x = 0;

  no_op (x);       /* c11_expect:  1171 */

  filter_ints (x); /* c11_expect: !1171 */
  only_ints (x);   /* c11_expect: !1171 */

  return 0;
}

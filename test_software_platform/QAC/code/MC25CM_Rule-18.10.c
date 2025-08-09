/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-18.10.c
 *
 * MISRA Mandatory - C99 and C11 Specific Rules
 *
 * Rule-18.10: Pointers to variably-modified array types shall not be used
 *
 * Enforced by message(s):
 *   1187   This defines a pointer to a variable length array.
 *
 *
 *//* PRQA S 1187 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

/* syntactic array types are adjusted to pointer-to-element types
   if the element type is a variable-length array type,
   the adjusted type is a pointer-to-VLA                       */

static void rule_1810_a (int16_t x1810
    , int16_t a1810[x1810]      /* expect:!1187 */
    , int16_t b1810[x1810][5]   /* expect:!1187 */
    , int16_t c1810[5][x1810]); /* expect: 1187 */

int16_t rule_1810 (void)
{
  int y1810 = 6;

  int16_t arr1810[y1810];       /* expect:!1187 */
  int16_t (*ptr1810)[y1810];    /* expect: 1187 */
}

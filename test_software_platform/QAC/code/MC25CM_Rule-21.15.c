/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.15.c
 *
 * MISRA Required - Rules
 *
 * Rule-21.15: The pointer arguments to the Standard Library functions memcpy,
 *             memmove and memcmp shall be pointers to qualified or unqualified
 *             versions of compatible types
 *
 * Enforced by message(s):
 *   1487   Comparing the representations of objects of different types.
 *
 *   1495   Destination and source objects have incompatible types.
 *
 *   1496   Destination and source objects may have incompatible types.
 *
 *
 *//* PRQA S 1487,1495,1496 -- *//*
 * <<<------------------------------------------------------------ */


#include <string.h>

#include "misra.h"
#include "mc25cmex.h"

uint8_t arr8_2115[8];
uint16_t arr16_2115[8];
void * ptr_2115;

extern int16_t rule_2115 (void)
{
  memcmp( arr8_2115, arr16_2115, 8);                                  /* expect: 1487 */

  memcpy( arr8_2115, arr16_2115, 8);                                  /* expect: 1495 */
  memmove( arr8_2115, arr16_2115, 8);                                 /* expect: 1495 */

  memcmp( arr8_2115, ptr_2115, 8);                                    /* expect: 1487 */

  memcpy( arr8_2115, ptr_2115, 8);                                    /* expect: 1496 */
  memmove( arr8_2115, ptr_2115, 8);                                   /* expect: 1496 */

  return 1;
}

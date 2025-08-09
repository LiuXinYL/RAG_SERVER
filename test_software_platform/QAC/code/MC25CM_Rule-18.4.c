/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-18.4.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-18.4: The +, -, += and -= operators should not be applied to an expression
 *            of pointer type
 *
 * Enforced by message(s):
 *   0488   Performing pointer arithmetic.
 *
 *   0489   The integer value 1 is being added or subtracted from a
 *          pointer.
 *
 *
 *//* PRQA S 0488,0489 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1804( void )
{
  uint8_t arr_1804[20];
  uint8_t * ptr_1804;

  ptr_1804 = arr_1804;

  ptr_1804 ++;                                                       /* Compliant     */

  ptr_1804 = ptr_1804 + 2;                                            /* expect: 0488 */
  *(ptr_1804 + 2) = 0u;                                               /* expect: 0488 */
  ptr_1804 += 2;                                                      /* expect: 0488 */
  ptr_1804[2] = 0u;                                                   /* Compliant    */

  ptr_1804[-2] = 0u;                                                  /* Compliant    */
  ptr_1804 -= 2;                                                      /* expect: 0488 */
  *(ptr_1804 - 2) = 0u;                                               /* expect: 0488 */
  ptr_1804 = ptr_1804 - 2;                                            /* expect: 0488 */

  ptr_1804 = ptr_1804 + 1;                                            /* expect: 0489 */
  *(ptr_1804 + 1) = 0u;                                               /* expect: 0489 */
  ptr_1804 += 1;                                                      /* expect: 0489 */
  ptr_1804[1] = 0u;                                                   /* Compliant    */

  ptr_1804[-1] = 0u;                                                  /* Compliant    */
  ptr_1804 -= 1;                                                      /* expect: 0489 */
  *(ptr_1804 - 1) = 0u;                                               /* expect: 0489 */
  ptr_1804 = ptr_1804 - 1;                                            /* expect: 0489 */

  ptr_1804 --;                                                        /* Compliant    */

  return 1;
}

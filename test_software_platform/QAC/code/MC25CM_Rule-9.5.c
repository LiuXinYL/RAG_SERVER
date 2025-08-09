/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-9.5.c
 *
 * MISRA Required - C99 and C11 Specific Rules
 *
 * Rule-9.5: Where designated initializers are used to initialize an array object
 *           the size of the array shall be specified explicitly
 *
 * Enforced by message(s):
 *   3676   Designators are used to initialize an array of unspecified
 *          size.
 *
 *
 *//* PRQA S 3676 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_0905( void )
{
  int r0905_a1[ ] = { [ 0 ] = 1 };	                                  /* expect: 3676 */

  int r0905_a2[ 10 ] = { [ 0 ] = 1 };

  return 0;
}

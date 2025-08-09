/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-12.3.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-12.3: The comma operator should not be used
 *
 * Enforced by message(s):
 *   3417   The comma operator has been used outside a 'for' statement.
 *
 *   3418   The comma operator has been used in a 'for' statement.
 *
 *
 *//* PRQA S 3417,3418 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1203( void )
{
   int16_t x;
   int16_t y;
   int16_t r1203_i;

   y = ( x, y );                                                      /* expect: 3417 */

   for ( r1203_i = 0, ++y; r1203_i < 5; ++r1203_i )                   /* expect: 3418 */
   {
      ++y;
   }

   return y;
}

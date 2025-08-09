/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-16.5.c
 *
 * MISRA Required - Rules
 *
 * Rule-16.5: A default label shall appear as either the first or the last switch
 *            label of a switch statement
 *
 * Enforced by message(s):
 *   2012   This 'default' label is neither the first nor the last label
 *          within the 'switch' block.
 *
 *
 *//* PRQA S 2012 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t s16a_1605;

extern int16_t rule_1605( void )
{
   int16_t ret_1605;

   switch ( s16a_1605 )
   {
   default:     /* Compliant */                                       /* expect: !2012 */
      ret_1605 = 2;
      break;
   case 2:
      ret_1605 = 3;
      break;
   case 3:
      ret_1605 = 5;
      break;
   }

   switch ( s16a_1605 )
   {
   case 1:
      ret_1605 = 7;
      break;
   default:     /* Not compliant */                                   /* expect:  2012 */
      ret_1605 = 11;
      break;
   case 3:
      ret_1605 = 13;
      break;
   }

   switch ( s16a_1605 )
   {
   case 1:
      ret_1605 = 17;
      break;
   case 2:
      ret_1605 = 19;
      break;
   default:     /* Compliant */                                       /* expect: !2012 */
      ret_1605 = 23;
      break;
   }

   return ret_1605;
}

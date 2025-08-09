/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-16.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-16.2: A switch label shall only be used when the most closely-enclosing
 *            compound statement is the body of a switch statement
 *
 * Enforced by message(s):
 *   2019   'Switch' label is located within a nested code block.
 *
 *
 *//* PRQA S 2019 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t s16a_1602;
int16_t s16b_1602;

extern int16_t rule_1602( void )
{
   int16_t ret_1602;

   switch ( s16a_1602 )
   {
   case 0:                                                            /* expect: !2019 */
      ret_1602 = 2;

      if ( s16b_1602 == 1 )
      {
         case 1:                                                      /* expect:  2019 */
            ret_1602 = 3;
            break;
      }

   default:                                                           /* expect: !2019 */
      ret_1602 = 5;
      break;
   }

   return ret_1602;
}

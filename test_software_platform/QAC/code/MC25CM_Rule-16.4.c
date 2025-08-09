/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-16.4.c
 *
 * MISRA Required - Rules
 *
 * Rule-16.4: Every switch statement shall have a default label
 *
 * Enforced by message(s):
 *   2002   No 'default' label found in this 'switch' statement.
 *
 *   2016   This 'switch' statement 'default' clause is empty.
 *
 *
 *//* PRQA S 2002,2016 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t s16a_1604;

extern int16_t rule_1604( void )
{
   int16_t ret_1604 = 0;

   switch ( s16a_1604 )                                               /* expect:  2002 */
   {
   case 0:
      ret_1604 = 2;
      break;
   case 1:
      ret_1604 = 3;
      break;
   }

   switch ( s16a_1604 )                                               /* expect: !2002 */
   {
   case 0:
      ret_1604 = 5;
      break;
   case 1:
      ret_1604 = 7;
      break;
   default:
      ret_1604 = 11;
      break;
   }

   switch ( s16a_1604 )
   {
   case 0:
      ret_1604 = 13;
      break;
   case 1:
      ret_1604 = 17;
      break;
                                                                      /* expect+1:  2016 */
   default:
      break;
   }

   switch ( s16a_1604 )
   {
   case 0:
      ret_1604 = 19;
      break;
   case 1:
      ret_1604 = 23;
      break;
   default:
      /* comment describing why we don't do anything here */
      break;
   }                                                                  /* expect: !2016 */

   return ret_1604;
}

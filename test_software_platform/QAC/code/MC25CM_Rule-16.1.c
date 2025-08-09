/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-16.1.c
 *
 * MISRA Required - Rules
 *
 * Rule-16.1: All switch statements shall be well-formed
 *
 * Enforced by message(s):
 *   2008   Code statements precede the first label in this 'switch'
 *          construct.
 *
 *   3234   Declarations precede the first label in this 'switch'
 *          construct.
 *
 *
 *//* PRQA S 2008,3234 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t s16a_1601;
int16_t s16b_1601;

extern int16_t rule_1601( void )
{
   int16_t ret_1601;

   switch ( s16a_1601 )
   {
      static int16_t static_1601;                                     /* expect: 3234 */

      case 1:
         ret_1601 = static_1601;
         break;
   }

   switch ( s16a_1601 )
   {
      int16_t auto_1601 = 0;                                          /* expect: 3234 */

      default:
         ret_1601 = auto_1601;
         break;
   }

   switch ( s16a_1601 )
   {
      ++ s16b_1601;                                                   /* expect: 2008 */

      default:
         ret_1601 = s16b_1601;
         break;
   }

   return ret_1601;
}

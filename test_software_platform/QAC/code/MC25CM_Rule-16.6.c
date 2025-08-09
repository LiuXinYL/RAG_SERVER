/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-16.6.c
 *
 * MISRA Required - Rules
 *
 * Rule-16.6: Every switch statement shall have at least two switch-clauses
 *
 * Enforced by message(s):
 *   3315   This 'switch' statement is redundant.
 *
 *   3353   This 'switch' statement contains only one case clause.
 *
 *
 *//* PRQA S 3315,3353 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

int16_t s16a_1606;
int16_t s16b_1606;
int16_t s16c_1606;
int16_t s16d_1606;

extern int16_t rule_1606( void )
{
   int16_t ret_1606;

   switch ( s16a_1606 )                          // expect:  3315
   {
   default: /* Non-compliant */
      ret_1606 = 1;
      break;
   }

   switch ( s16b_1606 )                          // expect:  3353
   {
   case 1: /* Non-compliant - only one path is explicit */
      ret_1606 = 1;
      break;
   }

   switch ( s16c_1606 )                          // expect:  3315
   {
   case 1:
   default: /* Non-compliant */
      ret_1606 = 1;
      break;
   }

   switch ( s16d_1606 )                          // expect: !3315
   {
   case 1:
      ret_1606 = 1;
      break;
   default: /* Compliant -separate paths */
      ret_1606 = 2;
      break;
   }

   return ret_1606;
}

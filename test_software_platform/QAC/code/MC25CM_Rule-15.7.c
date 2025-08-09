/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-15.7.c
 *
 * MISRA Required - Rules
 *
 * Rule-15.7: All if ... else if constructs shall be terminated with an else
 *            statement
 *
 * Enforced by message(s):
 *   2004   No concluding 'else' exists in this 'if'-'else'-'if' statement.
 *
 *   2013   This 'if .. else if ' construct 'else' statement is empty.
 *
 *
 *//* PRQA S 2004,2013 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t rule_1507_s16a;

extern int16_t rule_1507( void )
{
   int16_t rule_1507_r = 0;

   if ( rule_1507_s16a == 2 )
   {
      rule_1507_r = 3;
   }
   else if ( rule_1507_s16a == 3 )
   {
      rule_1507_r = 2;
   }                                                                  /* expect+1: 2013 */
   else
   {
   }

   if ( rule_1507_s16a == 2 )
   {
      rule_1507_r = 3;
   }
   else if ( rule_1507_s16a == 3 )                                    /* expect: 2004 */
   {
      rule_1507_r = 2;
   }

   return rule_1507_r;
}

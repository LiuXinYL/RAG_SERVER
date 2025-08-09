/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-15.6.c
 *
 * MISRA Required - Rules
 *
 * Rule-15.6: The body of an iteration-statement or a selection-statement shall be
 *            a compound-statement
 *
 * Enforced by message(s):
 *   2212   Body of control statement is not enclosed within braces.
 *
 *   2214   Body of control statement is on the same line and is not
 *          enclosed within braces.
 *
 *   2218   Body of switch statement is not enclosed within braces.
 *
 *   2219   Body of switch statement is on the same line and is not
 *          enclosed within braces.
 *
 *   3402   Braces are needed to clarify the structure of this
 *          'if'-'if'-'else' statement.
 *
 *
 *//* PRQA S 2212,2214,2218,2219,3402 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t rule_1506_s16a;
int16_t rule_1506_s16b;
int16_t rule_1506_s16c;

extern int16_t rule_1506_get_s16(void)
{
  return 6;
}

extern int16_t rule_1506( void )
{
   int16_t rule_1506_n = 0;

   if ( rule_1506_s16a == 0 )
   {
      rule_1506_s16c += 4;
   }
   else if ( rule_1506_s16a == 1 )
   {
      if ( rule_1506_s16b > 1 )
      {
         ++rule_1506_s16b;
      }
   }
   else
   {
      ++rule_1506_s16c;
   }

   if ( rule_1506_s16b == 2 )
      rule_1506_s16c += 3;                                            /* expect: 2212 */
   else
      rule_1506_n = 2;                                                /* expect: 2212 */

   if ( rule_1506_s16b == 5 ) rule_1506_n = 6;                        /* expect: 2214 */
   else rule_1506_n = rule_1506_n - rule_1506_s16a;                   /* expect: 2214 */

   if ( rule_1506_n > 5 )                                             /* expect: 3402 */
      if ( rule_1506_s16b > 10 )                                      /* expect: 2212 */
      {
         rule_1506_s16a = 1;
      }
      else
      {
         rule_1506_s16a = 2;
      }


   for ( rule_1506_n = 0; rule_1506_n < 5; rule_1506_n++ )
      ++rule_1506_s16a;                                               /* expect: 2212 */

   for ( rule_1506_n = 0; rule_1506_n < 5; rule_1506_n++ ) ++rule_1506_s16a;    /* expect: 2214 */

   rule_1506_n = rule_1506_get_s16();
   while ( rule_1506_n < 5 )
      ++rule_1506_n;                                                  /* expect: 2212 */

   do rule_1506_n++; while ( rule_1506_n < 9 );                       /* expect: 2214 */

   switch ( rule_1506_n )
   default:                                                           /* expect: 2218 */
      ++ rule_1506_n;

   switch ( rule_1506_n ) case 1: ++ rule_1506_n;                     /* expect: 2219 */

   return rule_1506_s16a;
}

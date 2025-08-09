/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-15.5.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-15.5: A function should have a single point of exit at the end
 *
 * Enforced by message(s):
 *   2889   This function has more than one 'return' path.
 *
 *
 *//* PRQA S 2889 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t rule_1505_s16a;

extern int16_t rule_1505a( void )                                     /* c2025_expect: 2889  */
{
   if ( rule_1505_s16a > 0 )
   {
      return 0;                                                       /* c2025_expect: 1572 */
   }
   else
   {
      return 1;                                                       /* c2025_expect: 1572 */
   }
}

extern void rule_1505b( void )                                        /* c2025_expect: 2889  */
{
   if ( rule_1505_s16a > 0 )
   {
      return;                                                         /* c2025_expect: 1572 */
   }
   rule_1505_s16a = 1;
}                                                                     /* c2025_expect: 1572 */

extern int16_t rule_1505c( void )                                     /* c2025_expect: !2889 */
{
   int16_t rule_1505_r = 0;
   if ( rule_1505_s16a > 0 )
   {
      rule_1505_r = 0;
   }
   else
   {
      rule_1505_r = 1;
   }
   return rule_1505_r;
}

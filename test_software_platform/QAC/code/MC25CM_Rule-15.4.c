/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-15.4.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-15.4: There should be no more than one break or goto statement used to
 *            terminate any iteration statement
 *
 * Enforced by message(s):
 *   0771   More than one 'break' statement has been used to terminate this
 *          iteration statement.
 *
 *   0772   Multiple jump statements are used to terminate this iteration
 *          statement, including 'goto'.
 *
 *
 *//* PRQA S 0771,0772 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t rule_1504_s16a;
int16_t rule_1504_s16b;

extern bool_t rule_1504_get_bool(void)
{
  return 0;
}

extern int16_t rule_1504_get_s16(void)
{
  return 6;
}

extern int16_t rule_1504( void )
{
   int16_t rule_1504_m;
   int16_t rule_1504_n;

   for ( rule_1504_n = 0; rule_1504_n < 5; rule_1504_n++ )            /* expect:  0771 */
   {
      if ( rule_1504_n > rule_1504_s16a )
      {
         break;
      }

      switch (rule_1504_s16a)
      {
      case 1:
         ++rule_1504_s16b;
         break;                                                       /* expect: !0771 */
      case 2:
         if (rule_1504_s16b > rule_1504_s16a)
         {
            break;                                                    /* expect: !0771 */
         }
         ++rule_1504_s16b;
         break;                                                       /* expect: !0771 */
      default:
         break;                                                       /* expect: !0771 */
      }

      if ( rule_1504_n > (rule_1504_s16a - 2) )
      {
         break;
      }

   }

   /* Both of the following nested loops are compliant
      as each has a single break used for early
      loop termination. */

   for ( rule_1504_m = 0; rule_1504_m < 10; ++rule_1504_m )
   {
      if ( rule_1504_get_bool() )
      {
         break;
      }

      for ( rule_1504_n = 0; rule_1504_n < rule_1504_m; ++rule_1504_n )
      {
         if ( rule_1504_get_bool() )
         {
            break;                                                    /* expect: !0771 */
         }
      }
   }

   return rule_1504_s16b;
}

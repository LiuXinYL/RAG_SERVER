/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-15.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-15.2: The goto statement shall jump to a label declared later in the same
 *            function
 *
 * Enforced by message(s):
 *   3310   This 'goto' statement involves a backward jump.
 *
 *
 *//* PRQA S 3310 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t rule_1502_s16a = 0;
int16_t rule_1502_s16b = 0;

extern int16_t rule_1502( void )
{
L: rule_1502_s16a = rule_1502_s16b;
   ++rule_1502_s16b;
   if (rule_1502_s16b == 10)
   {
       goto L;                                                        /* expect: 3310 */
   }

   return 1;
}

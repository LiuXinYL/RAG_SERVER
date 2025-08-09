/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-17.1.c
 *
 * MISRA Required - Rules
 *
 * Rule-17.1: The standard header file <stdarg.h> shall not be used
 *
 * Enforced by message(s):
 *   5130   Use of standard header file <stdarg.h>.
 *
 *   5140   Use of variable arguments handling identifier: va_arg,
 *          va_start, va_end, va_copy
 *
 *   1337   Function defined with a variable number of parameters.
 *
 *
 *//* PRQA S 5130,5140,1337 -- *//*
 * <<<------------------------------------------------------------ */


#include <stdarg.h>                                                   /* expect:  5130 */
#include "misra.h"
#include "mc25cmex.h"

static void rule_1701a (uint16_t count_1701, ...)                     /* expect:  1337 */
{
  va_list args_1701;
  va_start (args_1701, count_1701);                                   /* expect:  5140 */

  va_list args_1701_copy;
  va_copy (args_1701_copy, args_1701);                                /* expect:  5140 */

  for (int i_1701 = 0; i_1701 < count_1701; ++ i_1701)
  {
    double num_1701 = va_arg (args_1701, double);                     /* expect:  5140 */
  }
  va_end (args_1701);                                                 /* expect:  5140 */

  for (int i_1701 = 0; i_1701 < count_1701; ++ i_1701)
  {
    double num_1701 = va_arg (args_1701_copy, double);                /* expect:  5140 */
  }
  va_end (args_1701_copy);                                            /* expect:  5140 */
}

extern int16_t rule_1701 (void)                                       /* expect: !1337 */
{
  rule_1701a (5, 1.1, 1.2, 1.3, 1.4, 1.5);
  return 1;
}

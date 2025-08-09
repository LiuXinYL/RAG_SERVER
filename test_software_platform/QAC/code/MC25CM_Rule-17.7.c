/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-17.7.c
 *
 * MISRA Required - Rules
 *
 * Rule-17.7: The value returned by a function having non-void return type shall be
 *            used
 *
 * Enforced by message(s):
 *   3200   '${name}' returns a value which is not being used.
 *
 *
 *//* PRQA S 3200 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

static int16_t rule_1707a( void )
{
  return 1;
}

extern int16_t rule_1707( void )
{
  int16_t ret_1707;

  rule_1707a();                                                       /* expect:  3200 */

  ret_1707 = rule_1707a();                                            /* expect: !3200 */

  return 1;
}

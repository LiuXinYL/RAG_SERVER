/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.5.c
 *
 * MISRA Required - Rules
 *
 * Rule-21.5: The standard header file <signal.h> shall not be used
 *
 * Enforced by message(s):
 *   5123   Use of standard header file <signal.h>.
 *
 *   5138   Use of signal handling identifier: signal, raise
 *
 *
 *//* PRQA S 5123,5138 -- *//*
 * <<<------------------------------------------------------------ */


#include <signal.h>                                                   /* expect: 5123 */

#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_2105_flag = 0;

static void sig_handler( int16_t signum )
{
  /* */
}

extern int16_t rule_2105( void )
{
  signal (SIGINT, sig_handler);                                      /* expect: 5138 */

  if (rule_2105_flag == 1)
  {
    raise (SIGINT);                                                  /* expect: 5138 */
  }

  return 1;
}

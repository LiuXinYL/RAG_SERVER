/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.8.c
 *
 * MISRA Required - Rules
 *
 * Rule-21.8: The Standard Library functions abort, exit, getenv and system of
 *            <stdlib.h> shall not be used
 *
 * Enforced by message(s):
 *   5128   Use of function: getenv.
 *
 *   5150   Use of function: system.
 *
 *   5151   Use of function: abort or exit.
 *
 *   5152   Use of function: _Exit or quick_exit.
 *
 *
 *//* PRQA S 5128,5150,5151,5152 -- *//*
 * <<<------------------------------------------------------------ */

#include <stdlib.h>

#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_2108 (void)
{
  int16_t ret_2108;


  // This test reflects the update introduced with MISRA C:2012
  // Amendment 2: use of system is no longer a violation of Rule
  // 21.8, since it is dealt with via the additional Rule 21.21

  ret_2108 = system( "test" );                                       // expect:  5150

  if ( ret_2108 < -99 )
  {
    abort();                                                         // expect:  5151
  }

  if ( ret_2108 == 40 )
  {
    exit( 1 );                                                       // expect:  5151
  }

  // This test reflects the update introduced with MISRA C:2012
  // Amendment 1: use of getenv is no longer a violation of Rule
  // 21.8, since it is dealt with via the additional Rules 21.19
  // and 21.20.
  char * env_2108 = getenv("ENV_2108");                              // expect:  !5128


// The following tests reflect the update introduced with MISRA C:2012
  // Amendment 2: addition of _Exit and quick_exit


if ( ret_2108 == 50 )
  {
    _Exit( 1 );                                                       // expect:  5152
  }

if ( ret_2108 == 60 )
  {
    quick_exit( 1 );                                                  // expect:  5152
  }

  return ret_2108;
}

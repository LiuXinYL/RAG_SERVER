/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.24.c
 *
 * MISRA Required - Rules
 *
 * Rule-21.24: The random number generator functions of <stdlib.h> shall not be
 *             used
 *
 * Enforced by message(s):
 *   5143   Use of pseudo-random number generation function: rand, srand
 *
 *
 *//* PRQA S 5143 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#include <stdlib.h>
#include <time.h>


extern int16_t rule_2124(void)
{
  srand (time (0));           /*  5143 */
  int32_t x = rand ();        /*  5143 */

  return 0;
}

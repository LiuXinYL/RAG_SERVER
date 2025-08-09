/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.9.c
 *
 * MISRA Required - Rules
 *
 * Rule-21.9: The Standard Library functions bsearch and qsort of <stdlib.h> shall
 *            not be used
 *
 * Enforced by message(s):
 *   5135   Use of function: bsearch or qsort.
 *
 *
 *//* PRQA S 5135 -- *//*
 * <<<------------------------------------------------------------ */


#include <stdlib.h>

#include "misra.h"
#include "mc25cmex.h"

static int rule_2109a(void const * lp_2109a, void const * rp_2109a)
{
  int16_t l_2109a = *(int16_t const *)lp_2109a;
  int16_t r_2109a = *(int16_t const *)rp_2109a;
  return l_2109a < r_2109a ? -1
       : l_2109a > r_2109a ? 1
       : 0;
}

extern int16_t rule_2109( void )
{
  int16_t arr_2109[8] = { 1, 3, 5, 7, 2, 4, 6, 8 };

  qsort(arr_2109, 8, sizeof(int16_t), rule_2109a);                    /* expect: 5135 */

  int16_t find_2109 = 6;
  int16_t * ptr_2109 = bsearch(&find_2109, arr_2109, 8, sizeof(int16_t), rule_2109a); /* expect: 5135 */

  return 1;
}

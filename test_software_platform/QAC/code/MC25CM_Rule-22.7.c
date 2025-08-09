/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.7.c
 *
 * MISRA Required - Rules
 *
 * Rule-22.7: The macro EOF shall only be compared with the unmodified return value
 *            from any Standard Library function capable of returning EOF
 *
 * Enforced by message(s):
 *   2671   Definite: The value being compared with macro EOF does not
 *          originate from an EOF returning function.
 *
 *   2676   Definite: The value originating from an EOF returning function
 *          was modified before being compared with macro EOF.
 *
 *   2678   Suspicious: The value originating from an EOF returning
 *          function was modified before being compared with macro
 *          EOF.
 *
 *
 *//* PRQA S 2671,2676,2678 -- *//*
 * <<<------------------------------------------------------------ */

#include <stdio.h>

#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_2207(void)
{
  int16_t i = 5;
  i == EOF;                            // expect: 2671

  i = getchar();
  i++;
  i == EOF;                            // expect: 2676

  {
    extern int n;
    int c;

    if (n == 0)
    {
      c = getchar ();
    }
    else
    {
      /* Value is modified by cast */
      c = (char) getchar ();
    }

    if (c == EOF)                      // expect: 2678
    {

    }
  }

  return 1;
}

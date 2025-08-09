/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.6.c
 *
 * MISRA Mandatory - Rules
 *
 * Rule-22.6: The value of a pointer to a FILE shall not be used after the
 *            associated stream has been closed
 *
 * Enforced by message(s):
 *   2696   Definite: Attempt to access a file which has been closed.
 *
 *   2697   Apparent: Attempt to access a file which has been closed.
 *
 *   2698   Suspicious: Attempt to access a file which has been closed.
 *
 *
 *//* PRQA S 2696,2697,2698 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#include <stdio.h>

int16_t s16a_2204;
int16_t s16b_2204;

extern int16_t rule_2206 (void)
{
  FILE * fp1_2206 = fopen ("path", "r");         // expect: 1581 1581
  FILE * fp2_2206 = fopen ("path", "r");         // expect: 1581 1581

  fclose (fp1_2206);                             // expect: 1581 1581

  fgetc (fp1_2206);                              // expect: 2696

  if (s16a_2204 > 10)
  {
    fclose (fp2_2206);                           // expect: 1581 1581
  }

  fgetc (fp2_2206);                              // expect: 2697

  fclose (fp1_2206);                             // expect: 2696
  fclose (fp2_2206);                             // expect: 2697

  {
    extern char const * path;
    extern int n;

    char s [8];

    FILE * fp = fopen (path, "r");               // expect: 1581

    while (-- n > 0)
    {
      fclose (fp);                               // expect: 2698 1581
    }

    fread (s, 1, sizeof (s), fp);                // expect: 2698
  }

  return 1;
}

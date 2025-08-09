/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.4.c
 *
 * MISRA Mandatory - Rules
 *
 * Rule-22.4: There shall be no attempt to write to a stream which has been opened
 *            as read-only
 *
 * Enforced by message(s):
 *   2686   Definite: Writing to a file opened for reading.
 *
 *   2687   Apparent: Writing to a file opened for reading.
 *
 *   2688   Suspicious: Writing to a file opened for reading.
 *
 *
 *//* PRQA S 2686,2687,2688 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#include <stdio.h>

int16_t s16a_2204;
int16_t s16b_2204;

extern int16_t rule_2204 (void)
{
  int16_t buf_2204[5] = { 1, 2, 3, 4, 5 };

  FILE * fp1_2204 = fopen ("path", "r");                   // expect: 1586 1594

  fwrite (buf_2204, sizeof(int16_t), 5, fp1_2204);         // expect: 2686

  FILE * fp2_2204 = fopen ("path2", "w");                  // expect: 1594

  if (s16a_2204 > 10)
  {
    fclose (fp2_2204);
    fp2_2204 = fopen ("path2", "r");                       // expect: 1586
  }

  fwrite (buf_2204, sizeof(int16_t), 5, fp2_2204);         // expect: 2687

  FILE * fp3_2204 = fopen ("path3", "w");                  // expect: 1594

  while (s16b_2204 > 10)
  {
    -- s16b_2204;
    fclose (fp3_2204);
    fp3_2204 = fopen ("path3", "r");                       // expect: 1586
  }

  fwrite (buf_2204, sizeof(int16_t), 5, fp3_2204);         // expect: 2688

  fclose (fp1_2204);
  fclose (fp2_2204);
  fclose (fp3_2204);

  return 1;
}

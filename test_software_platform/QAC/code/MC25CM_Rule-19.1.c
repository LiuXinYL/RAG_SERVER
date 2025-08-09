/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-19.1.c
 *
 * MISRA Mandatory - Rules
 *
 * Rule-19.1: An object shall not be assigned or copied to an overlapping object
 *
 * Enforced by message(s):
 *   2776   Definite: Copy between overlapping objects.
 *
 *   2777   Apparent: Copy between overlapping objects.
 *
 *   2778   Suspicious: Copy between overlapping objects.
 *
 *   0681   Assignment between two incompatible members of the same union.
 *
 *
 *//* PRQA S 2776,2777,2778,0681 -- *//*
 * <<<------------------------------------------------------------ */

#include "string.h"
#include "misra.h"
#include "mc25cmex.h"

union u1_1901
{
  int16_t x;
  int32_t y;
};

union u2_1901
{
  int16_t x;
  int16_t y;
};

int16_t s16a_1901;

extern int16_t rule_1901 (void)
{
  union u1_1901 unc_1901;
  union u2_1901 uc_1901;

  unc_1901.y = 1;                                          /* expect: 1575 */
  unc_1901.x = unc_1901.y;                                 /* expect:  681 2776 */
  uc_1901.y = 1;
  uc_1901.x = uc_1901.y;                                   /* expect: !681 !2776 */

  PC buf_1901[100] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";         /* expect: 1594 1594 */

  memcpy (&buf_1901[ 10 ], &buf_1901[ 20 ], 20U);          /* expect:  2776 */

  uint16_t size_1901;

  size_1901 = 5;
  memcpy (&buf_1901[ 10 ], &buf_1901[ 20 ], size_1901);    /* expect: !2776 */

  if (s16a_1901 == 0)
  {
    size_1901 = 30;                                        /* expect: 1575 */
  }
  memcpy (&buf_1901[ 10 ], &buf_1901[ 20 ], size_1901);    /* expect:  2777 1574 */

  memmove (&buf_1901[ 10 ], &buf_1901[ 20 ], 20U);         /* expect: !2776 */

  if (s16a_1901 == 1)
  {
    size_1901 = 30;
  }
  memmove (&buf_1901[ 10 ], &buf_1901[ 20 ], size_1901);   /* expect: !2777 */

  {
    extern int p;
    extern int v [8];

    int * p1;
    int * p2;
    unsigned int n = 4;
    int i;

    p1 = v;
    p2 = & v [3];

    for (i = 0; i < p; ++i)
    {
      --n;
    }

    (void) memcpy  (p1, p2, n * sizeof (int));             /* expect:  2778 1574 */

    (void) memmove (p1, p2, n * sizeof (int));             /* expect: !2778 */
  }

  return 1;
}

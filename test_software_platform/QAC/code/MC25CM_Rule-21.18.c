/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.18.c
 *
 * MISRA Mandatory - Rules
 *
 * Rule-21.18: The size_t argument passed to any function in <string.h> shall have
 *             an appropriate value
 *
 * Enforced by message(s):
 *   2865   Constant: Using 0 as size parameter of a function call.
 *
 *   2866   Definite: Using 0 as size parameter of a function call.
 *
 *   2867   Apparent: Using 0 as size parameter of a function call.
 *
 *   2868   Suspicious: Using 0 as size parameter of a function call.
 *
 *   4880   Constant: Pointed to object has smaller size than the size_t
 *          argument.
 *
 *   4881   Definite: Pointed to object has smaller size than the size_t
 *          argument.
 *
 *   4882   Apparent: Pointed to object has smaller size than the size_t
 *          argument.
 *
 *   4883   Suspicious: Pointed to object has smaller size than the size_t
 *          argument.
 *
 *
 *//* PRQA S 2865,2866,2867,2868,4880,4881,4882,4883 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

#include <string.h>

int16_t s16a_2118;                                                   // expect: 1594
int16_t s16b_2118;
int16_t s16c_2118;                                                   // expect: 1594
int16_t s16d_2118;
int16_t s16e_2118;
int16_t s16f_2118;

bool_t ba_2118;
uint16_t u16a_2118;

extern int16_t rule_2118 (void)
{
  char buf1_2118[5] = "12345";                                       // expect: 1594 1594 1594
  char buf2_2118[10] = "1234567890";                                 // expect: 1594

  if (memcmp (buf1_2118, buf2_2118, 5) == 0)
  {
  }

  if (memcmp (buf1_2118, buf2_2118, 6) == 0)                         // expect: 4880
  {
  }

  if (memcmp (buf1_2118, buf2_2118, 0) == 0)                         // expect: 2865
  {
  }

  if (s16a_2118 > 5)                                                 // expect: 1575
  {
    memcmp (buf1_2118, buf2_2118, s16a_2118);                        // expect: 4881
  }

  if (s16b_2118 > 10)                                                // expect: 1575 1575
  {
  }

  memcmp (buf1_2118, buf2_2118, s16b_2118);                          // expect: 4882 4882 1574 1574

  {
    extern int n;
    int v [8];
    int i;
    int x = 8;

    for (i = 0; i < n; ++i)
    {
      -- x;
    }

    v [x] = 1;
  }

  {
    extern int  n;
    extern char a [8];
    extern char b [9];

    int i;
    int m = sizeof (b);

    for (i = 0; i < n; ++i)
    {
      -- m;
    }

    strncpy (a, b, m);                                               // expect: 4883 1574
  }

  if (s16c_2118 == 0)                                                // expect: 1575
  {
    memcmp (buf1_2118, buf2_2118, s16c_2118);                        // expect: 2866
  }

  if (ba_2118)
  {
    s16d_2118 = 0;                                                   // expect: 1575
  }

  memcmp (buf1_2118, buf2_2118, s16d_2118);                          // expect: 2867 1574

  for (uint16_t i_2118 = u16a_2118; i_2118 > 0; -- i_2118)
  {
    s16e_2118 = 0;
  }

  memcmp (buf1_2118, buf2_2118, s16e_2118);                          // expect: 2868

  return 1;
}

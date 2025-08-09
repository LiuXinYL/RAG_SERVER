/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-18.1.c
 *
 * MISRA Required - Rules
 *
 * Rule-18.1: A pointer resulting from arithmetic on a pointer operand shall
 *            address an element of the same array as that pointer operand
 *
 * Enforced by message(s):
 *   2840   Constant: Dereference of an invalid pointer value.
 *
 *   2841   Definite: Dereference of an invalid pointer value.
 *
 *   2842   Apparent: Dereference of an invalid pointer value.
 *
 *   2843   Suspicious: Dereference of an invalid pointer value.
 *
 *   2930   Constant: Computing an invalid pointer value.
 *
 *   2931   Definite: Computing an invalid pointer value.
 *
 *   2932   Apparent: Computing an invalid pointer value.
 *
 *   2933   Suspicious: Computing an invalid pointer value.
 *
 *   2935   Constant: Dereference of an invalid char pointer value.
 *
 *   2936   Definite: Dereference of an invalid char pointer value.
 *
 *   2937   Apparent: Dereference of an invalid char pointer value.
 *
 *   2938   Suspicious: Dereference of an invalid char pointer value.
 *
 *   2840   Constant: Dereference of an invalid pointer value.
 *
 *
 *//* PRQA S 2840,2841,2842,2843,2930,2931,2932,2933,2935,2936,2937,2938,2840 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

int16_t s16a_1801;

extern int16_t rule_1801 (void)
{
  int16_t * ptr_1801;

  ptr_1801 = &s16a_1801 + 5;                     /* expect: 2930 */

  *(&s16a_1801 + 5) = 64;                        /* expect: 2840 */

  ptr_1801 = &s16a_1801;                         /* expect: 1582 */
  ptr_1801 = ptr_1801 + 5;                       /* expect: 2931 1582 */

  *ptr_1801 = s16a_1801;                         /* expect: 2841 */

  ptr_1801 = &s16a_1801;                         /* expect: 1582 */
  if (s16a_1801 < 10)                            /* expect: 1575 */
  {
    //
  }
  ptr_1801 = ptr_1801 + s16a_1801;               /* expect: 2932 1574 */

  ptr_1801 = &s16a_1801;                         /* expect: 1582 */
  if (s16a_1801 < 10)                            /* expect: 1575 */
  {
    //
  }
  ptr_1801[s16a_1801] = 64;                      /* expect: 2842 1574 */

  {
    extern int n;
    int i;
    int v [10];
    int x = 10;

     for (i = 0; i < n; ++i)
     {
       --x;
     }

     v [x] = 1;                                  /* expect: 2843 1574 */
  }

  {
    extern int n;
    extern int v [10];
    int * p;
    int   i;
    int   x = 11;

     for (i = 0; i < n; ++i)
     {
       -- x;
     }

     p = & v [x];                                /* expect: 2933 1574 */
  }

  return 1;
}

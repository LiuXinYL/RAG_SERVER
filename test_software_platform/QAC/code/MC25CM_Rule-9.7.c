/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-9.7.c
 *
 * MISRA Mandatory - C11 Specific Rules
 *
 * Rule-9.7: Atomic objects shall be appropriately initialized before being
 *           accessed
 *
 * Enforced by message(s):
 *   4836   Definite: The C Atomic object is accessed before being
 *          initialised.
 *
 *   4837   Apparent: The C Atomic object is accessed before being
 *          initialised.
 *
 *   4838   Suspicious: The C Atomic object is accessed before being
 *          initialised.
 *
 *
 *//* PRQA S 4836,4837,4838 -- *//*
 * <<<------------------------------------------------------------ */
/* PRQA S 0-9999 ++ */
/* PRQA S 4836-4838 -- */

#include "MC25CM_Rule-9.7.h"

static int cond();

extern int16_t rule_0907(void)
{
  int x = 1;

  _Atomic int a1 = x;        /* c11_expect: !4836 */

  _Atomic int a2;
  a2 = x;                    /* c11_expect:  4836 */

  _Atomic int a3 = 0;
  a3 = x;                    /* c11_expect: !4836 */

  _Atomic int a4;
  atomic_init (&a4, 0);      /* c11_expect: !4836 */
  a4 = x;

  _Atomic int a5;
  a5 = 5;                    /* c11_expect:  4836 */
  atomic_init (&a5, 0);

  static _Atomic int si;
  si = 0;                    /* c11_expect: !4836 */

  _Atomic int b1;
  if (cond())
  {
    atomic_init (&b1, 0);
  }
  b1;                        /* c11_expect:  4837 */

  _Atomic int b2;
  while (cond())
  {
    atomic_init (&b2, 0);
  }
  b2;                        /* c11_expect:  4838 */

  return 1;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-1.4-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-1.4-C11: Emergent language features shall not be used
 *
 * Enforced by message(s):
 *   1081   The keyword '_Atomic' has been used.
 *
 *   1084   The keyword '_Thread_local' has been used.
 *
 *
 *//* PRQA S 1081,1084 -- *//*
 * <<<------------------------------------------------------------ */


#include <stddef.h> /* for size_t */

void Rule_0104_C11 (void)
{
  /* C11 language features */
  {
    _Atomic int i;                                         /* expect: 1081 */

    static _Thread_local int v = 0;                        /* expect: 1084 */
  }
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-1.1-C90.c
 *
 * MISRA Required - C90 Specific Rules
 *
 * Rule-1.1-C90: The program shall contain no violations of the standard C syntax
 *               and constraints, and shall not exceed the implementation's
 *               translation limits
 *
 * Enforced by message(s):
 *   3421   Expression with persistent side effects is used in an
 *          initializer list.
 *
 *
 *//* PRQA S 3421 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"

extern void Rule_0101_C90 (void)
{
  volatile uint16_t x;

  uint16_t v [2] =
  {
    x,                                 /* expect: 3421 */
    0
  };
}

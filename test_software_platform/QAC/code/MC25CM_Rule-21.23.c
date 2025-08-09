/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.23.c
 *
 * MISRA Required - C99 and C11 Specific Rules
 *
 * Rule-21.23: All operand arguments to any multi-argument type-generic macros
 *             declared in <tgmath.h> shall have the same standard type
 *
 * Enforced by message(s):
 *   1163   Not all arguments to '${name}' have the same type.
 *
 *
 *//* PRQA S 1163 -- *//*
 * <<<------------------------------------------------------------ */
#include <complex.h>
#include <tgmath.h>

#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_2123 (void)
{
  float f2123a;
  float f2123b;
  double d2123a;
  double d2123b;

  f2123b = pow (f2123a, f2123b);           /* expect:!1163 */
  d2123b = pos (d2123a, d2123b);           /* expect:!1163 */

  f2123b = pow (f2123a, d2123b);           /* expect: 1163 */
  f2123b = pos (f2123a, (float)d2123b);    /* expect:!1163 */
}

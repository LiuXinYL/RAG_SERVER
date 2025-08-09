/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.22.c
 *
 * MISRA Mandatory - C99 and C11 Specific Rules
 *
 * Rule-21.22: All operand arguments to any type-generic macros declared in
 *             <tgmath.h> shall have an appropriate essential type
 *
 * Enforced by message(s):
 *   1160   Passing an argument to '${name}' that has complex type.
 *
 *   1161   Passing an argument to '${name}' that has imaginary type.
 *
 *   1162   Passing an argument to '${name}' that does not have essentially
 *          integer or essentially floating type.
 *
 *
 *//* PRQA S 1160,1161,1162 -- *//*
 * <<<------------------------------------------------------------ */
#include <complex.h>
#include <tgmath.h>

#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_2122 (void)
{
  float f2122a, f2122b;
  int   i2122a, i2122b;

  char ch2122a, ch2122b;
  void * p2122a, * p2122b;

  f2122b = sqrt (f2122a);     /* expect: !1162 */
  i2122b = sqrt (i2122a);     /* expect: !1162 */

  ch2122b = sqrt (ch2122a);   /* expect:  1162 */
  p2122b = sqrt (p2122a);     /* expect:  1162 */

  complex float cx2122a;
  complex float cx2122b;

  f2122b = sqrt (f2122a);     /* expect: !1160 */
  cx2122b = sqrt (cx2122a);   /* expect: !1160 */

  f2122b = ceil (f2122a);     /* expect: !1160 */
  cx2122b = ceil (cx2122a);   /* expect:  1160 */
}

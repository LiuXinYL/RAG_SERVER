/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.12.c
 *
 * MISRA Required - Rules
 *
 * Rule-20.12: A macro parameter used as an operand to the # or ## operators, which
 *             is itself subject to further macro replacement, shall only be
 *             used as an operand to these operators
 *
 * Enforced by message(s):
 *   0893   Macro argument '%1s' is both expanded as a macro and used with
 *          the '%2s' operator.
 *
 *   0895   Macro parameter '%s' is inconsistently subject to macro
 *          replacement.
 *
 *
 *//* PRQA S 0893,0895 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#define AA 2012

#define BB1(X) (X) + s16a_2012_ ## X                                  /* expect:  0895 */

#define BB2(X) BB1(X)

int16_t s16a_2012_AA = 1;
int16_t s16a_2012_2012 = 2;

extern int16_t rule_2012 (void)
{
  int16_t ret_2012 = 0;

  /* Expands as ret_2012 = ( 2012 ) + s16a_2012_AA;   */
  ret_2012 = BB1(AA);                                                 /* expect:  0893 */
  /* Expands as ret_2012 = ( 2012 ) + s16a_2012_2012; */
  ret_2012 = BB2(AA);                                                 /* expect: !0893 */

  return ret_2012;
}

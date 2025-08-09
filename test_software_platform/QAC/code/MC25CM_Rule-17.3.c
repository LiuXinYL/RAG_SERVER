/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-17.3.c
 *
 * MISRA Mandatory - Rules
 *
 * Rule-17.3: A function shall not be declared implicitly
 *
 * Enforced by message(s):
 *   3335   No function declaration. Implicit declaration inserted: 'extern
 *          int ${name}();'.
 *
 *
 *//* PRQA S 3335 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

static int32_t rule_1703b ();
static int32_t rule_1703c (int32_t x_1703c, float64_t y_1703c);

extern int16_t rule_1703 (void)
{
  int32_t ret_1703;

  ret_1703 = rule_1703a (50, 1.2);                                    /* expect:  3335 */
  ret_1703 = rule_1703b (50, 1.2);                                    /* expect: !3335 */
  ret_1703 = rule_1703c (50, 1.2);                                    /* expect: !3335 */

  return ret_1703;
}

extern int rule_1703a (int x_1703a, float64_t y_1703a)
{
  return y_1703a + x_1703a;
}

static int32_t rule_1703b (int x_1703b, float64_t y_1703b)
{
  return y_1703b + x_1703b;
}

static int32_t rule_1703c (int32_t x_1703c, float64_t y_1703c)
{
  return y_1703c + x_1703c;
}

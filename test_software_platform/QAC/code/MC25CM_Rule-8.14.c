/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.14.c
 *
 * MISRA Required - C99 and C11 Specific Rules
 *
 * Rule-8.14: The restrict type qualifier shall not be used
 *
 * Enforced by message(s):
 *   1057   The keyword 'restrict' has been used.
 *
 *
 *//* PRQA S 1057 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

static void rule_0814a(int16_t n, int16_t * restrict p, const int16_t * restrict q)    /* expect: 1057 1057 */
{
    while (n > 0)
    {
        *p++ = *q++ + n;
        --n;
    }
}

extern int16_t rule_0814(void)
{
  static int16_t ia[1000] = {0};

  rule_0814a(10, &ia[5], &ia[6]);
  return 1;
}

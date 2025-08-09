/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.7.c
 *
 * MISRA Required - Rules
 *
 * Rule-20.7: Expressions resulting from the expansion of macro parameters shall be
 *            appropriately delimited
 *
 * Enforced by message(s):
 *   3430   Macro argument expression may require parentheses.
 *
 *   3432   Simple macro argument expression is not parenthesized.
 *
 *
 *//* PRQA S 3430,3432 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#define MULTIPLY1(X, Y) ((X) * (Y))  /* always safe to use */

#define MULTIPLY2(X, Y) (X * Y)      /* not safe to use unless arguments are atomic */

#define OPERATE1(X) (-(X))           /* always safe to use */

#define OPERATE2(X) (-X)             /* not safe to use unless argument is atomic */

struct s_2007
{
  int x;
};

static int16_t fn_2007 (void)
{
  return 2;
}

extern int16_t rule_2007 (void)
{
  int16_t ret_2007;

  int16_t a_2007 = 4;
  int16_t b_2007 = 5;
  struct s_2007 dot_2007 = { 6 };

  ret_2007 = MULTIPLY1(a_2007, b_2007);                               /* Compliant         */
  ret_2007 = MULTIPLY2(a_2007, b_2007);                               /* expect: 3432,3432 */

  ret_2007 = MULTIPLY1(a_2007 + 1, b_2007 + 2);                       /* Compliant         */
  ret_2007 = MULTIPLY2(a_2007 + 1, b_2007 + 2);                       /* expect: 3430,3430 */

  ret_2007 = MULTIPLY1((a_2007 + 1), (b_2007 + 2));                   /* Compliant         */
  ret_2007 = MULTIPLY2((a_2007 + 1), (b_2007 + 2));                   /* Compliant         */

  /* postfix expressions are safe to use unparenthesized, but may
     indicate a vulnerability in the future if the argument changes */
  ret_2007 = MULTIPLY1(dot_2007.x, fn_2007());                        /* Compliant         */
  ret_2007 = MULTIPLY2(dot_2007.x, fn_2007());                        /* expect: 3432,3432 */

  ret_2007 = MULTIPLY1((dot_2007.x), (fn_2007()));                    /* Compliant         */
  ret_2007 = MULTIPLY2((dot_2007.x), (fn_2007()));                    /* Compliant         */

  ret_2007 = OPERATE1(a_2007);                                        /* Compliant         */
  ret_2007 = OPERATE2(a_2007);                                        /* expect: 3432      */

  ret_2007 = OPERATE1(a_2007 + 1);                                    /* Compliant         */
  ret_2007 = OPERATE2(a_2007 + 1);                                    /* expect: 3430      */

  ret_2007 = OPERATE1((a_2007 + 1));                                  /* Compliant         */
  ret_2007 = OPERATE2((a_2007 + 1));                                  /* Compliant         */

  ret_2007 = OPERATE1(dot_2007.x);                                    /* Compliant         */
  ret_2007 = OPERATE2(dot_2007.x);                                    /* expect: 3432      */

  ret_2007 = OPERATE1((dot_2007.x));                                  /* Compliant         */
  ret_2007 = OPERATE2((dot_2007.x));                                  /* Compliant         */

  return ret_2007;
}

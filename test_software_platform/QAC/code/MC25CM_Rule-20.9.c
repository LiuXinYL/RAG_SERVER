/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.9.c
 *
 * MISRA Required - Rules
 *
 * Rule-20.9: All identifiers used in the controlling expression of #if or #elif
 *            preprocessing directives shall be #define'd before evaluation
 *
 * Enforced by message(s):
 *   3332   The macro '${name}' used in this '#if' or '#elif' expression is
 *          not defined.
 *
 *   3336   The reserved macro '${name}' used in this '#if' or '#elif'
 *          expression is not defined.
 *
 *
 *//* PRQA S 3332,3336 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#if X < 0                                                             /* expect:  3332 */
#define M 1
#endif

#define X 1

#if X < 0                                                             /* expect: !3332 */
#define N 1
#endif

extern int16_t rule_2009 (void)
{
  return 1;
}

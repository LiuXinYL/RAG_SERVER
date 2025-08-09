/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.13.c
 *
 * MISRA Required - Rules
 *
 * Rule-20.13: A line whose first token is # shall be a valid preprocessing
 *             directive
 *
 * Enforced by message(s):
 *   3115   Unrecognized preprocessing directive has been ignored because
 *          of conditional inclusion directives.
 *
 *
 *//* PRQA S 3115 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#define N 2

extern int16_t rule_2013 (void)
{
  int16_t ret_2013 = 1;

#ifndef N
  ret_2013 = 0;
/* Note misspelling below */
#alse                                                                 /* expect: 3115 */
  /* This section will be ignored because of the misspelling */
  ret_2013 = N;
#endif

  return ret_2013; /* Still equal to 1 */
}

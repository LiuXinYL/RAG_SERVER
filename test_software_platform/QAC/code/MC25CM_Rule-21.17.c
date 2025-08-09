/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.17.c
 *
 * MISRA Mandatory - Rules
 *
 * Rule-21.17: Use of the string handling functions from <string.h> shall not
 *             result in accesses beyond the bounds of the objects referenced by
 *             their pointer parameters
 *
 * Enforced by message(s):
 *   2835   Constant: Non-null terminated string used in a string function.
 *
 *   2836   Definite: Non-null terminated string used in a string function.
 *
 *   2935   Constant: Dereference of an invalid char pointer value.
 *
 *   2936   Definite: Dereference of an invalid char pointer value.
 *
 *   2937   Apparent: Dereference of an invalid char pointer value.
 *
 *   2938   Suspicious: Dereference of an invalid char pointer value.
 *
 *
 *//* PRQA S 2835,2836,2935,2936,2937,2938 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#include <string.h>

char * str_2117;

#define ARR_2117 (char []){ 'H', 'e', 'l', 'l', 'o' }

extern int16_t rule_2117 (void)
{
  char const lhs_2117 [5];
  char const rhs_2117 [5];

  strlen (ARR_2117);                                                 // expect: 2835
  strcmp (ARR_2117, str_2117);                                       // expect: 2835
  strcoll (ARR_2117, str_2117);                                      // expect: 2835

  // These examples are 'definite use of unset' and so it cannot be
  // said for sure that these are not null terminated.
  strlen (rhs_2117);                                                 // expect: !2836
  strcmp (lhs_2117, rhs_2117);                                       // expect: !2836
  strcoll (lhs_2117, rhs_2117);                                      // expect: !2836

  // The value of str_2117 is unknown.
  strlen (str_2117);                                                 // expect: !2836
  strcmp (lhs_2117, str_2117);                                       // expect: !2836
  strcmp (lhs_2117, str_2117);                                       // expect: !2836

  return 1;
}

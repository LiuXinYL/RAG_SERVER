/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-18.8.c
 *
 * MISRA Required - C99 and C11 Specific Rules
 *
 * Rule-18.8: Variable-length arrays shall not be used
 *
 * Enforced by message(s):
 *   1051   A variable length array has been declared.
 *
 *
 *//* PRQA S 1051 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1808( void )
{
  int16_t ret_1808;

  uint16_t size_1808 = 5;

  int16_t vla1_1808[size_1808];                                       /* expect: 1051 */
  rule_1808a (vla1_1808);

  ret_1808 = sizeof (int16_t[size_1808]);                             /* expect:!1051 */
  typedef uint16_t vector_1808 [size_1808];                           /* expect:!1051 */

  return ret_1808;
}

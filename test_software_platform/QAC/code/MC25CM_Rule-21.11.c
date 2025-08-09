/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.11.c
 *
 * MISRA Advisory - C99 and C11 Specific Rules
 *
 * Rule-21.11: The standard header file <tgmath.h> should not be used
 *
 * Enforced by message(s):
 *   5131   Use of standard header file <tgmath.h>.
 *
 *   5141   Use of type-generic math identifier
 *
 *
 *//* PRQA S 5131,5141 -- *//*
 * <<<------------------------------------------------------------ */


#include <tgmath.h>                                                   /* expect: 5131 */

#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_2111 (void)
{
  double d = sqrt (4);                                                /* expect: 5141 */

  return 1;
}

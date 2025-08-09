/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.1.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-20.1: #include directives should only be preceded by preprocessor
 *            directives or comments
 *
 * Enforced by message(s):
 *   5087   Use of #include directive after code fragment.
 *
 *
 *//* PRQA S 5087 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_2001 (void)
{
  return 1;
}

#include "MC25CM_Rule-20.1.h"                                           /* expect: 5087 */

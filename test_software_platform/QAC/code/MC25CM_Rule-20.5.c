/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.5.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-20.5: #undef should not be used
 *
 * Enforced by message(s):
 *   0841   Using '#undef'.
 *
 *   0847   Using '#undef' in a conditionally-excluded block.
 *
 *
 *//* PRQA S 0841,0847 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_2005 (void)
{
  return 1;
}

#define  L      0
#undef   L                                                            /* expect: 0841 */

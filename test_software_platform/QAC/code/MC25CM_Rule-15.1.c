/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-15.1.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-15.1: The goto statement should not be used
 *
 * Enforced by message(s):
 *   2001   A 'goto' statement has been used.
 *
 *
 *//* PRQA S 2001 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1501( void )
{
   goto rule_1501_label;                                              /* expect: 2001 */

rule_1501_label:

   return 1;
}

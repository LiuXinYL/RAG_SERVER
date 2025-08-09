/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-12.4.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-12.4: Evaluation of constant expressions should not lead to unsigned
 *            integer wrap-around
 *
 * Enforced by message(s):
 *   2910   Constant: Wraparound in unsigned arithmetic operation.
 *
 *
 *//* PRQA S 2910 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1204( void )
{
   0x1U - 0x2U;                    /* expect: 2910 */
   return 0;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-2.6.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-2.6: A function should not contain unused label declarations
 *
 * Enforced by message(s):
 *   3202   The label '%s:' is not used in this function and could be
 *          removed.
 *
 *
 *//* PRQA S 3202 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_0206( void )
{
    int16_t r0206_i;
    int16_t r0206_j;
    int16_t r0206_s16a;
    int16_t r0206_s16b;

L1: r0206_i = r0206_s16a;                                             /* expect: 3202 */

L2: r0206_j = r0206_s16b;                                             /* expect: 3202 */

    return r0206_i + r0206_j;
}

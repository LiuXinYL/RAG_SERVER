/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-7.1.c
 *
 * MISRA Required - Rules
 *
 * Rule-7.1: Octal constants shall not be used
 *
 * Enforced by message(s):
 *   0336   Macro defined as an octal constant.
 *
 *   0339   Octal constant used.
 *
 *
 *//* PRQA S 0336,0339 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#define MRET 015                                                      /* expect: 0336 */

extern int16_t rule_0701( void )
{
    int16_t r0701_i;
    int16_t r0701_j;
    int16_t r0701_k;

    r0701_i = 0xFF;
    r0701_j = 052;                                                    /* expect: 0339 */
    r0701_k = MRET;

    return r0701_i + r0701_j + r0701_k;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-11.8.c
 *
 * MISRA Required - Rules
 *
 * Rule-11.8: A conversion shall not remove any const, volatile or _Atomic
 *            qualification from the type pointed to by a pointer
 *
 * Enforced by message(s):
 *   0311   Dangerous pointer cast results in loss of const qualification.
 *
 *   0312   Dangerous pointer cast results in loss of volatile
 *          qualification.
 *
 *
 *//* PRQA S 0311,0312 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1108( void )
{
    const    uint8_t * pcuc;
    volatile uint8_t * pvuc;

    (uint8_t *)pcuc;                                                  /* expect: 0311 */
    (uint8_t *)pvuc;                                                  /* expect: 0312 */

    return 0;
}

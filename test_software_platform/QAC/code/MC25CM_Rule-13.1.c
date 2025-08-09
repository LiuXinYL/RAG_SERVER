/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-13.1.c
 *
 * MISRA Required - C99 and C11 Specific Rules
 *
 * Rule-13.1: Initializer lists shall not contain persistent side-effects
 *
 * Enforced by message(s):
 *   3421   Expression with persistent side effects is used in an
 *          initializer list.
 *
 *
 *//* PRQA S 3421 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

volatile uint16_t r1301_v1;

static void f_1301a (uint16_t ap[2]);

extern int16_t rule_1301( void )
{
    uint16_t ax[2] = { r1301_v1, 0 };                                 /* expect: 3421 */
    return 1;
}

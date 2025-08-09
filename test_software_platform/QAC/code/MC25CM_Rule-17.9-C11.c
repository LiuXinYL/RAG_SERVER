/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-17.9-C11.c
 *
 * MISRA Mandatory - C11 Specific Rules
 *
 * Rule-17.9-C11: A function declared with a _Noreturn function specifier shall not
 *                return to its caller
 *
 * Enforced by message(s):
 *   2886   This function returns to the caller despite being declared as
 *          non-returning.
 *
 *
 *//* PRQA S 2886 -- *//*
 * <<<------------------------------------------------------------ */
#include <stdlib.h>

#include "misra.h"
#include "mc25cmex.h"

static void rule_1709a ( void )                                /* c11_expect: !2886 */
{
    return;
}

static _Noreturn void rule_1709b ( void )                      /* c11_expect:  2886 */
{
    return;
}

static _Noreturn void rule_1709c ( void )                      /* c11_expect: !2886 */
{
    abort ();
    return;
}

extern int16_t rule_1709( void )
{
    rule_1709a();
    rule_1709b();
    rule_1709c();

    return 10;
}

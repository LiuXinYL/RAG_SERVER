/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-17.10-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-17.10-C11: A function declared with a _Noreturn function specifier shall
 *                 have void return type
 *
 * Enforced by message(s):
 *   1085   The function '%s' is being declared as _Noreturn but has a non-
 *          void return type.
 *
 *
 *//* PRQA S 1085 -- *//*
 * <<<------------------------------------------------------------ */
#include <stdlib.h>

#include "misra.h"
#include "mc25cmex.h"

static _Noreturn void rule_1710a ( void )                      /* expect: !1085 */
{
    abort ();
    return;
}

static _Noreturn int16_t rule_1710b ( void )                   /* c11_expect:  1085 */
{
    abort ();
    return 6;
}

extern int16_t rule_1710( void )
{
    rule_1710a();
    rule_1710b();

    return 11;
}
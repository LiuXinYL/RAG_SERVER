/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-17.12.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-17.12: A function identifier should only be used with either a preceding &,
 *             or with a parenthesised parameter list
 *
 * Enforced by message(s):
 *   3635   Function identifier used as a pointer without a preceding &
 *          operator.
 *
 *
 *//* PRQA S 3635 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

static int16_t rule_1712a ( void )
{
    return 11;
}

static void rule_1712b ( int16_t (* f_1712) (void) )
{
    return (*f_1712) ();
}

extern int16_t rule_1712( void )
{
    rule_1712b(rule_1712a);                                     /*  3635 */
    rule_1712b(&rule_1712a);

    return 12;
}

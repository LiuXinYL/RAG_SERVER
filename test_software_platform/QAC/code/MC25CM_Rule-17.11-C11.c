/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-17.11-C11.c
 *
 * MISRA Advisory - C11 Specific Rules
 *
 * Rule-17.11-C11: A function that never returns should be declared with a
 *                 _Noreturn function specifier
 *
 * Enforced by message(s):
 *   2885   This function doesn't return to the caller despite not being
 *          declared as non-returning.
 *
 *
 *//* PRQA S 2885 -- *//*
 * <<<------------------------------------------------------------ */
#include <stdlib.h>

#include "misra.h"
#include "mc25cmex.h"

static void rule_1711a ( void )                                /* c11_expect: !2885 */
{
    return;
}

static void rule_1711b ( void )                                /* c11_expect:  2885 */
{
    abort ();
    return;
}

static _Noreturn void rule_1711c ( void )                      /* c11_expect: !2885 */
{
    abort ();
    return;
}

static void rule_1711d (  )                                    /* c11_expect: !2885 */
{
    uint16_t a_1711 = 50;
    for (uint16_t i_1711 = 0; i_1711 < a_1711; ++ i_1711)
    {
      //
    }
}

static void rule_1711e ( void )                                /* c11_expect:  2885 */
{
    uint16_t b_1711 = 50;
    for (uint16_t j_1711 = 0; j_1711 < b_1711; )
    {
      //
    }
}

static _Noreturn void rule_1711f ( void )                      /* c11_expect: !2885 */
{
    uint16_t b_1711 = 50;
    for (uint16_t j_1711 = 0; j_1711 < b_1711; )
    {
      //
    }
}

extern int16_t rule_1711( void )                               /* c11_expect:  2885 */
{
    rule_1711a();
    rule_1711b();
    rule_1711c();
    rule_1711d();
    rule_1711e();
    rule_1711f();

    return 9;
}
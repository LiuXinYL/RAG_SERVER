/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.7_1.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-8.7: Functions and objects should not be defined with external linkage if
 *           they are referenced in only one translation unit
 *
 * Enforced by message(s):
 *   1504   The object '${name}' is only referenced in the translation unit
 *          where it is defined.
 *
 *   1505   The function '${name}' is only referenced in the translation
 *          unit where it is defined.
 *
 *   1514   The object '${entity}' is only referenced by function
 *          '${func}', in the translation unit where it is defined
 *
 *
 *//* PRQA S 1504,1505,1514 -- *//*
 * <<<------------------------------------------------------------ */

#include "MC25CM_Rule-8.7.h"

extern int16_t rule_0807a(void);       // expect: 1594

extern int16_t x0807;                  // expect: 1594

int16_t x0807 = 1;                     // expect: 1504

int16_t x0807_1 = 1;                   // expect: 1514

int16_t x0807_2 = 1;                   // expect: none

extern int16_t rule_0807( void )
{
    x0807 = rule_0807a();              // expect: 1579 1579

    return x0807_1;
}

extern int16_t rule_0807a(void)        // expect: 1505
{
    rule0807_foo();
    return x0807;                      // expect: 1579
}

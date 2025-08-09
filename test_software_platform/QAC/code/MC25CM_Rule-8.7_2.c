/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.7_2.c
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

int16_t rule0807_foo()                 // expect: none
{
    x0807_2 = 1;
    return x0807_2;
}

int16_t rule0807_bar()
{
    x0807_2 = 1;
    return x0807_2;
}

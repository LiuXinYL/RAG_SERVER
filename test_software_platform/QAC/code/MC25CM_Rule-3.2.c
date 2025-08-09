/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-3.2.c
 *
 * MISRA Required - C99 and C11 Specific Rules
 *
 * Rule-3.2: Line-splicing shall not be used in // comments
 *
 * Enforced by message(s):
 *   0247   '//' comment line ends with a backslash, continuing it to the
 *          next line.
 *
 *
 *//* PRQA S 0247 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"


extern int16_t rule_0302( void )
{
    int16_t r0302_x = 1;                                              /* expect: 0247 */    // comment \
    if (bla)
    {
        r0302_x = r0302_x + 1;                     /* This is always executed */
    }
    ++r0302_x;

    return r0302_x;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-14.1.c
 *
 * MISRA Required - Rules
 *
 * Rule-14.1: A loop counter shall not have essentially floating type
 *
 * Enforced by message(s):
 *   3339   Floating point variable used as 'while' loop control variable.
 *
 *   3340   Floating point variable used as 'for' loop control variable.
 *
 *
 *//* PRQA S 3339,3340 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

float32_t f32a_1401;
uint32_t u32a_1401;

extern int16_t rule_1401( void )
{
    uint16_t ui;
    uint16_t buf[10];
    float32_t ft;
    float32_t fuf[10];

    for (ui = 0u; ui < 10u; ++ui)
    {
        buf[ui] = ui + 4u;
        fuf[ui] = (float32_t)(ui);
    }

    for (ui = 0 ; buf[ui] < 10u ; ++ui )
    {
    }

    for (ft = 0.0f; ft < f32a_1401; ++ft)                             /* expect: 3340 */
    {
    }

    for (ui = 0 ; fuf[ui] < 5.0f ; ++ui )                             /* expect: !3340 */
    {
    }

    ft = 0.0f;

    /* The following while loop is non-compliant because ft
       is being used as a loop counter. */

    while (ft < 1.0f)                                                 /* expect: 3339 */
    {
        ft += 0.001f;
    }


    /* ft does not change in the following loop so cannot
       be a loop counter */

    ft = 1.1f;

    do                                                                /* expect: !3339 */
    {
        u32a_1401 --;
    } while (((float32_t)u32a_1401 - ft) > 10.0f);

    return 1;
}

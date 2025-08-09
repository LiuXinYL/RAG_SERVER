/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-14.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-14.2: A for loop shall be well-formed
 *
 * Enforced by message(s):
 *   2461   Loop control variable in this 'for' statement, ${name}, has
 *          file scope.
 *
 *   2462   The variable initialized in the first expression of this 'for'
 *          statement is not the variable identified as the 'loop
 *          control variable' (${name}).
 *
 *   2463   The variable incremented in the third expression of this 'for'
 *          statement is not the variable identified as the 'loop
 *          control variable' (${name}).
 *
 *   2464   Loop control variable, ${name}, modified twice in for-loop
 *          header.
 *
 *   2467   Loop control variable in this 'for' statement, ${name}, is not
 *          modified inside loop.
 *
 *   2468   Loop control variable in this 'for' statement, ${name}, is not
 *          modified inside loop but has file scope.
 *
 *   2469   Loop control variable in this 'for' statement, ${name}, is
 *          modified in the body of the loop.
 *
 *   2471   Unable to identify a 'for' loop control variable.
 *
 *   2472   More than one possible 'for' loop control variable.
 *
 *   2476   No variable appears to be initialized in the first expression
 *          of this 'for' statement (control variable identified as
 *          ${name}).
 *
 *   2477   No variable appears to be incremented in the third expression
 *          of this 'for' statement (control variable identified as
 *          ${name}).
 *
 *
 *//* PRQA S 2461,2462,2463,2464,2467,2468,2469,2471,2472,2476,2477 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t s16a_1402;
int16_t s16b_1402;

extern bool_t get_bool_1402()
{
    return 0;
}

extern int16_t get_s16_1402()
{
    return 16;
}

extern int16_t rule_1402( void )
{
    int16_t i_1402;
    int16_t j_1402;
    bool_t bl_1402;

    for (;;)
    {
        if (bl_1402)
        {
            break;
        }
    }

    bl_1402 = get_bool_1402();

    for (i_1402 = 0; i_1402 < 10; ++i_1402)
    {
    }

    i_1402 = 0;
    for (     ; i_1402 < 10; ++i_1402)
    {
    }

    for (s16a_1402 = 0; s16a_1402 < 10; ++s16a_1402)                  /* expect: 2461 */
    {
    }

    j_1402 = get_s16_1402();
    for (i_1402 = 0; j_1402 < 10; ++j_1402)                           /* expect: 2462 */
    {
        ++i_1402;
    }

    j_1402 = get_s16_1402();
    for (i_1402 = 0; i_1402++ < 10; ++j_1402)                         /* expect: 2463 */
    {
    }

    for (i_1402 = 0; ++i_1402 < 10; ++i_1402)                         /* expect: 2464 */
    {
    }

    for (i_1402 = 0; (i_1402 < 10) || bl_1402; ++i_1402)
    {
    }

    for (i_1402 = 0; i_1402 < 10; ++j_1402)                           /* expect: 2463  2467 */
    {
    }

    for (s16b_1402 = 0; s16b_1402 < 10; )                             /* expect: 2461  2468 */
    {
    }

    for (i_1402 = 0; i_1402 < 10; ++i_1402)
    {
        ++i_1402;                                                     /* expect: 2469       */
    }

    for (i_1402 = get_s16_1402(); i_1402 < s16a_1402; ++j_1402)       /* expect: 2463       */
    {
        ++i_1402;                                                     /* expect: 2469       */
    }

    for (i_1402 = 0, j_1402 = 5; (i_1402 < get_s16_1402()) && (j_1402 < 10); ++i_1402, ++j_1402) /* expect: 2472 */
    {
    }

    return 1;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-14.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-14.3: Controlling expressions shall not be invariant
 *
 * Enforced by message(s):
 *   2990   The value of this loop controlling expression is always 'true'.
 *
 *   2991   The value of this 'if' controlling expression is always 'true'.
 *
 *   2992   The value of this 'if' controlling expression is always
 *          'false'.
 *
 *   2993   The value of this 'do - while' loop controlling expression is
 *          always 'false'. The loop will only be executed once.
 *
 *   2994   The value of this 'while' or 'for' loop controlling expression
 *          is always 'false'. The loop will not be entered.
 *
 *   2997   The first operand of this conditional operator is always
 *          'true'.
 *
 *   2998   The first operand of this conditional operator is always
 *          'false'.
 *
 *   2741   This 'if' controlling expression is a constant expression and
 *          its value is 'true'.
 *
 *   2742   This 'if' controlling expression is a constant expression and
 *          its value is 'false'.
 *
 *   2990   The value of this loop controlling expression is always 'true'.
 *
 *   2991   The value of this 'if' controlling expression is always 'true'.
 *
 *   2992   The value of this 'if' controlling expression is always
 *          'false'.
 *
 *   2993   The value of this 'do - while' loop controlling expression is
 *          always 'false'. The loop will only be executed once.
 *
 *   2994   The value of this 'while' or 'for' loop controlling expression
 *          is always 'false'. The loop will not be entered.
 *
 *   2997   The first operand of this conditional operator is always
 *          'true'.
 *
 *   2998   The first operand of this conditional operator is always
 *          'false'.
 *
 *   3493   The first operand of this conditional operator is always
 *          constant 'true'.
 *
 *   3494   The first operand of this conditional operator is always
 *          constant 'false'.
 *
 *
 *//* PRQA S 2990,2991,2992,2993,2994,2997,2998,2741,2742,2990,2991,2992,2993,2994,2997,2998,3493,3494 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

enum {
    enum_1403 = 1
};

int16_t s16a_1403;                                         // expect: 1594 1594 1594 1594
uint16_t u16a_1403;

extern int16_t rule_1403( void )
{
    int16_t loop_1403 = 1;                                 // expect: 1575 1575

    if (12)                                                // expect: 2741
    {
    }

    if (enum_1403 == enum_1403)                            // expect: 2741
    {
    }

    if (0)                                                 // expect: 2742
    {
    }

    if (enum_1403 - enum_1403)                             // expect: 2742
    {
    }

    while (loop_1403 != 0)                                 // expect: 2990
    {
        if (s16a_1403 > 10)                                // expect: 1575 1575 1575 1575
        {
            break;
        }
    }

    while (loop_1403 == 0)                                 // expect: 2994
    {
    }

    if ((s16a_1403 < 10) || (s16a_1403 > 0))               // expect: 2991 1575
    {
    }

    if ((s16a_1403 < 10) && (s16a_1403 > 20))              // expect: 2992
    {
    }

    do
    {
        ++u16a_1403;                                       // expect: 1575
    } while (u16a_1403 < 0u);                              // expect: 2993

    u16a_1403 =
      ((s16a_1403 < 10) || (s16a_1403 > 0)) ? 1 : 0;       // expect: 2997

    u16a_1403 =
      ((s16a_1403 < 10) && (s16a_1403 > 20)) ? 1 : 0;      // expect: 2998

    u16a_1403 =
      ((enum_1403 < 10) || (enum_1403 > 0)) ? 1 : 0;       // expect: 3493

    u16a_1403 =
      ((enum_1403 < 10) && (enum_1403 > 20)) ? 1 : 0;      // expect: 3494

    return 1;
}

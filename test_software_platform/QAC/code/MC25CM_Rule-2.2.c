/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-2.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-2.2: A project shall not contain dead code
 *
 * Enforced by message(s):
 *   2980   The value of this function parameter is never used before being
 *          modified.
 *
 *   2982   This assignment is redundant. The value of this object is never
 *          used before being modified.
 *
 *   2983   This assignment is redundant. The value of this object is never
 *          subsequently used.
 *
 *   2985   This operation is redundant. The value of the result is always
 *          that of the left-hand operand.
 *
 *   2986   This operation is redundant. The value of the result is always
 *          that of the right-hand operand.
 *
 *   2987   This function call produces no side effects and is redundant.
 *
 *   2995   The result of this logical operation is always 'true'.
 *
 *   2996   The result of this logical operation is always 'false'.
 *
 *   2995   The result of this logical operation is always 'true'.
 *
 *   2996   The result of this logical operation is always 'false'.
 *
 *   3110   The left-hand operand of this ',' has no side effects.
 *
 *   3112   This statement has no side-effect - it can be removed.
 *
 *   3404   Statement contains a redundant * operator at top level. *p++
 *          means *(p++) not (*p)++.
 *
 *   3422   Statement contains a redundant operator at top level.
 *
 *   3423   Statement contains a redundant cast at top level.
 *
 *   3424   Statement contains a redundant & or | at top level.
 *
 *   3425   One branch of this conditional operation is a redundant
 *          expression.
 *
 *   3426   Right hand side of comma expression has no side effect and its
 *          value is not used.
 *
 *   3427   Right hand side of logical operator has no side effect and its
 *          value is not used.
 *
 *
 *//* PRQA S 2980,2982,2983,2985,2986,2987,2995,2996,2995,2996,3110,3112,3404,3422,3423,3424,3425,3426,3427 -- *//*
 * <<<------------------------------------------------------------ */


#include <stdbool.h>
#include "misra.h"
#include "mc25cmex.h"

PC *r0202_ptr;
int16_t r0202_s16a;
int16_t r0202_s16b;
int16_t r0202_s16c;
uint32_t r0202_u32a;
uint32_t r0202_u32b;
BL r0202_blb;

static BL get_bool(void)                                               // expect: 1593
{
    return true;
}

// static int16_t rule_0202a(int16_t p, int16_t q);

extern int16_t rule_0202( void )
{
    return 1;
}

static int16_t rule_0202a(int16_t p, int16_t q)                        // expect: 2980 1594 1594 1594
{
    int16_t y;                                                         // expect: 1594
    int16_t x = 0;
    int16_t z = 0;                                                     // expect: 1575 1575
    x = 2;
    p = 6;                                                             // expect: 2982 1585
    y = q;                                                             // expect: 2983

    (int16_t)(p = q);                                                  // expect: 3423 1575 1585 1575
    *r0202_ptr++;                                                      // expect: 3404
    x + r0202_ptr++;                                                   // expect: 3422
    x & rule_0202();                                                   // expect: 3424
    if (r0202_s16a > 20)                                               // expect: 1575 1575
    {
        if (r0202_s16a > 10)                                           // expect: 2995
        {
        }

        if (r0202_s16a < 5)                                            // expect: 2996
        {
        }
    }

    r0202_s16a * r0202_s16b, r0202_s16c = 1;                           // expect: 3110
    r0202_s16a * r0202_s16b;                                           // expect: 3112

    (r0202_u32a > r0202_u32b) ? r0202_s16a = r0202_s16b : r0202_s16b;  // expect: 3425
    r0202_s16b = 3, r0202_s16a * r0202_s16b;                           // expect: 3426
    get_bool() && r0202_blb;                                           // expect: 3427

    get_bool();                                                        // expect: 2987
    z + p;                                                             // expect: 2986 3112
    return p + z;                                                      // expect: 2985
}

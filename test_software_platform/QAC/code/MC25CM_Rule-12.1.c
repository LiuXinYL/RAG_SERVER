/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-12.1.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-12.1: The precedence of operators within expressions should be made
 *            explicit
 *
 * Enforced by message(s):
 *   3389   Extra parentheses recommended to clarify the ordering of a %
 *          operator and another arithmetic operator (* / % + -).
 *
 *   3391   Extra parentheses recommended. A conditional operation is the
 *          operand of another conditional operator.
 *
 *   3392   Extra parentheses recommended. A shift, relational or equality
 *          operation is the operand of a second identical operator.
 *
 *   3394   Extra parentheses recommended. A shift, relational or equality
 *          operation is the operand of a different operator with the
 *          same precedence.
 *
 *   3395   Extra parentheses recommended. A * or / operation is the
 *          operand of a + or - operator.
 *
 *   3396   Extra parentheses recommended. A binary operation is the
 *          operand of a conditional operator.
 *
 *   3397   Extra parentheses recommended. A binary operation is the
 *          operand of a binary operator with different precedence.
 *
 *   3433   Expression operand to sizeof is not parenthesized.
 *
 *
 *//* PRQA S 3389,3391,3392,3394,3395,3396,3397,3433 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#include <stddef.h>

static int32_t r12001_a;
static int32_t r12001_b;
static int32_t r12001_c;
static int32_t r12001_d;
static int32_t r12001_e;

extern int16_t rule_1201( void )
{
    size_t sz;
    r12001_c ? r12001_d : r12001_e ? r12001_a : r12001_b;               /* expect: 3391 3390 */
    r12001_a == r12001_b == r12001_c;                                   /* expect: 3392 3390 */
    r12001_a == r12001_b != r12001_c;                                   /* expect: 3394 3390 */
    r12001_a * r12001_b -  r12001_c;                                    /* expect: 3395 3390 */
    r12001_d = r12001_a == r12001_b ? r12001_a : r12001_a - r12001_b;   /* expect: 3396 3390 */
    r12001_a * r12001_b || r12001_c;                                    /* expect: 3397 3390 */
    r12001_a * r12001_b %  r12001_c;                                    /* expect: 3389 3390 */
    sz = sizeof r12001_a - r12001_b;                                    /* expect: 3433      */

    return 1;
}

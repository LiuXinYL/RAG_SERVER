/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-10.1.c
 *
 * MISRA Required - Rules
 *
 * Rule-10.1: Operands shall not be of an inappropriate essential type
 *
 * Enforced by message(s):
 *   3101   Unary '-' applied to an operand of type unsigned int or
 *          unsigned long gives an unsigned result.
 *
 *   3102   Unary '-' applied to an operand whose underlying type is
 *          unsigned.
 *
 *   4115   Operand of logical && or || operator is not an 'essentially
 *          Boolean' expression.
 *
 *   4116   Operand of logical ! operator is not an 'essentially Boolean'
 *          expression.
 *
 *   4500   An expression of 'essentially Boolean' type (%1s) is being used
 *          as an array subscript.
 *
 *   4501   An expression of 'essentially Boolean' type (%1s) is being used
 *          as the %2s operand of this arithmetic operator (%3s).
 *
 *   4502   An expression of 'essentially Boolean' type (%1s) is being used
 *          as the %2s operand of this bitwise operator (%3s).
 *
 *   4503   An expression of 'essentially Boolean' type (%1s) is being used
 *          as the left-hand operand of this shift operator (%2s).
 *
 *   4504   An expression of 'essentially Boolean' type (%1s) is being used
 *          as the right-hand operand of this shift operator (%2s).
 *
 *   4505   An expression of 'essentially Boolean' type (%1s) is being used
 *          as the %2s operand of this relational operator (%3s).
 *
 *   4507   An expression of 'essentially Boolean' type (%1s) is being used
 *          as the operand of this increment/decrement operator (%2s).
 *
 *   4510   An expression of 'essentially character' type (%1s) is being
 *          used as an array subscript.
 *
 *   4511   An expression of 'essentially character' type (%1s) is being
 *          used as the %2s operand of this arithmetic operator (%3s).
 *
 *   4512   An expression of 'essentially character' type (%1s) is being
 *          used as the %2s operand of this bitwise operator (%3s).
 *
 *   4513   An expression of 'essentially character' type (%1s) is being
 *          used as the left-hand operand of this shift operator
 *          (%2s).
 *
 *   4514   An expression of 'essentially character' type (%1s) is being
 *          used as the right-hand operand of this shift operator
 *          (%2s).
 *
 *   4518   An expression of 'essentially character' type (%1s) is being
 *          used as the %2s operand of this logical operator (%3s).
 *
 *   4519   An expression of 'essentially character' type (%1s) is being
 *          used as the first operand of this conditional operator
 *          (%2s).
 *
 *   4521   An expression of 'essentially enum' type (%1s) is being used as
 *          the %2s operand of this arithmetic operator (%3s).
 *
 *   4522   An expression of 'essentially enum' type (%1s) is being used as
 *          the %2s operand of this bitwise operator (%3s).
 *
 *   4523   An expression of 'essentially enum' type (%1s) is being used as
 *          the left-hand operand of this shift operator (%2s).
 *
 *   4524   An expression of 'essentially enum' type (%1s) is being used as
 *          the right-hand operand of this shift operator (%2s).
 *
 *   4527   An expression of 'essentially enum' type is being used as the
 *          operand of this increment/decrement operator.
 *
 *   4528   An expression of 'essentially enum' type (%1s) is being used as
 *          the %2s operand of this logical operator (%3s).
 *
 *   4529   An expression of 'essentially enum' type (%1s) is being used as
 *          the first operand of this conditional operator (%2s).
 *
 *   4532   An expression of 'essentially signed' type (%1s) is being used
 *          as the %2s operand of this bitwise operator (%3s).
 *
 *   4533   An expression of 'essentially signed' type (%1s) is being used
 *          as the left-hand operand of this shift operator (%2s).
 *
 *   4534   An expression of 'essentially signed' type (%1s) is being used
 *          as the right-hand operand of this shift operator (%2s).
 *
 *   4538   An expression of 'essentially signed' type (%1s) is being used
 *          as the %2s operand of this logical operator (%3s).
 *
 *   4539   An expression of 'essentially signed' type (%1s) is being used
 *          as the first operand of this conditional operator (%2s).
 *
 *   4542   A non-negative constant expression of 'essentially signed' type
 *          (%1s) is being used as the %2s operand of this bitwise
 *          operator (%3s).
 *
 *   4543   A non-negative constant expression of 'essentially signed' type
 *          (%1s) is being used as the left-hand operand of this shift
 *          operator (%2s).
 *
 *   4548   A non-negative constant expression of 'essentially signed' type
 *          (%1s) is being used as the %2s operand of this logical
 *          operator (%3s).
 *
 *   4549   A non-negative constant expression of 'essentially signed' type
 *          (%1s) is being used as the first operand of this
 *          conditional operator (%2s).
 *
 *   4558   An expression of 'essentially unsigned' type (%1s) is being
 *          used as the %2s operand of this logical operator (%3s).
 *
 *   4559   An expression of 'essentially unsigned' type (%1s) is being
 *          used as the first operand of this conditional operator
 *          (%2s).
 *
 *   4568   An expression of 'essentially floating' type (%1s) is being
 *          used as the %2s operand of this logical operator (%3s).
 *
 *   4569   An expression of 'essentially floating' type (%1s) is being
 *          used as the first operand of this conditional operator
 *          (%2s).
 *
 *
 *//* PRQA S 3101,3102,4115,4116,4500,4501,4502,4503,4504,4505,4507,4510,4511,4512,4513,4514,4518,4519,4521,4522,4523,4524,4527,4528,4529,4532,4533,4534,4538,4539,4542,4543,4548,4549,4558,4559,4568,4569 -- *//*
 * <<<------------------------------------------------------------ */


#include <stdbool.h>
#include "misra.h"
#include "mc25cmex.h"

BL r1001_bla;
uint16_t r1001_u16a;
uint16_t r1001_u16b;
PC r1001_pca;
N1 r1001_n1a;
float32_t r1001_fta;
int16_t r1001_s16a;
uint8_t r1001_u8b;

extern int16_t rule_1001_Boolean( void )
{
    uint16_t buf[10] = {0};

    buf[r1001_bla];                                                   /* expect: 4500 */
    r1001_bla + r1001_u16a;                                           /* expect: 4501 */
    r1001_bla & r1001_u16a;                                           /* expect: 4502 */
    r1001_bla << 1u;                                                  /* expect: 4503 */
    r1001_u16a << r1001_bla;                                          /* expect: 4504 */
    r1001_bla <  r1001_u16a;                                          /* expect: 4505 */
    ++r1001_bla;                                                      /* expect: 4507 */

    return 1;
}

extern int16_t rule_1001_character( void )
{
    uint16_t buf[300] = {0};

    buf[r1001_pca];                                                   /* expect: 4510       */
    r1001_pca % r1001_u16a;                                           /* expect: 4511       */
    r1001_pca & r1001_u16a;                                           /* expect: 4512       */
    r1001_pca << 1u;                                                  /* expect: 4513       */
    r1001_u16a << r1001_pca;                                          /* expect: 4514       */
    r1001_bla  || r1001_pca;                                          /* expect: 4518  4115 */
    r1001_pca ? r1001_u16a : r1001_u16b;                              /* expect: 4519       */

    return 1;
}

extern int16_t rule_1001_enum( void )
{
    r1001_u16a  - r1001_n1a;                                          /* expect: 4521       */
    r1001_n1a & r1001_u16a;                                           /* expect: 4522       */
    r1001_n1a << 1u;                                                  /* expect: 4523       */
    r1001_u16a << r1001_n1a;                                          /* expect: 4524       */
    ++r1001_n1a;                                                      /* expect: 4527       */
    r1001_n1a && r1001_bla;                                           /* expect: 4528  4115 */
    r1001_n1a ? r1001_u16a : r1001_u16b;                              /* expect: 4529       */

    return 1;
}

extern int16_t rule_1001_floating( void )
{
    r1001_fta || r1001_bla;                                           /* expect: 4568  4115 */
    r1001_fta ? r1001_u16a : r1001_u16b;                              /* expect: 4569       */

    return 1;
}

extern int16_t rule_1001_signed( void )
{
    r1001_s16a & r1001_u16a;                                          /* expect: 4532       */
    r1001_s16a << 0u;                                                 /* expect: 4533       */
    r1001_u16a >> r1001_s16a;                                         /* expect: 4534       */
    r1001_s16a && r1001_bla;                                          /* expect: 4538  4115 */
    r1001_s16a ? r1001_u16a : r1001_u16b;                             /* expect: 4539       */
    3 & r1001_u16a;                                                   /* expect: 4542       */
    3 >> 1u;                                                          /* expect: 4543       */
    3 && r1001_bla;                                                   /* expect: 4548       */
    3 ? r1001_u16a : r1001_u16b;                                      /* expect: 4549       */

    return 1;
}

extern int16_t rule_1001_unsigned( void )
{
    -r1001_u16b;                                                      /* expect: 3101       */
    -r1001_u8b;                                                       /* expect: 3102       */
    r1001_u16b || r1001_bla;                                          /* expect: 4558  4115 */
    r1001_u16b ? r1001_u16a : r1001_u16b;                             /* expect: 4559       */

    return 1;
}

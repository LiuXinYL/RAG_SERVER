/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-10.4.c
 *
 * MISRA Required - Rules
 *
 * Rule-10.4: Both operands of an operator in which the usual arithmetic
 *            conversions are performed shall have the same essential type
 *            category
 *
 * Enforced by message(s):
 *   1800   The ${side} operand (essential type: '${from}') will be
 *          implicitly converted to a floating type, '${to}', in this
 *          arithmetic operation.
 *
 *   1802   The ${side} operand (essential type: '${from}') will be
 *          implicitly converted to a floating type, '${to}', in this
 *          relational operation.
 *
 *   1803   The ${side} operand (essential type: '${from}') will be
 *          implicitly converted to a floating type, '${to}', in this
 *          equality operation.
 *
 *   1804   The ${side} operand (essential type: '${from}') will be
 *          implicitly converted to a floating type, '${to}', in this
 *          conditional operation.
 *
 *   1820   The %1s operand is non-constant and 'essentially signed' (%2s)
 *          but will be implicitly converted to an unsigned type (%3s)
 *          in this arithmetic operation.
 *
 *   1821   The %1s operand is non-constant and 'essentially signed' (%2s)
 *          but will be implicitly converted to an unsigned type (%3s)
 *          in this bitwise operation.
 *
 *   1822   The %1s operand is non-constant and 'essentially signed' (%2s)
 *          but will be implicitly converted to an unsigned type (%3s)
 *          in this relational operation.
 *
 *   1823   The %1s operand is non-constant and 'essentially signed' (%2s)
 *          but will be implicitly converted to an unsigned type (%3s)
 *          in this equality operation.
 *
 *   1824   The %1s operand is non-constant and 'essentially signed' (%2s)
 *          but will be implicitly converted to an unsigned type (%3s)
 *          in this conditional operation.
 *
 *   1830   The %1s operand is constant, 'essentially signed' (%2s) and
 *          negative but will be implicitly converted to an unsigned
 *          type (%3s) in this arithmetic operation.
 *
 *   1831   The %1s operand is constant, 'essentially signed' (%2s) and
 *          negative but will be implicitly converted to an unsigned
 *          type (%3s) in this bitwise operation.
 *
 *   1832   The %1s operand is constant, 'essentially signed' (%2s) and
 *          negative but will be implicitly converted to an unsigned
 *          type (%3s) in this relational operation.
 *
 *   1833   The %1s operand is constant, 'essentially signed' (%2s) and
 *          negative but will be implicitly converted to an unsigned
 *          type (%3s) in this equality operation.
 *
 *   1834   The %1s operand is constant, 'essentially signed' (%2s) and
 *          negative but will be implicitly converted to an unsigned
 *          type (%3s) in this conditional operation.
 *
 *   1840   The %1s operand is constant, 'essentially signed' (%2s) and
 *          non-negative but will be implicitly converted to an
 *          unsigned type (%3s) in this arithmetic operation.
 *
 *   1841   The %1s operand is constant, 'essentially signed' (%2s) and
 *          non-negative but will be implicitly converted to an
 *          unsigned type (%3s) in this bitwise operation.
 *
 *   1842   The %1s operand is constant, 'essentially signed' (%2s) and
 *          non-negative but will be implicitly converted to an
 *          unsigned type (%3s) in this relational operation.
 *
 *   1843   The %1s operand is constant, 'essentially signed' (%2s) and
 *          non-negative but will be implicitly converted to an
 *          unsigned type (%3s) in this equality operation.
 *
 *   1844   The %1s operand is constant, 'essentially signed' (%2s) and
 *          non-negative but will be implicitly converted to an
 *          unsigned type (%3s) in this conditional operation.
 *
 *   1850   The %1s operand is 'essentially unsigned' (%2s) but will be
 *          implicitly converted to a signed type (%3s) in this
 *          arithmetic operation.
 *
 *   1851   The %1s operand is 'essentially unsigned' (%2s) but will be
 *          implicitly converted to a signed type (%3s) in this
 *          bitwise operation.
 *
 *   1852   The %1s operand is 'essentially unsigned' (%2s) but will be
 *          implicitly converted to a signed type (%3s) in this
 *          relational operation.
 *
 *   1853   The %1s operand is 'essentially unsigned' (%2s) but will be
 *          implicitly converted to a signed type (%3s) in this
 *          equality operation.
 *
 *   1854   The %1s operand is 'essentially unsigned' (%2s) but will be
 *          implicitly converted to a signed type (%3s) in this
 *          conditional operation.
 *
 *   1860   The operands of this arithmetic operator are of different
 *          'essential signedness' but will generate a result of type
 *          'signed int'.
 *
 *   1861   The operands of this bitwise operator are of different
 *          'essential signedness' but will generate a result of type
 *          'signed int'.
 *
 *   1862   The operands of this relational operator are of different
 *          'essential signedness' but will both be promoted to
 *          'signed int' for comparison.
 *
 *   1863   The operands of this equality operator are of different
 *          'essential signedness' but will both be promoted to
 *          'signed int' for comparison.
 *
 *   1864   The 2nd and 3rd operands of this conditional operator are of
 *          different 'essential signedness'. The result will be in
 *          the promoted type 'signed int'.
 *
 *   1880   The operands of this relational operator are expressions of
 *          different 'essential type' categories (%1s and %2s).
 *
 *   1881   The operands of this equality operator are expressions of
 *          different 'essential type' categories (%1s and %2s).
 *
 *   1882   The 2nd and 3rd operands of this conditional operator are
 *          expressions of different 'essential type' categories (%1s
 *          and %2s).
 *
 *
 *//* PRQA S 1800,1802,1803,1804,1820,1821,1822,1823,1824,1830,1831,1832,1833,1834,1840,1841,1842,1843,1844,1850,1851,1852,1853,1854,1860,1861,1862,1863,1864,1880,1881,1882 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1004( void )
{
    int32_t r1004_s32a;
    int8_t r1004_s8a;
    uint32_t r1004_u32a;
    uint32_t r1004_u32b;
    uint16_t r1004_u16a;
    uint8_t r1004_u8a;
    float32_t r1004_f32a;
    PC r1004_pca;
    N1 r1004_n1a;

    r1004_s32a +  r1004_f32a;                                         /* expect: 1800 */
    r1004_n1a > r1004_f32a;                                           /* expect: 1802 */
    r1004_n1a == r1004_f32a;                                          /* expect: 1803 */
    (r1004_u32a > r1004_u32b) ? r1004_n1a : r1004_f32a;               /* expect: 1804 */

    r1004_s32a *  r1004_u32a;                                         /* expect: 1820 */
    r1004_s32a &  r1004_u32a;                                         /* expect: 1821 */
    r1004_s32a <  r1004_u32a;                                         /* expect: 1822 */
    r1004_s32a == r1004_u32a;                                         /* expect: 1823 */
    (r1004_u32a > r1004_u32b) ? r1004_s32a : r1004_u32a;              /* expect: 1824 */

    -123 +  r1004_u32a;                                               /* expect: 1830 */
    -123 &  r1004_u32a;                                               /* expect: 1831 */
    -123 <  r1004_u32a;                                               /* expect: 1832 */
    -123 == r1004_u32a;                                               /* expect: 1833 */
    (r1004_u32a > r1004_u32b) ? -123 : r1004_u32a;                    /* expect: 1834 */

    1234 +  r1004_u32a;                                               /* expect: 1840 */
    1234 &  r1004_u32a;                                               /* expect: 1841 */
    1234 <  r1004_u32a;                                               /* expect: 1842 */
    1234 == r1004_u32a;                                               /* expect: 1843 */
    (r1004_u32a > r1004_u32b) ? 1234 : r1004_u32a;                    /* expect: 1844 */

    r1004_s32a +  r1004_u16a;                                         /* expect: 1850 */
    r1004_s32a &  r1004_u16a;                                         /* expect: 1851 */
    r1004_s32a <  r1004_u16a;                                         /* expect: 1852 */
    r1004_s32a != r1004_u16a;                                         /* expect: 1853 */
    (r1004_u32a > r1004_u32b) ? r1004_s32a : r1004_u16a;              /* expect: 1854 */

    r1004_s8a +  r1004_u8a;                                           /* expect: 1860 */
    r1004_s8a &  r1004_u8a;                                           /* expect: 1861 */
    r1004_s8a <  r1004_u8a;                                           /* expect: 1862 */
    r1004_s8a == r1004_u8a;                                           /* expect: 1863 */
    (r1004_u32a > r1004_u32b) ? r1004_s8a : r1004_u8a;                /* expect: 1864 */

    r1004_pca > r1004_n1a;                                            /* expect: 1880 */
    r1004_pca == r1004_n1a;                                           /* expect: 1881 */
    (r1004_u32a > r1004_u32b) ? r1004_pca : r1004_n1a;                /* expect: 1882 */



    return 0;
}

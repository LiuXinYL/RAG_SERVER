/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.12.c
 *
 * MISRA Required - Rules
 *
 * Rule-8.12: Within an enumerator list, the value of an implicitly-specified
 *            enumeration constant shall be unique
 *
 * Enforced by message(s):
 *   0724   The value of this implicitly-specified enumeration constant is
 *          not unique.
 *
 *
 *//* PRQA S 0724 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

enum T1 { A1=3, A2, A3, A4=5 };                                       /* expect: 0724 */
enum T2 { B1=2, B2=0, B3, B4 };                                       /* expect: 0724 */

int16_t rule_0812b(enum T1 t1, enum T2 t2)
{
    return 0;
}

void rule_0812a( void )
{
    enum T1 r0812_t1 = A1;
    enum T2 r0812_t2 = B1;
    rule_0812b(r0812_t1, r0812_t2);
}

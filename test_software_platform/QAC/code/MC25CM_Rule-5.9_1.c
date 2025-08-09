/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-5.9_1.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-5.9: Identifiers that define objects or functions with internal linkage
 *           should be unique
 *
 * Enforced by message(s):
 *   1525   Object/function '${name}' with external linkage has same
 *          identifier as another object/function with internal
 *          linkage.
 *
 *   1527   Object/function '${name}' with internal linkage has same
 *          identifier as another object/function with internal
 *          linkage.
 *
 *   1528   Object '${name}' with no linkage has same identifier as another
 *          object/function with internal linkage.
 *
 *   1759   Object '${name}' with internal linkage is not unique.
 *
 *
 *//* PRQA S 1525,1527,1528,1759 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

extern int16_t obj_0509a = 0;          // expect: 1525 1594 1594
static int16_t obj_0509c = 0;          // expect: 1527 1594 1594

extern int16_t rule_0509( void )
{
    struct s_0509b                     // expect: 1759 1594
    {
        int16_t m_0509b;               // expect: 1759 1594
    };
    int16_t obj_0509b = 0;             // expect: 1528 1594
    return 1;
}

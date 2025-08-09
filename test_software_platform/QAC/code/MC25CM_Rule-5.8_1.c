/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-5.8_1.c
 *
 * MISRA Required - Rules
 *
 * Rule-5.8: Identifiers that define objects or functions with external linkage
 *           shall be unique
 *
 * Enforced by message(s):
 *   1525   Object/function '${name}' with external linkage has same
 *          identifier as another object/function with internal
 *          linkage.
 *
 *   1526   Object '${name}' with no linkage has same identifier as another
 *          object/function with external linkage.
 *
 *   1756   External identifier '${name}' shall be unique.
 *
 *   1758   Object '${name}' with external linkage is not unique.
 *
 *
 *//* PRQA S 1525,1526,1756,1758 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

extern int16_t obj_0508a;              /* expect: 1525 1594 1594 1594 1756 */

extern int16_t obj_0508b;              /* expect: 1526 1594 1594 1594 1756 */

int16_t obj_0508a = 5;                 /* expect: 1525 1594 1594 1594 1756 */

int16_t obj_0508b = 5;                 /* expect: 1526 1594 1594 1594 1756 */

extern int16_t rule_0508( void )
{
    struct s_0508a                     // expect: 1758 1594 1756 1594
    {
        int16_t m_0508a;               // expect: 1758 1594 1756 1594
    };

    int16_t obj_0508b;                 /* expect: 1526 1594 1594 1594 1756 */

    obj_0508b = 5;

    return 1;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-17.13.c
 *
 * MISRA Required - Rules
 *
 * Rule-17.13: A function type shall not be type qualified
 *
 * Enforced by message(s):
 *   1147   Qualifying a function type is undefined.
 *
 *
 *//* PRQA S 1147 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

const uint16_t        rule_1713a (void);  /* expect: !1147 */
const uint16_t       *rule_1713b (void);  /* expect: !1147 */

typedef uint16_t    rule_1713c (void);    /* expect: !1147 */
typedef rule_1713c   const rule_1713d;    /* expect:  1147 */
typedef rule_1713c         rule_1713e;    /* expect: !1147 */
typedef rule_1713c * const rule_1713f;    /* expect: !1147 */

extern int16_t rule_1713( void )
{
    rule_1713a ();
    rule_1713b ();

    return 13;
}

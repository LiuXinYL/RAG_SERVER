/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-9.6.c
 *
 * MISRA Required - Rules
 *
 * Rule-9.6: An initializer using chained designators shall not contain
 *           initializers without designators
 *
 * Enforced by message(s):
 *   1395   This initializer specifies both chained designators and
 *          positional initializers.
 *
 *
 *//* PRQA S 1395 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

struct Rule_0906_S
{
    int32_t x;
    int32_t y;
};

struct Rule_0906_T
{
    int32_t            w;
    struct Rule_0906_S s;
    int32_t            z;
};

/* Non-compliant - chained designators and implicit positional initializers mixed */
static struct Rule_0906_T tt = {
    1,
    .s.x = 2,   /* To a human reader, this looks like .z is being initialized     */    /*  1395 */
    3,          /* tt is actually initialized as { 1, { 2, 3 }, 0 }               */    /*  1395 */
};              /* This also violates Rule 9.2                                    */


/* Compliant - allow the y dimension to implicitly initialize to zero             */
static struct Rule_0906_S aa[5] = {
    [0].x = 1,
    [1].x = 2,
    [2].x = 3,
    [3].x = 4,
    [4].x = 5,
};

/* Compliant - the initializer for [1] is not chained, but is explicit            */
static struct Rule_0906_S ab[2] = {
    [0].x = 1,
    [1] = { 2, 3 }, /* Compliant by exception:                                    */
};                  /* the positional initializers are inside a braced sub-object */

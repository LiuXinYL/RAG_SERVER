/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-5.6_1.c
 *
 * MISRA Required - Rules
 *
 * Rule-5.6: A typedef name shall be a unique identifier
 *
 * Enforced by message(s):
 *   1506   The identifier '${name}' is declared as a typedef and is used
 *          elsewhere for a different kind of declaration.
 *
 *   1507   '${name}' is used as a typedef for different types.
 *
 *   1508   The typedef '${name}' is declared in more than one location.
 *
 *
 *//* PRQA S 1506,1507,1508 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

struct t0506a {                                                       /* expect: 1506 1581 1581 */
    int8_t a;
};
typedef void *    t0506a;                                             /* expect: 1506 1581 1581 */

typedef int16_t   t0506b;                                             /* expect: 1507 1581      */

typedef int16_t   t0506c;                                             /* expect: 1508 1581 1581 */
typedef int16_t   t0506c;                                             /* expect: 1508 1581 1581 */

int16_t rule_0506(void)
{
    struct t0506a r0505_a;
    return 1;
}

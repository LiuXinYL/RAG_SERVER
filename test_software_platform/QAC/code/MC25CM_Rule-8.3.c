/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-8.3: All declarations of an object or function shall use the same names and
 *           type qualifiers
 *
 * Enforced by message(s):
 *   0606   Object '%s' is declared using typedefs which are different to
 *          those in a previous declaration.
 *
 *   0624   Function '%s' is declared using typedefs which are different to
 *          those in a previous declaration.
 *
 *   1330   The parameter identifiers in this function declaration differ
 *          from those in a previous declaration.
 *
 *   3675   Function parameter declared with type qualification which
 *          differs from previous declaration.
 *
 *   1707   Function '${name}' is not using the same aliases.
 *
 *   1708   Function '${name}' is not using the same qualifiers.
 *
 *   1709   Function '${name}' is not using the same parameter names.
 *
 *
 *//* PRQA S 0606,0624,1330,3675,1707,1708,1709 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

static int16_t rule_0803a(int16_t aa);
static int16_t rule_0803b(const int16_t bb);
static int16_t rule_0803c(int16_t cc);

typedef int16_t MOD;

extern int16_t rule_0803( void )
{
    int16_t n;
    n = rule_0803a(1);
    n = n + rule_0803b(2);
    n = n + rule_0803c(3);

    return n;
}

static int16_t rule_0803a(int16_t aaa)                                /* expect:  1330 */
{
    return aaa;
}

static int16_t rule_0803b(int16_t bb)                                 /* expect:  3675 */
{
    return bb;
}

static int16_t rule_0803c(MOD cc)                                     /* expect:  0624 */
{
    return cc;
}

extern MOD rule_0803d();                                                     /* expect:  1707 */
extern void rule_0803e(const int i);                                         /* expect:  1708 */
extern void rule_0803f(int x);                                               /* expect:  1709 */
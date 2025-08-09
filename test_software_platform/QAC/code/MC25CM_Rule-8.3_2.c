/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.3_2.c
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

int16_t rule_0803d() { return 0; }                                    /* expect:  1707 */
void rule_0803e(int i) {}                                             /* expect:  1708 */
void rule_0803f(int y) {}                                             /* expect:  1709 */
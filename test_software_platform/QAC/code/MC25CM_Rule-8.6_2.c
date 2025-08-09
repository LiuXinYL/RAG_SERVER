/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.6_2.c
 *
 * MISRA Required - Rules
 *
 * Rule-8.6: An identifier with external linkage shall have exactly one external
 *           definition
 *
 * Enforced by message(s):
 *   0630   More than one definition of '%s' (with external linkage).
 *
 *   3406   Object/function '%s', with external linkage, has been defined
 *          in a header file.
 *
 *   1509   '${name}' has external linkage and has multiple definitions.
 *
 *   1752   The object '${name}' with external linkage is declared but not
 *          defined within this project.
 *
 *   1753   The function '${name}' with external linkage is declared but
 *          not defined within this project.
 *
 *
 *//* PRQA S 0630,3406,1509,1752,1753 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

// also defined in MC25CM_Rule-8.6_1.c
extern int16_t rule_0806(void)                   // expect: 1509 1593
{
    return 2;
}

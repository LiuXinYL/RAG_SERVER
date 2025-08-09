/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.6.h
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


#ifndef RULE_08_06_H
#define RULE_08_06_H

extern int16_t rule_0806b(void)       /*expect: 3406 */
{
    return 1;
}

#endif

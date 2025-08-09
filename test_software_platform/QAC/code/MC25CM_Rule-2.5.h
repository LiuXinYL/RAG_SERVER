/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-2.5.h
 *
 * MISRA Advisory - Rules
 *
 * Rule-2.5: A project should not contain unused macro definitions
 *
 * Enforced by message(s):
 *   1534   The macro '${name}' is declared but not used within this
 *          project.
 *
 *
 *//* PRQA S 1534 -- *//*
 * <<<------------------------------------------------------------ */

#define USED_MACRO_IN_HEADER_FILE    1           // expect: !1534

#define UNUSED_MACRO_IN_HEADER_FILE  1           // expect:  1534

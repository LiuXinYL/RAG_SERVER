/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-2.3.h
 *
 * MISRA Advisory - Rules
 *
 * Rule-2.3: A project should not contain unused type declarations
 *
 * Enforced by message(s):
 *   3205   The identifier '${name}' is not used and could be removed.
 *
 *   1535   The typedef '${name}' is declared but not used within this
 *          project.
 *
 *
 *//* PRQA S 3205,1535 -- *//*
 * <<<------------------------------------------------------------ */

typedef int R0203_Type_Used;           // expect: !1535

typedef int R0203_Type_Unused;         // expect:  1535

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-11.2.h
 *
 * MISRA Required - Rules
 *
 * Rule-11.2: Conversions shall not be performed between a pointer to an incomplete
 *            type and any other type
 *
 * Enforced by message(s):
 *   0308   Non-portable cast involving pointer to an incomplete type.
 *
 *   0323   Cast between a pointer to incomplete type and a floating type.
 *
 *   0324   Cast between a pointer to incomplete type and an integral type.
 *
 *   0325   Cast between a pointer to incomplete type and a pointer to
 *          function.
 *
 *
 *//* PRQA S 0308,0323,0324,0325 -- *//*
 * <<<------------------------------------------------------------ */


extern struct S1102 *ps1102;

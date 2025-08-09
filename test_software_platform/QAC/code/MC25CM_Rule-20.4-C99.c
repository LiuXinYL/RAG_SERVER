/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.4-C99.c
 *
 * MISRA Required - C99 Specific Rules
 *
 * Rule-20.4-C99: A macro shall not be defined with the same name as a keyword
 *
 * Enforced by message(s):
 *   3468   The name of this macro is a reserved identifier in C90 and a
 *          keyword in C99.
 *
 *
 *//* PRQA S 3468 -- *//*
 * <<<------------------------------------------------------------ */

#define _Bool       BOOL               // expect: 3468
#define _Complex    COMPLEX            // expect: 3468
#define _Imaginary  IMAGINARY          // expect: 3468

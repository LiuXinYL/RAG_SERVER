/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.15-C90.c
 *
 * MISRA Required - C90 Specific Rules
 *
 * Rule-20.15-C90: #define and #undef shall not be used on a reserved identifier or
 *                 reserved macro name
 *
 * Enforced by message(s):
 *   3468   The name of this macro is a reserved identifier in C90 and a
 *          keyword in C99.
 *
 *
 *//* PRQA S 3468 -- *//*
 * <<<------------------------------------------------------------ */

#define _Bool       BOOL               /* expect: 3468 */
#define _Complex    COMPLEX            /* expect: 3468 */
#define _Imaginary  IMAGINARY          /* expect: 3468 */

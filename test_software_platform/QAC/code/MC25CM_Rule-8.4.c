/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.4.c
 *
 * MISRA Required - Rules
 *
 * Rule-8.4: A compatible declaration shall be visible when an object or function
 *           with external linkage is defined
 *
 * Enforced by message(s):
 *   3331   The definition for identifier '%s' with external linkage
 *          conflicts with a previous declaration in the same scope.
 *
 *   3408   '${name}' has external linkage and is being defined without any
 *          previous declaration.
 *
 *
 *//* PRQA S 3331,3408 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t obj0804 = 1;                                                  /* expect: 3408 */

extern int16_t rule_0804(void)
{
    return 1;
}

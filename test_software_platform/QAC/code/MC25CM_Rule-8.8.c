/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.8.c
 *
 * MISRA Required - Rules
 *
 * Rule-8.8: The static storage class specifier shall be used in all declarations
 *           of objects and functions that have internal linkage
 *
 * Enforced by message(s):
 *   3224   This identifier has previously been declared with internal
 *          linkage but is not declared here with the static storage
 *          class specifier.
 *
 *
 *//* PRQA S 3224 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

/* Internal linkage */
static int16_t obj_0808a;

extern int16_t obj_0808a;              // expect: 3224

/* Internal linkage */
static int16_t rule_0808a( void );

int16_t rule_0808a( void )             // expect: 3224
{
    return 0;
}

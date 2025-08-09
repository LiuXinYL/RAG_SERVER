/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-1.5.c
 *
 * MISRA Required - C99 and C11 Specific Rules
 *
 * Rule-1.5: Obsolescent language features shall not be used
 *
 * Enforced by message(s):
 *   4871   Definite: Zero size has been passed to realloc, malloc or
 *          calloc.
 *
 *   4872   Apparent: Zero size has been passed to realloc, malloc or
 *          calloc.
 *
 *   4873   Suspicious: Zero size has been passed to realloc, malloc or
 *          calloc.
 *
 *   5142   Use of ATOMIC_VAR_INIT
 *
 *   1169   Attempting to undefine the stdbool.h macro '${name}'.
 *
 *   3001   Function has been declared with an empty parameter list.
 *
 *   3002   Defining '${name}()' with an identifier list and separate
 *          parameter declarations is an obsolescent feature.
 *
 *   3224   This identifier has previously been declared with internal
 *          linkage but is not declared here with the static storage
 *          class specifier.
 *
 *   3228   Storage class specifier not positioned at the beginning of
 *          declaration.
 *
 *
 *//* PRQA S 4871,4872,4873,5142,1169,3001,3002,3224,3228 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


static int32_t g0105x;
extern int32_t g0105x;                 /* expect: 3224 */

int typedef t0105Int;                  /* expect: 3228 */

void f0105a ();                        /* expect: 3001 */

// 6.11.7
void f0105b (a, b, c)                  /* expect: 3002 */
  int a;
  int b;
  int c;
{ }

atomic_int g1015atomic = ATOMIC_VAR_INIT(42);  /* expect: 5142 */

// 7.31.9
#undef bool                   /* expect: 1169 */
#undef true                   /* expect: 1169 */
#undef false                  /* expect: 1169 */


extern int16_t rule_0105 (void)
{
  return 0;
}

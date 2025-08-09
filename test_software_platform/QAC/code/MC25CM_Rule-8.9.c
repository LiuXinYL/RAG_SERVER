/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.9.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-8.9: An object should be declared at block scope if its identifier only
 *           appears in a single function
 *
 * Enforced by message(s):
 *   3218   File scope static, '${name}', is only accessed in one function.
 *
 *   1514   The object '${entity}' is only referenced by function
 *          '${func}', in the translation unit where it is defined
 *
 *   1533   The object '${entity}' is only referenced by function
 *          '${func}'.
 *
 *
 *//* PRQA S 3218,1514,1533 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

static int16_t s0809a;                                                /* expect: 3218 */
static int16_t s0809b;                                                /* expect: 3218 */
extern int16_t obj_0809c = 0;                                         /* expect: 1514 */

static int16_t r0809a;
static int16_t r0809b;                                                /* expect: 3218 */

static int16_t rule_0809a( void );

extern int16_t rule_0809( void )
{
   s0809a += r0809a;

   r0809a = rule_0809a();

   return s0809a;
}

static int16_t rule_0809a( void )
{
   s0809b = r0809b;
   obj_0809c = r0809a;                                                /* expect: 1579 */

   return s0809b + obj_0809c;                                         /* expect: 1579*/
}

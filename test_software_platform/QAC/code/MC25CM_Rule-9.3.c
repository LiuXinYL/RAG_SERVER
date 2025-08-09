/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-9.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-9.3: Arrays shall not be partially initialized
 *
 * Enforced by message(s):
 *   0686   Array has fewer initializers than its declared size. Default
 *          initialization is applied to the remainder of the array
 *          elements.
 *
 *
 *//* PRQA S 0686 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

static int32_t   a0903[4]    = { 1, 2, 3, 4};
static int32_t   b0903[4]    = { 1, 2, 3 };                           /* expect: 0686 */

static int32_t   c0903[3]    = { 0, 1, 2 };
static int32_t   d0903[3]    = { 0, 1 };                              /* expect: 0686 */

extern int16_t rule_0903( void )
{
   return 0;
}

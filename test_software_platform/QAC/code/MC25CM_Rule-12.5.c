/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-12.5.c
 *
 * MISRA Mandatory - Rules
 *
 * Rule-12.5: The sizeof operator shall not have an operand which is a function
 *            parameter declared as 'array of type'
 *
 * Enforced by message(s):
 *   1321   Operand of sizeof is a function parameter of array type.
 *
 *
 *//* PRQA S 1321 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

static void rule_1205a( int32_t const A[4] )
{
   uint32_t numElements = sizeof (A) /  sizeof (int32_t);             /* expect: 1321 */
}

extern int16_t rule_1205( void )
{
   int32_t A[4] = { 1, 2, 3, 4 };
   return rule_1205a(A);
}

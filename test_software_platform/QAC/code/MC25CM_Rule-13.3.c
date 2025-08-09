/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-13.3.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-13.3: A full expression containing an increment (++) or decrement (--)
 *            operator should have no other potential side effects other than
 *            that caused by the increment or decrement operator
 *
 * Enforced by message(s):
 *   3387   A full expression containing an increment (++) or decrement
 *          (--) operator should have no potential side effects other
 *          than that caused by the increment or decrement operator.
 *
 *   3440   Using the value resulting from a ++ or -- operation.
 *
 *
 *//* PRQA S 3387,3440 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1303( void )
{
   int16_t x = 0;
   int16_t r;

   r = ++x;                                                           /* expect: 3387,3440 */
   return r;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-13.6.c
 *
 * MISRA Required - Rules
 *
 * Rule-13.6: The operand of the sizeof operator shall not contain any expression
 *            which has potential side-effects
 *
 * Enforced by message(s):
 *   0945   Operand of sizeof is an expression of variable length array
 *          type with side effects.
 *
 *   3307   The operand of 'sizeof' is an expression with implied side
 *          effects, but they will not be evaluated.
 *
 *
 *//* PRQA S 0945,3307 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1306( void )
{
   uint16_t r1306_u;
   uint16_t r1306_x;
   uint16_t r1306_v = 2U;
   r1306_x = sizeof( r1306_u++ );                                     /* expect: 3307 */
   r1306_x = sizeof(int[r1306_v++]);                                  /* expect: 0945 */

   return 1;
}

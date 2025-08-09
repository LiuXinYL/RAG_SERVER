/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-15.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-15.3: Any label referenced by a goto statement shall be declared in the
 *            same block, or in any block enclosing the goto statement
 *
 * Enforced by message(s):
 *   3327   This goto statement references a label that is declared in a
 *          separate block.
 *
 *
 *//* PRQA S 3327 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1503a( int rule_1503a_a, int rule_1503a_b )
{
   if (rule_1503a_a > 10) {
      goto rule_1503a_LAB1;                                           /* expect: 3327  */
   }

   if (rule_1503a_a > 5) {
      SI rule_1503a_z = 5;

      rule_1503a_LAB1:
      rule_1503a_z = 1;
      rule_1503a_b = rule_1503a_b + rule_1503a_z;
   }

   return 1;
}

void rule_1503b ( int rule_1503b_a )
{
  if ( rule_1503b_a <= 0 )
  {
    goto rule_1503b_L2;                                               /* expect: 3327  */
  }
  goto rule_1503b_L1;                                                 /* expect: !3327 */
  if ( rule_1503b_a == 0 )
  {
    goto rule_1503b_L1;                                               /* expect: !3327 */
  }
  goto rule_1503b_L2;                                                 /* expect: 3327  */
  rule_1503b_L1:
  if ( rule_1503b_a > 0 )
  {
    rule_1503b_L2:
    ;
  }
}

extern void rule_1503c ( int rule_1503c_x, int rule_1503c_y )
{
  switch ( rule_1503c_x )
  {
  case 0:
    if ( rule_1503c_x == rule_1503c_y )
    {
      goto rule_1503c_L1;                                             /* expect: 3327  */
    }
    break;
  case 1:
    rule_1503c_y = rule_1503c_x;
    rule_1503c_L1:
    ++rule_1503c_x;
    break;
  default:
    break;
  }
}

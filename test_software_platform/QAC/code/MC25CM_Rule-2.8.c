/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-2.8.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-2.8: A project should not contain unused object definitions
 *
 * Enforced by message(s):
 *   3205   The identifier '${name}' is not used and could be removed.
 *
 *   3207   File scope static, '${name}', is not used, and could be
 *          removed.
 *
 *   1502   The object '${name}' is defined but is not used within this
 *          project.
 *
 *
 *//* PRQA S 3205,3207,1502 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

int32_t rule_0208_g1;                             /*  1502       */
static int32_t rule_0208_g2;                      /*        3207 */
int32_t rule_0208_g3 = 0;                         /*  1502       */
int32_t rule_0208_g4;                             /* !1502       */

extern int16_t rule_0208( void )
{
  int32_t rule_0208_l1;                           /*        3205 */
  static int32_t rule_0208_l2;                    /*        3205 */
  int32_t rule_0208_l3 = 0;                       /*        3205 */
  int32_t rule_0208_l4;                           /*       !3205 */

  rule_0208_g4 = rule_0208_l4;
  return 0;
}

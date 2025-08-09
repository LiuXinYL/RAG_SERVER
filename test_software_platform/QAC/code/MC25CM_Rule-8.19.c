/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.19.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-8.19: There should be no external declarations in a source file
 *
 * Enforced by message(s):
 *   3447   '%s' is being declared with external linkage but this
 *          declaration is not in a header file.
 *
 *
 *//* PRQA S 3447 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#include "MC25CM_Rule-8.19.h"

int16_t rule_0819x = 0;         /* !3447 */
int16_t rule_0819x1;            /* !3447 */

int16_t rule_0819y = 0;         /* !3447 */
int16_t rule_0819y1;            /* !3447 */

int16_t rule_0819z = 0;         /* !3447 */
int16_t rule_0819z1;            /* !3447 */

extern int16_t rule_0819w;      /*  3447 */
extern int16_t rule_0819d = 1;  /* !3447 */


extern int16_t rule_0819 (void)
{
  return 1;
}

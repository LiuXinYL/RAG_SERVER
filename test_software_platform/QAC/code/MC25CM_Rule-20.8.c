/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.8.c
 *
 * MISRA Required - Rules
 *
 * Rule-20.8: The controlling expression of a #if or #elif preprocessing directive
 *            shall evaluate to 0 or 1
 *
 * Enforced by message(s):
 *   0894   '#%s' directive controlling expression does not evaluate to
 *          zero or one.
 *
 *
 *//* PRQA S 0894 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#define FALSE 0
#define TRUE 1
#define A 10
#define B 20

#if TRUE                                                              /* Compliant    */
#endif

#if FALSE                                                             /* Compliant    */
#endif

#if !defined(X)                                                       /* Compliant    */
#endif

#if A > B                                                             /* Compliant    */
#endif

#if A                                                                 /* expect:  894 */
#endif

#if B                                                                 /* expect:  894 */
#endif

#if 10                                                                /* expect:  894 */
#endif

#if A || B                                                            /* Compliant    */
#endif

extern int16_t rule_2008 (void)
{
  return 1;
}

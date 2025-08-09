/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.10.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-20.10: The # and ## preprocessor operators should not be used
 *
 * Enforced by message(s):
 *   0341   Using the stringify operator '#'.
 *
 *   0342   Using the glue operator '##'.
 *
 *
 *//* PRQA S 0341,0342 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#define STRINGIFY(S) #S                                               /* expect:  0341 */
#define GLUE(S1, S2) S1 ## S2                                         /* expect:  0342 */

#define EAT(S) ""                                                     /* expect: !0341 */
#define COMBINE(S1, S2) (EAT(S1), S2)                                 /* expect: !0342 */

extern int16_t rule_2010 (void)
{
  char buf1_2010[] = STRINGIFY(MISRA);
  int16_t GLUE(ret_, 2010) = 1;

  char buf2_2010[] = EAT(MISRA);
  ret_2010 = COMBINE(ret_, 2010);

  return ret_2010;
}

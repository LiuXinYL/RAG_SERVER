/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.11.c
 *
 * MISRA Required - Rules
 *
 * Rule-20.11: A macro parameter immediately following a # operator shall not
 *             immediately be followed by a ## operator
 *
 * Enforced by message(s):
 *   0892   This macro parameter is preceded by '#' and followed by '##'.
 *
 *
 *//* PRQA S 0892 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#define A(x)    #x                                                    /* expect: !0892 */
#define B(x, y) x ## y                                                /* expect: !0892 */
#define C(x, y) #x ## y                                               /* expect:  0892 */

#define C(x, y) #x x ## y                                             /* expect: !0892 */
#define C(x, y) x ## y # y                                            /* expect: !0892 */

extern int16_t rule_2011 (void)
{
  return 1;
}

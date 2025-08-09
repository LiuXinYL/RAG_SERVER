/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.5.c
 *
 * MISRA Mandatory - Rules
 *
 * Rule-22.5: A pointer to a FILE object shall not be dereferenced
 *
 * Enforced by message(s):
 *   1485   A pointer to a FILE object is dereferenced.
 *
 *   1486   A pointer to a FILE object is converted to a different type.
 *
 *
 *//* PRQA S 1485,1486 -- *//*
 * <<<------------------------------------------------------------ */


#include <stdio.h>
#include "misra.h"
#include "mc25cmex.h"

FILE * fpa_2205;
FILE * fpb_2205;
FILE * fpc_2205;

struct File_2205
{
  char buf[sizeof(FILE)];
};

extern int16_t rule_2205 (void)
{
  fpc_2205 = fpa_2205;                                                /* expect: !1485 */
  *fpc_2205 = *fpb_2205;                                              /* expect: 1485,1485 */

  struct File_2205 fobj_2205;
  fobj_2205 = *(struct File_2205 *)fpa_2205;                          /* expect:  1486 */

  return 1;
}

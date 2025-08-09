/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.21.c
 *
 * MISRA Required - Rules
 *
 * Rule-21.21: The Standard Library system of <stdlib.h> shall not be used
 *
 * Enforced by message(s):
 *   5150   Use of function: system.
 *
 *
 *//* PRQA S 5150 -- *//*
 * <<<------------------------------------------------------------ */


#include <stdlib.h>

#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_2121 (void)
{
  int16_t ret_2121;


  ret_2121 = system( "test" );                                       // expect:  5150

   return ret_2121;
}



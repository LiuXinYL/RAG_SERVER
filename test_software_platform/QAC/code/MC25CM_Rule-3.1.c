/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-3.1.c
 *
 * MISRA Required - Rules
 *
 * Rule-3.1: The character sequences /* and // shall not be used within a comment
 *
 * Enforced by message(s):
 *   3108   Nested comments are not recognized in the ISO standard.
 *
 *
 *//* PRQA S 3108 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_0301( void )
{
                                                                      /* expect: 3108 */ /* /*  nested comment ? */

                                                                      /* expect: 3108 */ /* //  nested comment ? */

                                                                      /* expect: 3108 */ // /*  nested comment ? */

   return 0;
}

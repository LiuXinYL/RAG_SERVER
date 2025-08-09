/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-7.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-7.2: A "u" or "U" suffix shall be applied to all integer constants that are
 *           represented in an unsigned type
 *
 * Enforced by message(s):
 *   1281   Integer literal constant is of an unsigned type but does not
 *          include a "U" suffix.
 *
 *
 *//* PRQA S 1281 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_0702( void )
{
   0x10000;
   0x7FFFFFFF;
   0x80000000;                                                        /* expect: 1281 */
   0xFFFFFFFF;                                                        /* expect: 1281 */

   return 0;
}

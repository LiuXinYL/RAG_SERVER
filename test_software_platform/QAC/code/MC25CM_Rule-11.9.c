/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-11.9.c
 *
 * MISRA Required - Rules
 *
 * Rule-11.9: The macro NULL shall be the only permitted form of integer null
 *            pointer constant
 *
 * Enforced by message(s):
 *   3003   This character constant is being interpreted as a null pointer
 *          constant.
 *
 *   3004   This integral constant expression is being interpreted as a
 *          null pointer constant.
 *
 *
 *//* PRQA S 3003,3004 -- *//*
 * <<<------------------------------------------------------------ */


#include <stddef.h>
#include "misra.h"
#include "mc25cmex.h"

#define NIL '\0'

extern int16_t rule_xxxx( void )
{
   PC  *gcb;
   SC  *lpsc = NIL;                                                   /* expect: 3003 */
   if (gcb != 0) {                                                    /* expect: 3004 */
   }

   return 1;
}

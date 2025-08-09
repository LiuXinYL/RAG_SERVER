/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.5_1.c
 *
 * MISRA Required - Rules
 *
 * Rule-8.5: An external object or function shall be declared once in one and only
 *           one file
 *
 * Enforced by message(s):
 *   3449   Multiple declarations of external object or function.
 *
 *   3451   The global identifier '${name}' has been declared in more than
 *          one file.
 *
 *   1513   Identifier '${name}' with external linkage has separate non-
 *          defining declarations in more than one location.
 *
 *
 *//* PRQA S 3449,3451,1513 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

extern int16_t obj_0805a;              // expect: 1513 1594
int16_t obj_0805a = 1;

extern int16_t rule_0805b( void );     // expect: 1513 1594
int16_t rule_0805b (void)
{
    return 1;
}

extern int16_t rule_0805( void );      // expect: 3449 3451

extern int16_t rule_0805( void )
{
   return 0;
}

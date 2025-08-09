/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-2.3.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-2.3: A project should not contain unused type declarations
 *
 * Enforced by message(s):
 *   3205   The identifier '${name}' is not used and could be removed.
 *
 *   1535   The typedef '${name}' is declared but not used within this
 *          project.
 *
 *
 *//* PRQA S 3205,1535 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"
#include "MC25CM_Rule-2.3.h" // for R0203_Type_Used & R0203_Type_Unused

extern int16_t rule_0203( void )
{
    typedef int INT;                   // expect: 3205  1535

    R0203_Type_Used x1;

#if 0
    R0203_Type_Unused x2;
#endif

    return x1;
}

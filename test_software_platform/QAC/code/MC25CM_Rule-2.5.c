/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-2.5.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-2.5: A project should not contain unused macro definitions
 *
 * Enforced by message(s):
 *   1534   The macro '${name}' is declared but not used within this
 *          project.
 *
 *
 *//* PRQA S 1534 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#include "MC25CM_Rule-2.5.h"

#define USED_MACRO_IN_SOURCE_FILE    1           // expect: !1534

#define UNUSED_MACRO_IN_SOURCE_FILE  1           // expect:  1534

extern int16_t rule_0205( void )
{
    USED_MACRO_IN_SOURCE_FILE;
    USED_MACRO_IN_HEADER_FILE;

#if 0
    UNUSED_MACRO_IN_SOURCE_FILE;
    UNUSED_MACRO_IN_HEADER_FILE;
#endif

    return 1;
}

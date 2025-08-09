/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.8.c
 *
 * MISRA Required - Rules
 *
 * Rule-22.8: The value of errno shall be set to zero prior to a call to an errno-
 *            setting-function
 *
 * Enforced by message(s):
 *   2500   Call to '${name}' is not immediately preceded by the zero-ing
 *          of 'errno'.
 *
 *
 *//* PRQA S 2500 -- *//*
 * <<<------------------------------------------------------------ */


#include <errno.h>
#include <stdlib.h>

#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_2208( void )
{
    int32_t r2208_sla;
    PC numbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
    PC *pChr;
    r2208_sla = strtol(numbers, &pChr, 10);                           /* expect: 2500 */
    if ( 0 == errno )
    {
    }
    else
    {
        errno = 0;
        r2208_sla = strtol(numbers, &pChr, 2);
        if ( 0 == errno )
        {
        }
    }
    return 1;
}

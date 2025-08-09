/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-11.5.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-11.5: A conversion should not be performed from pointer to void into
 *            pointer to object
 *
 * Enforced by message(s):
 *   0316   Cast from a pointer to void to a pointer to object type.
 *
 *   0317   Implicit conversion from a pointer to void to a pointer to
 *          object type.
 *
 *
 *//* PRQA S 0316,0317 -- *//*
 * <<<------------------------------------------------------------ */


#include <stdlib.h>
#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1105( void )
{
    void * pv = NULL;
    int16_t  * pi;

    pi = (int16_t *)pv;                                               /* expect: 0316 */
    pi =        pv;                                                   /* expect: 0317 */

    return 0;
}

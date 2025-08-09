/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-11.6.c
 *
 * MISRA Required - Rules
 *
 * Rule-11.6: A cast shall not be performed between pointer to void and an
 *            arithmetic type
 *
 * Enforced by message(s):
 *   0326   Cast between a pointer to void and an integral type.
 *
 *   0327   Cast between a pointer to void and a floating type.
 *
 *
 *//* PRQA S 0326,0327 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1106( void )
{

    (void *)1234u;                                                    /* expect: 0326 */
    (void *)1024.0f;                                                  /* expect: 0327 */

    return 0;
}

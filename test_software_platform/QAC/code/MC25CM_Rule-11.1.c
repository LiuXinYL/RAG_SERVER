/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-11.1.c
 *
 * MISRA Required - Rules
 *
 * Rule-11.1: Conversions shall not be performed between a pointer to a function
 *            and any other type
 *
 * Enforced by message(s):
 *   0302   Cast between a pointer to function and a floating type.
 *
 *   0305   Cast between a pointer to function and an integral type.
 *
 *   0307   Cast between a pointer to object and a pointer to function.
 *
 *   0313   Casting to different function pointer type.
 *
 *
 *//* PRQA S 0302,0305,0307,0313 -- *//*
 * <<<------------------------------------------------------------ */


#include <stdlib.h>
#include "misra.h"
#include "mc25cmex.h"

typedef void (*fp16)(int16_t s);
typedef void (*fp32)(int32_t i);

extern int16_t rule_1101( void )
{
    void (*pf)(void) = NULL;

    fp16 fp1 = NULL;
    (float64_t)pf;                                                    /* expect: 0302 */
    (uint32_t)pf;                                                     /* expect: 0305 */
    fp32 fp2 = (fp32)fp1;                                             /* expect: 0313 */
    (int16_t *)pf;                                                    /* expect: 0307 */

    return 0;
}

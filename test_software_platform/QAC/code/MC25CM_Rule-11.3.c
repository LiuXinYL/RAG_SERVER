/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-11.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-11.3: A conversion shall not be performed between a pointer to object type
 *            and a pointer to a different object type
 *
 * Enforced by message(s):
 *   0310   Casting to different object pointer type.
 *
 *   3305   Pointer cast to stricter alignment.
 *
 *
 *//* PRQA S 0310,3305 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_1103( void )
{
    char    * ppc;
    uint16_t   * pui;
    uint32_t   * pul;
    float32_t  * pft;

    pui = (uint16_t  *)ppc;                                           /* expect: 0310 3305 */
    pul = (uint32_t  *)ppc;                                           /* expect: 0310 3305 */

    pui = (uint16_t  *)pft;                                           /* expect: 0310      */
    pul = (uint32_t  *)pft;                                           /* expect: 0310      */

    return 0;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-10.6.c
 *
 * MISRA Required - Rules
 *
 * Rule-10.6: The value of a composite expression shall not be assigned to an
 *            object with wider essential type
 *
 * Enforced by message(s):
 *   4490   A composite expression of 'essentially signed' type (%1s) is
 *          being converted to wider signed type, '%2s' on assignment.
 *
 *   4491   A composite expression of 'essentially unsigned' type (%1s) is
 *          being converted to wider unsigned type, '%2s' on
 *          assignment.
 *
 *   4492   A composite expression of 'essentially floating' type (%1s) is
 *          being converted to wider floating type, '%2s' on
 *          assignment.
 *
 *
 *//* PRQA S 4490,4491,4492 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int8_t r1006_s8a;
int8_t r1006_s8b;
uint8_t r1006_u8a;
uint8_t r1006_u8b;
float32_t r1006_f32a;
float32_t r1006_f32b;

extern int16_t rule_1006( void )
{
    int32_t s16x = r1006_s8a + r1006_s8b;                             /* expect: 4490 */
    uint32_t u16x = r1006_u8a + r1006_u8b;                            /* expect: 4491 */
    uint32_t u16y = ~r1006_u8a;                                       /* expect: 4491 */
    uint32_t u16z = r1006_u8a << 2U;                                  /* expect: 4491 */
    float64_t f64x = r1006_f32a + r1006_f32b;                         /* expect: 4492 */

    return 1;
}

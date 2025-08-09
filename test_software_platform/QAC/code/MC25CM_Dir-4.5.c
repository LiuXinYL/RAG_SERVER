/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-4.5.c
 *
 * MISRA Advisory - Directives
 *
 * Dir-4.5: Identifiers in the same name space with overlapping visibility should
 *          be typographically unambiguous
 *
 * Assisted by message(s):
 *   1710   Identifiers have the same matching pattern '${name}'.
 *
 *
 *//* PRQA S 1710 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t dir_0405( void )
{
  int32_t id3_a_bc = 1;                   /* expect: 1710,1594,1594 */
  int32_t id3_ab_c = 1;                   /* expect: 1710,1594,1594 */

  int32_t id4_I = 1;                      /* expect: 1710,1594,1594 */
  int32_t id4_1 = 1;                      /* expect: 1710,1594,1594 */

  int32_t id5_Z = 1;                      /* expect: 1710,1594,1594 */
  int32_t id5_2 = 1;                      /* expect: 1710,1594,1594 */

  int32_t id6_O = 1;                      /* expect: 1710,1594,1594 */
  int32_t id6_0 = 1;                      /* expect: 1710,1594,1594 */

  int32_t id7_B = 1;                      /* expect: 1710,1594,1594 */
  int32_t id7_8 = 1;                      /* expect: 1710,1594,1594 */

  return 1;
}

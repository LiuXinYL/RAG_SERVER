/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-7.6.c
 *
 * MISRA Required - C99 and C11 Specific Rules
 *
 * Rule-7.6: The small integer variants of the minimum-width integer constant
 *           macros shall not be used
 *
 * Enforced by message(s):
 *   3187   This integer constant macro is for a type smaller than int.
 *
 *
 *//* PRQA S 3187 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#include <stdint.h>

extern int16_t rule_0706( void )
{
  /* Non-compliant: 8 bits is definitely smaller than int */
  uint16_t x0706 = UINT8_C ( 10 );          /* expect:  3187 */

  /* Compliant if int is 16-bit */
  uint16_t y0706 = UINT16_C ( 10 );         /* expect: !3187 */

  /* Compliant if int is 32-bit or narrower */
  uint16_t z0706 = UINT32_C ( 10 );         /* expect: !3187 */

  return 0;
}

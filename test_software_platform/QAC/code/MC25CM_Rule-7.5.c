/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-7.5.c
 *
 * MISRA Mandatory - C99 and C11 Specific Rules
 *
 * Rule-7.5: The argument of an integer-constant macro shall have an appropriate
 *           form
 *
 * Enforced by message(s):
 *   3185   The argument value to this integer constant macro is not a
 *          valid integer literal.
 *
 *   3186   The argument value to this integer constant macro is out of
 *          range.
 *
 *
 *//* PRQA S 3185,3186 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#include <stdint.h>

extern int16_t rule_0705( void )
{
  uint16_t u07051 = UINT16_C ( 10 );              /* expect: !3185 */
  uint16_t u07052 = UINT16_C ( 10UL );            /* expect:  3185 */
  uint16_t u07053 = UINT16_C ( 10.0 );            /* expect:  3185 */

  uint_least16_t u07054 = UINT16_C ( 0x10000 );   /* expect:  3186 */

  return 0;
}

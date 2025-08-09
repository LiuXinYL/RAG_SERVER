/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.16-C11.c
 *
 * MISRA Advisory - C11 Specific Rules
 *
 * Rule-8.16-C11: The alignment specification of zero should not appear in an
 *                object declaration
 *
 * Enforced by message(s):
 *   1165   Specifying an zero alignment.
 *
 *
 *//* PRQA S 1165 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_0816(void)
{
  _Alignas (4) char a;              /* c11_expect: !1165 */

  _Alignas (0) char b;              /* c11_expect:  1165 */


  #ifdef REQUIRE_ALIGNMENT // not defined
  #define ALIGNMENT 4
  #else
  #define ALIGNMENT 0
  #endif

  _Alignas (ALIGNMENT) char c;      /* c11_expect: 1165 */

  #ifdef REQUIRE_ALIGNMENT // not defined
  #define ALIGNSPEC _Alignas (4)
  #else
  #define ALIGNSPEC /**/
  #endif

  ALIGNSPEC char d;                 /* c11_expect: !1165 */

  return 0;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-11.8-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-11.8-C11: A conversion shall not remove any const, volatile or _Atomic
 *                qualification from the type pointed to by a pointer
 *
 * Enforced by message(s):
 *   2039   This conversion implicitly loses atomic qualification of the
 *          pointed-to type.
 *
 *   2040   This cast discards atomic qualification of the pointed-to type.
 *
 *
 *//* PRQA S 2039,2040 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

struct A1108 {
  int32_t x1108;
  int32_t y1108;
};

int16_t rule_1108_C11 (void)
{
  _Atomic struct A1108 astr1108;
          struct A1108 lstr1108;

  struct A1108 * sptr1108;

  sptr1108 = &astr1108;                   /* c11_expect:  2039 */
  sptr1108 = &lstr1108;                   /* c11_expect: !2039 */

  sptr1108 = (struct A1108 *)&astr1108;   /* c11_expect:  2040 */
  sptr1108 = (struct A1108 *)&lstr1108;   /* c11_expect: !2040 */

  return 0;
}

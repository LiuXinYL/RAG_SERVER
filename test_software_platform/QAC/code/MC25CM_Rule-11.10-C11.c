/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-11.10-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-11.10-C11: The _Atomic qualifier shall not be applied to the incomplete
 *                 type void
 *
 * Enforced by message(s):
 *   2038   Attempting to derive an atomic type from void.
 *
 *
 *//* PRQA S 2038 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

struct A1110 {
  int32_t _Atomic x1110;
  int32_t _Atomic y1110;
};

int16_t rule_1110 (void)
{
  struct A1110 a1110 = { 6, 7 };

  void _Atomic * pav1110 = &a1110;                       /* c11_expect: 2038 */
  void _Atomic * pax1110 = &a1110.x1110;                 /* c11_expect: 2038 */

  return 0;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-19.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-19.3: A union member shall not be read unless it has been previously set
 *
 * Enforced by message(s):
 *   3596   Definite: Accessing union member with different type to the
 *          member set.
 *
 *   3597   Apparent: Accessing union member with different type to the
 *          member set.
 *
 *   3598   Suspicious: Accessing union member with different type to the
 *          member set.
 *
 *
 *//* PRQA S 3596,3597,3598 -- *//*
 * <<<------------------------------------------------------------ */

#include "string.h"
#include "misra.h"
#include "mc25cmex.h"

uint32_t rule_1903_1 (float32_t f)
{
  union {
    float32_t f;
    uint32_t bits;
  } tmp;

  tmp.f = f;
  return tmp.bits;  /* expect: 3596 */
}

uint32_t rule_1903_2 (uint32_t x)
{
  union {
    uint32_t x;
    uint16_t lo;
  } tmp;

  tmp.x = x;
  tmp.lo = 0;
  return tmp.x;  /* expect: 3596 */
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-12.6-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-12.6-C11: Structure and union members of atomic objects shall not be
 *                directly accessed
 *
 * Enforced by message(s):
 *   2037   Directly accessing a member of an atomic-qualified structure or
 *          union.
 *
 *
 *//* PRQA S 2037 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#include <stdatomic.h>

typedef struct s1206 {
  uint8_t a1206;
  uint8_t b1206;
} s1206;

_Atomic s1206 astr_1206;

int16_t rule_1206 (void)
{
  s1206 lstr_1206 = { 7U, 42U };
  astr_1206 = lstr_1206;

  astr_1206.b1206 = 43U;                   /* c11_expect:  2037 */

  lstr_1206 = atomic_load( &astr_1206 );
  lstr_1206.b1206 = 43U;                   /* c11_expect: !2037 */
  atomic_store( &astr_1206, lstr_1206 );

  lstr_1206.a1206 = 8U;                    /* c11_expect: !2037 */
  astr_1206 = lstr_1206;                   /* c11_expect: !2037 */

  return 0;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.25.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-21.25: All memory synchronization operations shall be executed in
 *             sequentially consistent order
 *
 * Enforced by message(s):
 *   1193   This operation does not statically use sequentially consistent
 *          memory ordering.
 *
 *
 *//* PRQA S 1193 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#include <stdatomic.h>

extern int16_t rule_2125( void )
{
  _Atomic int16_t a2125 = 0;
          int16_t i2125 = 0;

  i2125 = a2125;                                                  /* expect:     !1193 */
  i2125 = atomic_load (&a2125);                                   /* expect:     !1193 */
  i2125 = atomic_load_explicit (&a2125, memory_order_seq_cst);    /* expect:     !1193 */

  i2125 = atomic_load_explicit (&a2125, memory_order_relaxed);    /* c11_expect:  1193 */

  a2125 += i2125;                                                 /* expect:     !1193 */
  atomic_fetch_add (&a2125, i2125);                               /* expect:     !1193 */

  atomic_fetch_add_explicit (&a2125, i2125, memory_order_relaxed);/* c11_expect:  1193 */

  return 0;
}

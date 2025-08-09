/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.12.c
 *
 * MISRA Mandatory - C11 Specific Rules
 *
 * Rule-22.12: Thread objects, thread synchronization objects, and thread-specific
 *             storage pointers shall only be accessed by the appropriate
 *             Standard Library functions
 *
 * Enforced by message(s):
 *   2035   This concurrency primitive is not accessed through the Threads
 *          library.
 *
 *   2036   This concurrency primitive is modified directly.
 *
 *
 *//* PRQA S 2035,2036 -- *//*
 * <<<------------------------------------------------------------ */


#include <threads.h>
#include <stddef.h>
#include <stdlib.h>
#include "misra.h"
#include "mc25cmex.h"

mtx_t Ra;
mtx_t Rb;
thrd_t id1;
thrd_t id2;
tss_t key;

int32_t t1 (void * ignore)
{
  mtx_lock (&Ra);
  int32_t val;
  if (id1 == id2)                      /* c11_expect:  2035x2    */ /* Non-compliant - use thrd_equal() */
  {
    Rb = Ra;                           /* c11_expect:  2035x2    */ /* Non-compliant  */
    memcpy (&Rb, &Ra, sizeof (mtx_t)); /* c11_expect:  2035x2    */ /* Non-compliant   */
  }
  if (thrd_equal (id1, id2))                                        /* Compliant */
  {
    // ...
  }
  key++;                               /* c11_expect:  2036      */ /* Non-compliant, explicit manipulation of TSS pointer */
  tss_set (key, &val);                                              /* Undefined, value of key not returned by tss_create() */
}

int16_t rule_2212 (void)
{
  mtx_init (&Ra, mtx_plain);
  mtx_init (&Rb, mtx_plain);
  tss_create (&key, NULL);
  thrd_create (&id1, t1, NULL);
  thrd_create (&id2, t1, NULL);
  // ...
  return 0;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.13.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-22.13: Thread objects, thread synchronization objects and thread-specific
 *             storage pointers shall have appropriate storage duration
 *
 * Enforced by message(s):
 *   2034   This concurrency primitive has automatic storage duration.
 *
 *
 *//* PRQA S 2034 -- *//*
 * <<<------------------------------------------------------------ */


#include <threads.h>
#include "misra.h"
#include "mc25cmex.h"

mtx_t Ra;                              /*                   */ /* Compliant */
int32_t t1 (void * ptr)                /* Thread entry */
{
  // ...
  mtx_lock (&Ra);
  mtx_lock ((mtx_t *) ptr);            /* Lifetime of Rb might have ended so ptr might be dangling */
  // ...
  mtx_unlock ((mtx_t *) ptr);          /* Lifetime of Rb might have ended so ptr might be dangling */
  mtx_unlock (&Ra);
}
int16_t rule_2213 (void)
{
  thrd_t id1;                          /* c11_expect:  2034 */ /* Non-compliant */
  mtx_t Rb;                            /* c11_expect:  2034 */ /* Non-compliant */
  mtx_init (&Ra, mtx_plain);
  mtx_init (&Rb, mtx_plain);
  thrd_create (&id1, t1, &Rb);

  return 0;
}

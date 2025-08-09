/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.19.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-22.19: A condition variable shall be associated with at most one mutex
 *             object
 *
 * Enforced by message(s):
 *   1769   Condition variable '${name}' used with multiple mutexes.
 *
 *
 *//* PRQA S 1769 -- *//*
 * <<<------------------------------------------------------------ */


#include <threads.h>

#include "misra.h"
#include "mc25cmex.h"

static mtx_t Ra;
static mtx_t Rb;
static cnd_t Cnd;                                                                               /* c11_expect:  1769 */

int rule_2219_t1(void *ignore )
{
  mtx_lock( &Ra       );
  cnd_wait( &Cnd, &Ra );  /* Non-compliant - t2 uses Cnd with Rb */                             /* c11_expect:  1582 */
  return 0;
}

int rule_2219_t2(void *ignore )
{
  mtx_lock( &Rb);
  cnd_wait( &Cnd, &Rb );  /* Non-compliant - t1 uses Cnd with Ra */                             /* c11_expect:  1582 */
  return 0;
}

int rule_2219_t3(void* ignore)
{
  cnd_signal( &Cnd );     /* Unblocks one of Ra and Rb, unclear whether t1 or t2 resumes */
  return 0;
}

int main(void)
{
  thrd_t id1, id2, id3;
  thrd_create( &id1, rule_2219_t1, NULL );
  thrd_create( &id2, rule_2219_t2, NULL );
  thrd_create( &id3, rule_2219_t2, NULL );
  thrd_join  ( id1, NULL );
  thrd_join  ( id2, NULL );
  thrd_join  ( id3, NULL );
}

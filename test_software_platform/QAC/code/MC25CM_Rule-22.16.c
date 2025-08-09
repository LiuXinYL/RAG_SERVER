/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.16.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-22.16: All mutex objects locked by a thread shall be explicitly unlocked by
 *             the same thread
 *
 * Enforced by message(s):
 *   4946   Definite: Mutex is still locked at thread exit
 *
 *   4947   Apparent: Mutex is still locked at thread exit
 *
 *   4971   Definite: Attempt to destroy a mutex which has not been created
 *          by the current thread
 *
 *   4972   Apparent: Attempt to destroy a mutex which has not been created
 *          by the current thread
 *
 *
 *//* PRQA S 4946,4947,4971,4972 -- *//*
 * <<<------------------------------------------------------------ */

#include <threads.h>

#include "misra.h"
#include "mc25cmex.h"

static mtx_t Ra;
static mtx_t Rb;

int rule_2216_t1( void *ignore )  /* Thread 1 */
{
  bool_t b;

  mtx_lock  ( &Ra );  /* Compliant                                 */  /* expect:     !1582 */
  mtx_unlock( &Ra );

  mtx_lock  ( &Rb );  /* No-compliant - unlock missing on one path */  /* c11_expect:  1582 */
  if ( b )
  {
    mtx_unlock( &Rb );
  }
  return 0;
}                                                                      /* c11_expect:  4947 */

int rule_2216_t2( void *ignore )  /* Thread 2 */
{
  mtx_t m1, m2;

  extern int x2216;
  if (x2216)
  {
    mtx_init (&m2, 0);
  }

  mtx_destroy (&m1);                                                   /* c11_expect:  4971 */
  mtx_destroy (&m2);                                                   /* c11_expect:  4972 */

  return 0;
}

int main(void)
{
  thrd_t id1, id2;
  thrd_create( &id1, rule_2216_t1, NULL );
  thrd_create( &id2, rule_2216_t2, NULL );
  thrd_join  ( id1, NULL );
  thrd_join  ( id2, NULL );
}

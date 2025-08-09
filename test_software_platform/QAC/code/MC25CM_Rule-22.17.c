/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.17.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-22.17: No thread shall unlock a mutex or call cnd_wait() or cnd_timedwait()
 *             for a mutex it has not locked before
 *
 * Enforced by message(s):
 *   4981   Definite: Attempt to unlock a mutex which has not been locked
 *          by the current thread
 *
 *   4982   Apparent: Attempt to unlock a mutex which has not been locked
 *          by the current thread
 *
 *
 *//* PRQA S 4981,4982 -- *//*
 * <<<------------------------------------------------------------ */

#include <threads.h>

#include "misra.h"
#include "mc25cmex.h"

static mtx_t Ra;
static mtx_t Rb;
static cnd_t Cnd1;
static cnd_t Cnd2;

int rule_2217_t1( void *ignore )  /* Thread 1 */
{
  mtx_lock  ( &Ra );
  mtx_unlock( &Ra );        /* Compliant                                                             */
  mtx_unlock( &Ra );        /* Non-compliant, mutex is not locked                                    */ /* c11_expect:  4981 */
  cnd_wait  ( &Cnd1, &Ra ); /* Non-compliant, mutex is not locked                                    */ /* c11_expect:  4981 */
  mtx_unlock( &Rb);         /* Non-compliant, mutex either not locked, or locked by different thread */
  cnd_wait  ( &Cnd2, &Rb ); /* Non-compliant, mutex either not locked, or locked by different thread */ /* c11_expect:  4981 */

  return 0;
}

void rule_2217_doSomething();

int rule_2217_t2( void *ignore )  /* Thread 2 */
{
  mtx_lock   ( &Rb );
  rule_2217_doSomething();
  mtx_unlock ( &Rb );       /* Not compliant, mutex might be unlocked                                 */
  return 0;
}

int main(void)
{
  thrd_t id1, id2;
  thrd_create( &id1, rule_2217_t1, NULL );
  thrd_create( &id2, rule_2217_t2, NULL );
  thrd_join  ( id1, NULL );
  thrd_join  ( id2, NULL );
}

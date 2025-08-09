/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.26-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-21.26-C11: The Standard Library function mtx_timedlock() shall only be
 *                 invoked on mutex objects of appropriate mutex type
 *
 * Enforced by message(s):
 *   3537   This timed lock operation is being applied to a non-timed
 *          mutex.
 *
 *
 *//* PRQA S 3537 -- *//*
 * <<<------------------------------------------------------------ */
#include <threads.h>
#include <stddef.h>

#include "misra.h"
#include "mc25cmex.h"

static mtx_t Ra;
static mtx_t Rb;
static mtx_t Rc;
static struct timespec *ts;

static int t1( void* ignore )
{
  mtx_timedlock( &Ra, ts );   /* c11_expect:  3537 */  /* Non-Compliant */
  mtx_timedlock( &Rb, ts );   /* c11_expect: !3537 */
  mtx_timedlock( &Rc, ts );   /* c11_expect: !3537 */

  mtx_unlock(&Ra);
  mtx_unlock(&Rc);
  mtx_unlock(&Rb);
  return 0;
}

int main( void )
{
  mtx_init( &Ra, mtx_plain );
  mtx_init( &Rb, mtx_timed );
  mtx_init( &Rc, mtx_timed | mtx_recursive );

  thrd_t t;
  thrd_create(&t, t1, NULL);
  thrd_join (t, NULL);

  return 0;
}

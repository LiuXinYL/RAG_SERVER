/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.15.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-22.15: Thread synchronization objects and thread-specific storage pointers
 *             shall not be destroyed until after all threads accessing them
 *             have terminated
 *
 * Enforced by message(s):
 *   4961   Definite: Attempt to destroy a mutex which is still locked
 *
 *   4962   Apparent: Attempt to destroy a mutex which is still locked
 *
 *   1789   Thread object '${name}' is deleted concurrently.
 *
 *   1790   Definite: race between thread object '${name}' deletion and
 *          use.
 *
 *
 *//* PRQA S 4961,4962,1789,1790 -- *//*
 * <<<------------------------------------------------------------ */
#include <threads.h>

#include "misra.h"
#include "mc25cmex.h"

static int32_t g=0;
static mtx_t   Ra;
static mtx_t   Rb;
static mtx_t   Rc;
static mtx_t   Rd;
static tss_t   key1;
static tss_t   key2;
static thrd_t  id1;
static thrd_t  id2;
static thrd_t  id3;

static int t1( void *ignore )                               /* Thread T1 entry       */
{
  tss_delete( key1 );                                       /* c11_expect:  1789     */ /* Non-compliant - might still be accessed from T2     */

  mtx_lock( &Ra );
  mtx_lock( &Rb );                                          /* c11_expect:  1582     */
  /* do something */
  mtx_unlock( &Ra );
  mtx_unlock( &Rb );
  return 0;
}

static int t2( void *ignore )                               /* Thread T2 entry       */
{
  mtx_lock( &Ra );
  mtx_lock( &Rb );
  /* do something */
  mtx_unlock( &Ra );
  mtx_unlock( &Rb );

  mtx_destroy( &Rb );                                      /* c11_expect:  1789 1790 */ /* Non-compliant - T1 might still access Rb            */
  return 0;
}

static int t3 (void * ignore)                              /* Thread T3 entry       */
{
  mtx_destroy( &Rc );                                      /* c11_expect:  4961 */

  extern int x;
  if (x)
  {
    mtx_destroy( &Rd );                                    /* c11_expect:  4962 */
  }

  return 0;
}

void rule_2215_spendSomeTime();

int main( void )
{
  mtx_init   ( &Ra, mtx_plain );
  mtx_init   ( &Rb, mtx_plain );
  mtx_init   ( &Rc, mtx_plain );
  mtx_init   ( &Rd, mtx_plain );

  tss_create ( &key1, NULL    );
  tss_create ( &key2, NULL    );

  thrd_create( &id1, t1, NULL );                          /* c11_expect:  1566x4     */
  thrd_create( &id2, t2, NULL );                          /* c11_expect:  1566x4     */
  thrd_create( &id3, t3, NULL );                          /* c11_expect:  1566x4     */

  while ( ( g != 1 ) && ( g != 2 ) )
  {
    rule_2215_spendSomeTime();
  }
  tss_delete ( key2 );                                    /* c11_expect:  1789       */ /* Non-compliant - might still be accessed by t1 or t2 */

  thrd_join  ( id1, NULL );
  thrd_join  ( id2, NULL );
  thrd_join  ( id3, NULL );

  mtx_destroy( &Ra       );                                                             /* Compliant                                           */
  return 0;
}


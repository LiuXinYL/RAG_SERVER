/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.14.c
 *
 * MISRA Mandatory - C11 Specific Rules
 *
 * Rule-22.14: Thread synchronization objects shall be initialized before being
 *             accessed
 *
 * Enforced by message(s):
 *   4936   Definite: Using a mutex which has not been initialised
 *
 *   4937   Apparent: Using a mutex which has not been initialised
 *
 *   1787   Thread synchronization primitive '${name}' is created
 *          concurrently.
 *
 *   1788   Definite: race between thread synchronization primitive
 *          '${name}' creation and use.
 *
 *
 *//* PRQA S 4936,4937,1787,1788 -- *//*
 * <<<------------------------------------------------------------ */

#include <threads.h>

#include "misra.h"
#include "mc25cmex.h"

static mtx_t Ra;
static mtx_t Rb;
static mtx_t Rc;
static mtx_t Rd;
static mtx_t Re;

int rule_2214_t1( void *ignore )                            /* Thread T1 entry */
{
  mtx_init( &Rb, mtx_plain );                               /* c11_expect:  1787 1788 */ /* Non-compliant - T2 might already have accessed Rb */

  mtx_lock( &Ra );
  mtx_lock( &Rb );
  mtx_lock( &Rc );                                          /* c11_expect:  1582 */
  return 0;
}

int rule_2214_t2( void *ignore )                            /* Thread T2 entry */
{
  mtx_lock( &Ra );
  mtx_lock( &Rb );                                          /* c11_expect:  1582 */
  mtx_lock( &Rc );                                          /* c11_expect:  1582 */
  return 0;
}

int rule_2214_t3( void *ignore )                            /* Thread T3 entry */
{
  mtx_lock( &Re );                                          /* c11_expect:  4936 */
  extern int x;
  if (x)
    mtx_lock( &Re );                                        /* c11_expect:  4937 */
  return 0;
}

int main(void)
{
  thrd_t id1, id2, id3;

  mtx_init   ( &Ra, mtx_plain );                                                         /* Compliant */

  thrd_create( &id1, rule_2214_t1, NULL );                  /* c11_expect:  1566x3 */
  thrd_create( &id2, rule_2214_t2, NULL );                  /* c11_expect:  1566x5 */
  thrd_create( &id3, rule_2214_t3, NULL );                  /* c11_expect:  1566x5 */

  mtx_init   ( &Rc, mtx_plain );                            /* c11_expect:  1787 1788 */ /* Non-compliant - T1/T2 might already have accessed Rc */
  mtx_init   ( &Rd, mtx_plain );                            /* c11_expect:  1787      */ /* Non-compliant - T1/T2 might already have accessed Rd */

  thrd_join  ( id1, NULL );
  thrd_join  ( id2, NULL );
  thrd_join  ( id3, NULL );

  mtx_destroy( &Ra );
  mtx_destroy( &Rb );
  mtx_destroy( &Rc );
  mtx_destroy( &Rd );
}

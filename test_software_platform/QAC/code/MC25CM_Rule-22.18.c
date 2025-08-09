/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.18.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-22.18: Non-recursive mutexes shall not be recursively locked
 *
 * Enforced by message(s):
 *   4986   Definite: Attempt to lock a non-recursive mutex which is
 *          already locked
 *
 *   4987   Apparent: Attempt to lock a non-recursive mutex which is
 *          already locked
 *
 *
 *//* PRQA S 4986,4987 -- *//*
 * <<<------------------------------------------------------------ */

#include <threads.h>

#include "misra.h"
#include "mc25cmex.h"

static mtx_t Ra;
static mtx_t Rb;

int rule_2218_t1( void *ignore )  /* Thread 1 */
{
  mtx_lock  ( &Rb );  /* Compliant                                              */
  mtx_lock  ( &Rb );  /* Compliant - Rb is recursive                            */  /* c11_expect:  4986 */
  mtx_unlock( &Rb );  /* Rb still locked                                        */
  mtx_unlock( &Rb );  /* Rb gets unlocked                                       */

  mtx_lock  ( &Ra );  /* Compliant                                              */
  mtx_lock  ( &Ra );  /* Non-compliant - undefined behaviour, deadlock possible */  /* c11_expect:  4986 */
  mtx_unlock( &Ra );  /* If reachable (i.e. no deadlock), Ra gets unlocked      */
  mtx_unlock( &Ra );  /* Undefined behaviour if reachable                       */

  return 0;
}

int main(void)
{
  thrd_t id1;
  thrd_t id2;

  mtx_init   ( &Ra, mtx_plain     );
  mtx_init   ( &Rb, mtx_recursive );
  thrd_create( &id1, rule_2218_t1, NULL     );
  /* ... */
}

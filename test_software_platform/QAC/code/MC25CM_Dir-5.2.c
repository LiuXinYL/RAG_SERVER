/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-5.2.c
 *
 * MISRA Required - C11 Specific Directives
 *
 * Dir-5.2: There shall be no deadlocks between threads
 *
 * Assisted by message(s):
 *   1767   Definite: detected cycle in lock graph, there is a potential
 *          deadlock.
 *
 *   1768   Apparent: detected cycle in lock graph, there is a potential
 *          deadlock.
 *
 *
 *//* PRQA S 1767,1768 -- *//*
 * <<<------------------------------------------------------------ */

#include <threads.h>

#include "misra.h"
#include "mc25cmex.h"

static mtx_t   Ra;                                                /* c11_expect:  1767  1594 */
static mtx_t   Rb;                                                /* c11_expect:  1767  1594 */

int dir_0502_t1( void *ignore ) /* Thread T1 entry         */
{
  mtx_lock( &Ra );
  // ...
  mtx_lock( &Rb );         /* Deadlock may occur here */          /* c11_expect:  1767       */
  // ...
  mtx_unlock( &Rb );
  mtx_unlock( &Ra );
  return 0;
}

int dir_0502_t2(void* ignore)   /* Thread T2 entry         */
{
  mtx_lock( &Rb );
  // ...
  mtx_lock( &Ra );         /* Deadlock may occur here */          /* c11_expect:  1767       */
  // ...
  mtx_unlock( &Ra );
  mtx_unlock( &Rb );
  return 0;
}

/*********************************************************************************
 *                       END OF MISRA DOCUMENT TESTS                             *
 ********************************************************************************/

static mtx_t   Rc;                                                /* c11_expect:  1768  1594 */
static mtx_t   Rd;                                                /* c11_expect:  1768  1594 */
int dir_0502_other_1 ( void * arg )
{
  if (arg)
  {
    mtx_lock( &Rc );
  }
  mtx_lock( &Rd );                                                /* c11_expect:  1768       */
}

int dir_0502_other_2 ( void * arg )
{
  mtx_lock( &Rd );
  if (arg)
  {
    mtx_lock( &Rc );                                              /* c11_expect:  1768       */
  }
}

int main(void)
{
  thrd_t id1, id2, id3, id4;

  thrd_create( &id1, dir_0502_t1, NULL );                         /* c11_expect:  1767  1566 */
  thrd_create( &id2, dir_0502_t2, NULL );                         /* c11_expect:  1767  1566 */

  thrd_create( &id3, dir_0502_other_1, NULL );                    /* c11_expect:  1768  1566 */
  thrd_create( &id4, dir_0502_other_2, NULL );                    /* c11_expect:  1768  1566 */
}

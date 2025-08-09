/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-5.3.c
 *
 * MISRA Required - C11 Specific Directives
 *
 * Dir-5.3: There shall be no dynamic thread creation
 *
 * Not Assisted.
 * <<<------------------------------------------------------------ */
#include <threads.h>

#include "misra.h"
#include "mc25cmex.h"

thrd_t id1;
thrd_t id2;

int dir_0503_t2( void* ignore );

int dir_0503_t1( void *ignore)            /* Thread T1 entry                            */
{
  /* ... */
  thrd_create( &id2, dir_0503_t2, NULL ); /* Non-compliant, not constrained to start-up */
  /* ... */
}

int dir_0503_t2( void* ignore )           /* Thread T2 entry                            */
{
  /* ... */
}

void main(void)
{
  thrd_create( &id1, dir_0503_t1, NULL ); /* Compliant                                  */
  /* ... */
}

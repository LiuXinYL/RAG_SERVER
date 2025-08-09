/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-5.1.c
 *
 * MISRA Required - C11 Specific Directives
 *
 * Dir-5.1: There shall be no data races between threads
 *
 * Assisted by message(s):
 *   4976   Definite: Call to a non-reentrant function outside of a
 *          critical section.
 *
 *   4977   Apparent: Call to a non-reentrant function outside of a
 *          critical section.
 *
 *   1765   Definite: data race for object '${name}'.
 *
 *   1766   Apparent: data race for object '${name}'.
 *
 *   1770   Definite: data race for a volatile object '${name}'.
 *
 *   1774   Definite: data race for an object '${name}' which shares its
 *          physical storage location with one or more others.
 *
 *   1775   Apparent: data race for an object '${name}' which shares its
 *          physical storage location with one or more others.
 *
 *
 *//* PRQA S 4976,4977,1765,1766,1770,1774,1775 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>

static int32_t x;                                                          /* c11_expect:  1765       */
static int32_t a=1;                                                        /* c11_expect:  1765       */
static int32_t b;                                                          /*             !1765       */

int dir_0501_t1( void *ignore )  /* Thread T1 entry */
{
  while ( 1 )
  {
    /* Write-write data race with t2. Possible values of x: 0xFFFF0000,
       0x0000FFFF, 0x00000000, 0xFFFFFFFF */
    x = -1;                                                                /* c11_expect:  1586       */
  }
  return 0;
}

int dir_0501_t2( void *ignore )  /* Thread T2 entry */
{
  while ( 1 )
  {
    /* Write-write data race with t1. Possible values of x: 0xFFFF0000,
       0x0000FFFF, 0x00000000, 0xFFFFFFFF */
    x = 0;                                                                 /* c11_expect:  1586       */
  }
  return 0;
}

int dir_0501_t3( void *ignore )  /* Thread T3 entry */
{
  while ( 1 )
  {
    if ( a != 0 )  /* Read-write  data race with T4 */                     /* c11_expect:  1582       */
    {
      b += 1/a;    /* Read-write  data race with T4 */                     /* c11_expect:  1582       */
      a = 1;       /* Write-write data race with T4 */                     /* c11_expect:  1586       */
    }
  }
  return 0;
}

int dir_0501_t4( void *ignore )  /* Thread T4 entry */
{
  while ( 1 )
  {
    a = 0;         /* Read-write data race with T3  */                     /* c11_expect:  1586       */
  }
  return 0;
}

/*********************************************************************************
 *                       END OF MISRA DOCUMENT TESTS                             *
 ********************************************************************************/

struct dir_0501_S
{
  unsigned n1 : 4;
  unsigned n2 : 4;
  unsigned    : 0;
  struct
  {
    unsigned q1 : 4;
    unsigned q2 : 4;
  } q;
  int counter;
};

struct dir_0501_B
{
  volatile struct dir_0501_S a;
};

struct dir_0501_C
{
  struct dir_0501_B b;
};


static mtx_t m1;
static int32_t y1;                                                         /* c11_expect:  1766       */
static struct dir_0501_S y2;                                               /* c11_expect:  1774  1774 */
static struct dir_0501_S y3;                                               /* c11_expect:  1775  1775 */
struct dir_0501_C y4 = {};                                                 /* c11_expect:  1770       */

int dir_0501_other_1 ( void * arg )
{
  ++y2.n1;                                                                 /* c11_expect:  1586       */

  if (arg)
  {
    mtx_lock (&m1);
  }
  y1 = 0;                                                                  /* c11_expect:  1586       */
  ++y3.q.q1;                                                               /* c11_expect:  1586       */
  if (arg)
  {
    mtx_unlock (&m1);
  }

  ++y4.b.a.counter;                                                        /* c11_expect:  1586       */

  return 0;
}

int dir_0501_other_2 ( void * arg )
{
  y1 = 1;                                                                  /* c11_expect:  1586       */
  ++y2.n2;                                                                 /* c11_expect:  1586       */
  ++y3.q.q2;                                                               /* c11_expect:  1586       */
  ++y4.b.a.counter;                                                        /* c11_expect:  1586       */
}

int dir_0501_stdlib_race (void * arg)
{
  extern int dir_0501_datarace_ext;
  mtx_t m2, m3, m4;

  mtx_init (&m2, 0);
  mtx_init (&m3, 0);
  mtx_init (&m4, 0);

  char * errmsg = NULL;

  // no lock
  FILE *fp = fopen ("example.txt", "r");
  if (fp != NULL) {
    fclose (fp);
    errmsg = strerror (errno);                                             /* expect:  4976           */
  }
  // no unlock

  if (dir_0501_datarace_ext)
  {
    mtx_lock (&m2);
  }
  if (dir_0501_datarace_ext)
  {
    errmsg = strerror (errno);                                             /* expect:  4977           */
  }
  if (dir_0501_datarace_ext)
  {
    mtx_unlock (&m2);
  }

  mtx_lock (&m3);
  if (dir_0501_datarace_ext)
  {
    errmsg = strerror (errno);                                             /* expect: !4976 !4977     */
  }
  mtx_unlock (&m3);

  if (dir_0501_datarace_ext)
  {
    errmsg = strerror (errno);                                             /* expect:  4977           */
  }

  mtx_lock (&m4);
  errmsg = strerror (errno);                                               /* expect: !4976 !4977     */
  mtx_unlock (&m4);

  mtx_destroy (&m2, 0);
  mtx_destroy (&m3, 0);
  mtx_destroy (&m4, 0);

  return 0;
}

int main(void)
{
  thrd_t id1, id2, id3, id4, id5, id6, id7;

  thrd_create( &id1, dir_0501_t1, NULL );                                  /* c11_expect:  1566       */
  thrd_create( &id2, dir_0501_t2, NULL );                                  /* c11_expect:  1566       */
  thrd_create( &id3, dir_0501_t3, NULL );                                  /* c11_expect:  1566       */
  thrd_create( &id4, dir_0501_t4, NULL );                                  /* c11_expect:  1566       */

  thrd_create( &id5, dir_0501_other_1, NULL );                             /* c11_expect:  1566       */
  thrd_create( &id6, dir_0501_other_2, NULL );                             /* c11_expect:  1566       */

  thrd_create( &id7, dir_0501_stdlib_race, NULL );
}

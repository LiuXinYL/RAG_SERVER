/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.20.c
 *
 * MISRA Mandatory - C11 Specific Rules
 *
 * Rule-22.20: Thread-specific storage pointers shall be created before being
 *             accessed
 *
 * Enforced by message(s):
 *   1785   TLS key '${name}' is created concurrently.
 *
 *   1786   Definite: race between TLS key '${name}' creation and use.
 *
 *
 *//* PRQA S 1785,1786 -- *//*
 * <<<------------------------------------------------------------ */


#include <threads.h>
#include <stddef.h>

#include "misra.h"
#include "mc25cmex.h"

static int32_t computeP1 (void);
static int32_t computeP2 (void);

static tss_t key1;
static tss_t key2;
static thrd_t id;
static mtx_t Ra;
static thrd_t idp [10];
static int32_t P1 [10];
static int32_t P2 [10];

static void print2 (int32_t *, int32_t *);

static int32_t s (void)                     /* Thread entry */
{
  int32_t ret;
  ret = tss_create (&key1, NULL);           /* c11_expect:  1785 1786 */ /* Non-compliant, t might already have tried to access */
}

static void f (void)
{
  int32_t * v1 = tss_get (key1);            /* c11_expect:  1582 */
  int32_t * v2 = tss_get (key2);
  *v1 = computeP1 ();
  *v2 = computeP2 ();
}

static void p (void)
{
  print2 (tss_get (key1), tss_get (key2));  /* c11_expect:  1582 */
}

static int32_t t (void)                     /* Thread entry */
{
  static int32_t ctr = 0;
  mtx_lock (&Ra);
  int32_t c = ctr++;
  mtx_unlock (&Ra);
  tss_set (key1, &P1 [c]);                  /* c11_expect: 1582 */ /* Non-compliant - might not yet be created */
  tss_set (key2, &P2 [c]);                                         /* Compliant */

  f ();                                     /* c11_expect: 1570 */
  p ();                                     /* c11_expect: 1570 */
}

void main (void)
{
  int32_t ret;
  int32_t i;
  ret = tss_create (&key2, NULL);                                  /* Compliant */

  mtx_init (&Ra, mtx_plain);

  for (i = 0; i < 10; i++)
  {
    thrd_create (&idp [i], t, NULL);        /* c11_expect: 1566x4 */
  }

  /* Sleep for some time */
  thrd_create (&id, s, NULL);
}

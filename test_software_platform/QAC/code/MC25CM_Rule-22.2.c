/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.2.c
 *
 * MISRA Mandatory - Rules
 *
 * Rule-22.2: A block of memory shall only be freed if it was allocated by means of
 *            a Standard Library function
 *
 * Enforced by message(s):
 *   2716   Definite: Memory deallocated multiple times (owning pointer:
 *          ${name}).
 *
 *   2717   Apparent: Memory deallocated multiple times (owning pointer:
 *          ${name}).
 *
 *   2718   Suspicious: Memory deallocated multiple times (owning pointer:
 *          ${name}).
 *
 *   2721   Definite: Deallocation of non dynamic memory (owning pointer:
 *          ${name}).
 *
 *   2722   Apparent: Deallocation of non dynamic memory  (owning pointer:
 *          ${name}).
 *
 *   2723   Suspicious: Deallocation of non dynamic memory  (owning
 *          pointer: ${name}).
 *
 *
 *//* PRQA S 2716,2717,2718,2721,2722,2723 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#include <stdlib.h>

static void Non_Dynamic_Deallocation (void)
{
  uint16_t x;

  uint16_t * p = & x;

  free (p);                            // expect: 2721

  extern int16_t R2202_c;

  uint16_t * q;

  if (R2202_c > 10)
  {
    q = malloc (sizeof (uint16_t));
  }
  else
  {
    q = & x;
  }

  free (q);                            // expect: 2722

  {
    extern int n;

    char v [8];
    void * p = malloc (8);

    while (-- n)
    {
      p = v;                           // expect: 1582
    }

    free (p);                          // expect: 2722
  }
}

static void Multiple_Deallocation (void)
{
  {
    void * p = malloc (8);
    free (p);
    free (p);                          // expect: 2716
  }

  {
    extern int n;
    void * p = malloc (8);

    if ( n > 0)
    {
      free (p);
    }

    realloc (p, 4);                    // expect: 2717
  }

  {
    extern int n;
    void * p = malloc (8);

    while (-- n > 0)
    {
      free (p);                        // expect: 2718
    }
  }
}

extern int16_t rule_2202 (void)
{
  Non_Dynamic_Deallocation ();
  Multiple_Deallocation ();

  return 1;
}

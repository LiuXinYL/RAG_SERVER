/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.1.c
 *
 * MISRA Required - Rules
 *
 * Rule-22.1: All resources obtained dynamically by means of Standard Library
 *            functions shall be explicitly released
 *
 * Enforced by message(s):
 *   2701   Definite: Opened file is not closed.
 *
 *   2702   Apparent: Opened file is not closed.
 *
 *   2703   Suspicious: Opened file is not closed.
 *
 *   2706   Definite: Allocated memory is not deallocated (owning pointer:
 *          ${name}).
 *
 *   2707   Apparent: Allocated memory is not deallocated (owning pointer:
 *          ${name}).
 *
 *   2708   Suspicious: Allocated memory is not deallocated (owning
 *          pointer: ${name}).
 *
 *   2736   Definite: Created resource is not destroyed.
 *
 *   2737   Apparent: Created resource is not destroyed.
 *
 *   2738   Suspicious: Created resource is not destroyed.
 *
 *
 *//* PRQA S 2701,2702,2703,2706,2707,2708,2736,2737,2738 -- *//*
 * <<<------------------------------------------------------------ */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "misra.h"
#include "mc25cmex.h"

int16_t u16a_2201;
int16_t u16b_2201;
int16_t u16c_2201;

static int16_t rule_2201a (void)
{
  FILE * f1_2201a = fopen ("path", "r");                   // expect: 2701
  FILE * f2_2201a = fopen ("path", "r");                   // expect: 2702

  if (u16a_2201)
  {
    fclose (f2_2201a);                                     // expect: 1581
  }

  {
    extern char const * path;
    extern int n;

    FILE * fp = fopen (path, "r");                         // expect: 2703

    while (n > 0)
    {
      fclose (fp);                                         // expect: 1581
      -- n;
    }
  }
}

static int16_t rule_2201b (void)
{
  void * m1_2201b = malloc (sizeof(int16_t[10]));          // expect: 1582
  void * m2_2201b = malloc (sizeof(int16_t[10]));          // expect: 1582

  if (u16a_2201)
  {
    free (m2_2201b);                                       // expect: 1582
  }

  {
    extern int n;
    int i;

    int * p = malloc (32);                                 // expect: 1582

    for (i = 0; i < n; ++ i)
    {
      free (p);                                            // expect: 1582
    }
  }
}                                                          // expect: 2706 2707x2

static int16_t rule_2201c (void)
{
  pthread_mutex_t mut1_2201c;
  pthread_mutex_t mut2_2201c;
  pthread_mutex_init (&mut1_2201c, 0);                     // expect: 2736
  pthread_mutex_init (&mut2_2201c, 0);                     // expect: 2737

  pthread_mutex_lock (&mut1_2201c);
  pthread_mutex_unlock (&mut1_2201c);

  if (u16a_2201)
  {
    pthread_mutex_destroy (&mut2_2201c);                   // expect: 1581
  }

  {
    extern int n;

    pthread_mutex_t  mutex;
    pthread_mutex_init (& mutex, 0);                       // expect: 2738

    while (-- n)
    {
      pthread_mutex_destroy (& mutex);                     // expect: 1581
    }
  }
}

extern int16_t rule_2201 (void)
{
  int16_t ret_2201 = 0;

  ret_2201 += rule_2201a ();
  ret_2201 += rule_2201b ();
  ret_2201 += rule_2201c ();

  return ret_2201;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-4.13.c
 *
 * MISRA Advisory - Directives
 *
 * Dir-4.13: Functions which are designed to provide operations on a resource
 *           should be called in an appropriate sequence
 *
 * Assisted by message(s):
 *   2726   Definite: Use of uninitialized resource.
 *
 *   2727   Apparent: Use of uninitialized resource.
 *
 *   2728   Suspicious: Use of uninitialized resource.
 *
 *   2731   Definite: Use of destroyed resource.
 *
 *   2732   Apparent: Use of destroyed resource.
 *
 *   2733   Suspicious: Use of destroyed resource.
 *
 *   2746   Definite: Use of uninitialized file handle.
 *
 *   2747   Apparent: Use of uninitialized file handle.
 *
 *   2748   Suspicious: Use of uninitialized file handle.
 *
 *   4866   Definite: Memory is used after free (owning pointer: ${name}).
 *
 *   4867   Apparent: Memory is used after free (owning pointer: ${name}).
 *
 *   4868   Suspicious: Memory is used after free (owning pointer:
 *          ${name}).
 *
 *
 *//* PRQA S 2726,2727,2728,2731,2732,2733,2746,2747,2748,4866,4867,4868 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void Use_of_Uninitialised_Resource (void)
{
  {
    pthread_mutex_t  mutex;

    pthread_mutex_lock (& mutex);                  // expect: 2726
    pthread_mutex_unlock (& mutex);                // expect: 2726
  }

  {
    extern int       n;
    pthread_mutex_t  mutex;

    if (n > 0)
    {
      pthread_mutex_init (& mutex, NULL);
    }

    pthread_mutex_lock (& mutex);                  // expect: 2727
    pthread_mutex_unlock (& mutex);                // expect: 2727
  }

  {
    extern int       n;
    pthread_mutex_t  mutex;

    pthread_mutex_init (& mutex, 0);

    while (--n)
    {
      pthread_mutex_t m;
      mutex = m;
    }

    pthread_mutex_lock (& mutex);                  // expect: 2728
    pthread_mutex_unlock (& mutex);                // expect: 2728
    pthread_mutex_destroy (& mutex);               // expect: 2728
  }
}

void Use_of_Destroyed_Resource (void)
{
  {
    pthread_mutex_t mutex;

    pthread_mutex_init (& mutex, 0);
    pthread_mutex_destroy (& mutex);
    pthread_mutex_lock (& mutex);                  // expect: 2731
    pthread_mutex_unlock (& mutex);                // expect: 2731
  }

  {
    extern int       n;
    pthread_mutex_t  mutex;

    pthread_mutex_init (& mutex, 0);

    if (n > 0)
    {
      pthread_mutex_destroy (& mutex);
    }

    pthread_mutex_lock (& mutex);                  // expect: 2732
    pthread_mutex_unlock (& mutex);                // expect: 2732
  }

  {
    extern int       n;
    pthread_mutex_t  mutex;

    pthread_mutex_init (& mutex, 0);

    while (-- n > 0)
    {
      pthread_mutex_destroy (& mutex);             // expect: 2733
    }

    pthread_mutex_lock (& mutex);                  // expect: 2733
    pthread_mutex_unlock (& mutex);                // expect: 2733
  }
}

void Use_of_Uninitialised_File_Handle (void)
{
  {
    FILE * f;
    fprintf (f, "hello");                          // expect: 2746
    fclose (f);                                    // expect: 2746
  }

  {
    extern int  n;
    FILE *      f;
    FILE *      g;

    f = fopen ("my_file.txt", "w");

    if (n > 0)
    {
      f = g;
    }

    fprintf (f, "hello");                          // expect: 2747
    fclose (f);                                    // expect: 2747
  }

  {
    extern int  n;
    FILE *      f;
    FILE *      g;

    f = fopen ("my_file.txt", "w");

    while (-- n > 0)
    {
      f = g;
    }

    fprintf (f, "hello");                          // expect: 2748
    fclose (f);                                    // expect: 2748
  }
}

void Use_of_freed_memory ()
{
  {
    char *buf = (char *)malloc(32);

    if (!buf)
      return;

    free(buf);

    buf[0];                                        // expect: 4866

    strcat(buf, "abc");                            // expect: 4866
  }

  {
    extern int n;
    char *buf = (char *)malloc(32);

    if (!buf)
      return;

    if( n == 0 )
    {
      free(buf);
    }

    buf[0];                                        // expect: 4867

    strcat(buf, "abc");                            // expect: 4867
  }
}

extern int16_t dir_0413( void )
{
  Use_of_Uninitialised_Resource ();
  Use_of_Destroyed_Resource ();
  Use_of_Uninitialised_File_Handle ();
  Use_of_freed_memory ();

  return 1;
}

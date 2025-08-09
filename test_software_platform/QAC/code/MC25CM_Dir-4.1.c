/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-4.1.c
 *
 * MISRA Required - Directives
 *
 * Dir-4.1: Run-time failures shall be minimized
 *
 * Assisted by message(s):
 *   2791   Definite: Right hand operand of shift operator is negative or
 *          too large.
 *
 *   2792   Apparent: Right hand operand of shift operator is negative or
 *          too large.
 *
 *   2793   Suspicious: Right hand operand of shift operator is negative or
 *          too large.
 *
 *   2794   Possible: Tainted right hand operand of shift operator is
 *          negative or too large.
 *
 *   2801   Definite: Overflow in signed arithmetic operation.
 *
 *   2802   Apparent: Overflow in signed arithmetic operation.
 *
 *   2803   Suspicious: Overflow in signed arithmetic operation.
 *
 *   2804   Possible: Overflow in signed arithmetic tainted operation.
 *
 *   2811   Definite: Dereference of NULL pointer.
 *
 *   2812   Apparent: Dereference of NULL pointer.
 *
 *   2813   Suspicious: Dereference of NULL pointer.
 *
 *   2821   Definite: Arithmetic operation on NULL pointer.
 *
 *   2822   Apparent: Arithmetic operation on NULL pointer.
 *
 *   2823   Suspicious: Arithmetic operation on NULL pointer.
 *
 *   2831   Definite: Division by zero.
 *
 *   2832   Apparent: Division by zero.
 *
 *   2833   Suspicious: Division by zero.
 *
 *   2841   Definite: Dereference of an invalid pointer value.
 *
 *   2842   Apparent: Dereference of an invalid pointer value.
 *
 *   2843   Suspicious: Dereference of an invalid pointer value.
 *
 *   2845   Constant: Maximum number of characters to be read/written is
 *          larger than the target buffer size.
 *
 *   2846   Definite: Maximum number of characters to be read/written is
 *          larger than the target buffer size.
 *
 *   2847   Apparent: Maximum number of characters to be read/written is
 *          larger than the target buffer size.
 *
 *   2848   Suspicious: Maximum number of characters to be read/written is
 *          larger than the target buffer size.
 *
 *   2871   Infinite loop identified.
 *
 *   2872   This loop, if entered, will never terminate.
 *
 *   2877   This loop will never be executed more than once.
 *
 *   2935   Constant: Dereference of an invalid char pointer value.
 *
 *   2936   Definite: Dereference of an invalid char pointer value.
 *
 *   2937   Apparent: Dereference of an invalid char pointer value.
 *
 *   2938   Suspicious: Dereference of an invalid char pointer value.
 *
 *   4951   Definite: Beware of race conditions when using fork and file
 *          descriptors.
 *
 *   4952   Apparent: Beware of race conditions when using fork and file
 *          descriptors.
 *
 *   2877   This loop will never be executed more than once.
 *
 *
 *//* PRQA S 2791,2792,2793,2794,2801,2802,2803,2804,2811,2812,2813,2821,2822,2823,2831,2832,2833,2841,2842,2843,2845,2846,2847,2848,2871,2872,2877,2935,2936,2937,2938,4951,4952,2877 -- *//*
 * <<<------------------------------------------------------------ */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "misra.h"
#include "mc25cmex.h"

int16_t s16a_d0401;                                                   // expect: 1594 1594 1594 1594 1594
int16_t s16b_d0401;
uint16_t u16a_d0401;
uint16_t u16b_d0401;
int16_t * p16a_d0401;                                                 // expect: 1594 1594
int16_t * p16b_d0401;
int16_t a16a_d0401[5];                                                // expect: 1594 1594 1594 1594 1594 1594 1594 1594 1594
int16_t a16b_d0401[5];
bool_t ba_d0401;
bool_t bb_d0401;

static int16_t dir_0401a (int16_t val_d0401a)                         // expect: 1594 1594 1594
{
  int16_t ret_d0401a;

  if (s16a_d0401 < 0)                                                 // expect: 1575 1575
  {
    ret_d0401a = val_d0401a << s16a_d0401;                            // expect: 2791
  }
  if (s16a_d0401 > 17)                                                // expect: 1575
  {
    ret_d0401a = val_d0401a << s16a_d0401;                            // expect: 2791
  }

  if (s16b_d0401 > 17)                                                // expect: 1575
  {
  }
  ret_d0401a = val_d0401a << s16b_d0401;                              // expect: 2792 1574

  {
    extern int n;
    int i;
    int s = 40;
    unsigned long x = 1;

    for (i = 0; i < n; ++i)
    {
      -- s;
    }

    x <<= s;                                                          // expect: 2793 1574
  }

  {
    int           s;
    unsigned long x = 1;

    scanf ("%d", & s);

    x <<= s;                                                          // expect: 2794
  }

  return ret_d0401a;
}

static int16_t dir_0401b (int16_t val_d0401b)                         // expect: 1594 1594
{
  int16_t ret_d0401b;

  if (s16a_d0401 > 0xFF && val_d0401b > 0xFF)                         // expect: 1575 1575 1575 1575
  {
    ret_d0401b = val_d0401b * s16a_d0401;                             // expect: 2801
  }
  if (s16a_d0401 > 30000 && val_d0401b > 30000)                       // expect: 1575 1575
  {
    ret_d0401b = val_d0401b + s16a_d0401;                             // expect: 2801
  }

  if (s16b_d0401 > 0xFF && val_d0401b > 0xFF)                         // expect: 1575 1575 1575 1575
  {
  }
  ret_d0401b = val_d0401b * s16b_d0401;                               // expect: 2802 1574
  if (s16a_d0401 > 10000 && val_d0401b > 10000)
  {
  }
  ret_d0401b = val_d0401b * s16b_d0401;                               // expect: 2802 1574

  {
    extern int n;
    int     i;
    int x = 10000;

    for (i = 0; i < n; ++i)
    {
      x = 2;
    }

    x *= 1000;                                                        // expect: 2803 1574
  }

  {
    int x;

    scanf ("%i", & x);

    x += 2;                                                           // expect: 2804
  }

  return ret_d0401b;
}

static int16_t dir_0401c (void)
{
  int16_t ret_d0401c;

  if (p16a_d0401 == NULL)                                             // expect: 1582
  {
    ret_d0401c = *p16a_d0401;                                         // expect: 2811
  }

  if (p16b_d0401 == NULL)                                             // expect: 1582
  {
  }
  ret_d0401c = *p16b_d0401;                                           // expect: 2812 1574

  {
    extern int n;
    int   i;
    int * p = NULL;

    for (i = 0; i < n; ++i)
    {
      p = & i;
    }

    * p;                                                              // expect: 2813 1574
  }

  return ret_d0401c;
}

static int16_t dir_0401d (int16_t val_d0401d)
{
  int16_t ret_d0401d;

  if (p16a_d0401 == NULL)                                             // expect: 1582
  {
    ret_d0401d = p16a_d0401[val_d0401d];                              // expect: 2821
  }

  if (p16b_d0401 == NULL)                                             // expect: 1582
  {
  }
  ret_d0401d = p16b_d0401[val_d0401d];                                // expect: 2822 1574

  {
    extern int n;
    int   i;
    int * p = NULL;

    for (i = 0; i < n; ++i)
    {
      p = & i;
    }

    ++ p;                                                             // expect: 2823 1574
  }

  return ret_d0401d;
}

static int16_t dir_0401e (int16_t val_d0401e)
{
  int16_t ret_d0401e;

  if (s16a_d0401 == 0)                                                // expect: 1575
  {
    ret_d0401e = val_d0401e / s16a_d0401;                             // expect: 2831
  }

  if (s16b_d0401 == 0)                                                // expect: 1575
  {
  }
  ret_d0401e = val_d0401e / s16b_d0401;                               // expect: 2832 1574

  {
    extern int n;
    int i;
    int x = 0;

    for (i = 0; i < n; ++i)
    {
      x += i;
    }

    x = 1000 / x;                                                     // expect: 2833 1574
  }

  return ret_d0401e;
}

static int16_t dir_0401f (int16_t val_d0401f)                         // expect: 1594 1594
{
  int16_t ret_d0401f;

  if (val_d0401f >= 5)                                                // expect: 1575 1575 1575 1575
  {
    ret_d0401f = a16a_d0401[val_d0401f];                              // expect: 2841
  }
  if (val_d0401f < 0)                                                 // expect: 1575 1575 1575
  {
    ret_d0401f = a16a_d0401[val_d0401f];                              // expect: 2841
  }

  if (val_d0401f >= 5)                                                // expect: 1575 1575
  {
  }
  ret_d0401f = a16a_d0401[val_d0401f];                                // expect: 2842 1574 1574 1574
  if (val_d0401f < 0)                                                 // expect: 1575
  {
  }
  ret_d0401f = a16a_d0401[val_d0401f];                                // expect: 2842 1574 1574 1574 1574

  {
    extern int n;
    int i;
    int x = 8;
    int v [4];

    for (i = 0; i < n; ++i)
    {
      -- x;
    }

    v [x] = 0;                                                        // expect: 2843 1574
  }

  return ret_d0401f;
}

static int16_t dir_0401g (void)
{
  int16_t ret_d0401g;

  char dst_d0401g[5];                                                 // expect: 1594 1594 1594 1594 1594 1594
  char src_d0401g[6] = "hello";

  dst_d0401g[0] = '\0';
  strncpy (dst_d0401g, src_d0401g, sizeof(src_d0401g));               // expect: 2845
  dst_d0401g[0] = '\0';
  strncat (dst_d0401g, src_d0401g, sizeof(src_d0401g));               // expect: 2845

  if (s16a_d0401 > sizeof(dst_d0401g))                                // expect: 1575
  {
    dst_d0401g[0] = '\0';
    strncpy (dst_d0401g, src_d0401g, s16a_d0401);                     // expect: 2846 1575
  }
  if (s16a_d0401 > sizeof(dst_d0401g))                                // expect: 1575
  {
    dst_d0401g[0] = '\0';
    strncat (dst_d0401g, src_d0401g, s16a_d0401);                     // expect: 2846
  }

  if (s16b_d0401 > sizeof(dst_d0401g))                                // expect: 1575
  {
  }
  dst_d0401g[0] = '\0';
  strncpy (dst_d0401g, src_d0401g, s16b_d0401);                       // expect: 2847 1574
  if (s16b_d0401 > sizeof(dst_d0401g))                                // expect: 1575
  {
  }
  dst_d0401g[0] = '\0';
  strncat (dst_d0401g, src_d0401g, s16b_d0401);                       // expect: 2847 1574

  {
    extern int  n;
    extern char a [8];
    extern char b [9];

    int i;
    int m = sizeof (b);

    for (i = 0; i < n; ++i)
    {
      -- m;
    }

    strncpy (a, b, m);                                                // expect: 2848 1574 1574
  }

  return ret_d0401g;
}

static int16_t dir_0401h (int16_t val_d0401h)
{
  int16_t ret_d0401h;

  if (ba_d0401)
  {
    for (val_d0401h = 1; val_d0401h != 0; -- u16a_d0401)              // expect: 2871
    {
    }
  }

  if (bb_d0401)
  {
    while (u16b_d0401 < 10)                                           // expect: 2872
    {
    }
  }

  ret_d0401h = 1;
  while (ret_d0401h > 0)                                              // expect: 2877
  {
    -- ret_d0401h;                                                    // expect: 1575
  }

  for (val_d0401h = 1; val_d0401h != 0; -- val_d0401h)                // expect: 2877 1575
  {
  }

  return ret_d0401h;
}

static void Invalid_Char_Pointer_Dereference (void)
{
  {
    char s [] = "Short";
    strcpy (s, "Too long to fit");                                   // expect: 2935
  }

  {
    char s [4];
    char * p = s;
    strcpy (p, "Too long to fit" );                                  // expect: 2936
  }

  {
    extern int n;
    char s1 [40];
    char s2 [4];
    char * p = s1;

    if (n > 0)
    {
      p = s2;
    }

    strcpy (p, "Too long to fit" );                                  // expect: 2937
  }

  {
    extern int n;
    char s1 [40];
    char s2 [4];
    char * p = s1;

    while (-- n > 0)
    {
      p = s2;
    }

    strcpy (p, "Too long to fit" );                                  // expect: 2938
  }
}

static int16_t dir_0401j (void)
{
  typedef int pid_t;
  extern pid_t fork(void);
  extern int x0401j;

  char c;
  size_t n;

  FILE *f = fopen ("example.txt", "r");
  if (NULL == f) {
    // ...
    return 1;
  }

  pid_t pid = fork();
  if (-1 == pid) {
    // ...
    return 2;
  }

  if (pid) {
    // ...
  } else {
    n = fread (&c, 1, 1, f);                                          // expect: 4951
    if (x0401j)
      n = fread (&c, 1, 1, f);                                        // expect: 4952
  }

  return 1;
}

extern int16_t dir_0401 (void)
{
  int16_t ret_d0401 = s16a_d0401;

  ret_d0401 += dir_0401a (s16b_d0401);
  ret_d0401 += dir_0401b (s16b_d0401);
  ret_d0401 += dir_0401c ();
  ret_d0401 += dir_0401d (s16b_d0401);
  ret_d0401 += dir_0401e (s16b_d0401);
  ret_d0401 += dir_0401f (s16b_d0401);
  ret_d0401 += dir_0401g ();
  ret_d0401 += dir_0401h (s16b_d0401);
  ret_d0401 += dir_0401j ();

  Invalid_Char_Pointer_Dereference ();

  return ret_d0401;
}

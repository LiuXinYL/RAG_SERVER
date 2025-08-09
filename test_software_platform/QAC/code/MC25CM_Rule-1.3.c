/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-1.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-1.3: There shall be no occurrence of undefined or critical unspecified
 *           behaviour
 *
 * Enforced by message(s):
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
 *   2801   Definite: Overflow in signed arithmetic operation.
 *
 *   2802   Apparent: Overflow in signed arithmetic operation.
 *
 *   2803   Suspicious: Overflow in signed arithmetic operation.
 *
 *   2804   Possible: Overflow in signed arithmetic tainted operation.
 *
 *   2806   Definite: Calling a standard library wide character handling
 *          function with an invalid character value.
 *
 *   2807   Apparent: Calling a standard library wide character handling
 *          function with an invalid character value.
 *
 *   2808   Suspicious: Calling a standard library wide character handling
 *          function with an invalid character value.
 *
 *   2810   Constant: Dereference of NULL pointer.
 *
 *   2811   Definite: Dereference of NULL pointer.
 *
 *   2812   Apparent: Dereference of NULL pointer.
 *
 *   2813   Suspicious: Dereference of NULL pointer.
 *
 *   2820   Constant: Arithmetic operation on NULL pointer.
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
 *   2840   Constant: Dereference of an invalid pointer value.
 *
 *   2841   Definite: Dereference of an invalid pointer value.
 *
 *   2842   Apparent: Dereference of an invalid pointer value.
 *
 *   2843   Suspicious: Dereference of an invalid pointer value.
 *
 *   2935   Constant: Dereference of an invalid char pointer value.
 *
 *   4866   Definite: Memory is used after free (owning pointer: ${name}).
 *
 *   4867   Apparent: Memory is used after free (owning pointer: ${name}).
 *
 *   4868   Suspicious: Memory is used after free (owning pointer:
 *          ${name}).
 *
 *   4931   Definite: Initialising a mutex which has already been
 *          initialised
 *
 *   4932   Apparent: Initialising a mutex which has already been
 *          initialised
 *
 *   4966   Definite: Performing a blocking action while holding a POSIX
 *          lock.
 *
 *   4967   Apparent: Performing a blocking action while holding a POSIX
 *          lock.
 *
 *   4976   Definite: Call to a non-reentrant function outside of a
 *          critical section.
 *
 *   4977   Apparent: Call to a non-reentrant function outside of a
 *          critical section.
 *
 *   4995   Constant: Using an invalid thread identifier.
 *
 *   4996   Definite: Using an invalid thread identifier.
 *
 *   4997   Apparent: Using an invalid thread identifier.
 *
 *   4998   Suspicious: Using an invalid thread identifier.
 *
 *   0160   Using unsupported conversion specifier number ${num}.
 *
 *   0161   Unknown length modifier used with 'i' or 'd' conversion
 *          specifier, number ${num}.
 *
 *   0162   Unknown length modifier used with 'o' conversion specifier,
 *          number ${num}.
 *
 *   0163   Unknown length modifier used with 'u' conversion specifier,
 *          number ${num}.
 *
 *   0164   Unknown length modifier used with 'x' conversion specifier,
 *          number ${num}.
 *
 *   0165   Unknown length modifier used with 'X' conversion specifier,
 *          number ${num}.
 *
 *   0166   Unknown length modifier used with 'f' conversion specifier,
 *          number ${num}.
 *
 *   0167   Unknown length modifier used with 'e' conversion specifier,
 *          number ${num}.
 *
 *   0168   Unknown length modifier used with 'E' conversion specifier,
 *          number ${num}.
 *
 *   0169   Unknown length modifier used with 'g' conversion specifier,
 *          number ${num}.
 *
 *   0170   Unknown length modifier used with 'G' conversion specifier,
 *          number ${num}.
 *
 *   0171   Unknown length modifier used with 'c' conversion specifier,
 *          number ${num}.
 *
 *   0172   Unknown length modifier used with '%%' conversion specifier,
 *          number ${num}.
 *
 *   0173   Unknown length modifier used with 's' conversion specifier,
 *          number ${num}.
 *
 *   0174   Unknown length modifier used with 'n' conversion specifier,
 *          number ${num}.
 *
 *   0175   Unknown length modifier used with 'p' conversion specifier,
 *          number ${num}.
 *
 *   0176   Incomplete conversion specifier, number ${num}.
 *
 *   0177   Field width of format conversion specifier exceeds 509
 *          characters.
 *
 *   0178   Precision of format conversion specifier exceeds 509
 *          characters.
 *
 *   0179   Argument type does not match conversion specifier number
 *          ${num}.
 *
 *   0184   Insufficient arguments to satisfy conversion specifier, number
 *          ${num}.
 *
 *   0185   Call contains more arguments than conversion specifiers.
 *
 *   0186   A call to this function must include at least one argument.
 *
 *   0190   Using unsupported conversion specifier number ${num}.
 *
 *   0191   Unknown length modifier used with 'd/i/n' conversion specifier,
 *          number ${num}.
 *
 *   0192   Unknown length modifier used with 'o' conversion specifier,
 *          number ${num}.
 *
 *   0193   Unknown length modifier used with 'u' conversion specifier,
 *          number ${num}.
 *
 *   0194   Unknown length modifier used with 'x/X' conversion specifier,
 *          number ${num}.
 *
 *   0195   Unknown length modifier used with 'e/E/f/F/g/G' conversion
 *          specifier, number ${num}.
 *
 *   0196   Unknown length modifier used with 's' conversion specifier,
 *          number ${num}.
 *
 *   0197   Unknown length modifier used with 'p' conversion specifier,
 *          number ${num}.
 *
 *   0198   Unknown length modifier used with '%%' conversion specifier,
 *          number ${num}.
 *
 *   0199   Unknown length modifier used with '[' conversion specifier,
 *          number ${num}.
 *
 *   0200   Unknown length modifier used with 'c' conversion specifier,
 *          number ${num}.
 *
 *   0201   Incomplete conversion specifier, number ${num}.
 *
 *   0203   Value of character prior to '-' in '[]' is greater than
 *          following character.
 *
 *   0204   Field width of format conversion specifier exceeds 509
 *          characters.
 *
 *   0206   Argument type does not match conversion specifier number
 *          ${num}.
 *
 *   0207   'scanf' expects address of objects being stored into.
 *
 *   0208   Same character occurs in scanset more than once.
 *
 *   0235   Unknown escape sequence.
 *
 *   0275   Floating value is out of range for conversion to destination
 *          type.
 *
 *   0301   Cast between a pointer to object and a floating type.
 *
 *   0302   Cast between a pointer to function and a floating type.
 *
 *   0304   The address of an array declared 'register' may not be
 *          computed.
 *
 *   0307   Cast between a pointer to object and a pointer to function.
 *
 *   0309   Integral type is not large enough to hold a pointer value.
 *
 *   0337   String literal has undefined value. This may be a result of
 *          using '#' on \\.
 *
 *   0400   '${name}' is modified more than once between sequence points -
 *          evaluation order unspecified.
 *
 *   0401   '${name}' may be modified more than once between sequence
 *          points - evaluation order unspecified.
 *
 *   0402   '${name}' is modified and accessed between sequence points -
 *          evaluation order unspecified.
 *
 *   0403   '${name}' may be modified and accessed between sequence points
 *          - evaluation order unspecified.
 *
 *   0404   More than one read access to volatile objects between sequence
 *          points.
 *
 *   0405   More than one modification of volatile objects between sequence
 *          points.
 *
 *   0475   Operand of 'sizeof' is an expression designating a bit-field.
 *
 *   0543   'void' expressions have no value and may not be used in
 *          expressions.
 *
 *   0544   The value of an incomplete 'union' may not be used.
 *
 *   0545   The value of an incomplete 'struct' may not be used.
 *
 *   0602   The identifier '${ident}' is reserved for use by the library.
 *
 *   0603   The macro identifier '${macro}' is reserved.
 *
 *   0623   '%s' has incomplete type and no linkage - this is undefined.
 *
 *   0625   '%s' has been declared with both internal and external linkage
 *          - the behaviour is undefined.
 *
 *   0626   '%s' has different type to previous declaration (which is no
 *          longer in scope).
 *
 *   0630   More than one definition of '%s' (with external linkage).
 *
 *   0632   Tentative definition of '%s' with internal linkage cannot have
 *          unknown size.
 *
 *   0636   There are no named members in this 'struct' or 'union'.
 *
 *   0658   Parameter cannot have 'void' type.
 *
 *   0661   '${name}()' may not have a storage class specifier of '${spec}'
 *          when declared at block scope.
 *
 *   0667   '%s' is declared as a typedef and may not be redeclared as an
 *          object at an inner scope without an explicit type
 *          specifier.
 *
 *   0668   '%s' is declared as a typedef and may not be redeclared as a
 *          member of a 'struct' or 'union' without an explicit type
 *          specifier.
 *
 *   0672   The initializer for a 'struct', 'union' or array is not
 *          enclosed in braces.
 *
 *   0676   Array element is of function type. Arrays cannot be constructed
 *          from function types.
 *
 *   0678   Array element is array of unknown size. Arrays cannot be
 *          constructed from incomplete types.
 *
 *   0680   Array element is 'void' or an incomplete 'struct' or 'union'.
 *          Arrays cannot be constructed from incomplete types.
 *
 *   0706   Label '%s' is not unique within this function.
 *
 *   0745   'return;' found in '%s()', which has been defined with a
 *          non-'void' return type.
 *
 *   0813   Using any of the characters ' " or /* in '#include <%s>' gives
 *          undefined behaviour.
 *
 *   0814   Using the characters ' or /* in '#include "%s"' gives undefined
 *          behaviour.
 *
 *   0836   Definition of macro named 'defined'.
 *
 *   0837   Use of '#undef' to remove the operator 'defined'.
 *
 *   0840   Extra tokens at end of #include directive.
 *
 *   0848   Attempting to #undef '${name}', which is a predefined macro
 *          name.
 *
 *   0853   Macro arguments contain a sequence of tokens that has the form
 *          of a preprocessing directive.
 *
 *   0854   Attempting to #define '${name}', which is a predefined macro
 *          name.
 *
 *   0864   '#line' directive specifies line number which is not in the
 *          range 1 to 32767.
 *
 *   0865   '#line' directive is badly formed.
 *
 *   0867   '#line' has not been followed by a line number.
 *
 *   0872   Result of '##' operator is not a legal preprocessing token.
 *
 *   0874   Character string literal and wide character string literal are
 *          adjacent.
 *
 *   0885   The token 'defined' is generated in the expansion of this
 *          macro.
 *
 *   0887   Use of 'defined' must match either 'defined(identifier)' or
 *          'defined identifier'.
 *
 *   0888   'defined' requires an identifier as an argument.
 *
 *   0905   Producing a universal character name through token
 *          concatenation is undefined.
 *
 *   0914   Source file does not end with a newline character.
 *
 *   0915   Source file ends with a backslash character followed by a
 *          newline.
 *
 *   0942   A * can only be used to specify array size within function
 *          prototype scope.
 *
 *   1119   Multiple declarations of '${name}' have different explicit
 *          alignments.
 *
 *   1147   Qualifying a function type is undefined.
 *
 *   1331   Type or number of arguments doesn't match previous use of the
 *          function.
 *
 *   1332   Type or number of arguments doesn't match prototype found
 *          later.
 *
 *   1333   Type or number of arguments doesn't match function definition
 *          found later.
 *
 *   2800   Constant: Overflow in signed arithmetic operation.
 *
 *   2830   Constant: Division by zero.
 *
 *   2840   Constant: Dereference of an invalid pointer value.
 *
 *   3113   'return' statement includes no expression but function '%s()'
 *          is implicitly of type 'int'.
 *
 *   3114   Function '%s()' is implicitly of type 'int' but ends without
 *          returning a value.
 *
 *   3239   inline function '${name}' has external linkage, but is not
 *          defined within this translation unit.
 *
 *   3311   An earlier jump to this statement will bypass the
 *          initialization of local variables.
 *
 *   3312   This goto statement will jump into a previous block and bypass
 *          the initialization of local variables.
 *
 *   3319   Function called with number of arguments which differs from
 *          number of parameters in definition.
 *
 *   3320   Type of argument no. ${n} differs from its type in definition
 *          of function.
 *
 *   3437   '${name}' is only provided by the standard library as a macro,
 *          but is being used as a value here.
 *
 *   3438   #undef'ing the assert macro to call a function of that name
 *          causes undefined behaviour.
 *
 *   1509   '${name}' has external linkage and has multiple definitions.
 *
 *   1510   '${name}' has external linkage and has incompatible
 *          declarations.
 *
 *
 *//* PRQA S 2726,2727,2728,2731,2732,2733,2746,2747,2748,2801,2802,2803,2804,2806,2807,2808,2810,2811,2812,2813,2820,2821,2822,2823,2831,2832,2833,2840,2841,2842,2843,2935,4866,4867,4868,4931,4932,4966,4967,4976,4977,4995,4996,4997,4998,0160,0161,0162,0163,0164,0165,0166,0167,0168,0169,0170,0171,0172,0173,0174,0175,0176,0177,0178,0179,0184,0185,0186,0190,0191,0192,0193,0194,0195,0196,0197,0198,0199,0200,0201,0203,0204,0206,0207,0208,0235,0275,0301,0302,0304,0307,0309,0337,0400,0401,0402,0403,0404,0405,0475,0543,0544,0545,0602,0603,0623,0625,0626,0630,0632,0636,0658,0661,0667,0668,0672,0676,0678,0680,0706,0745,0813,0814,0836,0837,0840,0848,0853,0854,0864,0865,0867,0872,0874,0885,0887,0888,0905,0914,0915,0942,1119,1147,1331,1332,1333,2800,2830,2840,3113,3114,3239,3311,3312,3319,3320,3437,3438,1509,1510 -- *//*
 * <<<------------------------------------------------------------ */

#include "mc25cmex.h"

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

void Multi_Extern_Different_Type_1 (void)
{
    extern int32_t n;                                       // expect: 1510
}

void Multi_Extern_Different_Type_2 (void)
{
    extern int n;                                           // expect: 0626  1510
}

void Overflow_In_Signed_Arithmetic_Operation (void)
{
  {
    int32_t x = 40000000 * 40000000;                        // expect: 2800
  }

  {
    int32_t n;
    int32_t x;

    n = 1000000000;
    x = n * 4;                                              // expect: 2801
  }

  {
    extern int32_t mc25cm_n;
    int32_t x = 2;

    if (mc25cm_n > 0)
    {
      x = 4;
    }

    x = 1000000000 * x;                                     // expect: 2802
  }

  {
    extern int32_t mc25cm_n;
    int32_t x = 4;
    int32_t i;

    for (i = 0; i < mc25cm_n; ++i)
    {
      x = 2;
    }

    x = 1000000000 * x;                                     // expect: 2803
  }

  {
    int x;
    scanf ("%d", & x);
    ++ x;                                                   // expect: 2804
  }
}

void Dereference_Of_Null_Pointer (void)
{
  {
    * (int *) 0 = 0;                                        // expect: 2810
  }

  {
    int * x = NULL;
    * x = 0;                                                // expect: 2811
  }

  {
    extern int32_t mc25cm_n;
    int v = 0;
    int * x = NULL;
    if (mc25cm_n > 0)
    {
      x = & v;
    }
    * x = 0;                                                // expect: 2812
  }

  {
    extern int32_t mc25cm_n;
    int v = 0;
    int * x = NULL;
    for (int i = 0; i < mc25cm_n; ++ i)
    {
      x = & v;
    }
    * x = 0;                                                // expect: 2813
  }
}

void Arithmetic_Operation_On_Null_Pointer (void)
{
  {
    int32_t * p;

    p = (int32_t *) NULL + 1 ;                              // expect: 2820
  }

  {
    int32_t * p = NULL;

    ++ p;                                                   // expect: 2821
  }

  {
    extern int32_t * p;                                     // expect: 1510

    if (p == NULL)
    {
    }

    ++ p;                                                   // expect: 2822
  }

  {
    extern int32_t mc25cm_n;
    int32_t i;
    int32_t v [2];
    int32_t * p = NULL;

    for (i = 0; i < mc25cm_n; ++ i)
    {
      p = v;
    }

    p++;                                                    // expect: 2823
  }
}

void division_by_zero_1( int32_t x, int32_t n )
{
  int32_t r;

  if ( n == 0 )
  {
    r = x / n;                                              // expect:2831
  }
}

void Division_By_Zero (void)
{
  {
    1000 / 0;                                               // expect: 2830
  }

  {
    int32_t x;
    int32_t y;

    x = 0;
    y = 10 / x;                                             // expect: 2831
  }

  {
    extern int32_t x;                                       // expect: 1510

    if (x == 0)
    {
    }

    1000 / x;                                               // expect: 2832
  }

  {
    extern int32_t mc25cm_n;
    int32_t r;
    int32_t i;
    int32_t x = 0;

    for ( i = 0; i < mc25cm_n; ++i )
    {
      x = x + i;
    }

    r = 10 / x;                                             // expect: 2833
  }
}

void Dereference_Of_An_Invalid_Pointer_Value (void)
{
  {
    int32_t v [8] = { 0 };
    int32_t x;

    x = v [8];                                              // expect: 2840

    v [8] = 0;                                              // expect: 2840

    * (v + 8) = 0;                                          // expect: 2840
  }

  {
    int32_t n = 8;
    int32_t v [8];

    v [n] = 1;                                              // expect: 2841
  }

  {
    extern int32_t mc25cm_n;
    int32_t v [8];

    if (mc25cm_n == 8)
    {
    }

    v [mc25cm_n] = 1;                                         // expect: 2842
  }

  {
    extern int32_t mc25cm_n;
    int32_t v [8];
    int32_t i;
    int32_t x = 8;

    for (i = 0; i < mc25cm_n; ++ i)
    {
      -- x;
    }

    v [x] = 1;                                              // expect: 2843
  }
}

void Wide_Character_Types (void)
{
  {
    iswalpha (666);                                         // expect: 2806
  }

  {
    extern int32_t mc25cm_n;
    int c = 'c';

    if (mc25cm_n > 0)
    {
      c += 666;
    }

    iswalnum (c);                                           // expect: 2807
  }

  {
    extern int32_t mc25cm_n;
    int c = 666;

    while (-- mc25cm_n > 0)
    {
      c -= 8;
    }

    iswupper (c);                                           // expect: 2808
  }
}

void Use_of_Uninitialised_Resource (void)                   // expect: 1509
{
  {
    pthread_mutex_t  mutex;

    pthread_mutex_lock (& mutex);                           // expect: 2726
    pthread_mutex_unlock (& mutex);                         // expect: 2726
  }

  {
    extern int32_t mc25cm_n;
    pthread_mutex_t  mutex;

    if (mc25cm_n > 0)
    {
      pthread_mutex_init (& mutex, NULL);
    }

    pthread_mutex_lock (& mutex);                           // expect: 2727
    pthread_mutex_unlock (& mutex);                         // expect: 2727
  }

  {
    extern int32_t mc25cm_n;
    pthread_mutex_t  mutex;

    pthread_mutex_init (& mutex, 0);

    while (--mc25cm_n)
    {
      pthread_mutex_t m;
      mutex = m;
    }

    pthread_mutex_lock (& mutex);                           // expect: 2728
    pthread_mutex_unlock (& mutex);                         // expect: 2728
    pthread_mutex_destroy (& mutex);                        // expect: 2728
  }
}

void Use_of_Destroyed_Resource (void)                       // expect: 1509
{
  {
    pthread_mutex_t mutex;

    pthread_mutex_init (& mutex, 0);
    pthread_mutex_destroy (& mutex);
    pthread_mutex_lock (& mutex);                           // expect: 2731
    pthread_mutex_unlock (& mutex);                         // expect: 2731
  }

  {
    extern int32_t mc25cm_n;
    pthread_mutex_t  mutex;

    pthread_mutex_init (& mutex, 0);

    if (mc25cm_n > 0)
    {
      pthread_mutex_destroy (& mutex);
    }

    pthread_mutex_lock (& mutex);                           // expect: 2732
    pthread_mutex_unlock (& mutex);                         // expect: 2732
  }


  {
    extern int32_t mc25cm_n;
    pthread_mutex_t  mutex;

    pthread_mutex_init (& mutex, 0);

    while (-- mc25cm_n > 0)
    {
      pthread_mutex_destroy (& mutex);                      // expect: 2733
    }

    pthread_mutex_lock (& mutex);                           // expect: 2733
    pthread_mutex_unlock (& mutex);                         // expect: 2733
  }
}

void Use_of_Uninitialised_File_Handle (void)                // expect: 1509
{
  {
    FILE * f;
    fprintf (f, "hello");                                   // expect: 2746
    fclose (f);                                             // expect: 2746
  }

  {
    extern int32_t mc25cm_n;
    FILE *      f;
    FILE *      g;

    f = fopen ("my_file.txt", "w");

    if (mc25cm_n > 0)
    {
      f = g;
    }

    fprintf (f, "hello");                                   // expect: 2747
    fclose (f);                                             // expect: 2747
  }

  {
    extern int32_t mc25cm_n;
    FILE *      f;
    FILE *      g;

    f = fopen ("my_file.txt", "w");

    while (-- mc25cm_n > 0)
    {
      f = g;
    }

    fprintf (f, "hello");                                   // expect: 2748
    fclose (f);                                             // expect: 2748
  }
}

void Use_of_freed_memory ()                                 // expect: 1509
{
  {
    char *buf = (char *)malloc(32);

    if (!buf)
      return;

    free(buf);

    buf[0];                                                 // expect: 4866

    strcat(buf, "abc");                                     // expect: 4866
  }

  {
    extern int32_t mc25cm_n;
    char *buf = (char *)malloc(32);

    if (!buf)
      return;

    if( mc25cm_n == 0 )
    {
      free(buf);
    }

    buf[0];                                                 // expect: 4867

    strcat(buf, "abc");                                     // expect: 4867
  }
}

void Invalid_Thread_Id (void)
{
  pthread_cancel (0);                                       // expect: 4995

  pthread_t tid = 0;
  pthread_cancel (tid);                                     // expect: 4996

  extern void * Invalid_thread (void *);

  extern int Invalid_x;
  if (Invalid_x != 0)
  {
    pthread_create (&tid, NULL, &Invalid_thread, NULL);
  }
  pthread_cancel (tid);                                     // expect: 4997

  pthread_create (&tid, NULL, &Invalid_thread, NULL);
  extern int Invalid_y;
  while (Invalid_y --)
  {
    tid = 0;
  }
  pthread_cancel (tid);                                     // expect: 4998
}

void Others (void)
{
  (void) printf ("%e", 0);                                  // expect: 0179
}

extern int16_t rule_0103 (void)
{
  Overflow_In_Signed_Arithmetic_Operation ();
  Dereference_Of_Null_Pointer ();
  Arithmetic_Operation_On_Null_Pointer ();
  Division_By_Zero ();
  Dereference_Of_An_Invalid_Pointer_Value ();
  Wide_Character_Types ();
  Use_of_Uninitialised_Resource ();
  Use_of_Destroyed_Resource ();
  Use_of_Uninitialised_File_Handle ();
  Use_of_freed_memory ();
  Invalid_Thread_Id ();
  Others ();

  return 0;
}

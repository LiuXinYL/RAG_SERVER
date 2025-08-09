/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-9.1.c
 *
 * MISRA Mandatory - Rules
 *
 * Rule-9.1: The value of an object with automatic storage duration shall not be
 *           read before it has been set
 *
 * Enforced by message(s):
 *   2961   Definite: Using value of uninitialized automatic object '%s'.
 *
 *   2962   Apparent: Using value of uninitialized automatic object '%s'.
 *
 *   2963   Suspicious: Using value of uninitialized automatic object '%s'.
 *
 *   2966   Definite: Some members of object '%s' are uninitialized.
 *
 *   2967   Apparent: Some members of object '%s' are uninitialized.
 *
 *   2968   Suspicious: Some members of object '%s' are uninitialized.
 *
 *   2971   Definite: Passing address of uninitialized object '%s' to a
 *          function parameter declared as a pointer to const.
 *
 *   2972   Apparent: Passing address of uninitialized object '%s' to a
 *          function parameter declared as a pointer to const.
 *
 *   2973   Suspicious: Passing address of uninitialized object '%s' to a
 *          function parameter declared as a pointer to const.
 *
 *   2883   This 'goto' statement will always bypass the initialization of
 *          local variables.
 *
 *
 *//* PRQA S 2961,2962,2963,2966,2967,2968,2971,2972,2973,2883 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

struct R0901_Struct
{
  int a;
  int b;
};

extern int16_t rule_0901a( const int16_t *p ){return *p;}             /* expect: 2961 2962 */

extern int16_t rule_0901( void )
{
   int16_t ax;                                                        /* expect: 1594 */
   int16_t bx;                                                        /* expect: 1594 */
   int16_t cx;
   int16_t dx;                                                        /* expect: 1594 */
   int16_t ex;                                                        /* expect: 1594 */
   int16_t rx;                                                        /* expect: 1594 */
   int16_t r0901_s16a;                                                /* expect: 1594 */

   goto JUMP_OVER_INIT;                                               /* expect: 2883 */
   int16_t r0901_ux = 0;                                              /* expect: 1594 */

JUMP_OVER_INIT:   ++rx;                                               /* expect: 2961 1576 */

   rx = ax;                                                           /* expect: 2961 */

   if ( r0901_s16a > 0 )                                              /* expect: 2961 */
   {
       bx = r0901_s16a;                                               /* expect: 1577 1586 */
       ex = r0901_s16a;                                               /* expect: 1577 1586 */
   }

   rx = rx + bx;                                                      /* expect: 2962 */

   {
     extern int n;
     int i;
     int x;

     for (i = 0; i < n; ++i)
     {
       x = i;
     }

     ++ x;                                                            /* expect: 2963 */
   }

   cx = rule_0901a( &dx );                                            /* expect: 2971 */

   dx = 1;

   cx += rule_0901a( &ex );                                           /* expect: 2972 */

   {
     extern int n;
     extern int x;
     extern void R0901_Suspicious (const int * x);

     int y;

      while (n > 0)
      {
        y = x;
        --n;
      }

      R0901_Suspicious (& y);                                         /* expect: 2973 */
   }
   {
      struct R0901_Struct definite;                                   /* expect: 1594 */
      definite.a = 0;
      definite;                                                       /* expect: 2966 */
   }
   {
      extern int a;
      struct R0901_Struct apparent;                                   /* expect: 1594 */
      apparent.a = 0;
      if (a)
      {
         apparent.b = 0;
      }
      apparent;                                                       /* expect: 2967 */
   }
   {
      extern int a;
      struct R0901_Struct suspicious;                                 /* expect: 1594 */
      suspicious.a = 0;
      while (--a)
      {
          suspicious.b = 0;
      }
      suspicious;                                                     /* expect: 2968 */
   }

   return rx + cx + dx;
}

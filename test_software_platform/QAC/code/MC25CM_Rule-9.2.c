/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-9.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-9.2: The initializer for an aggregate or union shall be enclosed in braces
 *
 * Enforced by message(s):
 *   0692   Union initializer is missing the optional {.
 *
 *   0693   Struct initializer is missing the optional {.
 *
 *   0694   Array initializer is missing the optional {.
 *
 *
 *//* PRQA S 0692,0693,0694 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

struct base1
{
   int16_t i;
   int16_t j;
};

extern int16_t rule_0902( void )
{
   struct base1 s1    = {  1, 2 };
   struct base1 s3[2] = {  1, 2,   3, 4  };                // expect: 0693

   int16_t bufb[2][3] = {  1, 2, 3 ,  4, 5, 6  };          // expect: 0694

   struct SS
   {
     int x1;

     struct S
     {
       int x2;
     } s;
   }
   ss =
   {
     1,
     2                                                     // expect: 0693
   };

   struct SU
   {
     int y1;

     union U
     {
       int y2;
     } u;
   }
   su =
   {
     1,
     2                                                     // expect: 0692
   };

   return s3[0].i;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-2.1.c
 *
 * MISRA Required - Rules
 *
 * Rule-2.1: A project shall not contain unreachable code
 *
 * Enforced by message(s):
 *   0594   Negative 'case' label expression is incompatible with unsigned
 *          controlling expression in 'switch' statement.
 *
 *   1460   'Switch' label value, ${val}, not contained in enum type.
 *
 *   2744   This 'while' or 'for' loop controlling expression is a constant
 *          expression and its value is 'false'. The loop will not be
 *          entered.
 *
 *   2880   This code is unreachable.
 *
 *   2882   This 'switch' statement will bypass the initialization of local
 *          variables.
 *
 *   3219   Static function '${name}()' is not used within this translation
 *          unit.
 *
 *   1503   The function '${name}' is defined but is not used within this
 *          project.
 *
 *
 *//* PRQA S 0594,1460,2744,2880,2882,3219,1503 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#define LIMIT 10
enum XX {A, B, C};
static enum XX exa;

static int32_t rule_0201b( void );
extern int32_t rule_0201_unused( void );

extern int16_t rule_0201( void )                                      /* expect: 1503 */
{
   int16_t r0201_s16a;
   int16_t r0201_s16b;
   int16_t r0201_s16c;
   uint16_t r0201_u16a;

   if ( r0201_s16a < 0 )
   {
      if (r0201_s16a > 10)
      {
          r0201_s16a = 10;                                            /* expect: 2880      */
      }
      else
      {
          r0201_s16a = 5;
      }
   }

   if (r0201_s16b < 0)
   {
       r0201_s16b = 0;
   }
   if (r0201_s16b > 1)
   {
       r0201_s16b = 1;
   }

   switch( r0201_s16b )                                               /* expect: 2882      */
   {
      int16_t m = 1;                                                  /* expect: 1594 */
      r0201_s16c = 0;                                                 /* expect: 2880 */

   case 0:
      r0201_s16c = 1;
      break;

   case 1:
      r0201_s16c = 10;
      break;

   default:
      r0201_s16c = 0;
      break;
   }

   while ( r0201_s16a > 10 )
   {
      --r0201_s16a;
      break;

      ++r0201_s16c;                                                   /* expect: 2880      */
   }

   while ( 0 )                                                        /* expect: 2744      */
   {
      ++r0201_s16a;                                                   /* expect: 2880      */
   }

   if ( LIMIT != 10 )
   {
      ++r0201_s16a;                                                   /* expect: 2880      */
   }

   switch (r0201_u16a)
   {
      case -1:                                                        /* expect: 0594      */
         ++r0201_u16a;
         break;
      default:
         break;
   }

   switch (exa)
   {
   case A:
   case B:
   case C:
       r0201_s16c = 2;
       break;
   case 3:                                                            /* expect: 1460 */
       r0201_s16c = 4;
       break;
   }

   return r0201_s16a + r0201_s16c;
}

static int32_t rule_0201b( void )                                     /* expect: 3219      */
{
   return 0;
}

extern int32_t rule_0201_unused( void )                               /* expect: 1503      */
{
    return 1;
}

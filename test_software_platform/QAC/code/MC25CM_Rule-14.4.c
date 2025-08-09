/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-14.4.c
 *
 * MISRA Required - Rules
 *
 * Rule-14.4: The controlling expression of an if-statement and the controlling
 *            expression of an iteration-statement shall have essentially
 *            Boolean type
 *
 * Enforced by message(s):
 *   3344   Controlling expression is not an 'essentially Boolean'
 *          expression.
 *
 *
 *//* PRQA S 3344 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t s16a_1404;
int16_t s16b_1404;
int16_t s16r_1404;

extern int16_t rule_1404( void )
{
   uint16_t ux_1404;

   ux_1404 = 128u;
   if ( ux_1404 )                                                     /* expect:  3344 */
   {
   }

   ux_1404 = 128u;
   if ( ux_1404 != 0 )                                                /* expect: !3344 */
   {
   }

   ux_1404 = 128u;
   while (ux_1404)                                                    /* expect:  3344 */
   {
       --ux_1404;
   }

   ux_1404 = 128u;
   while (ux_1404 != 0)                                               /* expect: !3344 */
   {
       --ux_1404;
   }

   ux_1404 = 128u;
   do
   {
       --ux_1404;
   } while (ux_1404);                                                 /* expect:  3344 */

   ux_1404 = 128u;
   do
   {
       --ux_1404;
   } while (ux_1404 > 0);                                             /* expect: !3344 */

   for (ux_1404 = 10; ux_1404; --ux_1404)                             /* expect:  3344 */
   {
   }

   for (ux_1404 = 10; ux_1404 > 0; --ux_1404)                         /* expect: !3344 */
   {
   }

   return s16r_1404;
}

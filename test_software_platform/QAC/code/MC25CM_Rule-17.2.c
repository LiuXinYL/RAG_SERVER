/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-17.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-17.2: Functions shall not call themselves, either directly or indirectly
 *
 * Enforced by message(s):
 *   3670   Recursive call to function containing this call.
 *
 *   1520   Functions are indirectly recursive.
 *
 *
 *//* PRQA S 3670,1520 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

static void rule_1702a( int16_t x );
static void rule_1702b( int16_t x );
static void rule_1702c( int16_t x );
static void rule_1702d( int16_t x );

extern int16_t rule_1702( void )
{
   rule_1702a( 5 );
   rule_1702d( 5 );
   return 1;
}

static void rule_1702a( int16_t x )
{
   if ( x > 0 )
   {
      --x;
      rule_1702b( x );                                                /* expect: 1520,    1580,1580,1580 */
   }
}

static void rule_1702b( int16_t x )
{
   if ( x > 0 )
   {
      --x;
      rule_1702c( x );                                                /* expect: 1520,    1580,1580,1580 */
   }
}

static void rule_1702c( int16_t x )
{
   if ( x > 0 )
   {
      --x;
      rule_1702a( x );                                                /* expect: 1520,    1580,1580,1580 */
   }
}

static void rule_1702d( int16_t x )
{
   if ( x > 0 )
   {
      --x;
      rule_1702d( x );                                                /* expect: 3670 */
   }
}

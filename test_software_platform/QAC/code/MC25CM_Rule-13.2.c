/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-13.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-13.2: The value of an expression and its persistent side-effects shall be
 *            the same under all permitted evaluation orders and shall be
 *            independent from thread interleaving
 *
 * Enforced by message(s):
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
 *   1114   This atomic variable is referenced directly twice in the same
 *          expression.
 *
 *   1115   This atomic lvalue appears to be referenced twice in the same
 *          expression.
 *
 *   1116   The atomic variable '${name}' appears to be updated non-
 *          atomically.
 *
 *
 *//* PRQA S 0400,0401,0402,0403,0404,0405,1114,1115,1116 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

#include <stdatomic.h>
#include <threads.h>

static int16_t rule_1302a( int16_t *p );
static int16_t rule_1302b( int16_t *p );
static int16_t rule_1302c( const int16_t *p );

extern int16_t rule_1302( void )
{
   int16_t       x = 5;
   int16_t       y = 10;
   volatile int16_t vx = 5;
   volatile int16_t vy = 5;

   x = y + ( x++ );                                                        /*  0400 */
   y = rule_1302a( &x ) + ( x++ );                                         /*  0401 */
   y = ( x + 6 ) / ( x++ );                                                /*  0402 */
   y = rule_1302a( &x ) + x;                                               /*  0403 */
   y = vx + vy;                                                            /*  0404 */
   y = (vx++) + (vy++);                                                    /*  0404 0405*/

   return 1;
}

static int16_t rule_1302a( int16_t *p )
{
   *p = 1;

   return 1;
}

static _Atomic int32_t a;
int32_t rule_1302_t1(void* ignore)  // Thread 1
{
   int32_t v1, v2;
   int32_t acopy;
   a = 10;
   acopy = a;
   v1 = a - a;         // Non-compliant, v1 may be 3.                      /*  1114 */
   v2 = acopy - acopy; // Compliant. acopy is either 10 or 7, but v2 is 0.
   return v1 + v2;
}

int32_t rule_1302_t2(void* ignore)  // Thread 2
{
  a = 7;
  return a;
}

/*********************************************************************************
 *                       END OF MISRA DOCUMENT TESTS                             *
 ********************************************************************************/

void rule_1302_other_2( void * x );

int32_t rule_1302_other_1( int x )
{
  _Atomic int ai = x;                                                      /*  1116 */
  rule_1302_other_2 (&ai);

  struct rule_1302_S
  {
    _Atomic int i;
  } a = { } ;

  return a.i + a.i + ai;                                                   /*  1115 */
}


void main (void)
{
  thrd_t id1, id2;
  thrd_create (&id1, rule_1302_t1, NULL);
  thrd_create (&id2, rule_1302_t2, NULL);
}

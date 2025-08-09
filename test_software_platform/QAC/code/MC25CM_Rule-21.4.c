/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.4.c
 *
 * MISRA Required - Rules
 *
 * Rule-21.4: The standard header file <setjmp.h> shall not be used
 *
 * Enforced by message(s):
 *   5132   Use of standard header file <setjmp.h>.
 *
 *   5137   Use of nonlocal jump identifier: setjmp, longjmp
 *
 *
 *//* PRQA S 5132,5137 -- *//*
 * <<<------------------------------------------------------------ */


#include <setjmp.h>                                                   /* expect: 5132 */

#include "misra.h"
#include "mc25cmex.h"

static jmp_buf myenv;

static void jmpfunc ( int8_t p )
{
  if( p == 10 )
  {
    longjmp ( myenv, 9 );                                             /* expect: 5137 */
  }
}

extern int16_t rule_2104( void )
{
  if ( setjmp ( myenv ) != 0 )                                        /* expect: 5137 */
  {
    jmpfunc( 10 );
  }

  return 1;
}

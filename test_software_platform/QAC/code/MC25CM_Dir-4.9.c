/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-4.9.c
 *
 * MISRA Advisory - Directives
 *
 * Dir-4.9: A function should be used in preference to a function-like macro where
 *          they are interchangeable
 *
 * Assisted by message(s):
 *   3469   This usage of a function-like macro looks like it could be
 *          replaced by an equivalent function call.
 *
 *   3471   Some uses of this function-like macro look like they could be
 *          replaced by equivalent function calls.
 *
 *   3472   All toplevel uses of this function-like macro look like they
 *          could be replaced by equivalent function calls.
 *
 *   3473   This usage of a function-like setter macro looks like it could
 *          be replaced by a similar function call.
 *
 *
 *//* PRQA S 3469,3471,3472,3473 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#define  MAX( A, B )   ( ( ( A ) > ( B ) ) ? ( A ) : ( B ) )         // expect: 3472
#define  MMAX          ( 14 + 32 )
#define  HELLO         10

extern int16_t dir_0409( void )
{
   return   MMAX
          + MAX (3, 5)                                               // expect: 3469
          + HELLO;
}

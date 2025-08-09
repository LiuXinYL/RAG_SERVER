/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-4.14.c
 *
 * MISRA Required - Directives
 *
 * Dir-4.14: The validity of values received from external sources shall be checked
 *
 * Assisted by message(s):
 *   2956   Definite: Using an object with tainted value.
 *
 *
 *//* PRQA S 2956 -- *//*
 * <<<------------------------------------------------------------ */

#include <stdio.h>

#include "misra.h"
#include "mc25cmex.h"

extern int16_t dir_0414( void )
{
   char input[128];
   (void) scanf( "%128c", input );
   (void) printf( "%s", input );                                      /* expect: 2956 */
   return 1;
}

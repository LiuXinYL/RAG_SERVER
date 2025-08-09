/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-4.12.c
 *
 * MISRA Required - Directives
 *
 * Dir-4.12: Dynamic memory allocation shall not be used
 *
 * Assisted by message(s):
 *   5118   Use of memory allocation or deallocation function: calloc,
 *          malloc, realloc or free.
 *
 *
 *//* PRQA S 5118 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#include <stdlib.h>

extern int16_t dir_0412( void )
{
  char *p = ( char * ) malloc ( 10 );              /* expect: 5118 */
  free ( p );                                      /* expect: 5118 */

  int *q = ( int * ) calloc ( 10, sizeof(int) );   /* expect: 5118 */

  q = ( int * ) realloc ( q, 5 * sizeof(int) );    /* expect: 5118 */
  free ( q );                                      /* expect: 5118 */

  return 1;
}

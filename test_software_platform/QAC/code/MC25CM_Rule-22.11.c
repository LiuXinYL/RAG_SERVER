/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-22.11: A thread that was previously either joined or detached shall not be
 *             subsequently joined nor detached
 *
 * Enforced by message(s):
 *   1776   Thread '${name}' is made unjoinable multiple times.
 *
 *
 *//* PRQA S 1776 -- *//*
 * <<<------------------------------------------------------------ */

#include <threads.h>

#include "misra.h"
#include "mc25cmex.h"

int rule_2211_t1(void*);
int rule_2211_t2(void*);
int rule_2211_t3(void*);
int rule_2211_t4(void*);
int rule_2211_t5(void*);
int rule_2211_t6(void*);

void main ( void )
{
  thrd_t id1, id2, id3, id4, id5, id6;

  thrd_create( &id1, rule_2211_t1, NULL );                           /* c11_expect:  1776 */
  thrd_create( &id2, rule_2211_t2, NULL );                           /* c11_expect:  1776 */
  thrd_create( &id3, rule_2211_t3, NULL );                           /* c11_expect:  1776 */ 
  thrd_create( &id4, rule_2211_t4, NULL );                           /* c11_expect:  1776 */ 
  thrd_create( &id5, rule_2211_t5, NULL );                           /* expect:     !1776 */
  thrd_create( &id6, rule_2211_t6, NULL );                           /* expect:     !1776 */

  thrd_join  ( id1, NULL); /* Compliant                        */    /* c11_expect:  1582 */
  thrd_join  ( id1, NULL); /* Non-compliant - already joined   */    /* c11_expect:  1582 */

  thrd_detach( id2);       /* Compliant                        */    /* c11_expect:  1582 */
  thrd_detach( id2);       /* Non-compliant - already detached */    /* c11_expect:  1582 */

  thrd_join  ( id3, NULL); /* Compliant                        */    /* c11_expect:  1582 */
  thrd_detach( id3);       /* Non-compliant - already joined   */    /* c11_expect:  1582 */

  thrd_detach( id4);       /* Compliant                        */    /* c11_expect:  1582 */
  thrd_join  ( id4, NULL); /* Non-compliant - already detached */    /* c11_expect:  1582 */

  thrd_detach( id5);       /* Compliant                        */    /* expect:     !1582 */

  thrd_join  ( id6, NULL); /* Compliant                        */    /* expect:     !1582 */
}

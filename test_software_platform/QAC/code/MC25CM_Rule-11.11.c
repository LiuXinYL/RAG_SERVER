/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-11.11.c
 *
 * MISRA Required - Rules
 *
 * Rule-11.11: Pointers shall not be implicitly compared to NULL
 *
 * Enforced by message(s):
 *   0361   An expression of pointer type is being cast to type _Bool.
 *
 *   3378   An expression of pointer type is being converted to _Bool.
 *
 *
 *//* PRQA S 0361,3378 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

typedef unsigned int uint32_t;
#define NULL (void*)0
typedef _Bool bool;

void foo (void)
{
  uint32_t *ptr;

  (bool)(ptr != NULL);            /* Compliant                                     */    /* !0361 !3378 */
  (bool)(ptr);                    /* Non-compliant - implicit test for zero        */    /*  0361 !3378 */
                                  /*               - this also violates R.11.4     */

  if (ptr != NULL) {     }        /* Compliant     - explicit test for NULL        */    /* !0361 !3378 */

  if (ptr != 0) {     }           /* Compliant     - explicit test for zero        */    /* !0361 !3378 */
                                  /*               - however, this violates R.11.9 */

  if (!ptr) {     }               /* Non-compliant - implicit test for zero        */    /* !0361  3378 */
  if (ptr && *ptr == 1) {     }   /* Non-compliant - implicit test for zero        */    /* !0361  3378 */

  /* The following non-compliant example also violates Rule 14.4                   */

  if (ptr) {     }                /* Non-compliant - implicit test for zero        */    /* !0361  3378 */
}

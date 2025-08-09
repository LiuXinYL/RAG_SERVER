/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-23.5-C11.c
 *
 * MISRA Advisory - C11 Specific Rules
 *
 * Rule-23.5-C11: A generic selection should not depend on implicit pointer type
 *                conversion
 *
 * Enforced by message(s):
 *   1174   This controlling expression for this generic selection will not
 *          convert to a pointer to void.
 *
 *
 *//* PRQA S 1174 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

#include <stdlib.h>


extern int16_t rule_2305 (void)
{
  void (* handle_pi) (int *);
  void (* handle_cpi) (int const *);
  void (* handle_vpi) (int volatile *);
  void (* handle_cvpi) (int const volatile *);
  void (* handle_any) (void *);

  /* potentially non-compliant */
  #define handle_pointer1(X) (_Generic ((X)  \
    , int const *: handle_cpi                \
    , default: handle_any) (X))

  /* compliant usage */
  const int ci;
  handle_pointer1 (&ci);                       /* c11_expect: !1174 */

  /* non-compliant usage */
  int mi;
  handle_pointer1 (&mi);                       /* c11_expect:  1174 */

  /* potentially non-compliant */
  #define handle_pointer2(X) (_Generic ((X)  \
    , void *: handle_any                     \
    , int const *: handle_cpi                \
    , int volatile *: handle_vpi             \
    , default: handle_cvpi) (X))

  /* non-compliant usage */
  handle_pointer2 (&mi);                       /* c11_expect:  1174 */

  /* compliant usage */
  handle_pointer2 ((void *)&mi);               /* c11_expect: !1174 */

  return 0;
}

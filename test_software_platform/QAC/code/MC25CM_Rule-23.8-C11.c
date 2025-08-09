/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-23.8-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-23.8-C11: A default association shall appear as either the first or the
 *                last association of a generic selection
 *
 * Enforced by message(s):
 *   1178   The default association is not in first or last position in
 *          this generic association list.
 *
 *
 *//* PRQA S 1178 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#include <stdlib.h>
#include <math.h>

#define my_sqrt(X) (_Generic((X)  \
  , float: sqrtf                  \
  , default: sqrt                 \
  , long double: sqrtl) (X))

#define my_cbrt(X) (_Generic((X)  \
  , default: cbrt                 \
  , float: cbrtf                  \
  , long double: cbrtl) (X))

/* No default in the list */
#define assert_untyped_nonatomic(X) (_Generic((X)  \
  , void *: r2308_handle_ptr                       \
  , void const *: r2308_handle_ptr                 \
  , void volatile *: r2308_handle_ptr              \
  , void const volatile *: r2308_handle_ptr) (X))

extern void r2308_handle_ptr (void const volatile *);

extern int16_t rule_2308 (void)
{
  int x;

  my_sqrt (x);  /* c11_expect:  1178 */
  my_cbrt (x);  /* c11_expect: !1178 */

  void * px = &x;
  assert_untyped_nonatomic (px);  /* c11_expect: !1178 */

  return 0;
}

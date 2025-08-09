/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-23.6-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-23.6-C11: The controlling expression of a generic selection shall have an
 *                essential type that matches its standard type
 *
 * Enforced by message(s):
 *   1175   This controlling expression for this generic selection matches
 *          a different association from its essential type.
 *
 *
 *//* PRQA S 1175 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

#include <stdlib.h>


extern int16_t rule_2306 (void)
{
  void (* handle_sshort) (double);
  void (* handle_ushort) (double);
  void (* handle_sint) (double);
  void (* handle_uint) (double);
  void (* handle_slong) (double);
  void (* handle_ulong) (double);
  void (* handle_anyint) (double);

  #define filter_ess_ints(X) (_Generic((X)  \
    , signed short: handle_sshort       \
    , unsigned short: handle_ushort     \
    , signed int: handle_sint           \
    , unsigned int: handle_uint         \
    , signed long: handle_slong         \
    , unsigned long: handle_ulong       \
    , default: handle_anyint) (X))

  short s = 0;
  int i = 0;
  long l = 0;

  /* Non-compliant usages */
  filter_ess_ints (s + s);               /* c11_expect: 1175 */
  filter_ess_ints ('c');                 /* c11_expect: 1175 */

  /* Compliant usages */
  filter_ess_ints (s);                   /* c11_expect: !1175 */
  filter_ess_ints (i);                   /* c11_expect: !1175 */
  filter_ess_ints (l);                   /* c11_expect: !1175 */

  return 0;
}

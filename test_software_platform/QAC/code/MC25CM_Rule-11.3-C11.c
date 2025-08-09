/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-11.3-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-11.3-C11: A conversion shall not be performed between a pointer to object
 *                type and a pointer to a different object type
 *
 * Enforced by message(s):
 *   2041   This is converting a pointer to an atomic type to a pointer to
 *          character type.
 *
 *
 *//* PRQA S 2041 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

int16_t rule_1103_C11 (void)
{
  _Atomic struct A1103 astr1103;
          struct A1103 lstr1103;

  char const * sptr1103;

  sptr1103 = (char const *)&astr1103;           /* c11_expect:  2041 */
  sptr1103 = (char const *)&lstr1103;           /* c11_expect: !2041 */

  _Atomic char const * aptr1103;

  aptr1103 = (_Atomic char const *)&astr1103;   /* c11_expect:  2041 */
  aptr1103 = (_Atomic char const *)&lstr1103;   /* c11_expect: !2041 */

  return 0;
}

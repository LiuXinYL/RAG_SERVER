/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.14.c
 *
 * MISRA Required - Rules
 *
 * Rule-21.14: The Standard Library function memcmp shall not be used to compare
 *             null terminated strings
 *
 * Enforced by message(s):
 *   2785   Constant: Null terminated string is being passed as argument to
 *          Standard Library function memcmp.
 *
 *   2786   Definite: Null terminated string is being passed as argument to
 *          Standard Library function memcmp.
 *
 *
 *//* PRQA S 2785,2786 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#include <string.h>

char buffer1_2114[12] = "abc";
char buffer2_2114[12] = "def";

extern int16_t rule_2114 (void)
{
  char buffer3_2114[12] = "ghi";

  memcmp(buffer1_2114,"abc", sizeof(buffer1_2114));                   // expect: 2785
  memcmp(buffer3_2114,"abc", sizeof(buffer3_2114));                   // expect: 2785 2786
  memcmp(buffer1_2114, buffer3_2114, sizeof(buffer3_2114));           // expect: 2786

  strcpy(buffer1_2114, "abc");
  strcpy(buffer2_2114, "abc");

  if (memcmp(buffer1_2114, buffer2_2114, sizeof(buffer1_2114)) != 0)  // expect: 2786
  {
  }

  return 1;
}

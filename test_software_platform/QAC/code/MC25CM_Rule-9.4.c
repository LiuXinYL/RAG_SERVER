/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-9.4.c
 *
 * MISRA Required - C99 and C11 Specific Rules
 *
 * Rule-9.4: An element of an object shall not be initialized more than once
 *
 * Enforced by message(s):
 *   1397   Array element '${member}' has already been initialized.
 *
 *   1398   Structure member '${member}' has already been initialized.
 *
 *   1399   A union member has already been initialized.
 *
 *
 *//* PRQA S 1397,1398,1399 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_0904( void )
{
  uint16_t *r904_p;
  uint16_t r904_a[2] = {[0] = *r904_p++, [0] = 1};                    /* expect: 1397 1586 */

  return 0;
}

struct mystruct
{
  int32_t a;
  int32_t b;
  int32_t c;
  int32_t d;
};

struct mystruct r904_s3 = {.a = 100, .b = -1, .a = 42, .d = 999};     /* expect: 1398 1586 */

union r904_U
{
  int32_t a;
  int32_t b;
  int32_t c;
  int32_t d;
};

/* Explicit overwriting */
union r904_U r904_x = { .c = 3, .c = 4 };                             /* expect: 1399 1586 */

/* Implicit overwriting */
union r904_U r904_y = { .c = 4, .d = 5 };                             /* expect: 1399 1586 */

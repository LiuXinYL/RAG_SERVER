/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-5.7.c
 *
 * MISRA Required - Rules
 *
 * Rule-5.7: A tag name shall be a unique identifier
 *
 * Enforced by message(s):
 *   2547   This declaration of tag '${name}' hides a more global
 *          declaration.
 *
 *   1750   '${name}' has multiple definitions.
 *
 *
 *//* PRQA S 2547,1750 -- *//*
 * <<<------------------------------------------------------------ */


#include "stdio.h"
#include "misra.h"
#include "mc25cmex.h"

union stag                             /* expect: 1750 1593 1593 */
{
  uint32_t c;
  uint32_t d;
} r0507_b;

struct stag                            /* expect: 1750 1593 1593 */
{
  uint16_t a;
  uint16_t b;
};


extern int16_t rule_0507( void )
{
  struct stag r0507_a;
  return 0;
}

struct XT {int a; int b;};             /* expect: 1750 */

void foo(void)
{
    union XT {float f; long t;};       /* expect: 1750 2547 */
    union XT r0507_x;
    struct XT r0507_y;
}

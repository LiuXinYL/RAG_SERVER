/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-19.2.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-19.2: The union keyword should not be used
 *
 * Enforced by message(s):
 *   0750   A union type specifier has been defined.
 *
 *   0759   An object of union type has been defined.
 *
 *
 *//* PRQA S 0750,0759 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

typedef union
{                                                                     /* expect: 0750 */
  uint8_t x[2];
  uint16_t s;
} tu_1902;

union u_1902
{                                                                     /* expect: 0750 */
   uint8_t * c;
   int32_t  i;
};

extern int16_t rule_1902 (void)
{
   union u_1902 u1_1902;                                              /* expect: 0759 */
   tu_1902 u2_1902;                                                   /* expect: 0759 */

   return 1;
}

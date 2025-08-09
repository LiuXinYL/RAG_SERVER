/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-18.7.c
 *
 * MISRA Required - C99 and C11 Specific Rules
 *
 * Rule-18.7: Flexible array members shall not be declared
 *
 * Enforced by message(s):
 *   1060   A flexible array member has been declared.
 *
 *
 *//* PRQA S 1060 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"
#include <stdlib.h>

struct s_1807
{
  uint16_t len;
  uint32_t data [];                                                   /* expect: 1060 */
};
struct s_1807 str_1807;

extern int16_t rule_1807 (void)
{
  struct s_1807 * sp_1807;

  sp_1807 = malloc (sizeof (struct s_1807) + (str_1807.len * sizeof (uint32_t)));
  *sp_1807 = str_1807;  /* only copies sp_1807.len */

  return 1;
}

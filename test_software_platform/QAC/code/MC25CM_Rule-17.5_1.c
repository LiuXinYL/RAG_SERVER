/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-17.5_1.c
 *
 * MISRA Required - Rules
 *
 * Rule-17.5: The function argument corresponding to a parameter declared to have
 *            an array type shall have an appropriate number of elements
 *
 * Enforced by message(s):
 *   2781   Definite: Function argument has fewer elements than the array
 *          dimension in the parameter declaration for non-inlined
 *          call.
 *
 *   2782   Apparent: Function argument has fewer elements than the array
 *          dimension in the parameter declaration for non-inlined
 *          call.
 *
 *   2783   Suspicious: Function argument has fewer elements than the array
 *          dimension in the parameter declaration for non-inlined
 *          call.
 *
 *   2784   Possible: Function argument has fewer elements than the array
 *          dimension in the parameter declaration for non-inlined
 *          call.
 *
 *
 *//* PRQA S 2781,2782,2783,2784 -- *//*
 * <<<------------------------------------------------------------ */

#include <stdlib.h>
#include "misra.h"
#include "mc25cmex.h"

extern void rule_1705a (int32_t arr_1705a[4]);
extern void rule_1705b (int32_t arr_1705c[]);

int32_t * ptr_1705;                                                   /* expect: 1594 */
int32_t s32a_1705;                                                    /* expect: 1594,1594 */

extern int16_t rule_1705 (void)
{
  int32_t arr3_1705 [3] = {1, 2, 3};                                  /* expect: 1594 */
  int32_t arr4_1705 [4] = {0, 1, 2, 3};
  int32_t * dyn4_1705 = malloc (4 * sizeof (int32_t));                /* expect: 1582,1582 */

  rule_1705a (arr4_1705);                                             /* Compliant    */
  rule_1705b (arr4_1705);                                             /* Compliant    */

  rule_1705a (arr3_1705);                                             /* expect: 2781 */
  rule_1705b (arr3_1705);                                             /* Compliant    */

  rule_1705a (dyn4_1705);                                             /* Compliant    */
  rule_1705b (dyn4_1705);                                             /* Compliant    */

  rule_1705a (dyn4_1705 + 1);                                         /* expect: 2782,    1574 */
  rule_1705b (dyn4_1705 + 1);                                         /* Compliant    */

  if (dyn4_1705)                                                      /* expect: 1582 ,1582*/
  {
    if (1 == s32a_1705)
    {
      rule_1705a (arr4_1705 + s32a_1705);                             /* expect: 2781,    1575 */
    }

    rule_1705a (dyn4_1705 + s32a_1705);                               /* expect: 2784 */
  }

  int32_t x_1705;
  for (x_1705 = 3; x_1705 > s32a_1705; --x_1705)                      /* expect: 1575 */
  {
  }

  rule_1705a (arr4_1705 + x_1705);                                    /* expect: 2783,    1574 */

  rule_1705a (ptr_1705);                                              /* expect: 2784 */

  rule_1705b (arr4_1705);                                             /* Compliant    */

  rule_1705b (ptr_1705);                                              /* Compliant    */

  return 1;
}

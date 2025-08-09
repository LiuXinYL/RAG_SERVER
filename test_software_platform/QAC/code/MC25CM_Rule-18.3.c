/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-18.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-18.3: The relational operators >, >=, < and <= shall not be applied to
 *            expressions of pointer type except where they point into the same
 *            object
 *
 * Enforced by message(s):
 *   2669   Comparison of a pointer to an array and a pointer to a non-
 *          array.
 *
 *   2771   Definite: Comparing pointers that address different objects.
 *
 *   2772   Apparent: Comparing pointers that address different objects.
 *
 *   2773   Suspicious: Comparing pointers that address different objects.
 *
 *
 *//* PRQA S 2669,2771,2772,2773 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

uint16_t * p16a_1803;

extern int16_t rule_1803 (void)
{
  int32_t arr1_1803[10];                         /* expect: 1594 */
  int32_t arr2_1803[10];                         /* expect: 1594 */
  int32_t * ptr1_1803 = arr1_1803;               /* expect: 1582 1582 */
  int32_t * ptr2_1803 = arr2_1803;               /* expect: 1582 1582 */

  bool_t cmp_1803;

  cmp_1803 = ptr1_1803 < arr1_1803;
  cmp_1803 = ptr2_1803 < arr2_1803;

  cmp_1803 = p16a_1803 < ptr1_1803;              /* expect: 2669 */

  cmp_1803 = arr1_1803 < arr2_1803;              /* expect: 2771 */
  cmp_1803 = ptr1_1803 < ptr2_1803;              /* expect: 2771 */

  if (p16a_1803)
  {
    ptr1_1803 = ptr2_1803;
  }
  cmp_1803 = ptr1_1803 < ptr2_1803;              /* expect: 2772 1574 */

  {
    extern int n;
    int i;
    int v1 [8];
    int v2 [8];

    int * p = v1;

    for (i = 0; i < n; ++i)
    {
      p = v2;
    }

    & v2 [2] > p;                                /* expect: 2773 1574 */
  }
}

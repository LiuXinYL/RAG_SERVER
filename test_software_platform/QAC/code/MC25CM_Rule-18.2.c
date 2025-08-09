/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-18.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-18.2: Subtraction between pointers shall only be applied to pointers that
 *            address elements of the same array
 *
 * Enforced by message(s):
 *   2668   Subtraction of a pointer to an array and a pointer to a non-
 *          array.
 *
 *   2761   Definite: Subtracting pointers that address different objects.
 *
 *   2762   Apparent: Subtracting pointers that address different objects.
 *
 *   2763   Suspicious: Subtracting pointers that address different
 *          objects.
 *
 *   2766   Definite: Subtracting pointers that address different members
 *          of the same object.
 *
 *   2767   Apparent: Subtracting pointers that address different members
 *          of the same object.
 *
 *   2768   Suspicious: Subtracting pointers that address different members
 *          of the same object.
 *
 *
 *//* PRQA S 2668,2761,2762,2763,2766,2767,2768 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

uint16_t * p16a_1802;

extern int16_t rule_1802 (void)
{
  int32_t arr1_1802[10];                         /* expect: 1594 */
  int32_t arr2_1802[10];                         /* expect: 1594 */
  int32_t * ptr1_1802 = arr1_1802;               /* expect: 1582 1582 */
  int32_t * ptr2_1802 = arr2_1802;               /* expect: 1582 1582 */

  uint32_t diff_1802;

  diff_1802 = ptr1_1802 - arr1_1802;
  diff_1802 = ptr2_1802 - arr2_1802;

  diff_1802 = p16a_1802 - ptr1_1802;             /* expect: 2668 */

  diff_1802 = arr1_1802 - arr2_1802;             /* expect: 2761 */
  diff_1802 = ptr1_1802 - ptr2_1802;             /* expect: 2761 */

  if (p16a_1802)
  {
    ptr1_1802 = ptr2_1802;
  }
  diff_1802 = ptr1_1802 - ptr2_1802;             /* expect: 2762 1574 */

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

    & v2 [2] - p;                                /* expect: 2763 1574 */
  }
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-17.5_2.c
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



/* Separate implementation to prevent dataflow engine inlining definitions */

#include "misra.h"
#include "mc25cmex.h"

extern void rule_1705a (int32_t arr_1705a[4])
{
  arr_1705a[0] = 4;
  arr_1705a[1] = 3;
  arr_1705a[2] = 2;
  arr_1705a[3] = 1;
}

extern void rule_1705b (int32_t arr_1705c[])
{
  arr_1705c[0] = 0;
}

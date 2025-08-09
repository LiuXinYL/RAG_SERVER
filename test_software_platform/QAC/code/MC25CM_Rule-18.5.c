/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-18.5.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-18.5: Declarations should contain no more than two levels of pointer
 *            nesting
 *
 * Enforced by message(s):
 *   3260   Typedef defined with more than 2 levels of indirection.
 *
 *   3261   Member of struct/union defined with more than 2 levels of
 *          indirection.
 *
 *   3262   Object defined or declared with more than 2 levels of
 *          indirection.
 *
 *   3263   Function defined or declared with a return type which has more
 *          than 2 levels of indirection.
 *
 *
 *//* PRQA S 3260,3261,3262,3263 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

typedef PC * CHARSTAR;                                                /* expect: !3260 */
typedef uint16_t *** PPPU;                                            /* expect:  3260 */

struct s_1805
{
  PPPU m1_1805;                                                       /* expect:  3261 */
  CHARSTAR m2_1805;                                                   /* expect: !3261 */
};

uint16_t *** pppu1_1805;                                              /* expect:  3262 */
PPPU pppu2_1805;                                                      /* expect:  3262 */
struct s_1805 *** ppps_1805;                                          /* expect:  3262 */

static void rule_1805a (PC ** const ptr_1805a[]);                     /* expect:  3262 */

static PPPU rule_1805b (void);                                        /* expect:  3263 */

extern int16_t rule_1805 (void)
{
  int16_t     ret_1805;

  PC          arr_1805[4];                                            /* expect: !3262 */
  PC         *ptr1_1805;                                              /* expect: !3262 */
  PC        **ptr2_1805;                                              /* expect: !3262 */
  PC       ***ptr3_1805;                                              /* expect:  3262 */
  CHARSTAR  **ptr4_1805;                                              /* expect:  3262 */
  CHARSTAR   *const * const ptr5_1805;                                /* expect:  3262 */

  ptr1_1805 = &arr_1805[0];
  ptr2_1805 = &ptr1_1805;
  ptr3_1805 = &ptr2_1805;

  ret_1805 = rule_1805a (ptr3_1805);
  ret_1805 = ***rule_1805b ();

  return ret_1805;
}

static void rule_1805a (PC ** const ptr_1805a[])                      /* expect:  3262 */
{
  ***ptr_1805a = 0;
}

static PPPU rule_1805b (void)                                         /* expect:  3263 */
{
  static struct s_1805 s_1805b;;
  struct s_1805 * ps_1805b = &s_1805b;
  struct s_1805 ** pps_1805b = &ps_1805b;
  struct s_1805 *** ppps_1805b = &pps_1805b;                          /* expect:  3262 */
  ppps_1805 = ppps_1805b;
  return (**ppps_1805b)->m1_1805;
}

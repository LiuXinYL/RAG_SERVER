/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-18.6.c
 *
 * MISRA Required - Rules
 *
 * Rule-18.6: The address of an object with automatic or thread-local storage shall
 *            not be copied to another object that persists after the first
 *            object has ceased to exist
 *
 * Enforced by message(s):
 *   2916   Definite: Storing the address of an object in a pointer that
 *          has greater lifetime.
 *
 *   2917   Apparent: Storing the address of an object in a pointer that
 *          has greater lifetime.
 *
 *   2918   Suspicious: Storing the address of an object in a pointer that
 *          has greater lifetime.
 *
 *   3217   Address of automatic object exported to a pointer with linkage
 *          or wider scope.
 *
 *   3225   Address of automatic object exported using a function
 *          parameter.
 *
 *   3230   Address of automatic object assigned to local pointer with
 *          static storage duration.
 *
 *   4140   Address of automatic object exported in function return value.
 *
 *
 *//* PRQA S 2916,2917,2918,3217,3225,3230,4140 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

int16_t * p16a_1806;

static void rule_1806a (void)
{
  int16_t auto1_1806a;
  p16a_1806 = &auto1_1806a;                      /* expect: 3217 2916 */

  int16_t * ptr_1806a;
  {
    int16_t auto2_1806a;
    ptr_1806a = &auto2_1806a;                    /* expect: 3217 2916 */
  }
  *ptr_1806a = 0;

  static int16_t * static1_1806a;
  {
    static int16_t * static2_1806a;
    int16_t auto3_1806a;
    static1_1806a = &auto3_1806a;                /* expect: 3217 2916 */
    static2_1806a = &auto3_1806a;                /* expect: 3230 2916 */
  }
}

static void rule_1806b (int16_t ** px_1806b)
{
  int16_t auto_1806b;
  *px_1806b = &auto_1806b;                       /* expect: 3225 2916 */
}

static int16_t * rule_1806d (void)
{
  int16_t auto_1806b;
  return &auto_1806b;                            /* expect: 4140 2916 */
}

static int16_t * s;

static void R1806_Apparent (int16_t a)
{
  int16_t i = 0;
  int16_t * p = s;

  if (a)
  {
    p = &i;
  }

  s = p;                                         /* expect: 2917 */
}

static void R1806_Suspicious (int16_t a)
{
  int16_t i = 0;
  int16_t * p = s;

  while (a)
  {
    p = &i;
    --a;
  }

  s = p;                                         /* expect: 2918 */
}

extern int16_t rule_1806 (void)
{
  int16_t * ptr_1806;

  rule_1806a ();
  rule_1806b (&ptr_1806);
  ptr_1806 = rule_1806d ();

  return 1;
}

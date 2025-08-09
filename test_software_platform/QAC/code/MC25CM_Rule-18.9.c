/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-18.9.c
 *
 * MISRA Required - Rules
 *
 * Rule-18.9: An object with temporary lifetime shall not undergo array-to-pointer
 *            conversion
 *
 * Enforced by message(s):
 *   0450   Passing an array with temporary lifetime as a function
 *          parameter.
 *
 *   0455   Passing an array with temporary lifetime as a constant function
 *          parameter.
 *
 *   0459   Modifying the contents of an array with temporary lifetime.
 *
 *   0464   Storing a pointer to an array with temporary lifetime.
 *
 *   0465   Returning a pointer to an array with temporary lifetime.
 *
 *
 *//* PRQA S 0450,0455,0459,0464,0465 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

struct S_1809 {
  int32_t array[10];
};

struct S_1809 getS_1809 (void);

void access_1809 (int32_t const * p);
void mutate_1809 (int32_t       * p);


extern int16_t rule_1809 (void)
{
  struct S_1809 s1;

  int32_t * p;
  int32_t j;

  p = s1.array;
  s1.array[0] = 1;
  access (s1.array);

  p = getS_1809().array;                    /* expect: 0464 */
  access_1809 (getS_1809().array);          /* expect: 0455 */
  mutate_1809 (getS_1809().array);          /* expect: 0450 */
  p = (0, s1).array;                        /* expect: 0464 */
  access_1809 ((s1 = s1).array);            /* expect: 0455 */
  mutate_1809 ((s1 = s1).array);            /* expect: 0450 */

  j = getS_1809().array[3];
  j = (s1 = s1).array[3];

  getS_1809().array[3] = j;                 /* expect: 0459 */
  (1 ? s1 : s1).array[3] = j;               /* expect: 0459 */

  return 0;
}

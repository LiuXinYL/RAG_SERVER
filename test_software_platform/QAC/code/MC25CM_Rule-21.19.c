/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.19.c
 *
 * MISRA Mandatory - Rules
 *
 * Rule-21.19: The pointers returned by the Standard Library functions lovaleconv,
 *             getenv, setlocale or strerror shall only be used as if they have
 *             pointer to const-qualified type
 *
 * Enforced by message(s):
 *   1492   The result of library function '${name}' is used to modify the
 *          referenced object.
 *
 *   1493   The result of library function '${name}' is used as a pointer
 *          to a modifiable object.
 *
 *   1494   The result of library function '${name}' might be modified.
 *
 *   1498   The string referenced by <locale.h> type 'struct lconv' member
 *          '${name}' is being modified.
 *
 *
 *//* PRQA S 1492,1493,1494,1498 -- *//*
 * <<<------------------------------------------------------------ */


#include <errno.h>
#include <locale.h>
#include <stdlib.h>
#include "misra.h"
#include "mc25cmex.h"

bool_t ba_2119;

extern int16_t rule_2119 (void)
{
  setlocale (LC_ALL, NULL)[1] = 'A';                                  /* expect: 1492 */

  char * loca_2119 = setlocale (LC_ALL, NULL);                        /* expect: 1493 */
  struct lconv * conva_2119 = localeconv ();                          /* expect: 1493 */

  char * enva_2119 = getenv ("ENV_2119");                             /* expect: 1493 */
  if (ba_2119)
  {
    enva_2119[0] = '\0';                                              /* expect: 1494 */
  }

  *(conva_2119->grouping + 2) = 'x';                                  /* expect: 1498 */
  localeconv ()->decimal_point[4] = 'y';                              /* expect: 1498 */

  const struct lconv * convb_2119 = localeconv ();                    /* Compliant    */
  const char * envb_2119 = getenv ("ENV_2119");                       /* Compliant    */
  const char * locb_2119 = setlocale (LC_ALL, NULL);                  /* Compliant    */
  const char * errb_2119 = strerror (EDOM);                           /* Compliant    *//* expect: 1594,1753 */

  return 1;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.20.c
 *
 * MISRA Mandatory - Rules
 *
 * Rule-21.20: The pointer returned by the Standard Library functions asctime,
 *             ctime, gmtime, localtime, localeconv, getenv, setlocale, or
 *             strerror shall not be used following a subsequent call to the
 *             same function
 *
 * Enforced by message(s):
 *   2681   Definite: Using an invalidated value '%s' returned from a
 *          Standard Library function.
 *
 *   2682   Apparent: Using an invalidated value '%s' returned from a
 *          Standard Library function.
 *
 *   2683   Suspicious: Using an invalidated value '%s' returned from a
 *          Standard Library function.
 *
 *
 *//* PRQA S 2681,2682,2683 -- *//*
 * <<<------------------------------------------------------------ */

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "misra.h"
#include "mc25cmex.h"

bool_t ba_2120;

extern int16_t rule_2120 (void)
{
  const char * str1_2120;                                  /* expect: 1594 */
  const char * str2_2120;
  const char * str3_2120 = NULL;                           /* expect: 1594 */
  char copy_2120[128];

  str1_2120 = setlocale (LC_ALL, NULL);                    /* expect: 1586 1586 */

  if (ba_2120)
  {
    str3_2120 = str1_2120;                                 /* expect: 1586 */
  }

  strcpy(copy_2120, str1_2120);
  str2_2120 = setlocale(LC_MONETARY, "French");            /* expect: 1586 1586 */

  printf("%s\n", str1_2120);                               /* expect: 2681 */
  printf("%s\n", copy_2120);                               /* Compliant    */
  printf("%s\n", str2_2120);                               /* Compliant    */
  printf("%s\n", str3_2120);                               /* expect: 2682 */

  {
    extern int b;
    char * str = getenv ("PATH");                          /* expect: 1586 1594 */
    while (b > 0)
    {
      getenv ("HOME");                                     /* expect: 1586 */
      --b;
    }

    * str;                                                 /* expect: 2683 */
  }

  return 1;
}

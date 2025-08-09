/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.10.c
 *
 * MISRA Required - Rules
 *
 * Rule-21.10: The Standard Library time and date functions shall not be used
 *
 * Enforced by message(s):
 *   5127   Use of standard header file <time.h>.
 *
 *   5139   Use of time handling identifier: clock, difftime, mktime, time,
 *          timespec_get, asctime, ctime, gmtime, localtime, strftime,
 *          wcsftime
 *
 *
 *//* PRQA S 5127,5139 -- *//*
 * <<<------------------------------------------------------------ */


#include <time.h>                                                     /* expect: 5127 */

#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_2110 (void)
{
  float64_t  time_dif;
  time_t     time_1;
  time_t     time_2;

  time_1   = clock ( );                                            /* expect: 5139 */
  time_2   = clock ( );                                            /* expect: 5139 */
  time_dif = difftime ( time_1, time_2 );                          /* expect: 5139 */

  return 1;
}

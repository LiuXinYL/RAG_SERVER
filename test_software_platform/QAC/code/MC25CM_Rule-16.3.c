/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-16.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-16.3: Every switch-clause shall be appropriately terminated
 *
 * Enforced by message(s):
 *   2003   The preceding 'switch' clause is not empty and does not end
 *          with a 'jump' statement. Execution will fall through.
 *
 *   2020   Final 'switch' clause does not end with an explicit 'jump'
 *          statement.
 *
 *   2023   The preceding 'switch' clause is not empty and ends with a jump
 *          statement other than 'break'.
 *
 *   2024   Final 'switch' clause ends with a 'jump' statement other than
 *          'break'.
 *
 *
 *//* PRQA S 2003,2020,2023,2024 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"
#include "stdlib.h"

int16_t s16a_1603;
int16_t s16b_1603;

extern int16_t rule_1603( void )
{
   int16_t ret_1603;

   do
   {
     switch ( s16a_1603 )
     {
     case 0:  /* Compliant */
        ret_1603 = 2;
        break;

     case 1:  /* Compliant - break without content */
        break;

     case 2:  /* Compliant - grouped labels for one clause */
     case 3:
        ret_1603 = 3;
        break;

     case 4:  /* Non compliant: no break */
        ret_1603 = 5;

     case 5:  /* Non compliant: conditional break */                            /*  2003       */
        if ( s16b_1603 )
        {
           ret_1603 = 7;
           break;
        }

     case 6:                                                                    /*  2003       */
        abort();        /* Compliant - abort is defined as _NoReturn       */
                        /*           - but violates R.21.8                 */
     case 7:                                                                    /*  2023       */
        continue;       /* Compliant                                       */

     default:  /* Non compliant */                                              /*  2023  2020 */
        ret_1603 = 11;
     }
   } while (0);

   return ret_1603;
}

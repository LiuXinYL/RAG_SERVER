/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-16.7.c
 *
 * MISRA Required - Rules
 *
 * Rule-16.7: A switch-expression shall not have essentially Boolean type
 *
 * Enforced by message(s):
 *   0735   Switch expression is of essentially Boolean type.
 *
 *
 *//* PRQA S 0735 -- *//*
 * <<<------------------------------------------------------------ */


#include <stdbool.h>
#include "misra.h"
#include "mc25cmex.h"

uint16_t u16a_1607;

extern int16_t rule_1607( void )
{
   int16_t ret_1607 = 0;

   switch ( u16a_1607 == 5u )                                         /* expect: 0735 */
   {
   case true:
      ret_1607 = 1;
      break;
   default:
      ret_1607 = 14;
      break;
   }

   return ret_1607;
}

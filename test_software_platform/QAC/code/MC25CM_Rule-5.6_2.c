/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-5.6_2.c
 *
 * MISRA Required - Rules
 *
 * Rule-5.6: A typedef name shall be a unique identifier
 *
 * Enforced by message(s):
 *   1506   The identifier '${name}' is declared as a typedef and is used
 *          elsewhere for a different kind of declaration.
 *
 *   1507   '${name}' is used as a typedef for different types.
 *
 *   1508   The typedef '${name}' is declared in more than one location.
 *
 *
 *//* PRQA S 1506,1507,1508 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

typedef int8_t    t0506b;                                             /* expect: 1507 1581      */

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-5.1_2.c
 *
 * MISRA Required - Rules
 *
 * Rule-5.1: External identifiers shall be distinct
 *
 * Enforced by message(s):
 *   0777   External identifier does not differ from other identifier(s)
 *          (e.g. '${id}') within the specified number of significant
 *          characters.
 *
 *   1712   External identifiers have the same first '${n}' characters
 *          '${name}'.
 *
 *
 *//* PRQA S 0777,1712 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

     /* 123456789012345678901234567890123456789012345678901234567890123********* Characters */
extern int32_t cm_engine_exhaust_gas_temperature_cm_engine_exhaust_gas_temperature_scaled; /*  1712 */      /* Non-compliant */

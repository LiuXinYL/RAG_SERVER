/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-5.4.c
 *
 * MISRA Required - Rules
 *
 * Rule-5.4: Macro identifiers shall be distinct
 *
 * Enforced by message(s):
 *   0788   This identifier, '${id}', is used as both a macro name and a
 *          function-like macro parameter name.
 *
 *   0791   Macro identifier does not differ from other macro identifier(s)
 *          (e.g. '${id}') within the specified number of significant
 *          characters.
 *
 *   0797   This identifier, '${id}', is used as both a macro name and a
 *          function-like macro parameter name.
 *
 *   0798   This identifier, '${id}', is used as both a macro name and a
 *          function-like macro parameter name.
 *
 *
 *//* PRQA S 0788,0791,0797,0798 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

/* The behavior of this test is impacted by either or both of the following options:
 *   -namelength=?
 *   -xnamelength=?
 *
 * By default, MC25CM is configured as per C99:
 *   -namelength=63
 *   -xnamelength=31
 *
 */

     /* 123456789012345678901234567890123456789012345678901234567890123********* Characters */
#define engine_exhaust_gas_temperature_1234567890123456789012345678901_raw egt_r
#define engine_exhaust_gas_temperature_1234567890123456789012345678901_scaled egt_s                /* expect: 0791  */

     /* 123456789012345678901234567890123456789012345678901234567890123********* Characters */
#define new_model_car_engine_electronic_exhaust_control_exhaust_gas_temp new_egt_r
#define new_model_car_engine_electronic_exhaust_control_exhaust_gas_temp_gradient new_egt_grd_r    /* expect: 0791  */

#define engine_exhaust_gas_temp_raw egt_r
#define engine_exhaust_gas_temp_scaled egt_s

#define engine_macro_power 1000
#define engine_macro_func(engine_macro_power)   engine_macro_power * engine_macro_power          /* expect: 0788 */

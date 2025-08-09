/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-6.1.c
 *
 * MISRA Required - Rules
 *
 * Rule-6.1: Bit-fields shall only be declared with an appropriate type
 *
 * Enforced by message(s):
 *   0634   Bit-field ${name} in ${type} has not been declared explicitly
 *          as unsigned or signed.
 *
 *   0635   Bit-field ${name} in ${type} has been declared with a type not
 *          explicitly supported.
 *
 *
 *//* PRQA S 0634,0635 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

typedef enum { A, B, C } e_t;


struct T01 { char                bpc: 3; };                           /* expect: 0634 0635 */
struct T02 { signed char         bsc: 3; };                           /* expect:      0635 */
struct T03 { unsigned char       buc: 3; };                           /* expect:      0635 */

extern int16_t rule_0601(void)
{
    struct T01 r0601_t1;
    struct T02 r0601_t2;
    struct T03 r0601_t3;

    return 0;
}

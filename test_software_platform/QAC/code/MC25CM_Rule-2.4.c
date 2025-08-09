/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-2.4.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-2.4: A project should not contain unused tag declarations
 *
 * Enforced by message(s):
 *   3213   The tag '${tag}' is not used and could be removed.
 *
 *   1536   The tag '${name}' is declared but not used within this project.
 *
 *   1755   The tag '${name}' is declared but not used within this project.
 *
 *
 *//* PRQA S 3213,1536,1755 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_0204( void )
{
    struct r0204_ST                                                   /* expect: 3213 1755 1594 */
    {
        int16_t a;
        int16_t b;
    };
    return 1;
}

void unusedtag (void)
{
	enum r0204_state {S_init, S_run, S_sleep}; 	                        /* expect: 3213 1755 1594 */
}

typedef struct r0204_record_t						                              /* expect: 3213 1536      */
{
	uint16_t key;
	uint16_t val;
} record1_t;

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.14.c
 *
 * MISRA Required - Rules
 *
 * Rule-20.14: All #else, #elif and #endif preprocessor directives shall reside in
 *             the same file as the #if, #ifdef or #ifndef directive to which
 *             they are related
 *
 * Enforced by message(s):
 *   3317   '#if...' not matched by '#endif' in included file. This is
 *          probably an error.
 *
 *   3318   '#else'/'#elif'/'#endif' in included file matched '#if...' in
 *          parent file. This is probably an error.
 *
 *
 *//* PRQA S 3317,3318 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

#if 1
#include "MC25CM_Rule-20.14.h"
#endif

#if 1                                                                 /* expect: !3317 */
#endif                                                                /* expect: !3318 */

extern int16_t rule_2014( void )
{
    return 1;
}

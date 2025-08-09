/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-10.8.c
 *
 * MISRA Required - Rules
 *
 * Rule-10.8: The value of a composite expression shall not be cast to a different
 *            essential type category or a wider essential type
 *
 * Enforced by message(s):
 *   4389   A composite expression of 'essentially char' type (${t1}) is
 *          being cast to a different type category, '${t2}'.
 *
 *   4390   A composite expression of 'essentially signed' type (${t1}) is
 *          being cast to a wider signed type, '${t2}'.
 *
 *   4391   A composite expression of 'essentially unsigned' type (${t1})
 *          is being cast to a wider unsigned type, '${t2}'.
 *
 *   4392   A composite expression of 'essentially floating' type (${t1})
 *          is being cast to a wider floating type, '${t2}'.
 *
 *   4393   A composite expression of 'essentially signed' type (${t1}) is
 *          being cast to a different type category, '${t2}'.
 *
 *   4394   A composite expression of 'essentially unsigned' type (${t1})
 *          is being cast to a different type category, '${t2}'.
 *
 *   4395   A composite expression of 'essentially floating' type (${t1})
 *          is being cast to a different type category, '${t2}'.
 *
 *
 *//* PRQA S 4389,4390,4391,4392,4393,4394,4395 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

PC r1008_pca;
SC r1008_sca;
SC r1008_scb;
UC r1008_uca;
UC r1008_ucb;
float32_t r1008_fta;
float32_t r1008_ftb;

extern int16_t rule_1008( void )
{
    (SI)(r1008_pca - 1);                                              /* expect: 4389 */
    (SI)(r1008_sca + r1008_scb);                                      /* expect: 4390 */
    (UI)(r1008_uca + r1008_ucb);                                      /* expect: 4391 */
    (DB)(r1008_fta + r1008_ftb);                                      /* expect: 4392 */
    (UI)(r1008_sca + r1008_scb);                                      /* expect: 4393 */
    (DB)(r1008_uca + r1008_ucb);                                      /* expect: 4394 */
    (SI)(r1008_fta + r1008_ftb);                                      /* expect: 4395 */
    (DB)(~r1008_uca);                                                 /* expect: 4394 */
    (UI)(~r1008_uca);                                                 /* expect: 4391 */

    return 0;
}

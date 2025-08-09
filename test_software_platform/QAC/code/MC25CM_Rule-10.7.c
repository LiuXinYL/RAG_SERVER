/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-10.7.c
 *
 * MISRA Required - Rules
 *
 * Rule-10.7: If a composite expression is used as one operand of an operator in
 *            which the usual arithmetic conversions are performed then the
 *            other operand shall not have wider essential type
 *
 * Enforced by message(s):
 *   1890   A composite expression of 'essentially signed' type (%1s) is
 *          being implicitly converted to a wider signed type, '%2s'.
 *
 *   1891   A composite expression of 'essentially unsigned' type (%1s) is
 *          being implicitly converted to a wider unsigned type,
 *          '%2s'.
 *
 *   1892   A composite expression of 'essentially floating' type (%1s) is
 *          being implicitly converted to a wider floating type,
 *          '%2s'.
 *
 *   1893   The 2nd and 3rd operands of this conditional operator are both
 *          'essentially signed' ('%1s' and '%2s') but one is a
 *          composite expression of a narrower type than the other.
 *
 *   1894   The 2nd and 3rd operands of this conditional operator are both
 *          'essentially unsigned' ('%1s' and '%2s') but one is a
 *          composite expression of a narrower type than the other.
 *
 *   1895   The 2nd and 3rd operands of this conditional operator are both
 *          'essentially floating' ('%1s' and '%2s') but one is a
 *          composite expression of a narrower type than the other.
 *
 *
 *//* PRQA S 1890,1891,1892,1893,1894,1895 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int32_t r1007_sia;
uint32_t r1007_uia;
SC r1007_sca;
SC r1007_scb;
UC r1007_uca;
UC r1007_ucb;
float64_t r1007_dba;
float32_t r1007_fta;
float32_t r1007_ftb;
BL r1007_bla;

extern int16_t rule_1007( void )
{
    r1007_sia + (r1007_sca + r1007_scb);                              /* expect: 1890      */
    r1007_uia + (r1007_uca << 2U);                                    /* expect: 1891      */
    r1007_dba + (r1007_fta + r1007_ftb);                              /* expect: 1892      */

    r1007_bla ? r1007_sia : (r1007_sca + r1007_scb);                  /* expect: 1893      */
    r1007_bla ? r1007_uia : (r1007_uca + r1007_ucb);                  /* expect: 1894      */
    r1007_bla ? r1007_dba : (r1007_fta + r1007_ftb);                  /* expect: 1895      */

    return 0;
}

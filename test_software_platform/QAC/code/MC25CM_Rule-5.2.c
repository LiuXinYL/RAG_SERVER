/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-5.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-5.2: Identifiers declared in the same scope and name space shall be
 *           distinct
 *
 * Enforced by message(s):
 *   0779   Identifier does not differ from other identifier(s) (e.g.
 *          '${id}') within the specified number of significant
 *          characters.
 *
 *
 *//* PRQA S 0779 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"


/* The behavior of this test is impacted by either or both of the following options:
 *   -namelength=?
 *   -xnamelength=?
 *
 * If not specified, the internal defaults for these settings in QAC are:
 *   -namelength=63
 *   -xnamelength=31
 *
 * However, these settings are normally matched to those of the compiler in the CCT.
 * The example project uses Helix_Generic_C which configures these settings as:
 *   -namelength=31
 *   -xnamelength=31
 *
 */


            /* 123456789012345678901234567890123456789012345678901234567890123456789 *****/
static int32_t c23456789012345678901234567890;
static int32_t c234567890123456789012345678901;                                           /* Compliant */

            /* 123456789012345678901234567890123456789012345678901234567890123456789 *****/
static int32_t b2345678901234567890123456789012345678901234567890123456789012;
static int32_t b23456789012345678901234567890123456789012345678901234567890123;          /* expect: 0779 */    /* Non-compliant if -na < 63 */

            /* 123456789012345678901234567890123456789012345678901234567890123456789 ******/
static int32_t a2345678901234567890123456789012341234567890123456789012345678901234;
static int32_t a2345678901234567890123456789012341234567890123456789012345678901234x;    /* expect: 0779 */    /* Non-compliant */

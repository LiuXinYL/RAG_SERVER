/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-20.3: The #include directive shall be followed by either a <filename> or
 *            "filename" sequence
 *
 * Enforced by message(s):
 *   0817   Closing quote or bracket '>' missing from include filename.
 *
 *   0821   '#include' does not identify a header or source file that can
 *          be processed.
 *
 *   0840   Extra tokens at end of #include directive.
 *
 *
 *//* PRQA S 0817,0821,0840 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#define  HEADER "MC25CM_Rule-20.3.h"

#include HEADER                       // OK

#include "MC25CM_Rule-20.3.h"           // OK

                                      // expect+1: 0817
#include <MC25CM_Rule-20.3.h

                                      // expect+1: 0817
#include "MC25CM_Rule-20.3.h

#include MC25CM_Rule-20.3.h             // expect: 0821

#include ?                            // expect: 0821

#include "MC25CM_Rule-20.3.h" extra     // expect: 0840

#include "MC25CM_Rule-20.3.inc" ".h"    // expect: 0840

extern int16_t rule_2003 (void)
{
  return 1;
}

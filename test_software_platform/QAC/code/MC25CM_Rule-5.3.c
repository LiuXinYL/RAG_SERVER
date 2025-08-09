/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-5.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-5.3: An identifier declared in an inner scope shall not hide an identifier
 *           declared in an outer scope
 *
 * Enforced by message(s):
 *   0795   Identifier matches other identifier(s) (e.g. '${id}') in an
 *          outer scope within the specified number of significant
 *          characters.
 *
 *   2547   This declaration of tag '${name}' hides a more global
 *          declaration.
 *
 *   3334   This declaration of '${name}' hides a more global declaration.
 *
 *
 *//* PRQA S 0795,2547,3334 -- *//*
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

struct ST0503
{
  int16_t a;
  int16_t b;
};

enum TE0503 { enx1, enx2, enx3 };
static enum TE0503 enva;
static int16_t rule5003_012345678901234567890123456789012345678901234567890123456789_a;

extern int16_t rule_0503( void )
{
  int16_t enx1;                                                                           /* expect: 3334 */      /* Non-compliant - type hides object */

  static int16_t rule5003_012345678901234567890123456789012345678901234567890123456789_b; /* expect: 0795 */

  struct ST0503                                                                           /* expect: 2547 */      /* Non-compliant - tag hides tag     */
  {
    uint16_t x;
    uint16_t y;
  } sl;

  return 1;
}

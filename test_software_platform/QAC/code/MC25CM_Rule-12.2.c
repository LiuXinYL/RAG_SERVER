/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-12.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-12.2: The right hand operand of a shift operator shall lie in the range
 *            zero to one less than the width in bits of the essential type of
 *            the left hand operand
 *
 * Enforced by message(s):
 *   2791   Definite: Right hand operand of shift operator is negative or
 *          too large.
 *
 *   2792   Apparent: Right hand operand of shift operator is negative or
 *          too large.
 *
 *   2793   Suspicious: Right hand operand of shift operator is negative or
 *          too large.
 *
 *   2794   Possible: Tainted right hand operand of shift operator is
 *          negative or too large.
 *
 *   0499   Right operand of shift operator is greater than or equal to the
 *          width of the essential type of the left operand.
 *
 *   2790   Constant: Right hand operand of shift operator is negative or
 *          too large.
 *
 *
 *//* PRQA S 2791,2792,2793,2794,0499,2790 -- *//*
 * <<<------------------------------------------------------------ */

#include "misra.h"
#include "mc25cmex.h"

#include <stdio.h>

extern int16_t rule_1202( void )
{
   return 1;
}

static void r1202_foo(int32_t r1202_si, uint8_t u8a, uint16_t u16a)   // expect: 1594 1594 1594
{
    if (r1202_si > 40)                                                // expect: 1575 1575
    {
        u8a >> r1202_si;                                              // expect: 2791
    }
    u8a >> r1202_si;                                                  // expect: 2792 1574
    u16a >> -16;                                                      // expect: 2790
    u8a >> 8u;                                                        // expect: 0499

    {
      extern int    n;
      int           i;
      unsigned int  x;
      int           s = 40;

      for (i = 0; i < n; ++i)
      {
          -- s;
      }

      x <<= s;                                                        // expect: 2793 1574
    }

    {
      int           s;
      unsigned long x = 1;

      scanf ("%d", & s);

      x <<= s;                                                        // expect: 2794
    }
}

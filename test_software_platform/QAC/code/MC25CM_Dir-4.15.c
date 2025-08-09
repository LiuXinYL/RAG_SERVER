/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-4.15.c
 *
 * MISRA Required - Directives
 *
 * Dir-4.15: Evaluation of floating-point expressions shall not lead to the
 *           undetected generation of infinities and NaNs
 *
 * Not Assisted.
 * <<<------------------------------------------------------------ */

#include <math.h>

#include "misra.h"
#include "mc25cmex.h"

extern float64_t d0415_get_result ();

extern void d0415_use_result (float64_t d0415c);

int16_t dir_0415 (void)
{
   float64_t d0415a = d0415_get_result ();

   d0415_use_result (d0415a);                   /*       */

   if (!isnan (d0415a))
   {
      d0415_use_result (d0415a);                /*       */
   }
   
   if (isfinite (d0415a))
   {
      d0415_use_result (d0415a);                /*       */
   }

   return 0;
}

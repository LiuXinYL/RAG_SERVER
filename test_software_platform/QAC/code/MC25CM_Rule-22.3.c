/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-22.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-22.3: The same file shall not be open for read and write access at the same
 *            time on different streams
 *
 * Enforced by message(s):
 *   2691   Definite: The same file will be open with write access and
 *          another mode.
 *
 *   2692   Apparent: The same file will be open with write access and
 *          another mode.
 *
 *   2693   Suspicious: The same file will be open with write access and
 *          another mode.
 *
 *
 *//* PRQA S 2691,2692,2693 -- *//*
 * <<<------------------------------------------------------------ */


#include <stdio.h>
#include "misra.h"
#include "mc25cmex.h"

int16_t s16a_2203;
int16_t s16b_2203;

static int16_t rule_2203a (char * path_2203a)                         /* expect: 1594   */
{
  FILE * fp1_2203a = fopen (path_2203a, "r");                         /* expect: 1586   */
  FILE * fp2_2203a = fopen (path_2203a, "w");                         /* expect: 2691x2 */

  fclose (fp1_2203a);
  fclose (fp2_2203a);
}

static int16_t rule_2203b (char * path_2203b)                         /* expect: 1594   */
{
  FILE * fp1_2203b = NULL;
  if (s16a_2203 > 10)
  {
    fp1_2203b = fopen (path_2203b, "w");                              /* expect: 1586   */
  }
  FILE * fp2_2203b = fopen (path_2203b, "r");                         /* expect: 2692   */

  if (fp1_2203b)
  {
    fclose (fp1_2203b);
  }
  fclose (fp2_2203b);
}

static int16_t rule_2203c (char * path_2203c)                         /* expect: 1594   */
{

  FILE * fp1_2203c = NULL;
  while (s16b_2203 > 10)
  {
    -- s16b_2203;
    fp1_2203c = fopen (path_2203c, "w");                              /* expect: 1586   */
  }
  FILE * fp2_2203c = fopen (path_2203c, "r");                         /* expect: 2693   */

  if (fp1_2203c)
  {
    fclose (fp1_2203c);
  }
  fclose (fp2_2203c);
}

extern int16_t rule_2203 (void)
{
  int16_t ret_2203 = 0;

  ret_2203 += rule_2203a ("path");
  ret_2203 += rule_2203b ("path");
  ret_2203 += rule_2203c ("path");

  return ret_2203;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.16.c
 *
 * MISRA Required - Rules
 *
 * Rule-21.16: The pointer arguments to the Standard Library function memcmp shall
 *             point to either a pointer type, an essentially signed type, an
 *             essentially unsigned type, an essentially Boolean type or an
 *             essentially enum type
 *
 * Enforced by message(s):
 *   1488   Comparison of a struct object representation.
 *
 *   1489   Comparison of a union object representation.
 *
 *   1490   Comparison of a floating point object representation.
 *
 *   1491   Comparison of an object representation.
 *
 *   1497   Comparison of a string object representation.
 *
 *
 *//* PRQA S 1488,1489,1490,1491,1497 -- *//*
 * <<<------------------------------------------------------------ */


#include <string.h>
#include "misra.h"
#include "mc25cmex.h"

struct S_2116
{
   uint8_t a;
   uint16_t b;
};

union U_2116
{
   uint8_t a;
   uint16_t b;
};

enum E_2116
{
  A,
  B
};

struct S_2116 * sa_2116;
struct S_2116 * sb_2116;

union U_2116 * ua_2116;
union U_2116 * ub_2116;

enum E_2116 * ea_2116;
enum E_2116 * eb_2116;

void * oa_2116;
void * ob_2116;

char * stra_2116;
char * strb_2116;

bool_t * ba_2116;
bool_t * bb_2116;

int16_t * s16a_2116;
int16_t * s16b_2116;

int32_t * s32a_2116;
int32_t * s32b_2116;

float32_t * f32a_2116;
float32_t * f32b_2116;

float64_t * f64a_2116;
float64_t * f64b_2116;

extern int16_t rule_2116 (void)
{
  int16_t ret_2116 = 0;

  ret_2116 |= memcmp (sa_2116, sb_2116, sizeof (struct S_2116));      /* expect: 1488 */
  ret_2116 |= memcmp (ua_2116, ub_2116, sizeof (union U_2116));       /* expect: 1489 */
  ret_2116 |= memcmp (ea_2116, eb_2116, sizeof (enum E_2116));        /* Compliant    */

  ret_2116 |= memcmp (oa_2116, ob_2116, sizeof (struct S_2116));      /* expect: 1491 */
  ret_2116 |= memcmp (oa_2116, ob_2116, sizeof (union U_2116));       /* expect: 1491 */
  ret_2116 |= memcmp (oa_2116, ob_2116, sizeof (enum E_2116));        /* expect: 1491 */

  ret_2116 |= memcmp (stra_2116, strb_2116, strlen (strb_2116));      /* expect: 1497 */

  ret_2116 |= memcmp (ba_2116, bb_2116, sizeof (bool_t));             /* Compliant    */
  ret_2116 |= memcmp (s16a_2116, s16b_2116, sizeof (int16_t));        /* Compliant    */
  ret_2116 |= memcmp (s32a_2116, s32b_2116, sizeof (int16_t));        /* Compliant    */
  ret_2116 |= memcmp (f32a_2116, f32b_2116, sizeof (float32_t));      /* expect: 1490 */
  ret_2116 |= memcmp (f64a_2116, f64b_2116, sizeof (float64_t));      /* expect: 1490 */

  ret_2116 |= memcmp (f64a_2116, f64b_2116, sizeof (UX));             /* expect: 1490 */

  return ret_2116;
}

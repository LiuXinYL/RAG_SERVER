/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.15.c
 *
 * MISRA Required - Rules
 *
 * Rule-20.15: #define and #undef shall not be used on a reserved identifier or
 *             reserved macro name
 *
 * Enforced by message(s):
 *   0603   The macro identifier '${macro}' is reserved.
 *
 *   0836   Definition of macro named 'defined'.
 *
 *   0837   Use of '#undef' to remove the operator 'defined'.
 *
 *   0848   Attempting to #undef '${name}', which is a predefined macro
 *          name.
 *
 *   0854   Attempting to #define '${name}', which is a predefined macro
 *          name.
 *
 *   4600   The macro '${macro}' is also defined in '<${lib}>'.
 *
 *   4601   The macro '${macro}' is the name of an identifier in
 *          '<${lib}>'.
 *
 *   4620   The macro '${macro}' may also be defined as a macro in
 *          '<${lib}>'.
 *
 *   4621   The macro '${macro}' may also be defined as a typedef in
 *          '<${lib}>'.
 *
 *
 *//* PRQA S 0603,0836,0837,0848,0854,4600,4601,4620,4621 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"


#define _reserved                                                     /* expect: 0603 */
#define _Reserved                                                     /* expect: 0603 */

#define defined ! defined                                             /* expect: 0836 */
#undef  defined                                                       /* expect: 0837 */

#undef __LINE__                                                       /* expect: 0603,0848 */
#undef __FILE__                                                       /* expect: 0603,0848 */
#undef __DATE__                                                       /* expect: 0603,0848 */
#undef __TIME__                                                       /* expect: 0603,0848 */
#undef __STDC__                                                       /* expect: 0603,0848 */

#define __LINE__ 1                                                    /* expect: 0603,0854 */
#define __FILE__ "default"                                            /* expect: 0603,0854 */
#define __DATE__ "01-01-2000"                                         /* expect: 0603,0854 */
#define __TIME__ "00:00:00"                                           /* expect: 0603,0854 */
#define __STDC__                                                      /* expect: 0603,0854 */

#define NULL (void *)0                                                /* expect: 4600 */
#define EDOM 22                                                       /* expect: 4600 */
#define tan 1                                                         /* expect: 4601 */
#define printf xprintf                                                /* expect: 4601 */

#define INT23_MAX 4194303                                             /* expect: 4620 */
#define int23_t int32_t                                               /* expect: 4621 */
#define uint23_t uint32_t                                             /* expect: 4621 */

extern int16_t rule_2101 (void)
{
  return 1;
}

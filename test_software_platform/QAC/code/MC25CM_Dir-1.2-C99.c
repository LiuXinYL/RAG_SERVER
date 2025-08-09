/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-1.2-C99.c
 *
 * MISRA Advisory - C99 Specific Directives
 *
 * Dir-1.2-C99: The use of language extensions should be minimised
 *
 * Enforced by message(s):
 *   1077   The keyword '_Noreturn' has been used.
 *
 *   1078   The keyword '_Alignas' has been used.
 *
 *   1079   The keyword '_Alignof' has been used.
 *
 *   1081   The keyword '_Atomic' has been used.
 *
 *   1082   The keyword '_Generic' has been used.
 *
 *   1084   The keyword '_Thread_local' has been used.
 *
 *
 *//* PRQA S 1077,1078,1079,1081,1082,1084 -- *//*
 * <<<------------------------------------------------------------ */


#include <stddef.h> /* for size_t */

void Rule_0102_C99 (void)
{
  /* C11 language extensions */
  {
    extern void _Noreturn my_function (void);              /* expect: 1077 */

    _Alignas (int) char x;                                 /* expect: 1078 */

    size_t s = _Alignof (size_t);                          /* expect: 1079 */

    _Atomic int i;                                         /* expect: 1081 */

    _Generic                                               /* expect: 1082 */
       ('x', char : 1, int : 2, default : 0);

    static _Thread_local int v = 0;                        /* expect: 1084 */
  }
}

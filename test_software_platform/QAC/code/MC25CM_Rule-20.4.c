/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.4.c
 *
 * MISRA Required - Rules
 *
 * Rule-20.4: A macro shall not be defined with the same name as a keyword
 *
 * Enforced by message(s):
 *   3439   Macro redefines a keyword.
 *
 *
 *//* PRQA S 3439 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

extern int16_t rule_2004( void )
{
    return 1;
}

#define auto AUTO                                                     /* expect: 3439 */
#define break BREAK                                                   /* expect: 3439 */
#define case CASE                                                     /* expect: 3439 */
#define char CHAR                                                     /* expect: 3439 */
#define const CONST                                                   /* expect: 3439 */
#define continue CONTINUE                                             /* expect: 3439 */
#define default DEFAULT                                               /* expect: 3439 */
#define do DO                                                         /* expect: 3439 */
#define double DOUBLE                                                 /* expect: 3439 */
#define else ELSE                                                     /* expect: 3439 */
#define enum ENUM                                                     /* expect: 3439 */
#define extern EXTERN                                                 /* expect: 3439 */
#define float FLOAT                                                   /* expect: 3439 */
#define for FOR                                                       /* expect: 3439 */
#define goto GOTO                                                     /* expect: 3439 */
#define if IF                                                         /* expect: 3439 */
#define int INT                                                       /* expect: 3439 */
#define long LONG                                                     /* expect: 3439 */
#define register REGISTER                                             /* expect: 3439 */
#define return RETURN                                                 /* expect: 3439 */
#define short SHORT                                                   /* expect: 3439 */
#define signed SIGNED                                                 /* expect: 3439 */
#define sizeof XSIZEOF                                                /* expect: 3439 */
#define static STATIC                                                 /* expect: 3439 */
#define struct STRUCT                                                 /* expect: 3439 */
#define switch SWITCH                                                 /* expect: 3439 */
#define typedef TYPEDEF                                               /* expect: 3439 */
#define union UNION                                                   /* expect: 3439 */
#define unsigned UNSIGNED                                             /* expect: 3439 */
#define void VOID                                                     /* expect: 3439 */
#define volatile VOLATILE                                             /* expect: 3439 */
#define while WHILE                                                   /* expect: 3439 */

/* ensure these aren't already hidden by any compatibility settings */
#undef inline
#undef restrict
#undef _Bool
#undef _Complex
#undef _Imaginary

/* additional keywords required for C99 */
#define inline INLINE                                                 /* expect: 3439 */
#define restrict RESTRICT                                             /* expect: 3439 */

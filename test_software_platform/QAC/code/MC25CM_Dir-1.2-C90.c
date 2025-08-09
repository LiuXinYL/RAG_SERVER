/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-1.2-C90.c
 *
 * MISRA Advisory - C90 Specific Directives
 *
 * Dir-1.2-C90: The use of language extensions should be minimised
 *
 * Enforced by message(s):
 *   5131   Use of standard header file <tgmath.h>.
 *
 *   5136   Use of exception handling identifier: feclearexcept,
 *          fegetexceptflag, feraiseexcept, fesetexceptflag or
 *          fetestexcept.
 *
 *   5141   Use of type-generic math identifier
 *
 *   0180   Use of ll for conversion specifier.
 *
 *   0181   Use of hh for conversion specifier.
 *
 *   0320   Declaration within 'for' statement.
 *
 *   0604   Declaration appears after statements in a compound statement.
 *
 *   0617   'const' qualifier has been duplicated.
 *
 *   0618   'volatile' qualifier has been duplicated.
 *
 *   0850   Macro argument is empty.
 *
 *   0930   Trailing comma at the end of an enumerator-list.
 *
 *   1011   Use of '//' comment.
 *
 *   1018   Use of LL suffix.
 *
 *   1027   Use of type 'long long'.
 *
 *   1030   Macro defined with variable argument list.
 *
 *   1031   Initializer for 'struct', 'union' or array type is not a
 *          constant expression.
 *
 *   1032   The identifier '__func__' has been used.
 *
 *   1051   A variable length array has been declared.
 *
 *   1052   A parameter has been declared with a variable length array
 *          size.
 *
 *   1053   Designators have been used in this initialization list.
 *
 *   1054   A compound literal has been used.
 *
 *   1055   The keyword 'inline' has been used.
 *
 *   1056   The keyword '_Bool' has been used.
 *
 *   1057   The keyword 'restrict' has been used.
 *
 *   1058   The keyword 'static' is used in the declaration of a function
 *          parameter of array type.
 *
 *   1059   A type qualifier (const, volatile or restrict) is used in the
 *          declaration of a function parameter of array type.
 *
 *   1060   A flexible array member has been declared.
 *
 *   1076   Use of hexadecimal floating constant.
 *
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
 *   1097   Using a universal character name in an identifier.
 *
 *   1098   Using a universal character name in a literal.
 *
 *   1135   Using the '_Pragma' operator.
 *
 *   1136   This is passing a prefixed string as the operand to '_Pragma'.
 *          The prefix '%1s' will be ignored.
 *
 *   1148   The keyword '_Imaginary' has been used.
 *
 *   1149   The keyword '_Complex' has been used.
 *
 *   1187   This defines a pointer to a variable length array.
 *
 *   1188   This is specifying a variable length array type.
 *
 *   1189   This is specifying a pointer type to a variable length array.
 *
 *
 *//* PRQA S 5131,5136,5141,0180,0181,0320,0604,0617,0618,0850,0930,1011,1018,1027,1030,1031,1032,1051,1052,1053,1054,1055,1056,1057,1058,1059,1060,1076,1077,1078,1079,1081,1082,1084,1097,1098,1135,1136,1148,1149,1187,1188,1189 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

#include <stddef.h> /* for size_t */

/* C99 standard library headers */
#include <tgmath.h>                                        /* expect: 5131 */
#include <fenv.h>

void Rule_0102_C90 (void)
{
  /* use of C99 standard library facilities */
  {
    /* fenv.h */
    feclearexcept (0);                                     /* expect: 5136 */

    /* tgmath.h */
    double d = sqrt (4);                                   /* expect: 5141 */
  }

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

  {
    extern long long           s;
    extern unsigned long long  u;

    // message 0180 will not be generated if the language extension option
    // "-ex LONGLONG" is enabled.

    (void) scanf                                           /* c90_expect: 0180 0180 */
             ("Lets input the values! %lld %llu",
              & s,
              & u);

    (void) printf                                          /* c90_expect: 0180 0180 */
             ("Lets output the values! %lld %llu",
              s,
              u);
  }

  {
    for (int16_t i; i < 8; ++i)                            /* c90_expect: 0320 */
    {

    }
  }

  {
    0;
    char c;                                                /* c90_expect: 0604 */
    0;
  }

  {
    int32_t const const x1;                                /* c90_expect: 0617 */
    int32_t volatile volatile x2;                          /* c90_expect: 0618 */
  }

  {
    #define MY_STRINGIFIED(X) #X
    const char * s = MY_STRINGIFIED ();                    /* c90_expect:  0850 */
  }

  {
    enum E
    {
      A,
      B,                                                   /* c90_expect:  0930 */
    };
  }

  {
                                                           /* c90_expect+1:  1011 */
    // [C99] Use of '//' comment.
  }

  {
    /* Message 1018 only generated when "-extensions longlong" not
     * specified. */
    0LL;                                                   /* c90_expect:  1018 */
  }

  {
    /* Message 1027 only generated when "-extensions longlong" not
     * specified. */
    (long long) 0;                                         /* c90_expect:  1027 */
  }

  {
    #define RULE_0102_C90_1030(X, ...)                     /* c90_expect:  1030 */
  }

  {
    struct S3
    {
      int i [10];
    } s3a;
    struct S3 s3b = { .i = (int []) { s3a.i [0] } };       /* c90_expect:  1031  1053  1054 */
  }

  {
    int n = 4;
    int v [n];                                             /* expect:  1051 */
  }

  {
    extern void Rule_0102_C90_1052 (int v [*]);            /* c90_expect:  1052 */

    inline void Rule_0102_C90_1055 (void);                 /* c90_expect:  1055 */

    _Bool b;                                               /* c90_expect:  1056 */

    int * restrict p;                                      /* expect:  1057 */

    void f (int x [static 4]);                             /* c2025_expect:  1058 */

    void g (int x [const 4]);                              /* c90_expect:  1059 */

    void h (int x [volatile 4]);                           /* c90_expect:  1059 */

    struct T { int x; int y []; };                         /* expect:  1060 */

    double d = 0x1.1p4;                                    /* c90_expect:  1076 */
  }

  {
    /* normal characters only */
    int a = 0;                                             /* c90_expect: !1097 */

    /* short universal character */
    int \u10a0 = 0;                                        /* c90_expect:  1097 */

    /* long universal character  */
    int \U10a020b0 = 0;                                    /* c90_expect:  1097 */

    /* normal characters only */
    char const * s0 = "a";                                 /* c90_expect: !1098 */

    /* short universal character */
    char const * s1 = "\u10a0";                            /* c90_expect:  1098 */

    /* long universal character  */
    char const * s2 = "\U10a020b0";                        /* c90_expect:  1098 */
  }

  {
    extern int my_function_D11 (void);
    _Pragma ("PRQA_NO_SIDE_EFFECTS \"my_function_D11\"")   /* c90_expect:  1135 */
  }

  {
    /* UTF-8 string literal */
    char const * sejong = u8"세종장헌영문예무인성명효대왕";

    /* trying to pass the same string as an operand to a pragma command */
    /* almost certainly won't work, depending on the implementation     */

    _Pragma (u8"sejong 세종장헌영문예무인성명효대왕")             /* c90_expect:  1135  1136 */
  }
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-1.1.c
 *
 * MISRA Required - Directives
 *
 * Dir-1.1: Any implementation-defined behaviour on which the output of the program
 *          depends shall be documented and understood
 *
 * Assisted by message(s):
 *   2851   Definite: Implicit conversion to a signed integer type of
 *          insufficient size.
 *
 *   2852   Apparent: Implicit conversion to a signed integer type of
 *          insufficient size.
 *
 *   2853   Suspicious: Implicit conversion to a signed integer type of
 *          insufficient size.
 *
 *   2856   Definite: Casting to a signed integer type of insufficient
 *          size.
 *
 *   2857   Apparent: Casting to a signed integer type of insufficient
 *          size.
 *
 *   2858   Suspicious: Casting to a signed integer type of insufficient
 *          size.
 *
 *   2861   Definite: Implementation-defined value resulting from left
 *          shift operation on expression of signed type.
 *
 *   2862   Apparent: Implementation-defined value resulting from left
 *          shift operation on expression of signed type.
 *
 *   2863   Suspicious: Implementation-defined value resulting from left
 *          shift operation on expression of signed type.
 *
 *   2896   Definite: Negative value cast to an unsigned type.
 *
 *   2897   Apparent: Negative value cast to an unsigned type.
 *
 *   2898   Suspicious: Negative value cast to an unsigned type.
 *
 *   0202   '-' character in '[]' conversion specification is
 *          implementation defined.
 *
 *   0240   This file contains the control-M character at the end of a
 *          line.
 *
 *   0241   This file contains the control-Z character - was this
 *          transferred from a PC?
 *
 *   0242   This file contains the control-M character in the middle of a
 *          line.
 *
 *   0243   Treating an invalid character as whitespace.
 *
 *   0246   Binary integer constants are a language extension.
 *
 *   0284   Multiple character constants have implementation defined
 *          values.
 *
 *   0285   Character constant contains character which is not a member of
 *          the basic source character set.
 *
 *   0286   String literal contains character which is not a member of the
 *          basic source character set.
 *
 *   0287   Header name contains character which is not a member of the
 *          basic source character set.
 *
 *   0288   Source file '%s' has comments containing characters which are
 *          not members of the basic source character set.
 *
 *   0289   Source file '%s' has preprocessing tokens containing characters
 *          which are not members of the basic source character set.
 *
 *   0292   Source file '%s' has comments containing one of the characters
 *          '$', '@' or '`'.
 *
 *   0299   Source file '%s' includes #pragma directives containing
 *          characters which are not members of the basic source
 *          character set.
 *
 *   0497   Performing pointer arithmetic on pointer to void.
 *
 *   0551   Cast may not operate on the left operand of the assignment
 *          operator.
 *
 *   0581   Floating-point constant may be too small to be representable.
 *
 *   0601   Function 'main()' is not of type 'int (void)' or 'int (int,
 *          char *[])'.
 *
 *   0609   More than 12 pointer, array or function declarators modifying a
 *          declaration - program does not conform strictly to
 *          ISO:C90.
 *
 *   0633   Empty structures and unions are a language extension.
 *
 *   0634   Bit-field ${name} in ${type} has not been declared explicitly
 *          as unsigned or signed.
 *
 *   0635   Bit-field ${name} in ${type} has been declared with a type not
 *          explicitly supported.
 *
 *   0660   Defining an unnamed member in a struct or union.
 *
 *   0662   Accessing a member of an unnamed struct or union member.
 *
 *   0830   Unrecognized text encountered after a preprocessing directive.
 *
 *   0831   Use of '\\' in this '#include' line is a PC extension - this
 *          usage is non-portable.
 *
 *   0840   Extra tokens at end of #include directive.
 *
 *   0899   Unrecognized preprocessing directive has been ignored - assumed
 *          to be a language extension.
 *
 *   0981   Redundant semicolon in 'struct' or 'union' member declaration
 *          list is a language extension.
 *
 *   1001   '#include %s' is a VMS extension.
 *
 *   1002   '%s' is not a legal identifier in ISO C.
 *
 *   1003   '#${directive}' is a language extension for in-line assembler.
 *          All statements located between #asm and #endasm will be
 *          ignored.
 *
 *   1006   This in-line assembler construct is a language extension. The
 *          code has been ignored.
 *
 *   1008   '#%s' is not a legal ISO C preprocessing directive.
 *
 *   1012   Use of a C++ reference type ('type &') will be treated as a
 *          language extension.
 *
 *   1014   Non-standard enum type specifier.
 *
 *   1015   '%s' is not a legal keyword in ISO C - this will be treated as
 *          a language extension.
 *
 *   1016   Using pre-standard field designator syntax.
 *
 *   1017   Omitting the '=' after an array element designator is a pre-
 *          standard extension.
 *
 *   1019   '@ address' is not supported in ISO C - this will be treated as
 *          a language extension.
 *
 *   1020   '${keyword}' is not supported in ISO C, and is treated as a
 *          language extension.
 *
 *   1021   A statement expression is not supported in ISO C, and is
 *          treated as a language extension.
 *
 *   1022   '__alignof__' is a language extension. It is mapped to the
 *          standard '_Alignof' operator.
 *
 *   1026   The indicated @word construct has been ignored.
 *
 *   1028   Use of the sizeof operator in a preprocessing directive is a
 *          language extension.
 *
 *   1029   Whitespace encountered between backslash and new-line has been
 *          ignored.
 *
 *   1034   Macro defined with named variable argument list. This is a
 *          language extension.
 *
 *   1035   No macro arguments supplied for variable argument list. This is
 *          a language extension.
 *
 *   1036   Comma before ## ignored in expansion of variadic macro. This is
 *          a language extension.
 *
 *   1037   Arrays of length zero are a language extension.
 *
 *   1038   The sequence ", ##__VA_ARGS__" is a language extension.
 *
 *   1039   Treating array of length one as potentially flexible member.
 *
 *   1040   The identifier '${id}' is an extension to get the name of the
 *          current function.
 *
 *   1041   Empty aggregate initializers are a language extension.
 *
 *   1042   Using I64 or UI64 as an integer constant suffix. This is a
 *          language extension.
 *
 *   1043   Defining an anonymous union object. This is a language
 *          extension.
 *
 *   1044   Defining an anonymous struct object. This is a language
 *          extension.
 *
 *   1045   Use of the #include_next preprocessing directive is a language
 *          extension.
 *
 *   1046   Function is being declared with default argument syntax. This
 *          is a language extension.
 *
 *   1049   Nested functions are a language extension.
 *
 *   1075   Passing a type name as the controlling operand of '_Generic' is
 *          an extension.
 *
 *   1086   '_Alignof (expression)' is a common non-standard extension. ISO
 *          C11 only defines '_Alignof (type)'.
 *
 *   1090   '__label__' is not supported in ISO C, and is treated as a
 *          language extension.
 *
 *   1094   '_Static_assert (expression)' with no message is a common non-
 *          standard extension.
 *
 *   1130   The '__has_include' operator is a language extension.
 *
 *   1131   The '__has_include_next' operator is a language extension.
 *
 *   1141   The '__VA_OPT__' operator is a language extension.
 *
 *   1180   The '__auto_type' specifier is a language extension.
 *
 *   1181   Using 'auto' to deduce the type of a declarator.
 *
 *   1186   Declaring a variadic function without any named parameters.
 *
 *   1194   Using digit separators in a numeric literal.
 *
 *   1197   Using an explicit enum type specifier.
 *
 *   1200   This is declaring an overloaded function.
 *
 *   1201   This is resolving an overload of function '${name}'.
 *
 *   1206   This is declaring an overloaded nested function.
 *
 *   1212   The keyword 'constexpr' has been used.
 *
 *   2070   Using [[attribute]] syntax.
 *
 *   2071   This attribute syntax is a language extension.
 *
 *   2072   This attribute specifier is unexpected in this source position,
 *          and will be ignored.
 *
 *   2850   Constant: Implicit conversion to a signed integer type of
 *          insufficient size.
 *
 *   2855   Constant: Casting to a signed integer type of insufficient
 *          size.
 *
 *   2860   Constant: Implementation-defined value resulting from left
 *          shift operation on expression of signed type.
 *
 *   2895   Constant: Negative value cast to an unsigned type.
 *
 *   3116   Unrecognized #pragma arguments '%s' This #pragma directive has
 *          been ignored.
 *
 *   3445   Conditional expression with middle operand omitted is a
 *          language extension.
 *
 *   3638   The ${dir_name} directive is only supported from C23.
 *
 *   3664   Using a dot operator to access an individual bit is a language
 *          extension.
 *
 *
 *//* PRQA S 2851,2852,2853,2856,2857,2858,2861,2862,2863,2896,2897,2898,0202,0240,0241,0242,0243,0246,0284,0285,0286,0287,0288,0289,0292,0299,0497,0551,0581,0601,0609,0633,0634,0635,0660,0662,0830,0831,0840,0899,0981,1001,1002,1003,1006,1008,1012,1014,1015,1016,1017,1019,1020,1021,1022,1026,1028,1029,1034,1035,1036,1037,1038,1039,1040,1041,1042,1043,1044,1045,1046,1049,1075,1086,1090,1094,1130,1131,1141,1180,1181,1186,1194,1197,1200,1201,1206,1212,2070,2071,2072,2850,2855,2860,2895,3116,3445,3638,3664 -- *//*
 * <<<------------------------------------------------------------ */

#include <stdio.h>

#include "misra.h"
#include "mc25cmex.h"

extern int16_t dir_0101( void )
{
  int16_t obj;
  void * v;

  fscanf(stdin, "%[() - 0123456789]", 0);                             /* expect:  0202             */
  'AB';                                                               /* expect:  0284             */
  '@';                                                                /* expect:  0285             */
  "@";                                                                /* expect:  0286             */

  /* Message 0287 could be operating system specific so has been
   * excluded from testing. */

  /* ¬ */                                                             /* expect:  0288             */
#define M1 @                                                          /* expect:  0289             */

  /* Message 292 is generated once per file on the first occurrence of
   * one of these characters.  For this test, the message will be
   * generated for the message text in the test header and will be
   * suppressed. */
  /* @ */

#pragma PRAGMA @                                                      /* expect:  0299  3116       */

  struct Without_Members                                              /* expect:  0633             */
  {

  };

  int * * * * * * * * * * * *   Derived_12;                           /* expect: !0609             */
  int * * * * * * * * * * * * * Derived_13;                           /* expect:  0609             */

  1.17549434E-38F;                                                    /* expect:  0581             */

  {
    struct S64
    {
      int m1 : 10;                                                    /* expect:  0634             */
      int m2;
    } s64;
  }

  {
    _Bool b;

    int8_t sc1, sc2;
    uint32_t ui1, ui2;
    int32_t i1, i2;
    ui1 = 0x80;                                                       /* expect:  1575  1575       */
    sc1 = 0x80;                                                       /* expect:  2850             */
    sc1 = ui1;                                                        /* expect:  2851             */
    if (b)
    {
      ui2 = 0x80;                                                     /* expect:  1575  1575       */
    }
    sc2 = ui2;                                                        /* expect:  2852  1574       */

    {
      extern int n;
      int        i;
      int        v = 128;
      int8_t     c;

      for (i = 0; i < n; ++i)
      {
         v = v - 10;
      }

      c = v;                                                          /* expect:  2853  1574       */
    }

    (int8_t)0x80;                                                     /* expect:  2855             */
    (int8_t)ui1;                                                      /* expect:  2856             */
    if (b)
    {
      ui2 = 0x80;                                                     /* expect:  1575             */
      i2 = -1;                                                        /* expect:  1575  1575       */
    }
    (int8_t)ui2;                                                      /* expect:  2857  1574  1574 */

    {
      extern int n;
      int        i;
      int        v = 128;
      int8_t     c;

      for (i = 0; i < n; ++i)
      {
         v = v - 10;
      }

      c = (int8_t) v;                                                 /* expect:  2858  1574       */
    }

    -1 << 0;                                                          /* expect:  2860             */
    i1 = -1;                                                          /* expect:  1575  1575       */
    i1 << 0;                                                          /* expect:  2861             */
    i2 << 0;                                                          /* expect:  2862  1574       */

    {
      extern int n;
      int        i;
      long       v = 0x10000000L;

      for (i = 0; i < n; ++i)
      {
         v >>= 1;
      }

      v << 2;                                                         /* expect: !2863             */
      v << 3;                                                         /* expect:  2863  1574       */
    }

    (uint32_t)-1;                                                     /* expect:  2895             */
    (uint32_t)i1;                                                     /* expect:  2896             */
    (uint32_t)i2;                                                     /* expect:  2897  1574       */

    {
      extern int n;
      int        i;
      int        v = -10;
      uint8_t    c;

      for (i = 0; i < n; ++i)
      {
         v = v + 20;
      }

      c = (uint8_t) v;                                                /* expect:  2898  1574        */
    }
  }

  {
    int x;

    x = __alignof__(char);                                            /* expect:  1022              */
    x = __alignof__(x);                                               /* expect:  1022              */
  }

#define F1034(x, args...)                                             /* expect:  1034              */

  {
    int     x;
    size_t  s;

    s = _Alignof (int);                                               /* expect: !1086              */
    s = _Alignof (x);                                                 /* expect:  1086              */
    s = _Alignof  x;                                                  /* expect:  1086              */
  }

#if __has_include ("my_header.h")                                     /* expect:  1130              */

#endif

#if __has_include_next ("my_header.h")                                /* expect:  1131              */

#endif


#define DIR_0101_MAC1(NAME, ...)  \
    NAME __VA_OPT__( = { __VA_ARGS__ })                               /* expect:  1141              */
  {
    int DIR_0101_MAC1(x);                                             /* expect:  1035              */

    int DIR_0101_MAC1(y, 32);                                         /* expect: !1035              */
  }

  return 1;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-1.2.c
 *
 * MISRA Advisory - Directives
 *
 * Dir-1.2: The use of language extensions should be minimised
 *
 * Assisted by message(s):
 *   0246   Binary integer constants are a language extension.
 *
 *   0497   Performing pointer arithmetic on pointer to void.
 *
 *   0551   Cast may not operate on the left operand of the assignment
 *          operator.
 *
 *   0601   Function 'main()' is not of type 'int (void)' or 'int (int,
 *          char *[])'.
 *
 *   0633   Empty structures and unions are a language extension.
 *
 *   0635   Bit-field ${name} in ${type} has been declared with a type not
 *          explicitly supported.
 *
 *   0660   Defining an unnamed member in a struct or union.
 *
 *   0662   Accessing a member of an unnamed struct or union member.
 *
 *   0710   This character array is being initialized by a parenthesized
 *          string literal.
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
 *   1083   The keyword '_Static_assert' has been used.
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
 *   1122   This non-standard usage of '_Alignof' retrieves the alignment
 *          of an array.
 *
 *   1130   The '__has_include' operator is a language extension.
 *
 *   1131   The '__has_include_next' operator is a language extension.
 *
 *   1141   The '__VA_OPT__' operator is a language extension.
 *
 *   1144   Operand to '__VA_OPT__' is ill-formed.
 *
 *   1145   Operand to '__VA_OPT__' is not terminated by a closing
 *          parenthesis.
 *
 *   1146   '__VA_OPT__' may only be used in a variadic function-like
 *          macro.
 *
 *   1152   Specifying complex or imaginary integer types is an extension.
 *
 *   1160   Passing an argument to '${name}' that has complex type.
 *
 *   1161   Passing an argument to '${name}' that has imaginary type.
 *
 *   1162   Passing an argument to '${name}' that does not have essentially
 *          integer or essentially floating type.
 *
 *   1163   Not all arguments to '${name}' have the same type.
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
 *   1282   A '${suffix}' suffix has been used to give a literal constant
 *          complex type.
 *
 *   1283   A hexadecimal floating constant requires both a fractional part
 *          and an explicit exponent.
 *
 *   1284   The '${op}' operator is being used to access part of a complex
 *          value.
 *
 *   1316   Resolving ordinary identifier '${name}' as the name of '${tag}
 *          ${name}'.
 *
 *   2070   Using [[attribute]] syntax.
 *
 *   2071   This attribute syntax is a language extension.
 *
 *   2072   This attribute specifier is unexpected in this source position,
 *          and will be ignored.
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
 *//* PRQA S 0246,0497,0551,0601,0633,0635,0660,0662,0710,0830,0831,0840,0899,0981,1001,1002,1003,1006,1008,1012,1014,1015,1016,1017,1019,1020,1021,1022,1026,1028,1029,1034,1035,1036,1037,1038,1039,1040,1041,1042,1043,1044,1045,1046,1049,1075,1083,1086,1090,1094,1122,1130,1131,1141,1144,1145,1146,1152,1160,1161,1162,1163,1180,1181,1186,1194,1197,1200,1201,1206,1212,1282,1283,1284,1316,2070,2071,2072,3445,3638,3664 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

struct rule_0102_struct { } ;                              /* expect:  0633 */

extern int16_t rule_0102( void )
{
   int16_t a[10] = { } ;                                   /* expect:  1041 */
   struct rule_0102_struct * volatile b;
   b;

    _Static_assert                                         /* expect: 1083  */
       (2 + 2 == 4, "indeed");

   return a[0];
}

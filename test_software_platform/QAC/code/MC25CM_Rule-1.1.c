/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-1.1.c
 *
 * MISRA Required - Rules
 *
 * Rule-1.1: The program shall contain no violations of the standard C syntax and
 *           constraints, and shall not exceed the implementation's translation
 *           limits
 *
 * Enforced by message(s):
 *   0232   Value of hex escape sequence is not representable in type
 *          'unsigned char'.
 *
 *   0233   Value of octal escape sequence is not representable in type
 *          'unsigned char'.
 *
 *   0244   Value of character constant is not representable in type 'int'.
 *
 *   0268   Comment open at end of translation unit.
 *
 *   0321   Declaration within 'for' statement defines an identifier
 *          '${name}' which is not an object.
 *
 *   0322   Illegal storage class specifier used in 'for' statement
 *          declaration.
 *
 *   0323   Cast between a pointer to incomplete type and a floating type.
 *
 *   0327   Cast between a pointer to void and a floating type.
 *
 *   0338   Octal or hex escape sequence value is too large for 'unsigned
 *          char' or 'wchar_t' type.
 *
 *   0422   Function call contains fewer arguments than prototype
 *          specifies.
 *
 *   0423   Function call contains more arguments than prototype specifies.
 *
 *   0426   Called function has incomplete return type.
 *
 *   0427   Object identifier used as if it were a function or a function
 *          pointer identifier.
 *
 *   0429   Function argument is not of arithmetic type.
 *
 *   0430   Function argument is not of compatible 'struct'/'union' type.
 *
 *   0431   Function argument points to a more heavily qualified type.
 *
 *   0432   Function argument is not of compatible pointer type.
 *
 *   0435   The 'struct'/'union' member '%s' does not exist.
 *
 *   0436   Left operand of '.' must be a 'struct' or 'union' object.
 *
 *   0437   Left operand of '->' must be a pointer to a 'struct' or 'union'
 *          object.
 *
 *   0446   Operand of ++/-- must have scalar (arithmetic or pointer) type.
 *
 *   0447   Operand of ++/-- must be a modifiable object.
 *
 *   0448   Operand of ++/-- must not be a pointer to an object of unknown
 *          size.
 *
 *   0449   Operand of ++/-- must not be a pointer to a function.
 *
 *   0451   Subscripting requires a pointer (or array lvalue).
 *
 *   0452   Cannot subscript a pointer to an object of unknown size.
 *
 *   0453   An array subscript must have integral type.
 *
 *   0454   The address-of operator '&' cannot be applied to an object
 *          declared with 'register'.
 *
 *   0456   This expression does not have an address - '&' may only be
 *          applied to an lvalue or a function designator.
 *
 *   0457   The address-of operator '&' cannot be applied to a bit-field.
 *
 *   0458   Indirection operator '*' requires operand of pointer type.
 *
 *   0460   The keyword static is used in the declaration of the index of
 *          an array which is not a function parameter.
 *
 *   0461   The keyword static is used in the declaration of an inner index
 *          of a multi-dimensional array.
 *
 *   0462   A type qualifier (const, volatile or restrict) is used in the
 *          declaration of the index of an array which is not a
 *          function parameter.
 *
 *   0463   A type qualifier (const, volatile or restrict) is used in the
 *          declaration of an inner index of a multi-dimensional
 *          array.
 *
 *   0466   Unary '+' requires arithmetic operand.
 *
 *   0467   Operand of '!' must have scalar (arithmetic or pointer) type.
 *
 *   0468   Unary '-' requires arithmetic operand.
 *
 *   0469   Bitwise not '~' requires integral operand.
 *
 *   0476   'sizeof' cannot be applied to a bit-field.
 *
 *   0477   'sizeof' cannot be applied to a function.
 *
 *   0478   'sizeof' cannot be applied to an object of unknown size.
 *
 *   0481   Only scalar expressions may be cast to other types.
 *
 *   0482   Expressions may only be cast to 'void' or scalar types.
 *
 *   0483   A pointer to an object of unknown size cannot be the operand of
 *          an addition operator.
 *
 *   0484   A pointer to an object of unknown size cannot be the operand of
 *          a subtraction operator.
 *
 *   0485   Only integral expressions may be added to pointers.
 *
 *   0486   Only integral expressions and compatible pointers may be
 *          subtracted from pointers.
 *
 *   0487   If two pointers are subtracted, they must be pointers that
 *          address compatible types.
 *
 *   0493   Type of left operand is not compatible with this operator.
 *
 *   0494   Type of right operand is not compatible with this operator.
 *
 *   0495   Left operand of '%', '<<', '>>', '&', '^' or '|' must have
 *          integral type.
 *
 *   0496   Right operand of '%', '<<', '>>', '&', '^' or '|' must have
 *          integral type.
 *
 *   0513   Relational operator used to compare pointers to incompatible
 *          types.
 *
 *   0514   Relational operator used to compare a pointer with an
 *          incompatible operand.
 *
 *   0515   Equality operator used to compare a pointer with an
 *          incompatible operand.
 *
 *   0536   First operand of '&&', '||' or '?' must have scalar (arithmetic
 *          or pointer) type.
 *
 *   0537   Second operand of '&&' or '||' must have scalar (arithmetic or
 *          pointer) type.
 *
 *   0540   2nd and 3rd operands of conditional operator '?' must have
 *          compatible types.
 *
 *   0541   Argument no. %s does not have object type.
 *
 *   0542   Controlling expression must have scalar (arithmetic or pointer)
 *          type.
 *
 *   0546   'enum ${name}' has unknown content. Use of an enum tag with
 *          undefined content is not permitted.
 *
 *   0547   This declaration of tag '${name}' conflicts with a previous
 *          declaration.
 *
 *   0550   Left operand of '+=' or '-=' is a pointer to an object of
 *          unknown size.
 *
 *   0554   'static ${name}()' has been declared and called but no
 *          definition has been given.
 *
 *   0555   Invalid assignment to object of void type or array type.
 *
 *   0556   Left operand of assignment must be a modifiable object.
 *
 *   0557   Right operand of assignment is not of arithmetic type.
 *
 *   0558   Right operand of '+=' or '-=' must have integral type when left
 *          operand is a pointer.
 *
 *   0559   Right operand of '<<=', '>>=', '&=', '|=', '^=' or '%=' must
 *          have integral type.
 *
 *   0560   Left operand of '<<=', '>>=', '&=', '|=', '^=' or '%=' must
 *          have integral type.
 *
 *   0561   Right operand of assignment is not of compatible
 *          'struct'/'union' type.
 *
 *   0562   Right operand of assignment points to a more heavily qualified
 *          type.
 *
 *   0563   Right operand of assignment is not of compatible pointer type.
 *
 *   0564   Left operand of assignment must be an lvalue (it must designate
 *          an object).
 *
 *   0565   Left operand of '+=' or '-=' must be of arithmetic or pointer
 *          to object type.
 *
 *   0580   Constant is too large to be representable.
 *
 *   0588   Width of bit-field must be an integral constant expression.
 *
 *   0589   Enumeration constant must be an integral constant expression.
 *
 *   0590   Array bound must be an integral constant expression.
 *
 *   0591   A 'case' label must be an integral constant expression.
 *
 *   0605   A declaration must declare a tag or an identifier.
 *
 *   0616   Illegal combination of type specifiers or storage class
 *          specifiers.
 *
 *   0619   The identifier '${name}' has already been defined in the
 *          current scope within the ordinary identifier namespace.
 *
 *   0620   Cannot initialize '${name}' because it has unknown size.
 *
 *   0621   The struct/union '%s' cannot be initialized because it has
 *          unknown size.
 *
 *   0622   The identifier '%s' has been declared both with and without
 *          linkage in the same scope.
 *
 *   0627   '%s' has different type to previous declaration in the same
 *          scope.
 *
 *   0628   '%s' has different type to previous declaration at wider scope.
 *
 *   0629   More than one definition of '%s' (with internal linkage).
 *
 *   0631   More than one declaration of '%s' (with no linkage).
 *
 *   0638   Duplicate member name '%s' in 'struct' or 'union'.
 *
 *   0640   '%s' in 'struct' or 'union' type may not have 'void' type.
 *
 *   0641   '%s' in 'struct' or 'union' type may not have function type.
 *
 *   0642   '%s' in 'struct' or 'union' type may not be an array of unknown
 *          size.
 *
 *   0643   '%s' in 'struct' or 'union' type may not be a 'struct' or
 *          'union' with unknown content.
 *
 *   0644   Width of bit-field must be no bigger than the width of its
 *          declared type.
 *
 *   0645   A zero width bit-field cannot be given a name.
 *
 *   0646   Enumeration constants must have values representable as 'int's.
 *
 *   0649   K&R style declaration of parameters is not legal after a
 *          function header that includes a parameter list.
 *
 *   0650   Illegal storage class specifier on named function parameter.
 *
 *   0651   Missing type specifiers in function declaration.
 *
 *   0653   Duplicate definition of 'struct', 'union' or 'enum' tag '%s'.
 *
 *   0655   Illegal storage class specifier on unnamed function parameter.
 *
 *   0656   Function return type cannot be function or array type, or an
 *          incomplete struct/union (for function definition).
 *
 *   0657   Unnamed parameter specified in function definition.
 *
 *   0659   The identifier '%s' was not given in the parameter list.
 *
 *   0664   Parameter specified with type 'void'.
 *
 *   0665   Two parameters have been declared with the same name
 *          '${ident}'.
 *
 *   0669   The restrict qualifier can only be applied to pointer types
 *          derived from object or incomplete types.
 *
 *   0671   Initializer for object of arithmetic type is not of arithmetic
 *          type.
 *
 *   0673   Initializer points to a more heavily qualified type.
 *
 *   0674   Initializer for pointer is of incompatible type.
 *
 *   0675   Initializer is not of compatible 'struct'/'union' type.
 *
 *   0677   Array size is negative, or unrepresentable.
 *
 *   0682   Initializer for object of a character type is a string literal.
 *
 *   0683   Initializer for object of a character type is a wide string
 *          literal.
 *
 *   0684   Too many initializers.
 *
 *   0685   Initializer for any object with static storage duration must be
 *          a constant expression.
 *
 *   0690   String literal contains too many characters to initialize
 *          object.
 *
 *   0698   String literal used to initialize an object of incompatible
 *          type.
 *
 *   0699   String literal used to initialize a pointer of incompatible
 *          type.
 *
 *   0708   No definition found for the label '%s' in this function.
 *
 *   0709   Initialization of locally declared 'extern %s' is illegal.
 *
 *   0711   This array is being initialized by a compound literal array
 *          instead of a braced initializer list.
 *
 *   0736   'case' label does not have unique value within this 'switch'
 *          statement.
 *
 *   0737   More than one 'default' label found in 'switch' statement.
 *
 *   0738   Controlling expression in a 'switch' statement must have
 *          integral type.
 *
 *   0746   'return exp;' found in '%s()' whose return type is 'void'.
 *
 *   0747   'return exp;' found in '%s()' whose return type is qualified
 *          'void'.
 *
 *   0755   'return' expression is not of arithmetic type.
 *
 *   0756   'return' expression is not of compatible 'struct'/'union' type.
 *
 *   0757   'return' expression points to a more heavily qualified type.
 *
 *   0758   'return' expression is not of compatible pointer type.
 *
 *   0766   'continue' statement found outside an iteration statement.
 *
 *   0767   'break' statement found outside a 'switch' or iteration
 *          statement.
 *
 *   0768   'case' or 'default' found outside a 'switch' statement.
 *
 *   0774   'auto' may not be specified on global declaration of '%s'.
 *
 *   0775   'register' may not be specified on global declaration of '%s'.
 *
 *   0801   The '##' operator may not be the first token in a macro
 *          replacement list.
 *
 *   0802   The '##' operator may not be the last token in a macro
 *          replacement list.
 *
 *   0803   The '#' operator may only appear before a macro parameter.
 *
 *   0804   Macro parameter '%s' is not unique.
 *
 *   0811   The glue operator '##' may only appear in a '#define'
 *          preprocessing directive.
 *
 *   0817   Closing quote or bracket '>' missing from include filename.
 *
 *   0818   Cannot find '%s' - Perhaps the appropriate search path was not
 *          given ?
 *
 *   0821   '#include' does not identify a header or source file that can
 *          be processed.
 *
 *   0834   Function-like macro '%s()' is being redefined as an object-like
 *          macro.
 *
 *   0835   Macro '%s' is being redefined with different parameter names.
 *
 *   0844   Macro '%s' is being redefined with a different replacement
 *          list.
 *
 *   0845   Object-like macro '%s' is being redefined as a function-like
 *          macro.
 *
 *   0851   Function macro '${name}' requires ${num} argument(s).
 *
 *   0852   Unable to find the ')' that marks the end of the macro call.
 *
 *   0866   The string literal in a '#line' directive cannot be a 'wide
 *          string literal'.
 *
 *   0873   Preprocessing token cannot be converted to an actual token.
 *
 *   0877   '#if' and '#elif' expressions may contain only integral
 *          constants.
 *
 *   0940   Illegal usage of a variably modified type.
 *
 *   0941   A variable length array may not be initialized.
 *
 *   0943   Jump to label '%s' is a jump into the scope of an identifier
 *          with variably modified type.
 *
 *   0944   The label '%s' is inside the scope of an identifier with
 *          variably modified type.
 *
 *   1023   Using '_Alignof' on function types is illegal.
 *
 *   1024   Using '_Alignof' on incomplete types is illegal.
 *
 *   1025   Using '_Alignof' on bit-fields is illegal.
 *
 *   1033   The identifier ${name} may only be used in the replacement list
 *          of a variadic macro.
 *
 *   1047   Function is being declared with default argument syntax after a
 *          previous call to the function. This is not allowed.
 *
 *   1048   Default argument values are missing for some parameters in this
 *          function declaration. This is not allowed.
 *
 *   1050   Nested functions cannot be 'extern' or 'static'.
 *
 *   1061   Structure '%1s' with flexible array member '%2s' cannot be used
 *          in the declaration of structure member '%3s'.
 *
 *   1062   Structure '${name}' with flexible array member '${fam}' cannot
 *          be used in the declaration of array elements.
 *
 *   1080   A typedef or pointer to function is being declared with default
 *          argument syntax. This is not allowed.
 *
 *   1087   Objects declared with '_Thread_local' must have linkage or
 *          static storage duration.
 *
 *   1088   '_Thread_local' must appear on every declaration of an object,
 *          or on none.
 *
 *   1089   '_Thread_local' may not form part of a function declaration.
 *
 *   1091   Declaration of a GNU local label must be the first statement in
 *          the block.
 *
 *   1092   No definition found for the label '%s' in this scope.
 *
 *   1093   Failed static assertion '${text}'.
 *
 *   1095   The message passed to '_Static_assert' must be a string
 *          literal.
 *
 *   1096   The expression passed to '_Static_assert' must be an integer
 *          constant expression.
 *
 *   1112   The _Atomic specifier may not be used to qualify this type.
 *
 *   1113   Implicit conversion may not add or remove the _Atomic
 *          qualifier.
 *
 *   1117   This is not a valid alignment expression.
 *
 *   1118   An explicitly specified alignment must be at least as strict as
 *          the default.
 *
 *   1120   This is not an object which can be declared with an alignment
 *          specifier.
 *
 *   1124   This '_Generic' selection contains multiple 'default'
 *          associations.
 *
 *   1125   This association does not describe a unique type in the
 *          '_Generic' selection.
 *
 *   1126   The controlling expression of this '_Generic' selection does
 *          not match any association.
 *
 *   1127   This '_Generic' association describes an incomplete or
 *          variably-modified type.
 *
 *   1133   Using the '${name}' operator outside of an #if or #elif
 *          directive.
 *
 *   1150   Using the relational operators with values in the imaginary or
 *          complex domain is a constraint violation.
 *
 *   1198   An enum type specifier must name a suitable integer type.
 *
 *   1199   Enum '${name}' is being redeclared with a conflicting type
 *          specification.
 *
 *   1202   This is resolving an unavailable overload of function
 *          '${name}'.
 *
 *   1203   Overloading can only be applied to function declarations.
 *
 *   1207   Overloading can only be applied to functions declared with a
 *          prototype.
 *
 *   1208   Unable to resolve an overload for this use of '${name}'.
 *
 *   1209   Inexact match for '${name}' with only one overload.
 *
 *   1211   '${name}' is declared both with and without the 'overloadable'
 *          attribute for the same signature.
 *
 *   1220   The value for this enumerator is not in range for the
 *          explicitly specified underlying type.
 *
 *   2025   This appears to jump across a nested function scope boundary.
 *
 *   3236   'inline' may not be applied to function 'main'.
 *
 *   3237   inline function '${fun}' has external linkage and is defining
 *          an object, '${obj}', with static storage duration.
 *
 *   3238   inline function '${fun}' has external linkage and is referring
 *          to an object, '${obj}', with internal linkage.
 *
 *   3244   'inline' may only be used in the declaration of a function
 *          identifier.
 *
 *   3639   Implicitly converting a pointer to an array, to a pointer to an
 *          array of more-qualified elements.
 *
 *   3640   Casting a pointer to an array, to a pointer to an array of
 *          more-qualified elements.
 *
 *   3645   Using the '#embed' directive.
 *
 *   3646   Using the '__has_embed' operator.
 *
 *
 *//* PRQA S 0232,0233,0244,0268,0321,0322,0323,0327,0338,0422,0423,0426,0427,0429,0430,0431,0432,0435,0436,0437,0446,0447,0448,0449,0451,0452,0453,0454,0456,0457,0458,0460,0461,0462,0463,0466,0467,0468,0469,0476,0477,0478,0481,0482,0483,0484,0485,0486,0487,0493,0494,0495,0496,0513,0514,0515,0536,0537,0540,0541,0542,0546,0547,0550,0554,0555,0556,0557,0558,0559,0560,0561,0562,0563,0564,0565,0580,0588,0589,0590,0591,0605,0616,0619,0620,0621,0622,0627,0628,0629,0631,0638,0640,0641,0642,0643,0644,0645,0646,0649,0650,0651,0653,0655,0656,0657,0659,0664,0665,0669,0671,0673,0674,0675,0677,0682,0683,0684,0685,0690,0698,0699,0708,0709,0711,0736,0737,0738,0746,0747,0755,0756,0757,0758,0766,0767,0768,0774,0775,0801,0802,0803,0804,0811,0817,0818,0821,0834,0835,0844,0845,0851,0852,0866,0873,0877,0940,0941,0943,0944,1023,1024,1025,1033,1047,1048,1050,1061,1062,1080,1087,1088,1089,1091,1092,1093,1095,1096,1112,1113,1117,1118,1120,1124,1125,1126,1127,1133,1150,1198,1199,1202,1203,1207,1208,1209,1211,1220,2025,3236,3237,3238,3244,3639,3640,3645,3646 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

struct rule_0101_struct
{
  int32_t a;
} ;

extern int16_t rule_0101( void )
{
   struct rule_0101_struct r;
   +r;                                                                /* expect: 0466  */
   return 0;
}

/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-23.4-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-23.4-C11: A generic association shall list an appropriate type
 *
 * Enforced by message(s):
 *   1128   The type in this '_Generic' association will never be
 *          considered for matching.
 *
 *
 *//* PRQA S 1128 -- *//*
 * <<<------------------------------------------------------------ */
#include "misra.h"
#include "mc25cmex.h"

#include <stdlib.h>

extern int16_t rule_2304 (void)
{
  typedef int Func (int);
  typedef int Array [10];
  typedef Func * FuncP;
  typedef Array * ArrayP;

  void r2304_handle_funcp (FuncP);
  void r2304_handle_array (int *);

  /* Non-compliant */
  #define handle_function_nc(X) _Generic((X) \
    , Func: r2304_handle_funcp (&(X))           \
    , FuncP: r2304_handle_funcp (X))

  /* Non-compliant */
  #define handle_array_nc(X) _Generic((X) \
    , Array: r2304_handle_array ((X) + 0)    \
    , ArrayP: r2304_handle_array (*(X))      \
    , default: r2304_handle_array (X))

  /* Compliant */
  #define handle_function(X) _Generic(((void)0, (X)) \
    , FuncP: r2304_handle_funcp (X))

  /* Compliant */
  #define handle_array(X) _Generic((X) + 0 \
    , int *: r2304_handle_array (X)           \
    , default: r2304_handle_array (X))

  {
    extern Func ef;
    Array ai;
    int * pi;
    Func * pf;

    handle_function_nc (ef);                  /* c11_expect:  1128 */
    handle_function_nc (pf);                  /* c11_expect:  1128 */
    handle_function (ef);                     /* c11_expect: !1128 */
    handle_function (pf);                     /* c11_expect: !1128 */

    handle_array_nc (ai);                     /* c11_expect:  1128 */
    handle_array_nc (pi);                     /* c11_expect:  1128 */
    handle_array (ai);                        /* c11_expect: !1128 */
    handle_array (pi);                        /* c11_expect: !1128 */
  }

  typedef int Int;
  typedef int const CInt;
  typedef int volatile VInt;

  extern void r2304_handle_const_intp (int const *);
  extern void r2304_handle_volatile_intp (int const *);
  extern void r2304_handle_other_value (void const *);

  /* Non-compliant */
  #define filter_const_nc(X) (_Generic((X)  \
    , CInt: r2304_handle_const_intp               \
    , default: r2304_handle_other_value) (&(X)))

  #define filter_cv_nc(X) (_Generic((X)  \
    , CInt: r2304_handle_const_intp            \
    , VInt: r2304_handle_volatile_intp         \
    , default: r2304_handle_other_value) (&(X)))

  /* Compliant */
  #define filter_const(X) (_Generic((X)  \
    , CInt *: r2304_handle_const_intp          \
    , Int *: r2304_handle_const_intp           \
    , default: r2304_handle_other_value) (X))

  #define filter_cv(X) (_Generic((X)  \
    , CInt *: r2304_handle_const_intp       \
    , VInt *: r2304_handle_volatile_intp    \
    , Int * : r2304_handle_other_value      \
    , default: r2304_handle_other_value) (&(X)))

  {
    Int ii;
    CInt ci;
    VInt vi;

    filter_const_nc (ii);                      /* c11_expect:  1128 */
    filter_const_nc (ci);                      /* c11_expect:  1128 */
    filter_const_nc (vi);                      /* c11_expect:  1128 */
    filter_cv_nc (ii);                         /* c11_expect:  1128 */
    filter_cv_nc (ci);                         /* c11_expect:  1128 */
    filter_cv_nc (vi);                         /* c11_expect:  1128 */
    filter_const (&ii);                        /* c11_expect: !1128 */
    filter_const (&ci);                        /* c11_expect: !1128 */
    filter_const (&vi);                        /* c11_expect: !1128 */
    filter_cv (ii);                            /* c11_expect: !1128 */
    filter_cv (ci);                            /* c11_expect: !1128 */
    filter_cv (vi);                            /* c11_expect: !1128 */
  }

  #define SizeofNonEmpty(A) (sizeof (A) > 1 ? sizeof (A) : 2)

  /* Non-compliant */
  #define only_strings_nc(X) (_Generic((X)                             \
    , char[SizeofNonEmpty (X)]: r2304_handle_sized_string (sizeof (X), (X))  \
    , char[1]: r2304_handle_null_terminator (1, (X))))

  /* Compliant */
  #define only_strings(X) (_Generic(&(X)                                    \
    , char (*) [SizeofNonEmpty (X)]: r2304_handle_sized_string (sizeof (X), (X))  \
    , char (*) [1]: r2304_handle_null_terminator (1, (X))))

  /* Compliant but wrong because of [1] */
  #define only_strings_wrong(X) (_Generic(&(X)                      \
    , char (*) [sizeof (X)]: r2304_handle_sized_string (sizeof (X), (X))  \
    , char (*) [1]: r2304_handle_null_terminator (1, (X))))

  extern void r2304_handle_sized_string (size_t, char const *);
  extern void r2304_handle_null_terminator (size_t, char const *);

  {
    char hello[] = "hello";
    char nil[1] = "";

    only_strings_nc (hello);         /* c11_expect: 1128x2 */
    only_strings_nc (nil);           /* c11_expect: 1128x2 */

    only_strings (hello);            /*        */
    only_strings (nil);              /*        */

    only_strings_wrong (hello);      /*        */
    only_strings_wrong (nil);        /*        */
  }

  {
    struct Tagged {
      int x;
    };

    typedef struct {
      int x;
    } Named;

    struct Tagged tagged;
    Named named;
    struct { int x; } unnamed;

    _Generic (tagged
      , struct Tagged : 1
      , Named : 2                  /* c11_expect: !1128 */
      , struct { int x; } : 3      /* c11_expect:  1128 */
      , default: 4);

    _Generic (named
      , struct Tagged : 1
      , Named : 2                  /* c11_expect: !1128 */
      , struct { int x; } : 3      /* c11_expect:  1128 */
      , default: 4);

    _Generic (unnamed
      , struct Tagged : 1
      , Named : 2                  /* c11_expect: !1128 */
      , struct { int x; } : 3      /* c11_expect:  1128 */
      , default: 4);
  }

  return 0;
}

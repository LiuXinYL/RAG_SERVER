/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-1.1-C11.c
 *
 * MISRA Required - C11 Specific Rules
 *
 * Rule-1.1-C11: The program shall contain no violations of the standard C syntax
 *               and constraints, and shall not exceed the implementation's
 *               translation limits
 *
 * Enforced by message(s):
 *   2050   The 'int' type specifier has been omitted from a function
 *          declaration.
 *
 *   2051   The 'int' type specifier has been omitted from an object
 *          declaration.
 *
 *   3335   No function declaration. Implicit declaration inserted: 'extern
 *          int ${name}();'.
 *
 *
 *//* PRQA S 2050,2051,3335 -- *//*
 * <<<------------------------------------------------------------ */

static f1 (void);                                          // expect: 2050

static void f2 (const x, char c);                          // expect: 2051

static f3 (void)                                           // expect: 2050
{
  return 0;
}

static void f2 (const x, char c)                           // expect: 2051
{

}

extern void Rule_0101_C11 (void)
{
  {
    typedef (* T) (void);                                  // expect: 2050

    static const x1 = 5;                                   // expect: 2051

    const        x2;                                       // expect: 2051

    volatile *   x3;                                       // expect: 2051

    extern       Rule_0101_x4;                             // expect: 2051
  }

  {
    extern void Rule_0101_C11_Declared (void);

    Rule_0101_C11_Declared ();                             // expect: !3335

    Rule_0101_C11_Undeclared ();                           // expect: 3335
  }
}

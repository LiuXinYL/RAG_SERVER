/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-8.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-8.2: Function types shall be in prototype form with named parameters
 *
 * Enforced by message(s):
 *   1335   Parameter identifiers missing in function prototype
 *          declaration.
 *
 *   1336   Parameter identifiers missing in declaration of a function
 *          type.
 *
 *   3001   Function has been declared with an empty parameter list.
 *
 *   3002   Defining '${name}()' with an identifier list and separate
 *          parameter declarations is an obsolescent feature.
 *
 *   3007   "void" has been omitted when defining a function with no
 *          parameters.
 *
 *
 *//* PRQA S 1335,1336,3001,3002,3007 -- *//*
 * <<<------------------------------------------------------------ */

#include <stdlib.h>
#include "misra.h"
#include "mc25cmex.h"

static int16_t  rule_0802_01();                            // expect: 3001

static int16_t  rule_0802_01()                             // expect: 3007
{
   return 1;
}

static int16_t  rule_0802_02();                            // expect: 3001

static int16_t  rule_0802_02(void)
{
   return 1;
}

static int16_t  rule_0802_03(void);

static int16_t  rule_0802_03( )                           // expect: 3007
{
   return 1;
}

static int16_t (*pfj)() = NULL;                            // expect: 3001


static int16_t rule_0802_04();                             // expect: 3001

static int16_t rule_0802_04(a)                             // expect: 3002
int16_t a;
{
   return a;
}

static int16_t rule_0802_05(int16_t a, int16_t b);

static int16_t rule_0802_05(a, b)                          // expect: 3002
int16_t a;
int16_t b;
{
   return a + b;
}

static float64_t rule_0802_06(float64_t d);

static float64_t rule_0802_06(d)                           // expect: 3002
float64_t d;
{
   return d;
}

static int16_t rule_0802_07(int16_t a);

static int16_t rule_0802_07(a)                             // expect: 3002
uint8_t a;
{
   return a;
}


static void rule_0802_08(int16_t);                         // expect: 1335
static void rule_0802_08(a)                                // expect: 3002
{
}

static void rule_0802_09(int16_t);                         // expect: 1335
static void rule_0802_09(a)                                // expect: 3002
    int16_t a;
{
}

static void rule_0802_10(int16_t a);                       // expect: none
static void rule_0802_10(a)                                // expect: 3002
{
}

static void rule_0802_11(int16_t a);                       // expect: none
static void rule_0802_11(a)                                // expect: 3002
    int16_t a;
{
}

static int16_t rule_0802_12();                             // expect: 3001
static int16_t rule_0802_12(m)                             // expect: 3002
    int16_t m;
{
    return m;
}

static int16_t rule_0802_13();                             // expect: 3001
static int16_t rule_0802_13(a,b)                           // expect: 3002
    int16_t a;
    int16_t b;
{
    return a*b;
}

static void rule_0802_14();                                // expect: 3001
static void rule_0802_14()                                 // expect: 3007
{
}

static void rule_0802_15();                                // expect: 3001
static void rule_0802_15(a)                                // expect: 3002
{
}

extern int16_t rule_0802( void )
{
   int16_t r = 1;

   r += rule_0802_01();
   r += rule_0802_02();
   r += rule_0802_03();
   r += rule_0802_04(1);
   r += rule_0802_05(1, 2);
   r += (int16_t)rule_0802_06(1.5);
   r += rule_0802_07(1);
   rule_0802_08(1);
   rule_0802_09(1);
   rule_0802_10(1);
   rule_0802_11(1);
   r += rule_0802_12(1);
   r += rule_0802_13(1, 2);
   rule_0802_14();
   rule_0802_15(1);

   return r;
}

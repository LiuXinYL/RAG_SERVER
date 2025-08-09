/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-10.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-10.3: The value of an expression shall not be assigned to an object with a
 *            narrower essential type or of a different essential type category
 *
 * Enforced by message(s):
 *   0570   This switch case label of 'essential type' '%1s', is not
 *          consistent with a controlling expression of essential type
 *          '%2s'.
 *
 *   0572   This switch case label of 'essential type' '%1s' is not
 *          consistent with a controlling expression which has an
 *          essential type of lower rank (%2s).
 *
 *   1157   This is converting a complex value to a real value.
 *
 *   1257   An integer constant suffixed with L or LL is being converted to
 *          a type of lower rank on assignment.
 *
 *   1264   A suffixed floating constant is being converted to a different
 *          floating type on assignment.
 *
 *   1265   An unsuffixed floating constant is being converted to a
 *          different floating type on assignment.
 *
 *   1266   A floating constant is being converted to integral type on
 *          assignment.
 *
 *   1291   An integer constant of 'essentially unsigned' type is being
 *          converted to signed type on assignment.
 *
 *   1292   An integer constant of 'essentially signed' type is being
 *          converted to type char on assignment.
 *
 *   1293   An integer constant of 'essentially unsigned' type is being
 *          converted to type char on assignment.
 *
 *   1294   An integer constant of 'essentially signed' type is being
 *          converted to type _Bool on assignment.
 *
 *   1295   An integer constant of 'essentially unsigned' type is being
 *          converted to type _Bool on assignment.
 *
 *   1296   An integer constant of 'essentially signed' type is being
 *          converted to enum type on assignment.
 *
 *   1297   An integer constant of 'essentially unsigned' type is being
 *          converted to enum type on assignment.
 *
 *   1298   An integer constant of 'essentially signed' type is being
 *          converted to floating type on assignment.
 *
 *   1299   An integer constant of 'essentially unsigned' type is being
 *          converted to floating type on assignment.
 *
 *   2850   Constant: Implicit conversion to a signed integer type of
 *          insufficient size.
 *
 *   2890   Constant: Negative value implicitly converted to an unsigned
 *          type.
 *
 *   2900   Constant: Positive integer value truncated by implicit
 *          conversion to a smaller unsigned type.
 *
 *   4401   An expression of 'essentially Boolean' type (%1s) is being
 *          converted to character type, '%2s' on assignment.
 *
 *   4402   An expression of 'essentially Boolean' type (%1s) is being
 *          converted to enum type, '%2s' on assignment.
 *
 *   4403   An expression of 'essentially Boolean' type (%1s) is being
 *          converted to signed type, '%2s' on assignment.
 *
 *   4404   An expression of 'essentially Boolean' type (%1s) is being
 *          converted to unsigned type, '%2s' on assignment.
 *
 *   4405   An expression of 'essentially Boolean' type (%1s) is being
 *          converted to floating type, '%2s' on assignment.
 *
 *   4410   An expression of 'essentially character' type (%1s) is being
 *          converted to Boolean type, '%2s' on assignment.
 *
 *   4412   An expression of 'essentially character' type (%1s) is being
 *          converted to enum type, '%2s' on assignment.
 *
 *   4413   An expression of 'essentially character' type (%1s) is being
 *          converted to signed type, '%2s' on assignment.
 *
 *   4414   An expression of 'essentially character' type (%1s) is being
 *          converted to unsigned type, '%2s' on assignment.
 *
 *   4415   An expression of 'essentially character' type (%1s) is being
 *          converted to floating type, '%2s' on assignment.
 *
 *   4420   An expression of 'essentially enum' type (%1s) is being
 *          converted to Boolean type, '%2s' on assignment.
 *
 *   4421   An expression of 'essentially enum' type (%1s) is being
 *          converted to character type, '%2s' on assignment.
 *
 *   4422   An expression of 'essentially enum' type (%1s) is being
 *          converted to a different enum type, '%2s' on assignment.
 *
 *   4423   An expression of 'essentially enum' type (%1s) is being
 *          converted to signed type, '%2s' on assignment.
 *
 *   4424   An expression of 'essentially enum' type (%1s) is being
 *          converted to unsigned type, '%2s' on assignment.
 *
 *   4425   An expression of 'essentially enum' type (%1s) is being
 *          converted to floating type, '%2s' on assignment.
 *
 *   4430   An expression of 'essentially signed' type (%1s) is being
 *          converted to Boolean type, '%2s' on assignment.
 *
 *   4431   An expression of 'essentially signed' type (%1s) is being
 *          converted to character type, '%2s' on assignment.
 *
 *   4432   An expression of 'essentially signed' type (%1s) is being
 *          converted to enum type, '%2s' on assignment.
 *
 *   4434   A non-constant expression of 'essentially signed' type (%1s) is
 *          being converted to unsigned type, '%2s' on assignment.
 *
 *   4435   A non-constant expression of 'essentially signed' type (%1s) is
 *          being converted to floating type, '%2s' on assignment.
 *
 *   4437   A constant expression of 'essentially signed' type (%1s) is
 *          being converted to floating type, '%2s' on assignment.
 *
 *   4440   An expression of 'essentially unsigned' type (%1s) is being
 *          converted to Boolean type, '%2s' on assignment.
 *
 *   4441   An expression of 'essentially unsigned' type (%1s) is being
 *          converted to character type, '%2s' on assignment.
 *
 *   4442   An expression of 'essentially unsigned' type (%1s) is being
 *          converted to enum type, '%2s' on assignment.
 *
 *   4443   A non-constant expression of 'essentially unsigned' type (%1s)
 *          is being converted to a wider signed type, '%2s' on
 *          assignment.
 *
 *   4445   An expression of 'essentially unsigned' type (%1s) is being
 *          converted to floating type, '%2s' on assignment.
 *
 *   4446   A non-constant expression of 'essentially unsigned' type (%1s)
 *          is being converted to signed type, '%2s' on assignment.
 *
 *   4447   A constant expression of 'essentially unsigned' type (%1s) is
 *          being converted to signed type, '%2s' on assignment.
 *
 *   4450   An expression of 'essentially floating' type (%1s) is being
 *          converted to Boolean type, '%2s' on assignment.
 *
 *   4451   An expression of 'essentially floating' type (%1s) is being
 *          converted to character type, '%2s' on assignment.
 *
 *   4452   An expression of 'essentially floating' type (%1s) is being
 *          converted to enum type, '%2s' on assignment.
 *
 *   4453   An expression of 'essentially floating' type (%1s) is being
 *          converted to signed type, '%2s' on assignment.
 *
 *   4454   An expression of 'essentially floating' type (%1s) is being
 *          converted to unsigned type, '%2s' on assignment.
 *
 *   4460   A non-constant expression of 'essentially signed' type (%1s) is
 *          being converted to narrower signed type, '%2s' on
 *          assignment.
 *
 *   4461   A non-constant expression of 'essentially unsigned' type (%1s)
 *          is being converted to narrower unsigned type, '%2s' on
 *          assignment.
 *
 *   4462   A non-constant expression of 'essentially floating' type (%1s)
 *          is being converted to narrower floating type, '%2s' on
 *          assignment.
 *
 *   4463   A constant expression of 'essentially signed' type (%1s) is
 *          being converted to narrower signed type, '%2s' on
 *          assignment.
 *
 *   4464   A constant expression of 'essentially unsigned' type (%1s) is
 *          being converted to narrower unsigned type, '%2s' on
 *          assignment.
 *
 *   4465   A constant expression of 'essentially floating' type (%1s) is
 *          being converted to narrower floating type, '%2s' on
 *          assignment.
 *
 *
 *//* PRQA S 0570,0572,1157,1257,1264,1265,1266,1291,1292,1293,1294,1295,1296,1297,1298,1299,2850,2890,2900,4401,4402,4403,4404,4405,4410,4412,4413,4414,4415,4420,4421,4422,4423,4424,4425,4430,4431,4432,4434,4435,4437,4440,4441,4442,4443,4445,4446,4447,4450,4451,4452,4453,4454,4460,4461,4462,4463,4464,4465 -- *//*
 * <<<------------------------------------------------------------ */
#include <stdbool.h>
#include "misra.h"
#include "mc25cmex.h"

BL r1003_bla;
PC r1003_pca;
SC r1003_sca;
N1 r1003_n1a;
N2 r1003_n2a;
int32_t r1003_sia;
uint32_t r1003_uia;
uint32_t r1003_uib;
SL r1003_sla;
float32_t r1003_fta;
float64_t r1003_f64a;
float128_t r1003_f128a;
float128_t r1003_f128b;
int16_t r1003_s16a;
int16_t r1003_s16b;
int8_t r1003_s8a;
uint16_t r1003_u16a;
uint16_t r1003_u16b;
uint8_t r1003_u8a;


extern int16_t rule_1003_from_Boolean( void )
{
    r1003_pca = r1003_bla;                                            /* expect: 4401 */
    r1003_n1a = r1003_bla;                                            /* expect: 4402 */
    r1003_sia = r1003_bla;                                            /* expect: 4403 */
    r1003_uia = r1003_bla;                                            /* expect: 4404 */
    r1003_fta = r1003_bla;                                            /* expect: 4405 */
    r1003_sca = 130;                                                  /* expect: 2850 */

    return 0;
}

extern int16_t rule_1003_from_character( void )
{
    r1003_bla = r1003_pca;                                            /* expect: 4410 */
    r1003_n1a = r1003_pca;                                            /* expect: 4412 */
    r1003_s16a = r1003_pca;                                           /* expect: 4413 */
    r1003_u16a = r1003_pca;                                           /* expect: 4414 */
    r1003_fta = r1003_pca;                                            /* expect: 4415 */

    return 0;
}

extern int16_t rule_1003_from_enum( void )
{
    r1003_bla = r1003_n1a;                                            /* expect: 4420 */
    r1003_pca = r1003_n1a;                                            /* expect: 4421 */
    r1003_n2a = AMBER;                                                /* expect: 4422 */
    r1003_s16a = r1003_n1a;                                           /* expect: 4423 */
    r1003_u16a = r1003_n1a;                                           /* expect: 4424 */
    r1003_fta = r1003_n1a;                                            /* expect: 4425 */
    return 0;
}

extern int16_t rule_1003_from_floating( void )
{
    r1003_bla = 0.0;                                                  /* expect: 1266 */
    r1003_bla = r1003_fta;                                            /* expect: 4450 */
    r1003_pca = r1003_fta;                                            /* expect: 4451 */
    r1003_n1a = r1003_fta;                                            /* expect: 4452 */
    r1003_s16a = r1003_fta;                                           /* expect: 4453 */
    r1003_u16a = r1003_fta;                                           /* expect: 4454 */

    return 0;
}

#define EXPA 23L
#define EXPB (23 + 46)
#define EXPC (-1)
#define EXPD (r1003_s16a + r1003_s16b)
extern int16_t rule_1003_from_signed( void )
{
    r1003_pca = EXPA;                                                 /* expect: 1292 1257 */
    r1003_bla = EXPA;                                                 /* expect: 1294 1257 */
    r1003_n1a = EXPA;                                                 /* expect: 1296      */
    r1003_fta = EXPA;                                                 /* expect: 1298      */
    r1003_u16a = (EXPC);                                              /* expect: 2890      */
    r1003_bla = EXPB;                                                 /* expect: 4430      */
    r1003_pca = EXPB;                                                 /* expect: 4431      */
    r1003_n1a = EXPB;                                                 /* expect: 4432      */
    r1003_u16a = EXPD;                                                /* expect: 4434      */
    r1003_fta = EXPD;                                                 /* expect: 4435      */
    r1003_fta = EXPB;                                                 /* expect: 4437      */

    return 0;
}

#define EXP1 23UL
#define EXP2 (23u+46u)
#define EXP3 (r1003_u8a)
#define EXP4 r1003_uia

extern int16_t rule_1003_from_unsigned( void )
{
    r1003_s16a = EXP1;                                                /* expect: 1291 1257 */
    r1003_pca = EXP1;                                                 /* expect: 1293 1257 */
    r1003_bla = EXP1;                                                 /* expect: 1295 1257 */
    r1003_n1a = EXP1;                                                 /* expect: 1297 */
    r1003_fta = EXP1;                                                 /* expect: 1299 */
    r1003_bla = EXP2;                                                 /* expect: 4440 */
    r1003_pca = EXP2;                                                 /* expect: 4441 */
    r1003_n1a = EXP2;                                                 /* expect: 4442 */
    r1003_sla = EXP3;                                                 /* expect: 4443 */
    r1003_fta = EXP2;                                                 /* expect: 4445 */
    r1003_s16a = EXP4;                                                /* expect: 4446 */
    r1003_s16a = EXP2;                                                /* expect: 4447 */

    return 0;
}


extern int16_t rule_1003_narrow_signed( void )
{
    r1003_s16a = 23L;                                                 /* expect: 1257 */
    r1003_s8a = 1L + 23LL;
    r1003_s8a = r1003_sla;                                            /* expect: 4460 */

    return 0;
}

extern int16_t rule_1003_narrow_floating( void )
{
    r1003_fta = 9.28L;                                                /* expect: 1264 */
    r1003_fta = 0.0;                                                  /* expect: 1265 */
    r1003_fta = (r1003_f128a+r1003_f128b);                            /* expect: 4462 */
    r1003_fta = (23.45L + 34.56L);                                    /* expect: 4465 */

    return 0;
}

extern int16_t rule_1003_narrow_unsigned( void )
{
    r1003_u8a = 300U;                                                 /* expect: 2900 */
    r1003_u8a = r1003_uia;                                            /* expect: 4461 */
    r1003_u8a = 1UL+23UL;                                             /* expect: 4464 */

    return 0;
}


extern int16_t rule_1003_switch( void )
{
    switch (r1003_u8a)
    {
    case 10UL:                                                        /* expect: 0572 */
        break;
    default:
        break;
    }

    switch (r1003_sia)
    {
    case 1U:                                                          /* expect: 0570 */
        break;
    default:
        break;
    }
    return 0;
}

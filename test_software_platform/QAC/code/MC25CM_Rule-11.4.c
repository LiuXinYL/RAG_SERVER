/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-11.4.c
 *
 * MISRA Advisory - Rules
 *
 * Rule-11.4: A conversion shall not be performed between a pointer to object and
 *            an arithmetic type
 *
 * Enforced by message(s):
 *   0301   Cast between a pointer to object and a floating type.
 *
 *   0303   Cast between a pointer to volatile object and an integral type.
 *
 *   0306   Cast between a pointer to object and an integral type.
 *
 *   0328   Cast between a pointer to object and an essential type other
 *          than signed/unsigned.
 *
 *   0360   An expression of pointer type is being converted to type _Bool
 *          on assignment.
 *
 *   0361   An expression of pointer type is being cast to type _Bool.
 *
 *   0362   An expression of essentially Boolean type is being cast to a
 *          pointer.
 *
 *   0376   Cast between a pointer to object type and an integral type that
 *          makes use of the intptr_t or uintptr_t typedef.
 *
 *
 *//* PRQA S 0301,0303,0306,0328,0360,0361,0362,0376 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

BL r1104_bla;
uint32_t r1104_uia;

extern int16_t rule_1104 ( void )
{
    volatile uint16_t * pvui;
             uint16_t * puim;
    volatile uint16_t vui = r1104_uia;
    pvui = (volatile uint16_t *) 0x1234U;                             /* expect: 0303 */
    puim = (uint16_t *) 0x1234U;                                      /* expect: 0306 */
    r1104_bla = puim;                                                 /* expect: 0360 */
    r1104_bla = (_Bool)puim;                                          /* expect: 0361 */
    puim = (uint16_t *) r1104_bla;                                    /* expect: 0328,0362 */


    return 0;
}

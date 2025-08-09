/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-4.2.c
 *
 * MISRA Advisory - Directives
 *
 * Dir-4.2: All usage of assembly language should be documented
 *
 * Assisted by message(s):
 *   1003   '#${directive}' is a language extension for in-line assembler.
 *          All statements located between #asm and #endasm will be
 *          ignored.
 *
 *   1006   This in-line assembler construct is a language extension. The
 *          code has been ignored.
 *
 *
 *//* PRQA S 1003,1006 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

int16_t s16a_d0402;

static asm int16_t dir_0402a (void)                                   /* expect: 1006 */
{
  The body of this function will be ignored.
}

static int16_t asm dir_0402b (void)                                   /* expect: 1006 */
{
  The body of this function will be ignored.
}

static int16_t __asm dir_0402c (void)                                 /* expect: 1006 */
{
  The body of this function will be ignored.
}

#pragma inline_asm dir_0402d
static int16_t dir_0402d (void)                                       /* expect: 1006 */
{
  The body of this function will be ignored.
}

static int16_t dir_0402e (void)
{
  const int16_t r = s16a_d0402 + 1;

  asm { ... Assembler ...}                                            /* expect: 1006 */

  __asm { ... Assembler ... }                                         /* expect: 1006 */

  asm( Assembler Statements );                                        /* expect: 1006 */

#asm                                                                  /* expect: 1003 */

  Any assembler statements
  will be ignored in this block

#endasm                                                               /* expect: 1003 */

  /* Non-block assembly directives */
  #asm ("Assembler line statement 1")                                 /* expect: 1003 */
  #asm ("Assembler line statement 2")                                 /* expect: 1003 */

  return r;
}

#define DIR_0402F() asm { ... Assembler ... }
static int16_t dir_0402f (void)
{
  int16_t ret_d0402f = s16a_d0402;
  DIR_0402F ();                                                       /* expect: 1006 */
  return ret_d0402f;
}

extern int16_t dir_0402 (void)
{
  int16_t ret_d0402 = s16a_d0402;

  ret_d0402 += dir_0402a ();
  ret_d0402 += dir_0402b ();
  ret_d0402 += dir_0402c ();
  ret_d0402 += dir_0402d ();
  ret_d0402 += dir_0402e ();
  ret_d0402 += dir_0402f ();

  return ret_d0402;
}

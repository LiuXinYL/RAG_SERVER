/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-4.3.c
 *
 * MISRA Required - Directives
 *
 * Dir-4.3: Assembly language shall be encapsulated and isolated
 *
 * Assisted by message(s):
 *   3006   This function contains a mixture of in-line assembler
 *          statements and C statements.
 *
 *   3008   This function contains a mixture of in-line assembler
 *          statements and C code.
 *
 *
 *//* PRQA S 3006,3008 -- *//*
 * <<<------------------------------------------------------------ */


/*********************************************************************
INLINE ASSEMBLER EXTENSIONS

1. The assembler extensions option (-ex asm) is accessed through the Project
   properties in the QA GUI. This option enables QAC to parse (and ignore) the
   following constructs:

   a. A function defined with the keywords asm or __asm in its prototype
      will be ignored. (Message 1006)
   b. Assembler code blocks introduced by the keywords asm and
      __asm will be ignored. (Message 1006)
   c. In-line assembler statements of the form asm(...); will be
      ignored.  (Message 1006)
   d. Blocks of statements enclosed between the directives
      #asm and #endasm will be ignored. (Message 1003)

2. Assembler statements can also be ignored by QAC if they are
   located between two #pragma directives which have been declared
   as a #pragma block using the -skippragma option (Analysis tab in Project Properties).

*********************************************************************/

#include "misra.h"
#include "mc25cmex.h"

int16_t s16a_d0403;
int16_t s16b_d0403;

static int16_t dir_0403a (void)                                       /* expect: 3006 */
{
  int16_t ret_d0403a;
  ret_d0403a = s16a_d0403;
  asm { .. Assembler ...}
  return ret_d0403a;
}

static int16_t dir_0403b (void)                                       /* expect: 3008 */
{
  int16_t ret_d0403b;
  /* No "effectful" C statements */
  asm { .. Assembler ...}
  return ret_d0403b;
}

static int16_t dir_0403c (void)                                       /* expect: 3006 */
{
  int16_t ret_d0403c;
  ret_d0403c = s16a_d0403;

  __asm { ... Assembler ... }

#asm

  Any assembler statements
  will be ignored in this block

#endasm

  #asm ("Assembler line (non-block)");
  #asm ("Assembler line (non-block)");

  return ret_d0403c;
}

/* Placing only assembly code inside a macro "encapsulates" it */
#define AM1 asm {... Assembler ...}
/* The macro can be nested in C code macros without breaking encapsulation */
#define AM2 do { AM1; s16b_d0403 = s16a_d0403; AM1; } while (0)

static int16_t dir_0403d (void)                                       /* expect: !3006,!3008 */
{
  int16_t ret_d0403d;
  ret_d0403d = s16a_d0403;
  AM1;
  AM2;
  return ret_d0403d;
}

/* Assembly and C code in the same macro does not "encapsulate" the assembly */
#define AM3(RET) do { asm {... Assembler ...}; RET = 0; } while (0)

static int16_t dir_0403e (void)                                       /* expect: 3006 */
{
  int16_t ret_d0403e;
  ret_d0403e = s16a_d0403;
  AM3 (ret_d0403e);
  return ret_d0403e;
}

/* ...even if the C code has no side effects */
#define AM4(RET) int16_t RET; asm {... Assembler ...}

static int16_t dir_0403f (void)                                       /* expect: 3008 */
{
  int16_t ret_d0403f;
  AM4 (scratch_d0403f);
  return ret_d0403f;
}

/* Placing assembly code in an assembly-function "encapsulates" it fully */
static asm int16_t dir_0403g (void)                                   /* expect: !3006,!3008 */
{
  Any content in this function will be ignored
}

#pragma inline_asm dir_0403h
static int16_t dir_0403h (void)                                       /* expect: !3006,!3008 */
{
  Any content in this function will be ignored
}

/* Pure C functions can call asm functions to use fully-encapsulated assembly */
static int16_t dir_0403i (void)                                       /* expect: !3006,!3008 */
{
  return dir_0403g () + dir_0403h ();
}

extern int16_t dir_0403 (void)                                        /* expect: !3006,!3008 */
{
  int16_t ret_d0403 = 1;

  ret_d0403 += dir_0403a();
  ret_d0403 += dir_0403b();
  ret_d0403 += dir_0403c();
  ret_d0403 += dir_0403d();
  ret_d0403 += dir_0403e();
  ret_d0403 += dir_0403f();
  ret_d0403 += dir_0403i();

  return ret_d0403;
}

/* >>>------------------------------------------------------------
 *
 * Tgt_File: fenv.h
 *
 * <<<------------------------------------------------------------ */


/* PRQA S 5136 EOF */

#ifndef FENV_H
#define FENV_H

typedef struct
{
   unsigned int __control;
} fenv_t;

typedef unsigned int fexcept_t;

#define FE_INVALID      0x01
#define FE_DIVBYZERO    0x04
#define FE_OVERFLOW     0x08
#define FE_UNDERFLOW    0x10
#define FE_INEXACT      0x20
#define FE_ALL_EXCEPT   (FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW | FE_INEXACT)
#define FE_TONEAREST    0x0000
#define FE_DOWNWARD     0x0400
#define FE_UPWARD       0x0800
#define FE_TOWARDZERO   0x0c00
#define FE_DFL_ENV      ((const fenv_t *) 0)

#endif

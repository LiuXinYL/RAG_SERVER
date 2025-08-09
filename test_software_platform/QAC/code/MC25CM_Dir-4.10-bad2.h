/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-4.10-bad2.h
 *
 * MISRA Required - Directives
 *
 * Dir-4.10: Precautions shall be taken in order to prevent the contents of a
 *           header file being included more than once
 *
 * Assisted by message(s):
 *   0883   Include file code is not protected against repeated inclusion
 *
 *
 *//* PRQA S 0883 -- *//*
 * <<<------------------------------------------------------------ */


#ifdef DIR_0410_BAD2_H
#error Multiple inclusion not allowed!
#else
#define DIR_0410_BAD2_H

#include "misra.h"

typedef int32_t bad2;

#endif                                                                /* expect: 0883 */

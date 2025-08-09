/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-4.10.c
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


#include "misra.h"
#include "mc25cmex.h"

#include "MC25CM_Dir-4.10-ok1.h"
#include "MC25CM_Dir-4.10-ok2.h"
#include "MC25CM_Dir-4.10-bad1.h"
#include "MC25CM_Dir-4.10-bad2.h"
#include "MC25CM_Dir-4.10-bad3.h"
extern int16_t dir_0410 (void)
{
  return 1;
}

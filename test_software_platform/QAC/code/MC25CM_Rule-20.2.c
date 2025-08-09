/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-20.2.c
 *
 * MISRA Required - Rules
 *
 * Rule-20.2: The ', " or \ characters and the /* or // character sequences shall
 *            not occur in a header file name
 *
 * Enforced by message(s):
 *   0813   Using any of the characters ' " or /* in '#include <%s>' gives
 *          undefined behaviour.
 *
 *   0814   Using the characters ' or /* in '#include "%s"' gives undefined
 *          behaviour.
 *
 *   0831   Use of '\\' in this '#include' line is a PC extension - this
 *          usage is non-portable.
 *
 *
 *//* PRQA S 0813,0814,0831 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

// The header files referred to in the #include directives here below are not
// included in the project, because they may be rejected by the underlying
// operating system to start with. QAC reports the absence of #include files
// through the generation of additional configuration error (level 9) messages.
// This is intentional, and does not affect the behaviour of messages that are
// applicable to file name format.

#define HAVE_FILES_WITH_NON_STANDARD_NAMES  false
#define ALLOW_CONFIGURATION_ERROR_MESSAGES  false

#if HAVE_FILES_WITH_NON_STANDARD_NAMES || ALLOW_CONFIGURATION_ERROR_MESSAGES

#include <John's.h>                          // conditional-expect: 0813

#include <Fred.h/*temporary*/>               // conditional-expect: 0813

#include "John's.h"                          // conditional-expect: 0814

#include "Fred.h/*temporary*/"               // conditional-expect: 0814

#include ".\abc.h"                           // conditional-expect: 0831

#endif

extern int16_t rule_2002 (void)
{
  return 1;
}

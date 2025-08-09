/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-9.7.h
 *
 * MISRA Mandatory - C11 Specific Rules
 *
 * Rule-9.7: Atomic objects shall be appropriately initialized before being
 *           accessed
 *
 * Enforced by message(s):
 *   4836   Definite: The C Atomic object is accessed before being
 *          initialised.
 *
 *   4837   Apparent: The C Atomic object is accessed before being
 *          initialised.
 *
 *   4838   Suspicious: The C Atomic object is accessed before being
 *          initialised.
 *
 *
 *//* PRQA S 4836,4837,4838 -- *//*
 * <<<------------------------------------------------------------ */
#pragma once

#include "mc25cmex.h"

#define atomic_init(obj, value) ((void) ((* (obj)) = (value)))

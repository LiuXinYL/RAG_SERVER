/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Dir-4.8.c
 *
 * MISRA Advisory - Directives
 *
 * Dir-4.8: If a pointer to a structure or union is never dereferenced within a
 *          translation unit, then the implementation of the object should be
 *          hidden
 *
 * Assisted by message(s):
 *   3630   The implementation of this struct/union type should be hidden.
 *
 *
 *//* PRQA S 3630 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"

typedef struct dir_0408_OpaqueType * dir_0408_pOpaqueType;

extern dir_0408_pOpaqueType dir_0408_GetObject(void);
extern void dir_0408_UseObject(const dir_0408_pOpaqueType p);

struct dir_0408_Not_OpaqueType                                          /* expect: 3630 */
{
  int32_t c;
  int32_t d;
};
typedef struct dir_0408_Not_OpaqueType * dir_0408_pNot_OpaqueType;

extern dir_0408_pNot_OpaqueType dir_0408_GetObject_notop(void);
extern void UseObject_notop(const dir_0408_pNot_OpaqueType p);

extern int16_t dir_0408(void)
{
  dir_0408_pOpaqueType pObject;
  pObject = dir_0408_GetObject ();
  dir_0408_UseObject (pObject);

  dir_0408_pNot_OpaqueType pObject2;
  pObject2 = dir_0408_GetObject_notop ();
  UseObject_notop (pObject2);

  return 1;
}

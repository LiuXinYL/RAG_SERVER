/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-6.3.c
 *
 * MISRA Required - Rules
 *
 * Rule-6.3: A bit field shall not be declared as a member of a union
 *
 * Enforced by message(s):
 *   3622   A bit-field is being defined as a member of a union.
 *
 *
 *//* PRQA S 3622 -- *//*
 * <<<------------------------------------------------------------ */


#include "misra.h"
#include "mc25cmex.h"


union U1 {
  uint8_t small;                    /* expect:!3622 */
  uint32_t big;                     /* expect:!3622 */
};

union U2 {
  uint32_t small:8;                 /* expect: 3622 */
  uint32_t big;                     /* expect:!3622 */
};

union U3 {
  uint32_t small:8;                 /* expect: 3622 */
  uint32_t big:24;                  /* expect: 3622 */
};

union U4 {
  struct
  {
    uint8_t a:4;                    /* expect:!3622 */
    uint8_t b:4;                    /* expect:!3622 */
    uint8_t c:4;                    /* expect:!3622 */
    uint8_t d:4;                    /* expect:!3622 */
  } q;
  uint16_t r;
};

struct S5 {
  uint16_t r;
  union {
    uint16_t a:4;                   /* expect: 3622 */
    uint16_t b:4;                   /* expect: 3622 */
    uint16_t c:4;                   /* expect: 3622 */
    uint16_t d:4;                   /* expect: 3622 */
  };
};

union U6 {
  uint16_t r;
  struct {
    uint16_t a:4;                   /* expect:!3622 */
    uint16_t b:4;                   /* expect:!3622 */
    uint16_t c:4;                   /* expect:!3622 */
    uint16_t d:4;                   /* expect:!3622 */
  };
};

extern int16_t rule_0603( void )
{
    union r0602_T01 t01;
    union r0602_T02 t02;
    union r0602_T03 t03;
    union r0602_T04 t04;
    struct r0602_T05 t05;
    union r0602_T06 t06;

    return 0;
}

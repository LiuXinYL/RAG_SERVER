/* PRQA S 1-9999 ++ */
/* >>>------------------------------------------------------------
 *
 * File: MC25CM_Rule-21.6.c
 *
 * MISRA Required - Rules
 *
 * Rule-21.6: The Standard Library input/output functions shall not be used
 *
 * Enforced by message(s):
 *   5124   The Standard Library input/output functions shall not be used
 *
 *   5129   The Standard Library input/output functions sprintf, sscanf,
 *          and vsprintf shall not be used
 *
 *
 *//* PRQA S 5124,5129 -- *//*
 * <<<------------------------------------------------------------ */


#include <stdio.h>

#include "misra.h"
#include "mc25cmex.h"
#include "stdarg.h"

char buffer_2106[BUFSIZ];
int32_t s32a_2106;

void vsprintf_test(char *format, ...) {
  va_list args;
  va_start(args, format);
  vsprintf(buffer_2106, format, args);                                /* expect: 5129 */
  va_end(args);
}

extern int16_t rule_2106 ()
{
  printf ("hello\n");                                                 /* expect: 5124 */


  remove ("filename");                                                /* expect: 5124 */
  rename ("oldname", "newname");                                      /* expect: 5124 */

  FILE * tmp_2106 = tmpfile ();                                       /* expect: 5124 */
  char tmp_name[L_tmpnam];
  tmpnam (tmp_name);                                                  /* expect: 5124 */

  FILE * file_2106 = fopen ("file", "w+");                            /* expect: 5124 */
  fflush (file_2106);                                                 /* expect: 5124 */
  file_2106 = freopen ("file", "w+", file_2106);                      /* expect: 5124 */
  fclose (file_2106);                                                 /* expect: 5124 */
  file_2106 = tmp_2106;

  setbuf (file_2106, buffer_2106);                                    /* expect: 5124 */
  setvbuf (file_2106, buffer_2106, _IOFBF, BUFSIZ);                   /* expect: 5124 */

  fprintf (stdout, "hello %d\n", s32a_2106);                          /* expect: 5124 */
  fscanf (stdin, "%d", &s32a_2106);                                   /* expect: 5124 */
  printf ("hello %d\n", s32a_2106);                                   /* expect: 5124 */
  scanf ("%d", &s32a_2106);                                           /* expect: 5124 */

  char buf2_2106[128];

  s32a_2106 = fgetc (stdin);                                          /* expect: 5124 */
  fgets (buf2_2106, 1, file_2106);                                    /* expect: 5124 */
  fputc ('c', file_2106);                                             /* expect: 5124 */
  fputs ("s", file_2106);                                             /* expect: 5124 */
  s32a_2106 = getc (file_2106);                                       /* expect: 5124 */
  s32a_2106 = getchar ();                                             /* expect: 5124 */
  gets (buf2_2106);                                                   /* expect: 5124 */
  putc ('c', file_2106);                                              /* expect: 5124 */
  putchar ('c');                                                      /* expect: 5124 */
  puts ("s");                                                         /* expect: 5124 */
  ungetc ('c', file_2106);                                            /* expect: 5124 */
  fread (buf2_2106, 1, sizeof(buf2_2106), file_2106);                 /* expect: 5124 */
  fwrite (buf2_2106, 1, sizeof(buf2_2106), file_2106);                /* expect: 5124 */

  fpos_t pos_2106;
  fgetpos (file_2106, pos_2106);                                      /* expect: 5124 */
  fseek (file_2106, 1, SEEK_CUR);                                     /* expect: 5124 */
  fsetpos (file_2106, pos_2106);                                      /* expect: 5124 */

  s32a_2106 = ftell (file_2106);                                      /* expect: 5124 */
  rewind (file_2106);                                                 /* expect: 5124 */
  clearerr (file_2106);                                               /* expect: 5124 */
  s32a_2106 = feof (file_2106);                                       /* expect: 5124 */
  s32a_2106 = ferror (file_2106);                                     /* expect: 5124 */
  perror ("error");                                                   /* expect: 5124 */

  sprintf (buf2_2106, "hi");                                          /* expect: 5129 */

  char  tokens[] = "42";
  int i;
  sscanf (tokens, "%d", &i);                                          /* expect: 5129 */

  vsprintf_test ("%d", i);

  return 1;
}

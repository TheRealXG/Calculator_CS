/*+ FILE DESCRIPTION -------------------------------------------------------
Filename:    srvport.h
Description: Integration porting implementation: system functions declaration

Copyright (C) 2020 ANSYS, Inc. ALL RIGHTS RESERVED.
Copyright (C) 2018 ESTEREL TECHNOLOGIES SAS. ALL RIGHTS RESERVED.
This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.

Warranty
ANSYS, Inc. makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose
---------------------------------------------------------------------------- +*/

#ifndef _SRVPORT_H
#define _SRVPORT_H

#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#include <math.h>

#include <a661_error_mgmt.h>

#define SRVPORT_ULONG_MAX ULONG_MAX
#define SRVPORT_LONG_MAX LONG_MAX
#define SRVPORT_INT_MAX INT_MAX

#define srvport_atan(v) (a661_float) (atan(v) * 57.2957795130823208767981548141F /* 180/pi */)
#define srvport_abs(v) (a661_float) fabs(v)
#define srvport_sqrt(v) (a661_float) sqrt(v)

#define srvport_fopen_r(name) fopen(name,"r")
#define srvport_fopen_rb(name) fopen(name,"rb")
#define srvport_fclose(fd) fclose(fd)

#define srvport_fgetc(f) fgetc(f)
#define srvport_fread(ptr, sz, nb, f) fread(ptr, sz, nb, f)
#define srvport_fseek_cur(f, o) fseek(f, o, SEEK_CUR)
#define srvport_fseek_set(f, o) (void) fseek(f, o, SEEK_SET)
#define srvport_fseek_end(f, o) (void) fseek(f, o, SEEK_END)
#define srvport_ftell(f) ftell(f)

#define srvport_print_err0(err) (void) fprintf(stderr,err)
#define srvport_print_err1(err,p1) (void) fprintf(stderr,err,p1)
#define srvport_print_err2(err,p1,p2) (void) fprintf(stderr,err,p1,p2)
#define srvport_print_err3(err,p1,p2,p3) (void) fprintf(stderr,err,p1,p2,p3)
#define srvport_print_err4(err,p1,p2,p3,p4) (void) fprintf(stderr,err,p1,p2,p3,p4)
#define srvport_print_err5(err,p1,p2,p3,p4,p5) (void) fprintf(stderr,err,p1,p2,p3,p4,p5)
#define srvport_print_err6(err,p1,p2,p3,p4,p5,p6) (void) fprintf(stderr,err,p1,p2,p3,p4,p5,p6)

#define srvport_print0(str) (void) printf(str)
#define srvport_print1(str,p1) (void) printf(str,p1)
#define srvport_print2(str,p1,p2) (void) printf(str,p1,p2)
#define srvport_print3(str,p1,p2,p3) (void) printf(str,p1,p2,p3)

#define srvport_print_buf1(b,str,p1) (void) sprintf(b,str,p1)

#define srvport_iswhitespacechar(c) isspace(c)
#define srvport_strcpy(d,s) (void) strcpy(d,s)
#define srvport_strncpy(d,s,l) (void) strncpy(d,s,l)
#define srvport_strstr(h,n) strstr(h,n)
#define srvport_strlen(s) strlen(s)

#define srvport_memcpy(d,s,l) (void) memcpy(d,s,l)
#define srvport_memmove(d,s,l) (void) memmove(d,s,l)

a661_uchar srvport_str2integer(const char *value, a661_long * result);
a661_uchar srvport_str2unsigned(const char *value, a661_ulong * result);
a661_uchar srvport_str2bool(const char *value, a661_uchar * result);
a661_uchar srvport_str2float(const char *value, a661_float * result);

void srvport_exit(int code);

#endif                          /* _SRVPORT_H */

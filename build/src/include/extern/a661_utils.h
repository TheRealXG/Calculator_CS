/*+ FILE DESCRIPTION -------------------------------------------------------
Filename:    a661_utils.h
Description: Integration porting API: utilities

Copyright (C) 2020 ANSYS, Inc. ALL RIGHTS RESERVED.
Copyright (C) 2011 ESTEREL TECHNOLOGIES SAS. ALL RIGHTS RESERVED.
This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.

Warranty
ANSYS, Inc. makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose
---------------------------------------------------------------------------- +*/

#ifndef A661_UTILS_H
#define A661_UTILS_H

#include <stddef.h>

void a661_sort(void *base, size_t nel, size_t width, int (*compar) (const void *, const void *));

a661_ushort a661_strlen(const a661_string s);
a661_ulong a661_strnlen(const a661_string s, a661_ulong max);

int a661_streq (const char *a, const char *b);

#endif                          /* A661_UTILS_H */

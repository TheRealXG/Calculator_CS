/*+ FILE DESCRIPTION -------------------------------------------------------
Filename:    a661_mem.h
Description: Integration porting API: memory allocation 

Copyright (C) 2020 ANSYS, Inc. ALL RIGHTS RESERVED.
Copyright (C) 2011 ESTEREL TECHNOLOGIES SAS. ALL RIGHTS RESERVED.
This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.

Warranty
ANSYS, Inc. makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose
---------------------------------------------------------------------------- +*/

#ifndef A661_MEM_H
#define A661_MEM_H

#include <a661_types.h>

void *a661_malloc(const char_t * msg, a661_ulong sz);

#if KCGOGLXVER >= 6640
void a661_free(void *mem);
#endif

#endif                          /* A661_MEM_H */

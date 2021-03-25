/*+ FILE DESCRIPTION -------------------------------------------------------
Filename:    a661_error.h
Description: Server Core API: errors management

Copyright (C) 2020 ANSYS, Inc. ALL RIGHTS RESERVED.
Copyright (C) 2011 ESTEREL TECHNOLOGIES SAS. ALL RIGHTS RESERVED.
This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.

Warranty
ANSYS, Inc. makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose
---------------------------------------------------------------------------- +*/

#ifndef A661_ERROR_H
#define A661_ERROR_H

#include <a661_types.h>
#include <a661_keywords.h>

typedef enum {
    A661_BLOCK_BUFFER_CONTINUE,
    A661_BLOCK_BUFFER_FINISHED,
    A661_BLOCK_BUFFER_FULL
} a661_block_buffer_status;


typedef a661_ushort a661_error;

#define A661_NO_ERROR ((a661_ushort)0x0000)

#endif                          /* A661_ERROR_H */

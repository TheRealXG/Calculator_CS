/*+ FILE DESCRIPTION -------------------------------------------------------
Filename:    a661_data_buffer.h
Description: Server Core API: memory buffer management

Copyright (C) 2020 ANSYS, Inc. ALL RIGHTS RESERVED.
Copyright (C) 2011 ESTEREL TECHNOLOGIES SAS. ALL RIGHTS RESERVED.
This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.

Warranty
ANSYS, Inc. makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose
---------------------------------------------------------------------------- +*/

#ifndef A661_DATA_BUFFER_H
#define A661_DATA_BUFFER_H

#include "a661_types.h"

typedef enum
{
    A661_DATA_OK  = 0,
    A661_DATA_ERR = 1
} a661_data_error_t;

/*
// If the host/target is not allowed to perform runtime 
// memory allocation (e.g., malloc), then a constant 
// memory buffer size can be defined in the build system.
// Example: -Da661_data_BUFFER_FIXED_SIZE=100000
*/
#ifdef A661_DATA_BUFFER_FIXED_SIZE

typedef struct _a661_data_buffer 
{
    a661_uchar b[A661_DATA_BUFFER_FIXED_SIZE];
    a661_ulong count;    /* # of data bytes present */
    a661_ulong getter;   /* offset for get functions */
    a661_ulong alloc;    /* amount of space allocated in "b" */
} a661_data_buffer;

#else  /* not defined: A661_DATA_BUFFER_FIXED_SIZE */

typedef struct _a661_data_buffer 
{
    a661_uchar *b;
    a661_ulong count;    /* # of data bytes present */
    a661_ulong getter;   /* offset for get functions */
    a661_ulong alloc;    /* amount of space allocated in "b" */
} a661_data_buffer;

#endif /* A661_DATA_BUFFER_FIXED_SIZE */

a661_data_error_t a661_data_buffer_init(a661_data_buffer* buf, a661_ulong sz);
a661_data_error_t a661_data_buffer_free(a661_data_buffer* buf);
a661_data_error_t a661_data_buffer_append(a661_data_buffer* buf, a661_uchar* data, a661_ulong len);
a661_data_error_t a661_data_buffer_remove(a661_data_buffer* buf, a661_ulong len);
a661_ulong        a661_data_buffer_count(a661_data_buffer* buf);
void              a661_data_buffer_clear(a661_data_buffer* buf);
void              a661_data_buffer_print(a661_data_buffer* buf);

a661_uchar   datab_get_uint8(a661_data_buffer *b);
a661_ushort  datab_get_uint16(a661_data_buffer *b);
a661_short   datab_get_int16(a661_data_buffer *b);
a661_ulong   datab_get_uint32(a661_data_buffer *b);
a661_long    datab_get_int32(a661_data_buffer *b);
a661_float   datab_get_float(a661_data_buffer *b);
a661_string  datab_get_str(a661_data_buffer *b, a661_ushort sz);
void         datab_align(a661_data_buffer *b, a661_ushort n);

void datab_put_uint8(a661_data_buffer *b, a661_uchar v);
void datab_put_uint16(a661_data_buffer *b, a661_ushort v);
void datab_put_int16(a661_data_buffer *b, a661_short v);
void datab_put_uint32(a661_data_buffer *b, a661_ulong v);
void datab_put_int32(a661_data_buffer *b, a661_long v);
void datab_put_float(a661_data_buffer *b, a661_float v);
void datab_put_str(a661_data_buffer *b, const a661_string v, a661_ushort sz);
void datab_put_pad(a661_data_buffer *b, a661_ushort n);
void datab_put_align(a661_data_buffer *b, a661_ushort n);

#endif /* A661_DATA_BUFFER_H */

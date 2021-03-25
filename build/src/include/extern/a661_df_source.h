/*+ FILE DESCRIPTION -------------------------------------------------------
Filename:    a661_df_source.h
Description: Integration porting API: DF handling

Copyright (C) 2020 ANSYS, Inc. ALL RIGHTS RESERVED.
Copyright (C) 2011 ESTEREL TECHNOLOGIES SAS. ALL RIGHTS RESERVED.
This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.

Warranty
ANSYS, Inc. makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose
---------------------------------------------------------------------------- +*/

#ifndef DF_SOURCE_H
#define DF_SOURCE_H

/* DF source API */
/* An API for a data stream. Typically, a wrapper around FILE* functions from stdio.h */

typedef struct a661_df_source a661_df_source;

a661_error df_get_uint8(a661_df_source * src, a661_uchar * v);
a661_error df_get_uint16(a661_df_source * src, a661_ushort * v);
a661_error df_get_int16(a661_df_source * src, a661_short * v);
a661_error df_get_uint32(a661_df_source * src, a661_ulong * v);
a661_error df_get_int32(a661_df_source * src, a661_long * v);
a661_error df_get_float(a661_df_source * src, a661_float * v);
a661_error df_get_str(a661_df_source * src, a661_string b, a661_ushort sz);
a661_error df_copy_block(a661_df_source * src, void *dst, a661_ulong sz);
a661_error df_skip(a661_df_source * src, a661_ulong off);
a661_error df_skip_align(a661_df_source * src, a661_ulong a);
a661_ulong df_position(a661_df_source * src);

#endif                          /* DF_SOURCE_H */

/*+ FILE DESCRIPTION -------------------------------------------------------
Filename:    a661_error_mgmt.h
Description: Integration porting API: errors reporting

Copyright (C) 2020 ANSYS, Inc. ALL RIGHTS RESERVED.
Copyright (C) 2011 ESTEREL TECHNOLOGIES SAS. ALL RIGHTS RESERVED.
This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.

Warranty
ANSYS, Inc. makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose
---------------------------------------------------------------------------- +*/

#ifndef A661_ERROR_MGMT_H
#define A661_ERROR_MGMT_H

#include <a661_error.h>
#include <a661_df_source.h>

void a661_report_simple_error(const char_t * message, a661_ushort value);
void a661_report_simple_error_format1(const char_t * message, char_t * name, a661_long value1);
void a661_report_simple_error_format2(const char_t * message, char_t * name, a661_long value1, a661_long value2);

void a661_report_df_error(a661_df_source * df_src, a661_error err, a661_uchar layer_id, a661_ushort widget_id, a661_ushort value);

void a661_report_rt_error(const char_t * message, a661_error err, a661_ushort app_id, a661_uchar layer_id, a661_ushort widget_id, a661_ushort value);

void a661_report_rtident_error(const char_t * message, a661_error err, a661_ushort app_id, a661_uchar layer_id, a661_ushort widget_id, a661_ushort value);

const char *constants_to_string(a661_ushort value);

const char *a661_error_to_str(a661_error err);

#endif                          /* A661_ERROR_MGMT_H */

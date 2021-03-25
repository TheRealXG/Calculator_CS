/*+ FILE DESCRIPTION -------------------------------------------------------
Filename:    a661_types.h
Description: Server Core API: types definition

Copyright (C) 2020 ANSYS, Inc. ALL RIGHTS RESERVED.
Copyright (C) 2011 ESTEREL TECHNOLOGIES SAS. ALL RIGHTS RESERVED.
This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.

Warranty
ANSYS, Inc. makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose
---------------------------------------------------------------------------- +*/

#ifndef A661_TYPES_H
#define A661_TYPES_H

/* For NULL and size_t */
#include <stddef.h>

/* Disable some useless warnings of Microsoft compiler */
#ifdef _MSC_VER
#pragma warning( disable : 4100 )
#endif

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L))
/* C99 sized integers */
#include <stdint.h>
typedef uint8_t a661_uchar;
typedef int16_t a661_short;
typedef uint16_t a661_ushort;
typedef int32_t a661_long;
typedef uint32_t a661_ulong;
#else
/* C90 integers */
typedef unsigned char a661_uchar;
typedef short int a661_short;
typedef unsigned short int a661_ushort;
typedef long int a661_long;
typedef unsigned long int a661_ulong;
#endif

typedef float a661_float;
typedef a661_uchar *a661_string;
typedef char char_t;

typedef enum {
    A661_UCHAR,
    A661_SHORT,
    A661_USHORT,
    A661_LONG,
    A661_ULONG,
    A661_FLOAT,
    A661_STRING,
    A661_CHAR_T,
    A661_BOOL /* an a661_uchar that accepts "false" / "0" or "true" /"1" as xml config param values */
} a661_types_kind;

typedef enum {
    A661SRV_TP_UNSIGNED,
    A661SRV_TP_SIGNED,
    A661SRV_TP_ENUM,
    A661SRV_TP_FR180,
    A661SRV_TP_FR32768,
    A661SRV_TP_FLOAT,
    A661SRV_TP_OTHER,
    A661SRV_TP_NOT_EXPECTED,
    A661SRV_TP_NOT_DEFINED
} a661_srv_types_param;

/* parameter access */
typedef struct a661_param_data a661_param_data;
struct a661_param_data {
    void * value;
    a661_srv_types_param kind;
    a661_ulong size;
    a661_long nbelem;          /* -1 means a scalar value, otherwise value points at size values */
};

#endif                          /* A661_TYPES_H */

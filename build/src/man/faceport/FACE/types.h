//! @file FACE/types.h
//! @brief Definitions of C types for IDL basic types to C mapping
//! @details This file contains editable type definitions for C types that 
//! align with the size and range requirements given in the IDL basic types
//! to C mapping. Because C types' sizes and ranges are platform-dependent,
//! implementations are responsible for supplying full type definitions.

#ifndef _FACE_TYPES_H
#define _FACE_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* These are defined exactly by C99 and C++ standards */
typedef int16_t 		FACE_short;
typedef int32_t		    FACE_long;
typedef int64_t    	    FACE_long_long;
typedef uint16_t 		FACE_unsigned_short;
typedef uint32_t 		FACE_unsigned_long;
typedef uint64_t    	FACE_unsigned_long_long;
typedef uint8_t		    FACE_char;
typedef uint8_t		    FACE_octet;
typedef float 			FACE_float;
typedef double 			FACE_double;
typedef long double 	FACE_long_double;
typedef wchar_t 		FACE_wchar;
typedef size_t          FACE_size_t;
typedef bool            FACE_boolean;

#endif /* _FACE_TYPES_H */

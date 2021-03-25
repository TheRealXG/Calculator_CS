/*+ FILE DESCRIPTION -------------------------------------------------------
Filename:    a661_keywords.h
Description: Server Core API: ARINC 661 keywords definition

Copyright (C) 2020 ANSYS, Inc. ALL RIGHTS RESERVED.
Copyright (C) 2011 ESTEREL TECHNOLOGIES SAS. ALL RIGHTS RESERVED.
This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.

Warranty
ANSYS, Inc. makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose
---------------------------------------------------------------------------- +*/

#ifndef A661_KEYWORDS_H
#define A661_KEYWORDS_H

#include <a661_types.h>

/* DF Constant */
#define A661_DF_MAGIC_NUMBER              ((a661_ushort)0xA661)

/* Block codes */
#define A661_BEGIN_LAYER_BLOCK            ((a661_uchar)0xA0)
#define A661_BEGIN_BLOCK                  ((a661_uchar)0xB0)
#define A661_BEGIN_PICTURE_BLOCK          ((a661_uchar)0xBB)
#define A661_END_PICTURE_BLOCK            ((a661_uchar)0xBE)
#define A661_BEGIN_PICTURE                ((a661_uchar)0xBC)
#define A661_END_PICTURE                  ((a661_uchar)0xBD)
#define A661_END_LAYER_BLOCK              ((a661_uchar)0xC0)
#define A661_BEGIN_CHARSET_ENCODING_BLOCK ((a661_uchar)0xC8)
#define A661_END_CHARSET_ENCODING_BLOCK   ((a661_uchar)0xC9)
#define A661_END_BLOCK                    ((a661_uchar)0xD0)
#define A661_DF_FOOTER                    ((a661_uchar)0xE0)
#define A661_BEGIN_SYMBOL_BLOCK           ((a661_uchar)0xF0)
#define A661_END_SYMBOL_BLOCK             ((a661_uchar)0xF8)

/* Pixel formats */
#define A661_PIX_FMT_RGBA_8               ((a661_uchar)0xC0)
#define A661_PIX_FMT_LUMINANCE_ALPHA_8    ((a661_uchar)0xC1)
#define A661_PIX_FMT_COLOR_INDEXED_8      ((a661_uchar)0xC2)

/* Character set encodings */
#define A661_ASCII_EXTENDED               ((a661_ushort)0x0001)
#define A661_UTF8                         ((a661_ushort)0x0002)
#define A661_GBK                          ((a661_ushort)0x0003)

/* Commands */
#define A661_CMD_CREATE                   ((a661_ushort)0xCA01)
#define A661_CMD_SET_PARAMETER            ((a661_ushort)0xCA02)
#define A661_CMD_UA_REQUEST               ((a661_ushort)0xCA03)
#define A661_CMD_CREATE_SYMBOL            ((a661_ushort)0xCA04)
#define A661_CMD_EXTEND                   ((a661_ushort)0xCA05)

/* Notifications */
#define A661_NOTIFY_EXCEPTION             ((a661_ushort)0xCC03)
#define A661_NOTIFY_LAYER_EVENT           ((a661_ushort)0xCC02)
#define A661_NOTIFY_WIDGET_EVENT          ((a661_ushort)0xCC01)

/* Requests / Notifications */
#define A661_REQ_LAYER_ACTIVE             ((a661_ushort)0xDA01)
#define A661_REQ_LAYER_INACTIVE           ((a661_ushort)0xDA02)
#define A661_REQ_FOCUS_ON_WIDGET          ((a661_ushort)0xDA03)
#define A661_REQ_LAYER_VISIBLE            ((a661_ushort)0xDA04)
#define A661_REQ_CURSOR_ON_WIDGET         ((a661_ushort)0xDA05)
#define A661_NOTE_REINIT_LAYER_DATA       ((a661_ushort)0xDC01)
#define A661_NOTE_LAYER_IS_ACTIVE         ((a661_ushort)0xDC02)
#define A661_NOTE_LAYER_IS_INACTIVE       ((a661_ushort)0xDC03)
#define A661_NOTE_CYCLIC_ACTIVATION       ((a661_ushort)0xDC82)
#define A661_NOTE_CONNECTOR_DATA          ((a661_ushort)0xDC86)

/* ExceptionType */
#define A661_ERR_BAD_COMMAND              ((a661_ushort)0xF001)
#define A661_ERR_CREATE_ABORTED           ((a661_ushort)0xF002)
#define A661_ERR_SET_ABORTED              ((a661_ushort)0xF003)
#define A661_ERR_UA_REQUEST_ABORTED       ((a661_ushort)0xF004)
#define A661_ERR_MEMORY_OVERLOAD          ((a661_ushort)0xF005)
#define A661_ERR_PROCESS_OVERLOAD         ((a661_ushort)0xF006)
#define A661_ERR_RENDERING_OVERLOAD       ((a661_ushort)0xF007)
#define A661_ERR_EXTEND_ABORTED           ((a661_ushort)0xF008)

/* OEM errors */
#define OEM_ERR_INVALID_BLOCK_STRUCTURE       ((a661_ushort)0x0001)
#define OEM_ERR_INVALID_COMMAND_CODE          ((a661_ushort)0x0002)
#define OEM_ERR_INVALID_APPLICATION_ID        ((a661_ushort)0x0003)
#define OEM_ERR_INVALID_LAYER_ID              ((a661_ushort)0x0004)
#define OEM_ERR_INVALID_CONTEXT_ID            ((a661_ushort)0x0005)
#define OEM_ERR_INVALID_WIDGET_TYPE           ((a661_ushort)0x0006)
#define OEM_ERR_INVALID_WIDGET_ID             ((a661_ushort)0x0007)
#define OEM_ERR_INVALID_PARENT_TYPE           ((a661_ushort)0x0008)
#define OEM_ERR_INVALID_PARENT_ID             ((a661_ushort)0x0009)
#define OEM_ERR_INVALID_PARAMETER_ID          ((a661_ushort)0x000A)
#define OEM_ERR_INVALID_PARAMETER_VALUE       ((a661_ushort)0x000B)
#define OEM_ERR_INCONSISTENT_PARAMETER_DATA   ((a661_ushort)0x000C)
#define OEM_ERR_INVALID_REQUEST_KEY_VALUE     ((a661_ushort)0x000D)
#define OEM_ERR_INVALID_EVENT_ID              ((a661_ushort)0x000E)
#define OEM_ERR_EVENT_QUEUE_FULL              ((a661_ushort)0x000F)
#define OEM_ERR_INVALID_SYMBOL_ID             ((a661_ushort)0x0010)
#define OEM_ERR_INVALID_PICTURE_ID            ((a661_ushort)0x0011)
#define OEM_ERR_INVALID_SYMBOLCOMMAND_TYPE    ((a661_ushort)0x0012)
#define OEM_ERR_INVALID_PIXEL_FORMAT          ((a661_ushort)0x0013)
#define OEM_ERR_INVALID_COLOR_FORMAT          ((a661_ushort)0x0014)
#define OEM_ERR_INVALID_COLOR_INDEX           ((a661_ushort)0x0015)
#define OEM_ERR_INVALID_EXTENSION_ID          ((a661_ushort)0x0016)
#define OEM_ERR_INVALID_EXTENSION_USAGE       ((a661_ushort)0x0017)

#endif                          /* A661_KEYWORDS_H */

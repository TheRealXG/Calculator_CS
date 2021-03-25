/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:15
*************************************************************$ */
#ifndef _KCG_TYPES_H_
#define _KCG_TYPES_H_

#include "stddef.h"

#define KCG_MAPW_CPY

#include "../man/user_macros.h"

#ifndef kcg_char
#define kcg_char kcg_char
typedef char kcg_char;
#endif /* kcg_char */

#ifndef kcg_bool
#define kcg_bool kcg_bool
typedef unsigned char kcg_bool;
#endif /* kcg_bool */

#ifndef kcg_float32
#define kcg_float32 kcg_float32
typedef float kcg_float32;
#endif /* kcg_float32 */

#ifndef kcg_float64
#define kcg_float64 kcg_float64
typedef double kcg_float64;
#endif /* kcg_float64 */

#ifndef kcg_size
#define kcg_size kcg_size
typedef ptrdiff_t kcg_size;
#endif /* kcg_size */

#ifndef kcg_uint64
#define kcg_uint64 kcg_uint64
typedef unsigned long long kcg_uint64;
#endif /* kcg_uint64 */

#ifndef kcg_uint32
#define kcg_uint32 kcg_uint32
typedef unsigned long kcg_uint32;
#endif /* kcg_uint32 */

#ifndef kcg_uint16
#define kcg_uint16 kcg_uint16
typedef unsigned short kcg_uint16;
#endif /* kcg_uint16 */

#ifndef kcg_uint8
#define kcg_uint8 kcg_uint8
typedef unsigned char kcg_uint8;
#endif /* kcg_uint8 */

#ifndef kcg_int64
#define kcg_int64 kcg_int64
typedef signed long long kcg_int64;
#endif /* kcg_int64 */

#ifndef kcg_int32
#define kcg_int32 kcg_int32
typedef signed long kcg_int32;
#endif /* kcg_int32 */

#ifndef kcg_int16
#define kcg_int16 kcg_int16
typedef signed short kcg_int16;
#endif /* kcg_int16 */

#ifndef kcg_int8
#define kcg_int8 kcg_int8
typedef signed char kcg_int8;
#endif /* kcg_int8 */

#ifndef kcg_lit_float32
#define kcg_lit_float32(kcg_C1) ((kcg_float32) (kcg_C1))
#endif /* kcg_lit_float32 */

#ifndef kcg_lit_float64
#define kcg_lit_float64(kcg_C1) ((kcg_float64) (kcg_C1))
#endif /* kcg_lit_float64 */

#ifndef kcg_lit_size
#define kcg_lit_size(kcg_C1) ((kcg_size) (kcg_C1))
#endif /* kcg_lit_size */

#ifndef kcg_lit_uint64
#define kcg_lit_uint64(kcg_C1) ((kcg_uint64) (kcg_C1))
#endif /* kcg_lit_uint64 */

#ifndef kcg_lit_uint32
#define kcg_lit_uint32(kcg_C1) ((kcg_uint32) (kcg_C1))
#endif /* kcg_lit_uint32 */

#ifndef kcg_lit_uint16
#define kcg_lit_uint16(kcg_C1) ((kcg_uint16) (kcg_C1))
#endif /* kcg_lit_uint16 */

#ifndef kcg_lit_uint8
#define kcg_lit_uint8(kcg_C1) ((kcg_uint8) (kcg_C1))
#endif /* kcg_lit_uint8 */

#ifndef kcg_lit_int64
#define kcg_lit_int64(kcg_C1) ((kcg_int64) (kcg_C1))
#endif /* kcg_lit_int64 */

#ifndef kcg_lit_int32
#define kcg_lit_int32(kcg_C1) ((kcg_int32) (kcg_C1))
#endif /* kcg_lit_int32 */

#ifndef kcg_lit_int16
#define kcg_lit_int16(kcg_C1) ((kcg_int16) (kcg_C1))
#endif /* kcg_lit_int16 */

#ifndef kcg_lit_int8
#define kcg_lit_int8(kcg_C1) ((kcg_int8) (kcg_C1))
#endif /* kcg_lit_int8 */

#ifndef kcg_false
#define kcg_false ((kcg_bool) 0)
#endif /* kcg_false */

#ifndef kcg_true
#define kcg_true ((kcg_bool) 1)
#endif /* kcg_true */

#ifndef kcg_lsl_uint64
#define kcg_lsl_uint64(kcg_C1, kcg_C2)                                        \
  ((kcg_uint64) ((kcg_C1) << (kcg_C2)) & 0xffffffffffffffff)
#endif /* kcg_lsl_uint64 */

#ifndef kcg_lsl_uint32
#define kcg_lsl_uint32(kcg_C1, kcg_C2)                                        \
  ((kcg_uint32) ((kcg_C1) << (kcg_C2)) & 0xffffffff)
#endif /* kcg_lsl_uint32 */

#ifndef kcg_lsl_uint16
#define kcg_lsl_uint16(kcg_C1, kcg_C2)                                        \
  ((kcg_uint16) ((kcg_C1) << (kcg_C2)) & 0xffff)
#endif /* kcg_lsl_uint16 */

#ifndef kcg_lsl_uint8
#define kcg_lsl_uint8(kcg_C1, kcg_C2)                                         \
  ((kcg_uint8) ((kcg_C1) << (kcg_C2)) & 0xff)
#endif /* kcg_lsl_uint8 */

#ifndef kcg_lnot_uint64
#define kcg_lnot_uint64(kcg_C1) ((kcg_C1) ^ 0xffffffffffffffff)
#endif /* kcg_lnot_uint64 */

#ifndef kcg_lnot_uint32
#define kcg_lnot_uint32(kcg_C1) ((kcg_C1) ^ 0xffffffff)
#endif /* kcg_lnot_uint32 */

#ifndef kcg_lnot_uint16
#define kcg_lnot_uint16(kcg_C1) ((kcg_C1) ^ 0xffff)
#endif /* kcg_lnot_uint16 */

#ifndef kcg_lnot_uint8
#define kcg_lnot_uint8(kcg_C1) ((kcg_C1) ^ 0xff)
#endif /* kcg_lnot_uint8 */

#ifndef kcg_assign
#include "kcg_assign.h"
#endif /* kcg_assign */

#ifndef kcg_assign_struct
#define kcg_assign_struct kcg_assign
#endif /* kcg_assign_struct */

#ifndef kcg_assign_array
#define kcg_assign_array kcg_assign
#endif /* kcg_assign_array */

/* Calc::valueEntry/SM2: */
typedef enum kcg_tag_SSM_TR_SM2 {
  SSM_TR_no_trans_SM2,
  SSM_TR_IntegerEntry_AddDecimalPoint_1_IntegerEntry_SM2,
  SSM_TR_AddDecimalPoint_FractionalEntry_1_AddDecimalPoint_SM2
} SSM_TR_SM2;
/* Calc::valueEntry/SM2: */
typedef enum kcg_tag_SSM_ST_SM2 {
  SSM_st_IntegerEntry_SM2,
  SSM_st_FractionalEntry_SM2,
  SSM_st_AddDecimalPoint_SM2
} SSM_ST_SM2;
/* Calc::valueEntry/SM1: */
typedef enum kcg_tag__3_SSM_TR_SM1 {
  _4_SSM_TR_no_trans_SM1,
  SSM_TR_NegativeSignToggle_NegativeSignToggle_1_NegativeSignToggle_SM1
} _3_SSM_TR_SM1;
/* Calc::valueEntry/SM1: */
typedef enum kcg_tag__2_SSM_ST_SM1 {
  SSM_st_NegativeSignToggle_SM1
} _2_SSM_ST_SM1;
/* Calc::root/SM1: */
typedef enum kcg_tag_SSM_TR_SM1 {
  SSM_TR_no_trans_SM1,
  SSM_TR_EnterValue1_EnterValue1_1_EnterValue1_SM1,
  SSM_TR_EnterValue1_StoreFunction_2_EnterValue1_SM1,
  SSM_TR_EnterValue2_EnterValue2_1_EnterValue2_SM1,
  SSM_TR_EnterValue2_Compute_2_EnterValue2_SM1,
  SSM_TR_EnterValue2_EnterValue1_3_EnterValue2_SM1,
  SSM_TR_Compute_EnterValue1_1_Compute_SM1,
  SSM_TR_StoreFunction_EnterValue2_1_StoreFunction_SM1
} SSM_TR_SM1;
/* Calc::root/SM1: */
typedef enum kcg_tag_SSM_ST_SM1 {
  SSM_st_EnterValue1_SM1,
  SSM_st_EnterValue2_SM1,
  SSM_st_Compute_SM1,
  SSM_st_StoreFunction_SM1
} SSM_ST_SM1;
typedef kcg_char array_char_15[15];

typedef kcg_char array_char_16[16];

typedef kcg_char array_char_255[255];

typedef array_char_255 array_char_255_4[4];

/* a661_types::msg_bool/ */
typedef struct kcg_tag_msg_bool_a661_types {
  kcg_bool Emit;
  kcg_bool Value;
} msg_bool_a661_types;

typedef kcg_bool array_bool_4[4];

typedef struct kcg_tag_struct_5269 {
  kcg_bool Emit;
  kcg_float32 Value;
} struct_5269;

/* a661_types::msg_float/ */
typedef struct_5269 msg_float_a661_types;

/* a661_types::msg_FR/ */
typedef struct_5269 msg_FR_a661_types;

/* a661_types::msg_uint32/ */
typedef struct kcg_tag_msg_uint32_a661_types {
  kcg_bool Emit;
  kcg_uint32 Value;
} msg_uint32_a661_types;

/* a661_types::msg_string255/ */
typedef struct kcg_tag_msg_string255_a661_types {
  kcg_bool Emit;
  kcg_uint16 String_size;
  array_char_255 LabelString;
} msg_string255_a661_types;

/* msg_notify/ */
typedef struct kcg_tag_msg_notify {
  kcg_bool Notify;
  kcg_uint16 EventOrigin;
} msg_notify;

typedef kcg_uint16 array_uint16_4[4];

/* a661_types::msg_string_list_255_4/ */
typedef struct kcg_tag_msg_string_list_255_4_a661_types {
  array_bool_4 Emit;
  array_uint16_4 StringIndex;
  array_uint16_4 StringSize;
  array_char_255_4 Element;
} msg_string_list_255_4_a661_types;

/* a661_types::msg_bool_list_4/ */
typedef struct kcg_tag_msg_bool_list_4_a661_types {
  array_bool_4 Emit;
  array_uint16_4 EntryIndex;
  array_bool_4 Element;
} msg_bool_list_4_a661_types;

/* a661_types::msg_uint16/ */
typedef struct kcg_tag_msg_uint16_a661_types {
  kcg_bool Emit;
  kcg_uint16 Value;
} msg_uint16_a661_types;

/* a661_util::SendStringOnValChanged/, msg_string16/ */
typedef struct kcg_tag_msg_string16 {
  kcg_bool Emit;
  kcg_uint16 String_size;
  array_char_16 LabelString;
} msg_string16;

/* a661_types::msg_uint8/ */
typedef struct kcg_tag_msg_uint8_a661_types {
  kcg_bool Emit;
  kcg_uint8 Value;
} msg_uint8_a661_types;

/* a661_types::msg_int32/ */
typedef struct kcg_tag_msg_int32_a661_types {
  kcg_bool Emit;
  kcg_int32 Value;
} msg_int32_a661_types;

/* a661_types::msg_XY/ */
typedef struct kcg_tag_msg_XY_a661_types {
  kcg_bool Emit;
  kcg_int32 PosX;
  kcg_int32 PosY;
} msg_XY_a661_types;

typedef kcg_int32 array_int32_4[4];

/* a661_types::msg_int_list_4/ */
typedef struct kcg_tag_msg_int_list_4_a661_types {
  array_bool_4 Emit;
  array_uint16_4 EntryIndex;
  array_int32_4 Element;
} msg_int_list_4_a661_types;

/* a661_types::msg_int16/ */
typedef struct kcg_tag_msg_int16_a661_types {
  kcg_bool Emit;
  kcg_int16 Value;
} msg_int16_a661_types;

#ifndef kcg_copy_msg_int_list_4_a661_types
#define kcg_copy_msg_int_list_4_a661_types(kcg_C1, kcg_C2)                    \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (msg_int_list_4_a661_types)))
#endif /* kcg_copy_msg_int_list_4_a661_types */

#ifndef kcg_copy_msg_bool_list_4_a661_types
#define kcg_copy_msg_bool_list_4_a661_types(kcg_C1, kcg_C2)                   \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (msg_bool_list_4_a661_types)))
#endif /* kcg_copy_msg_bool_list_4_a661_types */

#ifndef kcg_copy_msg_XY_a661_types
#define kcg_copy_msg_XY_a661_types(kcg_C1, kcg_C2)                            \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (msg_XY_a661_types)))
#endif /* kcg_copy_msg_XY_a661_types */

#ifndef kcg_copy_msg_string16
#define kcg_copy_msg_string16(kcg_C1, kcg_C2)                                 \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (msg_string16)))
#endif /* kcg_copy_msg_string16 */

#ifndef kcg_copy_msg_uint32_a661_types
#define kcg_copy_msg_uint32_a661_types(kcg_C1, kcg_C2)                        \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (msg_uint32_a661_types)))
#endif /* kcg_copy_msg_uint32_a661_types */

#ifndef kcg_copy_msg_string_list_255_4_a661_types
#define kcg_copy_msg_string_list_255_4_a661_types(kcg_C1, kcg_C2)             \
  (kcg_assign_struct(                                                         \
      (kcg_C1),                                                               \
      (kcg_C2),                                                               \
      sizeof (msg_string_list_255_4_a661_types)))
#endif /* kcg_copy_msg_string_list_255_4_a661_types */

#ifndef kcg_copy_msg_uint16_a661_types
#define kcg_copy_msg_uint16_a661_types(kcg_C1, kcg_C2)                        \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (msg_uint16_a661_types)))
#endif /* kcg_copy_msg_uint16_a661_types */

#ifndef kcg_copy_msg_uint8_a661_types
#define kcg_copy_msg_uint8_a661_types(kcg_C1, kcg_C2)                         \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (msg_uint8_a661_types)))
#endif /* kcg_copy_msg_uint8_a661_types */

#ifndef kcg_copy_msg_int32_a661_types
#define kcg_copy_msg_int32_a661_types(kcg_C1, kcg_C2)                         \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (msg_int32_a661_types)))
#endif /* kcg_copy_msg_int32_a661_types */

#ifndef kcg_copy_msg_int16_a661_types
#define kcg_copy_msg_int16_a661_types(kcg_C1, kcg_C2)                         \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (msg_int16_a661_types)))
#endif /* kcg_copy_msg_int16_a661_types */

#ifndef kcg_copy_msg_notify
#define kcg_copy_msg_notify(kcg_C1, kcg_C2)                                   \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (msg_notify)))
#endif /* kcg_copy_msg_notify */

#ifndef kcg_copy_msg_string255_a661_types
#define kcg_copy_msg_string255_a661_types(kcg_C1, kcg_C2)                     \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (msg_string255_a661_types)))
#endif /* kcg_copy_msg_string255_a661_types */

#ifndef kcg_copy_msg_bool_a661_types
#define kcg_copy_msg_bool_a661_types(kcg_C1, kcg_C2)                          \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (msg_bool_a661_types)))
#endif /* kcg_copy_msg_bool_a661_types */

#ifndef kcg_copy_struct_5269
#define kcg_copy_struct_5269(kcg_C1, kcg_C2)                                  \
  (kcg_assign_struct((kcg_C1), (kcg_C2), sizeof (struct_5269)))
#endif /* kcg_copy_struct_5269 */

#ifndef kcg_copy_array_int32_4
#define kcg_copy_array_int32_4(kcg_C1, kcg_C2)                                \
  (kcg_assign_array((kcg_C1), (kcg_C2), sizeof (array_int32_4)))
#endif /* kcg_copy_array_int32_4 */

#ifndef kcg_copy_array_char_255
#define kcg_copy_array_char_255(kcg_C1, kcg_C2)                               \
  (kcg_assign_array((kcg_C1), (kcg_C2), sizeof (array_char_255)))
#endif /* kcg_copy_array_char_255 */

#ifndef kcg_copy_array_bool_4
#define kcg_copy_array_bool_4(kcg_C1, kcg_C2)                                 \
  (kcg_assign_array((kcg_C1), (kcg_C2), sizeof (array_bool_4)))
#endif /* kcg_copy_array_bool_4 */

#ifndef kcg_copy_array_char_16
#define kcg_copy_array_char_16(kcg_C1, kcg_C2)                                \
  (kcg_assign_array((kcg_C1), (kcg_C2), sizeof (array_char_16)))
#endif /* kcg_copy_array_char_16 */

#ifndef kcg_copy_array_uint16_4
#define kcg_copy_array_uint16_4(kcg_C1, kcg_C2)                               \
  (kcg_assign_array((kcg_C1), (kcg_C2), sizeof (array_uint16_4)))
#endif /* kcg_copy_array_uint16_4 */

#ifndef kcg_copy_array_char_255_4
#define kcg_copy_array_char_255_4(kcg_C1, kcg_C2)                             \
  (kcg_assign_array((kcg_C1), (kcg_C2), sizeof (array_char_255_4)))
#endif /* kcg_copy_array_char_255_4 */

#ifndef kcg_copy_array_char_15
#define kcg_copy_array_char_15(kcg_C1, kcg_C2)                                \
  (kcg_assign_array((kcg_C1), (kcg_C2), sizeof (array_char_15)))
#endif /* kcg_copy_array_char_15 */

#ifdef kcg_use_msg_int_list_4_a661_types
#ifndef kcg_comp_msg_int_list_4_a661_types
extern kcg_bool kcg_comp_msg_int_list_4_a661_types(
  msg_int_list_4_a661_types *kcg_c1,
  msg_int_list_4_a661_types *kcg_c2);
#endif /* kcg_comp_msg_int_list_4_a661_types */
#endif /* kcg_use_msg_int_list_4_a661_types */

#ifdef kcg_use_msg_bool_list_4_a661_types
#ifndef kcg_comp_msg_bool_list_4_a661_types
extern kcg_bool kcg_comp_msg_bool_list_4_a661_types(
  msg_bool_list_4_a661_types *kcg_c1,
  msg_bool_list_4_a661_types *kcg_c2);
#endif /* kcg_comp_msg_bool_list_4_a661_types */
#endif /* kcg_use_msg_bool_list_4_a661_types */

#ifdef kcg_use_msg_XY_a661_types
#ifndef kcg_comp_msg_XY_a661_types
extern kcg_bool kcg_comp_msg_XY_a661_types(
  msg_XY_a661_types *kcg_c1,
  msg_XY_a661_types *kcg_c2);
#endif /* kcg_comp_msg_XY_a661_types */
#endif /* kcg_use_msg_XY_a661_types */

#ifdef kcg_use_msg_string16
#ifndef kcg_comp_msg_string16
extern kcg_bool kcg_comp_msg_string16(
  msg_string16 *kcg_c1,
  msg_string16 *kcg_c2);
#endif /* kcg_comp_msg_string16 */
#endif /* kcg_use_msg_string16 */

#ifdef kcg_use_msg_uint32_a661_types
#ifndef kcg_comp_msg_uint32_a661_types
extern kcg_bool kcg_comp_msg_uint32_a661_types(
  msg_uint32_a661_types *kcg_c1,
  msg_uint32_a661_types *kcg_c2);
#endif /* kcg_comp_msg_uint32_a661_types */
#endif /* kcg_use_msg_uint32_a661_types */

#ifdef kcg_use_msg_string_list_255_4_a661_types
#ifndef kcg_comp_msg_string_list_255_4_a661_types
extern kcg_bool kcg_comp_msg_string_list_255_4_a661_types(
  msg_string_list_255_4_a661_types *kcg_c1,
  msg_string_list_255_4_a661_types *kcg_c2);
#endif /* kcg_comp_msg_string_list_255_4_a661_types */
#endif /* kcg_use_msg_string_list_255_4_a661_types */

#ifdef kcg_use_msg_uint16_a661_types
#ifndef kcg_comp_msg_uint16_a661_types
extern kcg_bool kcg_comp_msg_uint16_a661_types(
  msg_uint16_a661_types *kcg_c1,
  msg_uint16_a661_types *kcg_c2);
#endif /* kcg_comp_msg_uint16_a661_types */
#endif /* kcg_use_msg_uint16_a661_types */

#ifdef kcg_use_msg_uint8_a661_types
#ifndef kcg_comp_msg_uint8_a661_types
extern kcg_bool kcg_comp_msg_uint8_a661_types(
  msg_uint8_a661_types *kcg_c1,
  msg_uint8_a661_types *kcg_c2);
#endif /* kcg_comp_msg_uint8_a661_types */
#endif /* kcg_use_msg_uint8_a661_types */

#ifdef kcg_use_msg_int32_a661_types
#ifndef kcg_comp_msg_int32_a661_types
extern kcg_bool kcg_comp_msg_int32_a661_types(
  msg_int32_a661_types *kcg_c1,
  msg_int32_a661_types *kcg_c2);
#endif /* kcg_comp_msg_int32_a661_types */
#endif /* kcg_use_msg_int32_a661_types */

#ifdef kcg_use_msg_int16_a661_types
#ifndef kcg_comp_msg_int16_a661_types
extern kcg_bool kcg_comp_msg_int16_a661_types(
  msg_int16_a661_types *kcg_c1,
  msg_int16_a661_types *kcg_c2);
#endif /* kcg_comp_msg_int16_a661_types */
#endif /* kcg_use_msg_int16_a661_types */

#ifdef kcg_use_msg_notify
#ifndef kcg_comp_msg_notify
extern kcg_bool kcg_comp_msg_notify(msg_notify *kcg_c1, msg_notify *kcg_c2);
#endif /* kcg_comp_msg_notify */
#endif /* kcg_use_msg_notify */

#ifdef kcg_use_msg_string255_a661_types
#ifndef kcg_comp_msg_string255_a661_types
extern kcg_bool kcg_comp_msg_string255_a661_types(
  msg_string255_a661_types *kcg_c1,
  msg_string255_a661_types *kcg_c2);
#endif /* kcg_comp_msg_string255_a661_types */
#endif /* kcg_use_msg_string255_a661_types */

#ifdef kcg_use_msg_bool_a661_types
#ifndef kcg_comp_msg_bool_a661_types
extern kcg_bool kcg_comp_msg_bool_a661_types(
  msg_bool_a661_types *kcg_c1,
  msg_bool_a661_types *kcg_c2);
#endif /* kcg_comp_msg_bool_a661_types */
#endif /* kcg_use_msg_bool_a661_types */

#ifdef kcg_use_struct_5269
#ifndef kcg_comp_struct_5269
extern kcg_bool kcg_comp_struct_5269(struct_5269 *kcg_c1, struct_5269 *kcg_c2);
#endif /* kcg_comp_struct_5269 */
#endif /* kcg_use_struct_5269 */

#ifdef kcg_use_array_int32_4
#ifndef kcg_comp_array_int32_4
extern kcg_bool kcg_comp_array_int32_4(
  array_int32_4 *kcg_c1,
  array_int32_4 *kcg_c2);
#endif /* kcg_comp_array_int32_4 */
#endif /* kcg_use_array_int32_4 */

#ifdef kcg_use_array_char_255
#ifndef kcg_comp_array_char_255
extern kcg_bool kcg_comp_array_char_255(
  array_char_255 *kcg_c1,
  array_char_255 *kcg_c2);
#endif /* kcg_comp_array_char_255 */
#endif /* kcg_use_array_char_255 */

#ifdef kcg_use_array_bool_4
#ifndef kcg_comp_array_bool_4
extern kcg_bool kcg_comp_array_bool_4(
  array_bool_4 *kcg_c1,
  array_bool_4 *kcg_c2);
#endif /* kcg_comp_array_bool_4 */
#endif /* kcg_use_array_bool_4 */

#ifndef kcg_comp_array_char_16
extern kcg_bool kcg_comp_array_char_16(
  array_char_16 *kcg_c1,
  array_char_16 *kcg_c2);
#define kcg_use_array_char_16
#endif /* kcg_comp_array_char_16 */

#ifdef kcg_use_array_uint16_4
#ifndef kcg_comp_array_uint16_4
extern kcg_bool kcg_comp_array_uint16_4(
  array_uint16_4 *kcg_c1,
  array_uint16_4 *kcg_c2);
#endif /* kcg_comp_array_uint16_4 */
#endif /* kcg_use_array_uint16_4 */

#ifdef kcg_use_array_char_255_4
#ifndef kcg_comp_array_char_255_4
extern kcg_bool kcg_comp_array_char_255_4(
  array_char_255_4 *kcg_c1,
  array_char_255_4 *kcg_c2);
#endif /* kcg_comp_array_char_255_4 */
#endif /* kcg_use_array_char_255_4 */

#ifdef kcg_use_array_char_15
#ifndef kcg_comp_array_char_15
extern kcg_bool kcg_comp_array_char_15(
  array_char_15 *kcg_c1,
  array_char_15 *kcg_c2);
#endif /* kcg_comp_array_char_15 */
#endif /* kcg_use_array_char_15 */

#define kcg_comp_msg_FR_a661_types kcg_comp_struct_5269

#define kcg_copy_msg_FR_a661_types kcg_copy_struct_5269

#define kcg_comp_msg_float_a661_types kcg_comp_struct_5269

#define kcg_copy_msg_float_a661_types kcg_copy_struct_5269

#endif /* _KCG_TYPES_H_ */
/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** kcg_types.h
** Generation date: 2021-03-18T11:28:15
*************************************************************$ */


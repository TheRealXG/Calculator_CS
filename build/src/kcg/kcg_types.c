/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:15
*************************************************************$ */

#include "kcg_types.h"

#ifdef kcg_use_array_int32_4
kcg_bool kcg_comp_array_int32_4(array_int32_4 *kcg_c1, array_int32_4 *kcg_c2)
{
  kcg_bool kcg_equ;
  kcg_size kcg_ci;

  kcg_equ = kcg_true;
  for (kcg_ci = 0; kcg_ci < 4; kcg_ci++) {
    kcg_equ = kcg_equ & ((*kcg_c1)[kcg_ci] == (*kcg_c2)[kcg_ci]);
  }
  return kcg_equ;
}
#endif /* kcg_use_array_int32_4 */

#ifdef kcg_use_array_char_255
kcg_bool kcg_comp_array_char_255(array_char_255 *kcg_c1, array_char_255 *kcg_c2)
{
  kcg_bool kcg_equ;
  kcg_size kcg_ci;

  kcg_equ = kcg_true;
  for (kcg_ci = 0; kcg_ci < 255; kcg_ci++) {
    kcg_equ = kcg_equ & ((*kcg_c1)[kcg_ci] == (*kcg_c2)[kcg_ci]);
  }
  return kcg_equ;
}
#endif /* kcg_use_array_char_255 */

#ifdef kcg_use_array_bool_4
kcg_bool kcg_comp_array_bool_4(array_bool_4 *kcg_c1, array_bool_4 *kcg_c2)
{
  kcg_bool kcg_equ;
  kcg_size kcg_ci;

  kcg_equ = kcg_true;
  for (kcg_ci = 0; kcg_ci < 4; kcg_ci++) {
    kcg_equ = kcg_equ & ((*kcg_c1)[kcg_ci] == (*kcg_c2)[kcg_ci]);
  }
  return kcg_equ;
}
#endif /* kcg_use_array_bool_4 */

#ifdef kcg_use_array_char_16
kcg_bool kcg_comp_array_char_16(array_char_16 *kcg_c1, array_char_16 *kcg_c2)
{
  kcg_bool kcg_equ;
  kcg_size kcg_ci;

  kcg_equ = kcg_true;
  for (kcg_ci = 0; kcg_ci < 16; kcg_ci++) {
    kcg_equ = kcg_equ & ((*kcg_c1)[kcg_ci] == (*kcg_c2)[kcg_ci]);
  }
  return kcg_equ;
}
#endif /* kcg_use_array_char_16 */

#ifdef kcg_use_array_uint16_4
kcg_bool kcg_comp_array_uint16_4(array_uint16_4 *kcg_c1, array_uint16_4 *kcg_c2)
{
  kcg_bool kcg_equ;
  kcg_size kcg_ci;

  kcg_equ = kcg_true;
  for (kcg_ci = 0; kcg_ci < 4; kcg_ci++) {
    kcg_equ = kcg_equ & ((*kcg_c1)[kcg_ci] == (*kcg_c2)[kcg_ci]);
  }
  return kcg_equ;
}
#endif /* kcg_use_array_uint16_4 */

#ifdef kcg_use_array_char_255_4
kcg_bool kcg_comp_array_char_255_4(
  array_char_255_4 *kcg_c1,
  array_char_255_4 *kcg_c2)
{
  kcg_bool kcg_equ;
  kcg_size kcg_ci;

  kcg_equ = kcg_true;
  for (kcg_ci = 0; kcg_ci < 4; kcg_ci++) {
    kcg_equ = kcg_equ & kcg_comp_array_char_255(
        &(*kcg_c1)[kcg_ci],
        &(*kcg_c2)[kcg_ci]);
  }
  return kcg_equ;
}
#endif /* kcg_use_array_char_255_4 */

#ifdef kcg_use_array_char_15
kcg_bool kcg_comp_array_char_15(array_char_15 *kcg_c1, array_char_15 *kcg_c2)
{
  kcg_bool kcg_equ;
  kcg_size kcg_ci;

  kcg_equ = kcg_true;
  for (kcg_ci = 0; kcg_ci < 15; kcg_ci++) {
    kcg_equ = kcg_equ & ((*kcg_c1)[kcg_ci] == (*kcg_c2)[kcg_ci]);
  }
  return kcg_equ;
}
#endif /* kcg_use_array_char_15 */

#ifdef kcg_use_msg_int_list_4_a661_types
kcg_bool kcg_comp_msg_int_list_4_a661_types(
  msg_int_list_4_a661_types *kcg_c1,
  msg_int_list_4_a661_types *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & kcg_comp_array_int32_4(&kcg_c1->Element, &kcg_c2->Element);
  kcg_equ = kcg_equ & kcg_comp_array_uint16_4(
      &kcg_c1->EntryIndex,
      &kcg_c2->EntryIndex);
  kcg_equ = kcg_equ & kcg_comp_array_bool_4(&kcg_c1->Emit, &kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_msg_int_list_4_a661_types */

#ifdef kcg_use_msg_bool_list_4_a661_types
kcg_bool kcg_comp_msg_bool_list_4_a661_types(
  msg_bool_list_4_a661_types *kcg_c1,
  msg_bool_list_4_a661_types *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & kcg_comp_array_bool_4(&kcg_c1->Element, &kcg_c2->Element);
  kcg_equ = kcg_equ & kcg_comp_array_uint16_4(
      &kcg_c1->EntryIndex,
      &kcg_c2->EntryIndex);
  kcg_equ = kcg_equ & kcg_comp_array_bool_4(&kcg_c1->Emit, &kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_msg_bool_list_4_a661_types */

#ifdef kcg_use_msg_XY_a661_types
kcg_bool kcg_comp_msg_XY_a661_types(
  msg_XY_a661_types *kcg_c1,
  msg_XY_a661_types *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & (kcg_c1->PosY == kcg_c2->PosY);
  kcg_equ = kcg_equ & (kcg_c1->PosX == kcg_c2->PosX);
  kcg_equ = kcg_equ & (kcg_c1->Emit == kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_msg_XY_a661_types */

#ifdef kcg_use_msg_string16
kcg_bool kcg_comp_msg_string16(msg_string16 *kcg_c1, msg_string16 *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & kcg_comp_array_char_16(
      &kcg_c1->LabelString,
      &kcg_c2->LabelString);
  kcg_equ = kcg_equ & (kcg_c1->String_size == kcg_c2->String_size);
  kcg_equ = kcg_equ & (kcg_c1->Emit == kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_msg_string16 */

#ifdef kcg_use_msg_uint32_a661_types
kcg_bool kcg_comp_msg_uint32_a661_types(
  msg_uint32_a661_types *kcg_c1,
  msg_uint32_a661_types *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & (kcg_c1->Value == kcg_c2->Value);
  kcg_equ = kcg_equ & (kcg_c1->Emit == kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_msg_uint32_a661_types */

#ifdef kcg_use_msg_string_list_255_4_a661_types
kcg_bool kcg_comp_msg_string_list_255_4_a661_types(
  msg_string_list_255_4_a661_types *kcg_c1,
  msg_string_list_255_4_a661_types *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & kcg_comp_array_char_255_4(
      &kcg_c1->Element,
      &kcg_c2->Element);
  kcg_equ = kcg_equ & kcg_comp_array_uint16_4(
      &kcg_c1->StringSize,
      &kcg_c2->StringSize);
  kcg_equ = kcg_equ & kcg_comp_array_uint16_4(
      &kcg_c1->StringIndex,
      &kcg_c2->StringIndex);
  kcg_equ = kcg_equ & kcg_comp_array_bool_4(&kcg_c1->Emit, &kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_msg_string_list_255_4_a661_types */

#ifdef kcg_use_msg_uint16_a661_types
kcg_bool kcg_comp_msg_uint16_a661_types(
  msg_uint16_a661_types *kcg_c1,
  msg_uint16_a661_types *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & (kcg_c1->Value == kcg_c2->Value);
  kcg_equ = kcg_equ & (kcg_c1->Emit == kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_msg_uint16_a661_types */

#ifdef kcg_use_msg_uint8_a661_types
kcg_bool kcg_comp_msg_uint8_a661_types(
  msg_uint8_a661_types *kcg_c1,
  msg_uint8_a661_types *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & (kcg_c1->Value == kcg_c2->Value);
  kcg_equ = kcg_equ & (kcg_c1->Emit == kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_msg_uint8_a661_types */

#ifdef kcg_use_msg_int32_a661_types
kcg_bool kcg_comp_msg_int32_a661_types(
  msg_int32_a661_types *kcg_c1,
  msg_int32_a661_types *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & (kcg_c1->Value == kcg_c2->Value);
  kcg_equ = kcg_equ & (kcg_c1->Emit == kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_msg_int32_a661_types */

#ifdef kcg_use_msg_int16_a661_types
kcg_bool kcg_comp_msg_int16_a661_types(
  msg_int16_a661_types *kcg_c1,
  msg_int16_a661_types *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & (kcg_c1->Value == kcg_c2->Value);
  kcg_equ = kcg_equ & (kcg_c1->Emit == kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_msg_int16_a661_types */

#ifdef kcg_use_msg_notify
kcg_bool kcg_comp_msg_notify(msg_notify *kcg_c1, msg_notify *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & (kcg_c1->EventOrigin == kcg_c2->EventOrigin);
  kcg_equ = kcg_equ & (kcg_c1->Notify == kcg_c2->Notify);
  return kcg_equ;
}
#endif /* kcg_use_msg_notify */

#ifdef kcg_use_msg_string255_a661_types
kcg_bool kcg_comp_msg_string255_a661_types(
  msg_string255_a661_types *kcg_c1,
  msg_string255_a661_types *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & kcg_comp_array_char_255(
      &kcg_c1->LabelString,
      &kcg_c2->LabelString);
  kcg_equ = kcg_equ & (kcg_c1->String_size == kcg_c2->String_size);
  kcg_equ = kcg_equ & (kcg_c1->Emit == kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_msg_string255_a661_types */

#ifdef kcg_use_msg_bool_a661_types
kcg_bool kcg_comp_msg_bool_a661_types(
  msg_bool_a661_types *kcg_c1,
  msg_bool_a661_types *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & (kcg_c1->Value == kcg_c2->Value);
  kcg_equ = kcg_equ & (kcg_c1->Emit == kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_msg_bool_a661_types */

#ifdef kcg_use_struct_5269
kcg_bool kcg_comp_struct_5269(struct_5269 *kcg_c1, struct_5269 *kcg_c2)
{
  kcg_bool kcg_equ;

  kcg_equ = kcg_true;
  kcg_equ = kcg_equ & (kcg_c1->Value == kcg_c2->Value);
  kcg_equ = kcg_equ & (kcg_c1->Emit == kcg_c2->Emit);
  return kcg_equ;
}
#endif /* kcg_use_struct_5269 */

/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** kcg_types.c
** Generation date: 2021-03-18T11:28:15
*************************************************************$ */


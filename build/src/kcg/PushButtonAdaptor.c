/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "PushButtonAdaptor.h"

/* PushButtonAdaptor/ */
kcg_int32 PushButtonAdaptor(
  /* PB_00/ */
  msg_notify *PB_00,
  /* PB_01/ */
  msg_notify *PB_01,
  /* PB_02/ */
  msg_notify *PB_02,
  /* PB_03/ */
  msg_notify *PB_03,
  /* PB_04/ */
  msg_notify *PB_04,
  /* PB_05/ */
  msg_notify *PB_05,
  /* PB_06/ */
  msg_notify *PB_06,
  /* PB_07/ */
  msg_notify *PB_07,
  /* PB_08/ */
  msg_notify *PB_08,
  /* PB_09/ */
  msg_notify *PB_09,
  /* PB_10_Decimal/ */
  msg_notify *PB_10_Decimal,
  /* PB_11_Negative/ */
  msg_notify *PB_11_Negative,
  /* PB_12_Equals/ */
  msg_notify *PB_12_Equals,
  /* PB_13_Plus/ */
  msg_notify *PB_13_Plus,
  /* PB_14_Minus/ */
  msg_notify *PB_14_Minus,
  /* PB_15_Times/ */
  msg_notify *PB_15_Times,
  /* PB_16_Divide/ */
  msg_notify *PB_16_Divide,
  /* PB_17_Clear_Entry/ */
  msg_notify *PB_17_Clear_Entry,
  /* PB_18_Clear_All/ */
  msg_notify *PB_18_Clear_All)
{
  /* keyEvent/ */
  kcg_int32 keyEvent;

  /* IfBlock1: */
  if ((*PB_00).Notify) {
    keyEvent = KEY_00_Calc;
  }
  else /* IfBlock1:else: */
  if ((*PB_01).Notify) {
    keyEvent = KEY_01_Calc;
  }
  else /* IfBlock1:else:else: */
  if ((*PB_02).Notify) {
    keyEvent = KEY_02_Calc;
  }
  else /* IfBlock1:else:else:else: */
  if ((*PB_03).Notify) {
    keyEvent = KEY_03_Calc;
  }
  else /* IfBlock1:else:else:else:else: */
  if ((*PB_04).Notify) {
    keyEvent = KEY_04_Calc;
  }
  else /* IfBlock1:else:else:else:else:else: */
  if ((*PB_05).Notify) {
    keyEvent = KEY_05_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else: */
  if ((*PB_06).Notify) {
    keyEvent = KEY_06_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else:else: */
  if ((*PB_07).Notify) {
    keyEvent = KEY_07_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else:else:else: */
  if ((*PB_08).Notify) {
    keyEvent = KEY_08_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else:else:else:else: */
  if ((*PB_09).Notify) {
    keyEvent = KEY_09_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else:else:else:else:else: */
  if ((*PB_10_Decimal).Notify) {
    keyEvent = KEY_10_DECIMAL_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else:else:else:else:else:else: */
  if ((*PB_11_Negative).Notify) {
    keyEvent = KEY_11_NEGATIVE_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else:else:else:else:else:else:else: */
  if ((*PB_12_Equals).Notify) {
    keyEvent = KEY_12_EQUALS_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else:else:else:else:else:else:else:else: */
  if ((*PB_13_Plus).Notify) {
    keyEvent = KEY_13_PLUS_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else:else:else:else:else:else:else:else:else: */
  if ((*PB_14_Minus).Notify) {
    keyEvent = KEY_14_MINUS_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else:else:else:else:else:else:else:else:else:else: */
  if ((*PB_15_Times).Notify) {
    keyEvent = KEY_15_TIMES_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else:else:else:else:else:else:else:else:else:else:else: */
  if ((*PB_16_Divide).Notify) {
    keyEvent = KEY_16_DIVIDE_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else:else:else:else:else:else:else:else:else:else:else:else: */
  if ((*PB_17_Clear_Entry).Notify) {
    keyEvent = KEY_17_CLEAR_ENTRY_Calc;
  }
  else /* IfBlock1:else:else:else:else:else:else:else:else:else:else:else:else:else:else:else:else:else:else: */
  if ((*PB_18_Clear_All).Notify) {
    keyEvent = KEY_18_CLEAR_ALL_Calc;
  }
  else {
    keyEvent = KEY_19_NONE_Calc;
  }
  return keyEvent;
}



/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** PushButtonAdaptor.c
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */


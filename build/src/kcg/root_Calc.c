/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "root_Calc.h"

/* Calc::root/ */
void root_Calc(/* keyEvent/ */ kcg_int32 keyEvent, outC_root_Calc *outC)
{
  kcg_float32 tmp;
  /* @1/_L6/, @1/isDigit/, @2/_L6/, @2/inRange/, SM1:EnterValue1:<2> */
  kcg_bool tr_2_guard_EnterValue1_SM1;
  /* SM1:EnterValue1:<1> */
  kcg_bool tr_1_clock_EnterValue1_SM1;
  /* SM1:EnterValue2:<3> */
  kcg_bool tr_3_guard_EnterValue2_SM1;
  /* SM1:EnterValue2:<2> */
  kcg_bool tr_2_guard_EnterValue2_SM1;
  /* SM1:EnterValue2:<1> */
  kcg_bool tr_1_guard_EnterValue2_SM1;
  /* SM1: */
  SSM_ST_SM1 SM1_state_act;
  /* SM1: */
  kcg_bool SM1_reset_act;

  /* SM1: */
  switch (outC->SM1_state_nxt) {
    case SSM_st_StoreFunction_SM1 :
      SM1_reset_act = (keyEvent >= KEY_00_Calc) & (keyEvent <= KEY_11_NEGATIVE_Calc);
      if (SM1_reset_act) {
        SM1_state_act = SSM_st_EnterValue2_SM1;
      }
      else {
        SM1_state_act = SSM_st_StoreFunction_SM1;
      }
      break;
    case SSM_st_Compute_SM1 :
      SM1_reset_act = keyEvent != KEY_19_NONE_Calc;
      if (SM1_reset_act) {
        SM1_state_act = SSM_st_EnterValue1_SM1;
      }
      else {
        SM1_state_act = SSM_st_Compute_SM1;
      }
      break;
    case SSM_st_EnterValue2_SM1 :
      tr_3_guard_EnterValue2_SM1 = keyEvent == KEY_18_CLEAR_ALL_Calc;
      tr_2_guard_EnterValue2_SM1 = keyEvent == KEY_12_EQUALS_Calc;
      tr_1_guard_EnterValue2_SM1 = keyEvent == KEY_17_CLEAR_ENTRY_Calc;
      if (tr_1_guard_EnterValue2_SM1) {
        SM1_state_act = SSM_st_EnterValue2_SM1;
      }
      else if (tr_2_guard_EnterValue2_SM1) {
        SM1_state_act = SSM_st_Compute_SM1;
      }
      else if (tr_3_guard_EnterValue2_SM1) {
        SM1_state_act = SSM_st_EnterValue1_SM1;
      }
      else {
        SM1_state_act = SSM_st_EnterValue2_SM1;
      }
      SM1_reset_act = tr_1_guard_EnterValue2_SM1 | (tr_2_guard_EnterValue2_SM1 |
          tr_3_guard_EnterValue2_SM1);
      break;
    case SSM_st_EnterValue1_SM1 :
      tr_2_guard_EnterValue1_SM1 = (keyEvent >= KEY_13_PLUS_Calc) & (keyEvent <=
          KEY_16_DIVIDE_Calc);
      tr_1_clock_EnterValue1_SM1 = (keyEvent == KEY_17_CLEAR_ENTRY_Calc) |
        (keyEvent == KEY_18_CLEAR_ALL_Calc);
      SM1_reset_act = tr_1_clock_EnterValue1_SM1 | tr_2_guard_EnterValue1_SM1;
      /* SM1:EnterValue1:<1> */
      if (tr_1_clock_EnterValue1_SM1) {
        SM1_state_act = SSM_st_EnterValue1_SM1;
      }
      else /* SM1:EnterValue1:<2> */
      if (tr_2_guard_EnterValue1_SM1) {
        SM1_state_act = SSM_st_StoreFunction_SM1;
        outC->storedValue = outC->entryValue;
        outC->storedFunction = keyEvent;
      }
      else {
        SM1_state_act = SSM_st_EnterValue1_SM1;
      }
      break;
    default :
      /* this default branch is unreachable */
      break;
  }
  /* SM1: */
  switch (SM1_state_act) {
    case SSM_st_StoreFunction_SM1 :
      outC->SM1_state_nxt = SSM_st_StoreFunction_SM1;
      break;
    case SSM_st_Compute_SM1 :
      tmp = /* SM1:Compute:_L1=(Calc::performFunction#1)/ */
        performFunction_Calc(
          outC->storedValue,
          outC->entryValue,
          outC->storedFunction);
      /* SM1:Compute:_L2=(Calc::Utils::printValue#1)/ */
      printValue_Calc_Utils(tmp, &outC->outputDisplay);
      outC->SM1_state_nxt = SSM_st_Compute_SM1;
      break;
    case SSM_st_EnterValue2_SM1 :
      if (SM1_reset_act) {
        /* SM1:EnterValue2:_L1=(Calc::valueEntry#2)/ */
        valueEntry_reset_Calc(&outC->Context_valueEntry_2);
      }
      /* SM1:EnterValue2:_L1=(Calc::valueEntry#2)/ */
      valueEntry_Calc(keyEvent, &outC->Context_valueEntry_2);
      kcg_copy_array_char_16(
        &outC->outputDisplay,
        &outC->Context_valueEntry_2.valueString);
      outC->entryValue = outC->Context_valueEntry_2.value;
      outC->SM1_state_nxt = SSM_st_EnterValue2_SM1;
      break;
    case SSM_st_EnterValue1_SM1 :
      if (SM1_reset_act) {
        /* SM1:EnterValue1:_L1=(Calc::valueEntry#1)/ */
        valueEntry_reset_Calc(&outC->Context_valueEntry_1);
      }
      /* SM1:EnterValue1:_L1=(Calc::valueEntry#1)/ */
      valueEntry_Calc(keyEvent, &outC->Context_valueEntry_1);
      kcg_copy_array_char_16(
        &outC->outputDisplay,
        &outC->Context_valueEntry_1.valueString);
      outC->entryValue = outC->Context_valueEntry_1.value;
      outC->SM1_state_nxt = SSM_st_EnterValue1_SM1;
      break;
    default :
      /* this default branch is unreachable */
      break;
  }
}

#ifndef KCG_USER_DEFINED_INIT
void root_init_Calc(outC_root_Calc *outC)
{
  /* SM1:EnterValue1:_L1=(Calc::valueEntry#1)/ */
  valueEntry_init_Calc(&outC->Context_valueEntry_1);
  /* SM1:EnterValue2:_L1=(Calc::valueEntry#2)/ */
  valueEntry_init_Calc(&outC->Context_valueEntry_2);
  kcg_copy_array_char_16(
    &outC->outputDisplay,
    (array_char_16 *) &DEFAULT_STRING_Calc);
  outC->storedFunction = KEY_19_NONE_Calc;
  outC->entryValue = kcg_lit_float32(0.0);
  outC->storedValue = kcg_lit_float32(0.0);
  outC->SM1_state_nxt = SSM_st_EnterValue1_SM1;
}
#endif /* KCG_USER_DEFINED_INIT */


#ifndef KCG_NO_EXTERN_CALL_TO_RESET
void root_reset_Calc(outC_root_Calc *outC)
{
  /* SM1:EnterValue1:_L1=(Calc::valueEntry#1)/ */
  valueEntry_reset_Calc(&outC->Context_valueEntry_1);
  /* SM1:EnterValue2:_L1=(Calc::valueEntry#2)/ */
  valueEntry_reset_Calc(&outC->Context_valueEntry_2);
  kcg_copy_array_char_16(
    &outC->outputDisplay,
    (array_char_16 *) &DEFAULT_STRING_Calc);
  outC->storedFunction = KEY_19_NONE_Calc;
  outC->entryValue = kcg_lit_float32(0.0);
  outC->storedValue = kcg_lit_float32(0.0);
  outC->SM1_state_nxt = SSM_st_EnterValue1_SM1;
}
#endif /* KCG_NO_EXTERN_CALL_TO_RESET */

/*
  Expanded instances for: Calc::root/
  @1: (Calc::keyIsFunction#2)
  @2: @1/(Calc::keyInRange#2)
*/

/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** root_Calc.c
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */


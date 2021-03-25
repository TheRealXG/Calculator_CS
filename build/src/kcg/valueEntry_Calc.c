/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "valueEntry_Calc.h"

/* Calc::valueEntry/ */
void valueEntry_Calc(
  /* _L33/, keyEvent/ */
  kcg_int32 keyEvent,
  outC_valueEntry_Calc *outC)
{
  kcg_bool tmp;
  kcg_float32 tmp1;
  /* SM2:IntegerEntry:IfBlock1: */
  kcg_bool IfBlock1_clock_IntegerEntry_SM2;
  /* @1/_L6/,
     @1/isDigit/,
     @2/_L6/,
     @2/inRange/,
     SM2:IntegerEntry:IfBlock1:else:else: */
  kcg_bool else_clock_else_IfBlock1_IntegerEntry_SM2;
  /* SM2:IntegerEntry:IfBlock1:else: */
  kcg_bool else_clock_IfBlock1_IntegerEntry_SM2;
  /* SM2:FractionalEntry:IfBlock1: */
  kcg_bool IfBlock1_clock_FractionalEntry_SM2;
  /* @3/_L6/,
     @3/isDigit/,
     @4/_L6/,
     @4/inRange/,
     SM1:,
     SM1:NegativeSignToggle:<1>,
     SM2:FractionalEntry:IfBlock1:else: */
  kcg_bool else_clock_IfBlock1_FractionalEntry_SM2;
  /* SM2: */
  SSM_ST_SM2 SM2_state_act;

  /* SM2: */
  switch (outC->SM2_state_nxt) {
    case SSM_st_AddDecimalPoint_SM2 :
      SM2_state_act = SSM_st_FractionalEntry_SM2;
      break;
    case SSM_st_FractionalEntry_SM2 :
      SM2_state_act = SSM_st_FractionalEntry_SM2;
      break;
    case SSM_st_IntegerEntry_SM2 :
      if (keyEvent == KEY_10_DECIMAL_Calc) {
        SM2_state_act = SSM_st_AddDecimalPoint_SM2;
      }
      else {
        SM2_state_act = SSM_st_IntegerEntry_SM2;
      }
      break;
    default :
      /* this default branch is unreachable */
      break;
  }
  else_clock_IfBlock1_FractionalEntry_SM2 = keyEvent == KEY_11_NEGATIVE_Calc;
  /* SM1:NegativeSignToggle:<1> */
  if (else_clock_IfBlock1_FractionalEntry_SM2) {
    outC->negativeSign = !outC->negativeSign;
  }
  /* SM2: */
  switch (SM2_state_act) {
    case SSM_st_AddDecimalPoint_SM2 :
      tmp = kcg_true;
      outC->numberLength = outC->numberLength + kcg_lit_int32(1);
      outC->SM2_state_nxt = SSM_st_AddDecimalPoint_SM2;
      break;
    case SSM_st_FractionalEntry_SM2 :
      IfBlock1_clock_FractionalEntry_SM2 = outC->numberLength >= DISPLAY_MAX_Calc;
      /* SM2:FractionalEntry:IfBlock1: */
      if (IfBlock1_clock_FractionalEntry_SM2) {
        tmp = kcg_false;
      }
      else {
        else_clock_IfBlock1_FractionalEntry_SM2 = (keyEvent >= KEY_00_Calc) &
          (keyEvent <= KEY_09_Calc);
        /* SM2:FractionalEntry:IfBlock1:else: */
        if (else_clock_IfBlock1_FractionalEntry_SM2) {
          tmp = kcg_true;
          outC->numberLength = outC->numberLength + kcg_lit_int32(1);
          outC->rightmostDigitValue = outC->rightmostDigitValue / kcg_lit_float32(10.0);
          outC->integerRepresentation = outC->integerRepresentation *
            kcg_lit_int32(10) + keyEvent;
        }
        else {
          tmp = kcg_false;
        }
      }
      outC->SM2_state_nxt = SSM_st_FractionalEntry_SM2;
      break;
    case SSM_st_IntegerEntry_SM2 :
      IfBlock1_clock_IntegerEntry_SM2 = outC->numberLength >= DISPLAY_MAX_Calc;
      /* SM2:IntegerEntry:IfBlock1: */
      if (IfBlock1_clock_IntegerEntry_SM2) {
        tmp = kcg_false;
      }
      else {
        else_clock_IfBlock1_IntegerEntry_SM2 = (outC->integerRepresentation ==
            kcg_lit_int32(0)) & ((keyEvent >= KEY_00_Calc) & (keyEvent <=
              KEY_09_Calc));
        /* SM2:IntegerEntry:IfBlock1:else: */
        if (else_clock_IfBlock1_IntegerEntry_SM2) {
          tmp = keyEvent != KEY_00_Calc;
          outC->integerRepresentation = keyEvent;
        }
        else {
          else_clock_else_IfBlock1_IntegerEntry_SM2 = (keyEvent >=
              KEY_00_Calc) & (keyEvent <= KEY_09_Calc);
          /* SM2:IntegerEntry:IfBlock1:else:else: */
          if (else_clock_else_IfBlock1_IntegerEntry_SM2) {
            tmp = kcg_true;
            outC->numberLength = outC->numberLength + kcg_lit_int32(1);
            outC->integerRepresentation = outC->integerRepresentation *
              kcg_lit_int32(10) + keyEvent;
          }
          else {
            tmp = kcg_false;
          }
        }
      }
      outC->SM2_state_nxt = SSM_st_IntegerEntry_SM2;
      break;
    default :
      /* this default branch is unreachable */
      break;
  }
  /* _L29=(Calc::Utils::updateDisplay#1)/ */
  updateDisplay_Calc_Utils(
    keyEvent,
    outC->negativeSign,
    tmp,
    outC->numberLength,
    &outC->Context_updateDisplay_1);
  kcg_copy_array_char_16(
    &outC->valueString,
    &outC->Context_updateDisplay_1.valueString);
  /* _L24= */
  if (outC->negativeSign) {
    tmp1 = kcg_lit_float32(-1.0);
  }
  else {
    tmp1 = kcg_lit_float32(1.0);
  }
  outC->value = /* _L34= */(kcg_float32) outC->integerRepresentation *
    outC->rightmostDigitValue * tmp1;
}

#ifndef KCG_USER_DEFINED_INIT
void valueEntry_init_Calc(outC_valueEntry_Calc *outC)
{
  kcg_size idx;

  outC->negativeSign = kcg_false;
  for (idx = 0; idx < 16; idx++) {
    outC->valueString[idx] = ' ';
  }
  outC->value = kcg_lit_float32(0.0);
  /* _L29=(Calc::Utils::updateDisplay#1)/ */
  updateDisplay_init_Calc_Utils(&outC->Context_updateDisplay_1);
  outC->rightmostDigitValue = kcg_lit_float32(1.0);
  outC->integerRepresentation = kcg_lit_int32(0);
  outC->numberLength = kcg_lit_int32(1);
  outC->SM2_state_nxt = SSM_st_IntegerEntry_SM2;
}
#endif /* KCG_USER_DEFINED_INIT */


void valueEntry_reset_Calc(outC_valueEntry_Calc *outC)
{
  outC->negativeSign = kcg_false;
  /* _L29=(Calc::Utils::updateDisplay#1)/ */
  updateDisplay_reset_Calc_Utils(&outC->Context_updateDisplay_1);
  outC->rightmostDigitValue = kcg_lit_float32(1.0);
  outC->integerRepresentation = kcg_lit_int32(0);
  outC->numberLength = kcg_lit_int32(1);
  outC->SM2_state_nxt = SSM_st_IntegerEntry_SM2;
}

/*
  Expanded instances for: Calc::valueEntry/
  @1: (Calc::keyIsDigit#1)
  @2: @1/(Calc::keyInRange#1)
  @3: (Calc::keyIsDigit#2)
  @4: @3/(Calc::keyInRange#1)
*/

/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** valueEntry_Calc.c
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */


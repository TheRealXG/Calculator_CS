/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "updateDisplay_Calc_Utils.h"

/* Calc::Utils::updateDisplay/ */
void updateDisplay_Calc_Utils(
  /* _L8/, keyEvent/ */
  kcg_int32 keyEvent,
  /* IfBlock1:, negativeSign/ */
  kcg_bool negativeSign,
  /* _L4/, validKeyPress/ */
  kcg_bool validKeyPress,
  /* _L15/, numberLength/ */
  kcg_int32 numberLength,
  outC_updateDisplay_Calc_Utils *outC)
{
  kcg_char tmp;
  /* _L5/ */
  kcg_int32 _L5;

  /* _L5= */
  if (validKeyPress) {
    _L5 = numberLength - kcg_lit_int32(1);
  }
  else {
    _L5 = kcg_lit_int32(-1);
  }
  tmp = /* _L9=(Calc::key2Char#1)/ */ key2Char_Calc(keyEvent);
  if ((kcg_lit_int32(0) <= _L5) & (_L5 < kcg_lit_int32(16))) {
    outC->absoluteValueString[_L5] = tmp;
  }
  if ((kcg_lit_int32(0) <= numberLength) & (numberLength < kcg_lit_int32(16))) {
    outC->absoluteValueString[numberLength] = NUL_Calc_Utils;
  }
  /* IfBlock1: */
  if (negativeSign) {
    outC->valueString[0] = '-';
    kcg_copy_array_char_15(
      &outC->valueString[1],
      (array_char_15 *) &outC->absoluteValueString[0]);
  }
  else {
    kcg_copy_array_char_16(&outC->valueString, &outC->absoluteValueString);
  }
}

#ifndef KCG_USER_DEFINED_INIT
void updateDisplay_init_Calc_Utils(outC_updateDisplay_Calc_Utils *outC)
{
  kcg_size idx;

  for (idx = 0; idx < 16; idx++) {
    outC->valueString[idx] = ' ';
  }
  kcg_copy_array_char_16(
    &outC->absoluteValueString,
    (array_char_16 *) &DEFAULT_STRING_Calc);
}
#endif /* KCG_USER_DEFINED_INIT */


void updateDisplay_reset_Calc_Utils(outC_updateDisplay_Calc_Utils *outC)
{
  kcg_copy_array_char_16(
    &outC->absoluteValueString,
    (array_char_16 *) &DEFAULT_STRING_Calc);
}



/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** updateDisplay_Calc_Utils.c
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */


/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "Calc_A661_Root.h"

/* Calc_A661_Root/ */
void Calc_A661_Root(inC_Calc_A661_Root *inC, outC_Calc_A661_Root *outC)
{
  /* _L1=(Calc::root#1)/ */
  root_Calc(
    /* _L2=(PushButtonAdaptor#1)/ */
    PushButtonAdaptor(
      &inC->PB_00,
      &inC->PB_01,
      &inC->PB_02,
      &inC->PB_03,
      &inC->PB_04,
      &inC->PB_05,
      &inC->PB_06,
      &inC->PB_07,
      &inC->PB_08,
      &inC->PB_09,
      &inC->PB_10_Decimal,
      &inC->PB_11_Negative,
      &inC->PB_12_Equals,
      &inC->PB_13_Plus,
      &inC->PB_14_Minus,
      &inC->PB_15_Times,
      &inC->PB_16_Divide,
      &inC->PB_17_Clear_Entry,
      &inC->PB_18_Clear_All),
    &outC->Context_root_1);
  /* _L22=(a661_util::SendStringOnValChanged#1)/ */
  SendStringOnValChanged_a661_util_16(
    &outC->Context_root_1.outputDisplay,
    &outC->Context_SendStringOnValChanged_1);
  kcg_copy_msg_string16(
    &outC->displayText,
    &outC->Context_SendStringOnValChanged_1.o_16);
}

#ifndef KCG_USER_DEFINED_INIT
void Calc_A661_Root_init(outC_Calc_A661_Root *outC)
{
  kcg_size idx;

  outC->displayText.Emit = kcg_true;
  outC->displayText.String_size = kcg_lit_uint16(0);
  for (idx = 0; idx < 16; idx++) {
    outC->displayText.LabelString[idx] = ' ';
  }
  /* _L22=(a661_util::SendStringOnValChanged#1)/ */
  SendStringOnValChanged_init_a661_util_16(
    &outC->Context_SendStringOnValChanged_1);
  /* _L1=(Calc::root#1)/ */ root_init_Calc(&outC->Context_root_1);
}
#endif /* KCG_USER_DEFINED_INIT */


#ifndef KCG_NO_EXTERN_CALL_TO_RESET
void Calc_A661_Root_reset(outC_Calc_A661_Root *outC)
{
  /* _L22=(a661_util::SendStringOnValChanged#1)/ */
  SendStringOnValChanged_reset_a661_util_16(
    &outC->Context_SendStringOnValChanged_1);
  /* _L1=(Calc::root#1)/ */ root_reset_Calc(&outC->Context_root_1);
}
#endif /* KCG_NO_EXTERN_CALL_TO_RESET */



/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Calc_A661_Root.c
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */


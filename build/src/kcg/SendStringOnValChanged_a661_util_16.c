/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "SendStringOnValChanged_a661_util_16.h"

/* a661_util::SendStringOnValChanged/ */
void SendStringOnValChanged_a661_util_16(
  /* i/ */
  array_char_16 *i_16,
  outC_SendStringOnValChanged_a661_util_16 *outC)
{
  outC->o_16.Emit = (!outC->init) & (!kcg_comp_array_char_16(
        i_16,
        &outC->mem_i_16));
  outC->init = kcg_false;
  outC->o_16.String_size = kcg_lit_uint16(16);
  kcg_copy_array_char_16(&outC->o_16.LabelString, i_16);
  kcg_copy_array_char_16(&outC->mem_i_16, i_16);
}

#ifndef KCG_USER_DEFINED_INIT
void SendStringOnValChanged_init_a661_util_16(
  outC_SendStringOnValChanged_a661_util_16 *outC)
{
  kcg_size idx;

  outC->init = kcg_true;
  outC->o_16.Emit = kcg_true;
  outC->o_16.String_size = kcg_lit_uint16(0);
  for (idx = 0; idx < 16; idx++) {
    outC->mem_i_16[idx] = ' ';
    outC->o_16.LabelString[idx] = ' ';
  }
}
#endif /* KCG_USER_DEFINED_INIT */


#ifndef KCG_NO_EXTERN_CALL_TO_RESET
void SendStringOnValChanged_reset_a661_util_16(
  outC_SendStringOnValChanged_a661_util_16 *outC)
{
  outC->init = kcg_true;
}
#endif /* KCG_NO_EXTERN_CALL_TO_RESET */



/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** SendStringOnValChanged_a661_util_16.c
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */


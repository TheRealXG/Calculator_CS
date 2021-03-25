/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */
#ifndef _Calc_A661_Root_H_
#define _Calc_A661_Root_H_

#include "kcg_types.h"
#include "PushButtonAdaptor.h"
#include "SendStringOnValChanged_a661_util_16.h"
#include "root_Calc.h"

/* ========================  input structure  ====================== */
typedef struct {
  msg_notify /* PB_00/, _L3/ */ PB_00;
  msg_notify /* PB_01/, _L4/ */ PB_01;
  msg_notify /* PB_02/, _L5/ */ PB_02;
  msg_notify /* PB_03/, _L6/ */ PB_03;
  msg_notify /* PB_04/, _L7/ */ PB_04;
  msg_notify /* PB_05/, _L8/ */ PB_05;
  msg_notify /* PB_06/, _L9/ */ PB_06;
  msg_notify /* PB_07/, _L10/ */ PB_07;
  msg_notify /* PB_08/, _L11/ */ PB_08;
  msg_notify /* PB_09/, _L12/ */ PB_09;
  msg_notify /* PB_10_Decimal/, _L13/ */ PB_10_Decimal;
  msg_notify /* PB_11_Negative/, _L14/ */ PB_11_Negative;
  msg_notify /* PB_12_Equals/, _L15/ */ PB_12_Equals;
  msg_notify /* PB_13_Plus/, _L16/ */ PB_13_Plus;
  msg_notify /* PB_14_Minus/, _L17/ */ PB_14_Minus;
  msg_notify /* PB_15_Times/, _L18/ */ PB_15_Times;
  msg_notify /* PB_16_Divide/, _L19/ */ PB_16_Divide;
  msg_notify /* PB_17_Clear_Entry/, _L20/ */ PB_17_Clear_Entry;
  msg_notify /* PB_18_Clear_All/, _L21/ */ PB_18_Clear_All;
} inC_Calc_A661_Root;

/* =====================  no output structure  ====================== */

/* ========================  context type  ========================= */
typedef struct {
  /* ---------------------------  outputs  --------------------------- */
  msg_string16 /* _L22/, displayText/ */ displayText;
  /* -----------------------  no local probes  ----------------------- */
  /* -----------------------  no local memory  ----------------------- */
  /* ---------------------  sub nodes' contexts  --------------------- */
  outC_SendStringOnValChanged_a661_util_16 /* _L22=(a661_util::SendStringOnValChanged#1)/ */ Context_SendStringOnValChanged_1;
  outC_root_Calc /* _L1=(Calc::root#1)/ */ Context_root_1;
  /* ----------------- no clocks of observable data ------------------ */
} outC_Calc_A661_Root;

/* ===========  node initialization and cycle functions  =========== */
/* Calc_A661_Root/ */
extern void Calc_A661_Root(inC_Calc_A661_Root *inC, outC_Calc_A661_Root *outC);

#ifndef KCG_NO_EXTERN_CALL_TO_RESET
extern void Calc_A661_Root_reset(outC_Calc_A661_Root *outC);
#endif /* KCG_NO_EXTERN_CALL_TO_RESET */

#ifndef KCG_USER_DEFINED_INIT
extern void Calc_A661_Root_init(outC_Calc_A661_Root *outC);
#endif /* KCG_USER_DEFINED_INIT */



#endif /* _Calc_A661_Root_H_ */
/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Calc_A661_Root.h
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */


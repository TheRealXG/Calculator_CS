/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:15
*************************************************************$ */
#ifndef _valueEntry_Calc_H_
#define _valueEntry_Calc_H_

#include "kcg_types.h"
#include "updateDisplay_Calc_Utils.h"

/* =====================  no input structure  ====================== */

/* =====================  no output structure  ====================== */

/* ========================  context type  ========================= */
typedef struct {
  /* ---------------------------  outputs  --------------------------- */
  kcg_float32 /* _L22/, value/ */ value;
  array_char_16 /* _L29/, valueString/ */ valueString;
  /* -----------------------  no local probes  ----------------------- */
  /* ----------------------- local memories  ------------------------- */
  SSM_ST_SM2 /* SM2: */ SM2_state_nxt;
  kcg_bool /* negativeSign/ */ negativeSign;
  kcg_float32 /* rightmostDigitValue/ */ rightmostDigitValue;
  kcg_int32 /* numberLength/ */ numberLength;
  kcg_int32 /* integerRepresentation/ */ integerRepresentation;
  /* ---------------------  sub nodes' contexts  --------------------- */
  outC_updateDisplay_Calc_Utils /* _L29=(Calc::Utils::updateDisplay#1)/ */ Context_updateDisplay_1;
  /* ----------------- no clocks of observable data ------------------ */
} outC_valueEntry_Calc;

/* ===========  node initialization and cycle functions  =========== */
/* Calc::valueEntry/ */
extern void valueEntry_Calc(
  /* _L33/, keyEvent/ */
  kcg_int32 keyEvent,
  outC_valueEntry_Calc *outC);

extern void valueEntry_reset_Calc(outC_valueEntry_Calc *outC);

#ifndef KCG_USER_DEFINED_INIT
extern void valueEntry_init_Calc(outC_valueEntry_Calc *outC);
#endif /* KCG_USER_DEFINED_INIT */



#endif /* _valueEntry_Calc_H_ */
/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** valueEntry_Calc.h
** Generation date: 2021-03-18T11:28:15
*************************************************************$ */


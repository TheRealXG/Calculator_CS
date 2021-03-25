/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:15
*************************************************************$ */
#ifndef _updateDisplay_Calc_Utils_H_
#define _updateDisplay_Calc_Utils_H_

#include "kcg_types.h"
#include "key2Char_Calc.h"

/* =====================  no input structure  ====================== */

/* =====================  no output structure  ====================== */

/* ========================  context type  ========================= */
typedef struct {
  /* ---------------------------  outputs  --------------------------- */
  array_char_16 /* valueString/ */ valueString;
  /* -----------------------  no local probes  ----------------------- */
  /* ----------------------- local memories  ------------------------- */
  array_char_16 /* absoluteValueString/ */ absoluteValueString;
  /* -------------------- no sub nodes' contexts  -------------------- */
  /* ----------------- no clocks of observable data ------------------ */
} outC_updateDisplay_Calc_Utils;

/* ===========  node initialization and cycle functions  =========== */
/* Calc::Utils::updateDisplay/ */
extern void updateDisplay_Calc_Utils(
  /* _L8/, keyEvent/ */
  kcg_int32 keyEvent,
  /* IfBlock1:, negativeSign/ */
  kcg_bool negativeSign,
  /* _L4/, validKeyPress/ */
  kcg_bool validKeyPress,
  /* _L15/, numberLength/ */
  kcg_int32 numberLength,
  outC_updateDisplay_Calc_Utils *outC);

extern void updateDisplay_reset_Calc_Utils(outC_updateDisplay_Calc_Utils *outC);

#ifndef KCG_USER_DEFINED_INIT
extern void updateDisplay_init_Calc_Utils(outC_updateDisplay_Calc_Utils *outC);
#endif /* KCG_USER_DEFINED_INIT */



#endif /* _updateDisplay_Calc_Utils_H_ */
/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** updateDisplay_Calc_Utils.h
** Generation date: 2021-03-18T11:28:15
*************************************************************$ */


/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */
#ifndef _SendStringOnValChanged_a661_util_16_H_
#define _SendStringOnValChanged_a661_util_16_H_

#include "kcg_types.h"

/* =====================  no input structure  ====================== */

/* =====================  no output structure  ====================== */

/* ========================  context type  ========================= */
typedef struct {
  /* ---------------------------  outputs  --------------------------- */
  msg_string16 /* o/ */ o_16;
  /* -----------------------  no local probes  ----------------------- */
  /* ----------------------- local memories  ------------------------- */
  array_char_16 /* i/ */ mem_i_16;
  kcg_bool init;
  /* -------------------- no sub nodes' contexts  -------------------- */
  /* ----------------- no clocks of observable data ------------------ */
} outC_SendStringOnValChanged_a661_util_16;

/* ===========  node initialization and cycle functions  =========== */
/* a661_util::SendStringOnValChanged/ */
extern void SendStringOnValChanged_a661_util_16(
  /* i/ */
  array_char_16 *i_16,
  outC_SendStringOnValChanged_a661_util_16 *outC);

#ifndef KCG_NO_EXTERN_CALL_TO_RESET
extern void SendStringOnValChanged_reset_a661_util_16(
  outC_SendStringOnValChanged_a661_util_16 *outC);
#endif /* KCG_NO_EXTERN_CALL_TO_RESET */

#ifndef KCG_USER_DEFINED_INIT
extern void SendStringOnValChanged_init_a661_util_16(
  outC_SendStringOnValChanged_a661_util_16 *outC);
#endif /* KCG_USER_DEFINED_INIT */



#endif /* _SendStringOnValChanged_a661_util_16_H_ */
/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** SendStringOnValChanged_a661_util_16.h
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */


/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "performFunction_Calc.h"

/* Calc::performFunction/ */
kcg_float32 performFunction_Calc(
  /* value1/ */
  kcg_float32 value1,
  /* value2/ */
  kcg_float32 value2,
  /* f/ */
  kcg_int32 f)
{
  /* IfBlock1:else: */
  kcg_bool else_clock_IfBlock1;
  /* IfBlock1:else:else:else: */
  kcg_bool else_clock_else_else_IfBlock1;
  /* IfBlock1:else:else: */
  kcg_bool else_clock_else_IfBlock1;
  /* IfBlock1: */
  kcg_bool IfBlock1_clock;
  /* output/ */
  kcg_float32 output;

  IfBlock1_clock = f == KEY_13_PLUS_Calc;
  /* IfBlock1: */
  if (IfBlock1_clock) {
    output = value1 + value2;
  }
  else {
    else_clock_IfBlock1 = f == KEY_14_MINUS_Calc;
    /* IfBlock1:else: */
    if (else_clock_IfBlock1) {
      output = value1 - value2;
    }
    else {
      else_clock_else_IfBlock1 = f == KEY_15_TIMES_Calc;
      /* IfBlock1:else:else: */
      if (else_clock_else_IfBlock1) {
        output = value1 * value2;
      }
      else {
        else_clock_else_else_IfBlock1 = (f == KEY_16_DIVIDE_Calc) & (value2 !=
            kcg_lit_float32(0.0));
        /* IfBlock1:else:else:else: */
        if (else_clock_else_else_IfBlock1) {
          output = value1 / value2;
        }
        else {
          output = kcg_lit_float32(0.);
        }
      }
    }
  }
  return output;
}



/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** performFunction_Calc.c
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */


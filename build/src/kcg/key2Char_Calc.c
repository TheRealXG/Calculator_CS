/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** Command: kcg661.exe -config config_kcg.txt
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */

#include "kcg_consts.h"
#include "kcg_sensors.h"
#include "key2Char_Calc.h"

/* Calc::key2Char/ */
kcg_char key2Char_Calc(/* keyEvent/ */ kcg_int32 keyEvent)
{
  /* IfBlock1:else: */
  kcg_bool else_clock_IfBlock1;
  /* IfBlock1:else:else:else: */
  kcg_bool else_clock_else_else_IfBlock1;
  /* IfBlock1:else:else:else:else:else: */
  kcg_bool else_clock_else_else_else_else_IfBlock1;
  /* IfBlock1:else:else:else:else:else:else:else: */
  kcg_bool _1_else_clock_else_else_else_else_else_else_IfBlock1;
  /* IfBlock1:else:else:else:else:else:else:else:else:else: */
  kcg_bool _2_else_clock_else_else_else_else_else_else_else_else_IfBlock1;
  /* IfBlock1:else:else:else:else:else:else:else:else:else:else: */
  kcg_bool _3_else_clock_else_else_else_else_else_else_else_else_else_IfBlock1;
  /* IfBlock1:else:else:else:else:else:else:else:else: */
  kcg_bool _4_else_clock_else_else_else_else_else_else_else_IfBlock1;
  /* IfBlock1:else:else:else:else:else:else: */
  kcg_bool _5_else_clock_else_else_else_else_else_IfBlock1;
  /* IfBlock1:else:else:else:else: */
  kcg_bool else_clock_else_else_else_IfBlock1;
  /* IfBlock1:else:else: */
  kcg_bool else_clock_else_IfBlock1;
  /* IfBlock1: */
  kcg_bool IfBlock1_clock;
  /* charOut/ */
  kcg_char charOut;

  IfBlock1_clock = keyEvent == KEY_00_Calc;
  /* IfBlock1: */
  if (IfBlock1_clock) {
    charOut = '0';
  }
  else {
    else_clock_IfBlock1 = keyEvent == KEY_01_Calc;
    /* IfBlock1:else: */
    if (else_clock_IfBlock1) {
      charOut = '1';
    }
    else {
      else_clock_else_IfBlock1 = keyEvent == KEY_02_Calc;
      /* IfBlock1:else:else: */
      if (else_clock_else_IfBlock1) {
        charOut = '2';
      }
      else {
        else_clock_else_else_IfBlock1 = keyEvent == KEY_03_Calc;
        /* IfBlock1:else:else:else: */
        if (else_clock_else_else_IfBlock1) {
          charOut = '3';
        }
        else {
          else_clock_else_else_else_IfBlock1 = keyEvent == KEY_04_Calc;
          /* IfBlock1:else:else:else:else: */
          if (else_clock_else_else_else_IfBlock1) {
            charOut = '4';
          }
          else {
            else_clock_else_else_else_else_IfBlock1 = keyEvent == KEY_05_Calc;
            /* IfBlock1:else:else:else:else:else: */
            if (else_clock_else_else_else_else_IfBlock1) {
              charOut = '5';
            }
            else {
              _5_else_clock_else_else_else_else_else_IfBlock1 = keyEvent == KEY_06_Calc;
              /* IfBlock1:else:else:else:else:else:else: */
              if (_5_else_clock_else_else_else_else_else_IfBlock1) {
                charOut = '6';
              }
              else {
                _1_else_clock_else_else_else_else_else_else_IfBlock1 = keyEvent == KEY_07_Calc;
                /* IfBlock1:else:else:else:else:else:else:else: */
                if (_1_else_clock_else_else_else_else_else_else_IfBlock1) {
                  charOut = '7';
                }
                else {
                  _4_else_clock_else_else_else_else_else_else_else_IfBlock1 =
                    keyEvent == KEY_08_Calc;
                  /* IfBlock1:else:else:else:else:else:else:else:else: */
                  if (_4_else_clock_else_else_else_else_else_else_else_IfBlock1) {
                    charOut = '8';
                  }
                  else {
                    _2_else_clock_else_else_else_else_else_else_else_else_IfBlock1 =
                      keyEvent == KEY_09_Calc;
                    /* IfBlock1:else:else:else:else:else:else:else:else:else: */
                    if (_2_else_clock_else_else_else_else_else_else_else_else_IfBlock1) {
                      charOut = '9';
                    }
                    else {
                      _3_else_clock_else_else_else_else_else_else_else_else_else_IfBlock1 =
                        keyEvent == KEY_10_DECIMAL_Calc;
                      /* IfBlock1:else:else:else:else:else:else:else:else:else:else: */
                      if (_3_else_clock_else_else_else_else_else_else_else_else_else_IfBlock1) {
                        charOut = '.';
                      }
                      else {
                        charOut = '0';
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return charOut;
}



/* $******* SCADE Suite KCG 32-bit 6.6.1 beta (build i1) ********
** key2Char_Calc.c
** Generation date: 2021-03-18T11:28:16
*************************************************************$ */


/*********************************************************
 **
 ** File  Operator1_UAA_LAY_1.c
 **
 ** Automatically generated by ANSYS(R) SCADE Suite(R) - UA Adaptor Code Generator
 ** Version 2021 R1 (build 20201118T194807)
 ** 
 ** Date of generation: 2021-03-18T11:28:55
 ** Command line: C:\Program Files\ANSYS Inc\v211\SCADE\SCADE\bin\uaadaptor.exe -sdy ..\Calculator\Calculator.sdy -n a661_description\a661.xml -outdir src\uaadaptor -k ..\Calculator\KCG\kcg_trace.xml -o Operator1_UAA -i Operator1.h -encoding ASCII ..\Calculator_A661\CalculatorPanel.sgfx
 *********************************************************/
#include "kcg_sensors.h"
#include "Operator1_UAA.h"
#include "Operator1_UAA_constants.h"
#include "Operator1_UAA_private.h"

/* Perform UA Request for layer 1 */
A661_INTERNAL uaa_size a661_com_A661_CMD_UA_REQUEST_layer_1(buffer_el msg[], 
  outC_Calc_A661_Root* scade_ctx,  extern_out_ctx_t * extern_ctx){
  uaa_size offset = 0;
  return offset ;
}

/* Pack messages for layer 1 */
 uaa_size a661_com_layer_1(buffer_el msg[], 
  outC_Calc_A661_Root* scade_ctx,  extern_out_ctx_t* extern_ctx){
  uaa_size offset = 0;
  if (scade_ctx->displayText.Emit){
    LAYER("a661_layer#1");
    offset = 8;
    a661_msg_cmd_header(msg, 1, Operator1_UAA_DEFAULT_CONTEXT_NUMBER);
    if (scade_ctx->displayText.Emit){
      WIDGET("Label#1");
      offset = offset + a661_com_csp_widget_Label(msg + offset, 1,
        scade_ctx->displayText.Emit, 16, scade_ctx->displayText.LabelString,
        scade_ctx->displayText.String_size);
    }
    WRITE_ULONG(msg + offset, A661_END_BLOCK);
    offset = offset + 4;
    WRITE_ULONG(msg + 4, offset);
  }
  return offset ;
}

/*********************************************************
 ** End of file
 ** End of generation: 2021-03-18T11:28:55
 *********************************************************/

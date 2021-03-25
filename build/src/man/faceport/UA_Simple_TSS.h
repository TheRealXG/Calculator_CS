#ifndef UA_SIMPLE_TSS_H
#define UA_SIMPLE_TSS_H

#include "FACE/TSS/Base_Injectable.h"
#include "FACE/TSS/DataModel/tCmdsInIDLS/TypedTS_Injectable.h"
#include "FACE/TSS/DataModel/tCmdsOutIDLS/TypedTS_Injectable.h"

void UA_Simple_TSS_Base_Inject(FACE_TSS_Base_Injectable_Injectable *injectable);
void UA_Simple_TSS_DataModel_tCmdsInIDLS_TypedTS_Inject(FACE_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_Injectable *injectable);
void UA_Simple_TSS_DataModel_tCmdsOutIDLS_TypedTS_Inject(FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_Injectable *injectable);

#endif /* UA_SIMPLE_TSS_H */

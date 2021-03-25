/*
 * memcpy must be provided to copy non-scalar data.
   The SCADE installation uses <string.h> for all host (Windows) builds
   For a more realistic target build, a simple public domain version is used.
 */

#ifndef kcg_assign

#include "memcpy.h"
#define kcg_assign(kcg_D, kcg_S, kcg_sz) (memcpy((kcg_D), (kcg_S), (kcg_sz)))
#endif

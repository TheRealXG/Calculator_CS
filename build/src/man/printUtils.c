/*NOTE: The emphasis of the current calculator demo is to focus on requirements and 
  workflow. Therefore, a quick string helper function is employed here.
  On an actual embedded project, we would not rely on stdio or this style of coding*/
  
#include "kcg_types.h"
#include <stdio.h>
#include <string.h>

#if _MSC_VER
#define snprintf _snprintf
#endif

const kcg_char NUL_Calc_Utils = 0;

typedef kcg_char my_array_char_16[16];

const int STRSZ = 16;

void printValue_Calc_Utils(
  kcg_float32 value,
  array_char_16 *displayValue)
{
    char *p;
    int count;

    /* print the number with printf */
    char fmt[10] = "%.5f";
    snprintf((char *)displayValue, STRSZ, "%.8f", value);

    /*remove trailing zeros*/
    /* reference: https://stackoverflow.com/questions/277772/avoid-trailing-zeroes-in-printf */

    p = strchr ((char *) displayValue,'.');         // Find decimal point, if any.
    if (p != NULL) {
        count = 5;              // Adjust for more or less decimals.
        while (count >= 0) {    // Maximum decimals allowed.
             count--;
             if (*p == '\0')    // If there's less than desired.
                 break;
             p++;               // Next character.
        }

        *p-- = '\0';            // Truncate string.
        while (*p == '0')       // Remove trailing zeros.
            *p-- = '\0';

        if (*p == '.') {        // If all decimals were zeros, remove ".".
            *p = '\0';
        }
    }

}
  

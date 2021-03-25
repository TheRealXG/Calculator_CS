/*+ FILE DESCRIPTION -------------------------------------------------------
Filename:    utils.c
Description: Integration porting implementation: utilities

Copyright (C) 2020 ANSYS, Inc. ALL RIGHTS RESERVED.
Copyright (C) 2011 ESTEREL TECHNOLOGIES SAS. ALL RIGHTS RESERVED.
This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.

Warranty
ANSYS, Inc. makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose
---------------------------------------------------------------------------- +*/

#include <a661_types.h>
#include <a661_utils.h>

#include "srvport.h"

/* Heapsort implementation to replace stdlib qsort */

void a661_sort(void *base, size_t nel, size_t width, int (*compar) (const void *, const void *))
{
    /* access one element */
#define ELEM(X) (((char*)base) + (width * (X)))

    size_t i;
    size_t j;
    size_t child;
    size_t parent;
    char *mem1;
    char *mem2;
    char tmp;

    /* First build a heap on the array */
    for (i = 1; i < nel; i++) {
        child = i;
        while (child > 0) {
            parent = (child - 1) / 2;
            /* Ensure parent is greater than child */
            if (compar(ELEM(parent), ELEM(child)) < 0) {
                /* Swap parent and child */
                for (j = 0, mem1 = ELEM(parent), mem2 = ELEM(child); j < width; j++, mem1++, mem2++) {
                    tmp = *mem1;
                    *mem1 = *mem2;
                    *mem2 = tmp;
                }
                child = parent;
            }
            else {
                /* Exit loop */
                child = 0;
            }
        }
    }

    /* Then iteratively place in last position the maximum value */
    while (nel > 1) {
        /* Swap element 0 (root of the heap, thus maximum element) and last element */
        for (j = 0, mem1 = ELEM(0), mem2 = ELEM(nel - 1); j < width; j++, mem1++, mem2++) {
            tmp = *mem1;
            *mem1 = *mem2;
            *mem2 = tmp;
        }
        /* Reduce the size of heap by one and repair it */
        nel = nel - 1;
        /* Fix a max-heap by pushing down the root value until the heap property is restored */
        for (parent = 0, child = 1; child < nel;) {
            /* Ensure parent is greater than its two children */
            i = parent;
            /* Check if left child is greater than parent */
            if (compar(ELEM(i), ELEM(child)) < 0) {
                i = child;
            }
            /* Check if right child (if it exists) is greater than parent or left child */
            if ((child + 1 < nel) && (compar(ELEM(i), ELEM(child + 1)) < 0)) {
                i = child + 1;
            }
            if (parent != i) {
                /* Swap child and parent */
                for (j = 0, mem1 = ELEM(i), mem2 = ELEM(parent); j < width; j++, mem1++, mem2++) {
                    tmp = *mem1;
                    *mem1 = *mem2;
                    *mem2 = tmp;
                }
                parent = i;
                child = (2 * parent) + 1;
            }
            else {
                /* Exit loop */
                child = nel;
            }
        }
    }
}

/* String length (a661_strlen is depecrated since 2021R1) */

a661_ushort a661_strlen(const a661_string s)
{
    return (a661_ushort) ((s == NULL) ? 0U : strlen((const char_t *) s));
}

/* String length with max */

a661_ulong a661_strnlen(const a661_string s, a661_ulong max)
{
    a661_ulong len;
    if (s == NULL) {
        len = 0U;
        a661_report_simple_error_format1("%sNULL string pointer used in a661_strnlen() function => %ld returned", "", 0L);
    }
    else {
        len = (a661_ulong) strnlen((const char_t *) s, (size_t)max);
        if (len == max) {
            a661_report_simple_error_format1("%sNo string terminator character found for a661_strnlen() function => max string length (%ld) returned", "", (a661_long)max);
        }
    }
    return len;
}

/* String compare */

int a661_streq(const char *a, const char *b)
{
    return (strcmp(a, b) == 0);
}

/*=== srvport specifics utility functions ===*/

/* String conversion */

a661_uchar srvport_str2integer(const char *value, a661_long * result)
{
    a661_uchar ok = 0U;
    char *tmp;

    if (value != NULL && *value != '\0') {
        errno = 0;              /* strtol only sets errno if out of range */
        *result = strtol(value, &tmp, 0);
        if (0 == errno && tmp != value && '\0' == *tmp) {
            ok = 1U;
        }
    }
    return ok;
}

a661_uchar srvport_str2unsigned(const char *value, a661_ulong * result)
{
    a661_uchar ok = 0U;
    char *tmp;

    if (value != NULL && *value != '\0') {
        errno = 0;              /* strtoul only sets errno if out of range */
        *result = strtoul(value, &tmp, 0);
        if (0 == errno && tmp != value && '\0' == *tmp) {
            ok = 1U;
        }
    }
    return ok;
}

a661_uchar srvport_str2bool(const char *value, a661_uchar * result)
{
    a661_uchar ok = 1U;

    if (a661_streq(value, "false") || a661_streq(value, "0")) {
        *result = (a661_uchar) 0U;
    }
    else if (a661_streq(value, "true") || a661_streq(value, "1")) {
        *result = (a661_uchar) 1U;
    }
    else {
        ok = 0U;
    }

    return ok;
}

a661_uchar srvport_str2float(const char *value, a661_float * result)
{
    a661_uchar ok = 0U;
    char *tmp;

    if (value != NULL && *value != '\0') {
        errno = 0;              /* strtod only sets errno if out of range */
        *result = strtof(value, &tmp);
        if (0 == errno && tmp != value && '\0' == *tmp) {
            ok = 1U;
        }
    }
    return ok;
}

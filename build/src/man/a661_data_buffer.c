/*+ FILE DESCRIPTION -------------------------------------------------------
Filename:    a661_data_buffer.c
Description: Server Core implementation: Memory buffer management

Copyright (C) 2020 ANSYS, Inc. ALL RIGHTS RESERVED.
Copyright (C) 2011 ESTEREL TECHNOLOGIES SAS. ALL RIGHTS RESERVED.
This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.

Warranty
ANSYS, Inc. makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose
---------------------------------------------------------------------------- +*/

#include <malloc.h>
#include <string.h>
#include <stdio.h>

#include "a661_data_buffer.h"

#ifdef A661_DATA_BUFFER_FIXED_SIZE
/* ----------------------------------------------------------------------------------- */
a661_data_error_t a661_data_buffer_init(a661_data_buffer* buf, a661_ulong ignored_sz)
{
    buf->getter = 0;
    buf->count   = 0;
    buf->alloc   = A661_DATA_BUFFER_FIXED_SIZE;
    return (buf->alloc == 0) ? A661_DATA_ERR : A661_DATA_OK;
}
/* ----------------------------------------------------------------------------------- */
a661_data_error_t a661_data_buffer_free(a661_data_buffer* buf)
{
    return A661_DATA_OK;
}
#else
/* ----------------------------------------------------------------------------------- */
a661_data_error_t a661_data_buffer_init(a661_data_buffer* buf, a661_ulong sz)
{
    buf->b = (a661_uchar*) malloc(sz);
    if (buf->b != NULL) {
        buf->getter = 0;
        buf->count  = 0;
        buf->alloc  = sz;
    }
    return (buf == NULL) ? A661_DATA_ERR : A661_DATA_OK;
}
/* ----------------------------------------------------------------------------------- */
a661_data_error_t a661_data_buffer_free(a661_data_buffer* buf)
{
    if (buf->b != NULL) {
        free(buf->b);
        buf->b = NULL;
    }
    buf->getter = 0;
    buf->count  = 0;
    buf->alloc  = 0;
    return A661_DATA_OK;
}
#endif
/* ----------------------------------------------------------------------------------- */
a661_data_error_t a661_data_buffer_append(a661_data_buffer* buf, 
                                          a661_uchar* data, a661_ulong len)
{
    a661_data_error_t err = A661_DATA_OK;
    if (len > buf->alloc - buf->count) {
        len = buf->alloc - buf->count;
        err = A661_DATA_ERR;
    }
    memcpy(buf->b + buf->count, data, len);
    buf->count += len;
    return err;
}
/* ----------------------------------------------------------------------------------- */
a661_data_error_t a661_data_buffer_remove(a661_data_buffer* buf, a661_ulong len)
{
    int err = A661_DATA_OK;
    if (len == buf->count) {
        buf->count = 0;
    }
    else if (len > buf->count) {
        buf->count = 0;
        err = A661_DATA_ERR;
    }
    else {
        memmove(buf->b, buf->b + len, buf->count - len);
        buf->count -= len;
    }
    return err;
}
/* ----------------------------------------------------------------------------------- */
a661_ulong a661_data_buffer_count(a661_data_buffer* buf)
{
    return buf->count;
}
/* ----------------------------------------------------------------------------------- */
void a661_data_buffer_clear(a661_data_buffer* buf)
{
    buf->count = 0;
    buf->getter = 0;
}
/* ----------------------------------------------------------------------------------- */
void a661_data_buffer_print(a661_data_buffer* buf)
{
    printf("Data Buffer Print: sz=%d  bytes=%d", buf->alloc, buf->count);
    for(int i = 0; i < buf->count; i++) {
        if (i % 8 == 0) { printf(" | "); }
        if (i % 32 == 0) { printf("\n"); }
        printf("%02X ", buf->b[i]);
    }
    printf("\n");
    fflush(stdout);
}
/* ----------------------------------------------------------------------------------- */
/* Memory Accessors */
/* ----------------------------------------------------------------------------------- */
a661_uchar datab_get_uint8(a661_data_buffer *b)
{
    a661_uchar v = 0U;
    if (b->getter <= (b->count - 1U)) {
        v = b->b[b->getter];
        b->getter++;
    }
    else {
        b->getter = b->count + 1U;
        v = 0U;
    }
    return v;
}

a661_ushort datab_get_uint16(a661_data_buffer * b)
{
    a661_ushort r = 0U;

    if (b->getter <= (b->count - 2U)) {
        r = b->b[b->getter];
        b->getter++;
        r = (r << 8U) | (b->b[b->getter]);
        b->getter++;
    }
    else {
        b->getter = b->count + 1U;
        r = 0U;
    }
    return r;
}

a661_short datab_get_int16(a661_data_buffer * b)
{
    return (a661_short) datab_get_uint16(b);
}

a661_ulong datab_get_uint32(a661_data_buffer * b)
{
    a661_ulong r = 0U;

    if (b->getter <= (b->count - 4U)) {
        r = b->b[b->getter];
        b->getter++;
        r = (r << 8U) | (b->b[b->getter]);
        b->getter++;
        r = (r << 8U) | (b->b[b->getter]);
        b->getter++;
        r = (r << 8U) | (b->b[b->getter]);
        b->getter++;
    }
    else {
        b->getter = b->count + 1U;
    }
    return r;
}

a661_long datab_get_int32(a661_data_buffer * b)
{
    return (a661_long) datab_get_uint32(b);
}

a661_float datab_get_float(a661_data_buffer * b)
{
    union {
        a661_float f;
        a661_ulong i;
    } u;

    u.i = datab_get_uint32(b);
    return u.f;
}

a661_string datab_get_str(a661_data_buffer * b, a661_ushort sz)
{
    a661_string r = NULL;

    if (((sz > 0U) && (b->getter <= b->count - sz))
        && (b->b[(b->getter + (sz - 1U))] == 0U)) {
        r = (a661_string) & (b->b[b->getter]);
        b->getter += sz;
    }
    else {
        r = NULL;
        b->getter = b->count + 1U;
    }
    return r;
}


void datab_align(a661_data_buffer *b, a661_ushort n)
{
    if (n > 0U) {
        a661_ulong off = 0U;

        off = n - (b->getter % n);

        b->getter = b->getter + (off % n);
    }
}

/* ----------------------------------------------------------------------------------- */

void datab_put_uint8(a661_data_buffer *b, a661_uchar v)
{
    if (b->count <= b->alloc - 1U) {
        b->b[b->count] = v;
        b->count++;
    }
    else {
        b->count = b->alloc + 1U;
    }
}

void datab_put_uint16(a661_data_buffer *b, a661_ushort v)
{
    if (b->count <= b->alloc - 2U) {
        b->b[b->count] = (a661_uchar) ((v >> 8U) & ((a661_ushort) 0xFFU));
        b->count++;
        b->b[b->count] = (a661_uchar) (v & 0xFFU);
        b->count++;
    }
    else {
        b->count = b->alloc + 1U;
    }
}

void datab_put_int16(a661_data_buffer *b, a661_short v)
{
    datab_put_uint16(b, (a661_ushort) v);
}

void datab_put_uint32(a661_data_buffer *b, a661_ulong v)
{
    if (b->count <= b->alloc - 4U) {
        b->b[b->count] = (a661_uchar) ((v >> 24U) & 0xFFU);
        b->count++;
        b->b[b->count] = (a661_uchar) ((v >> 16U) & 0xFFU);
        b->count++;
        b->b[b->count] = (a661_uchar) ((v >> 8U) & 0xFFU);
        b->count++;
        b->b[b->count] = (a661_uchar) (v & 0xFFU);
        b->count++;
    }
    else {
        b->count = b->alloc + 1U;
    }
}

void datab_put_int32(a661_data_buffer *b, a661_long v)
{
    datab_put_uint32(b, (a661_ulong) v);
}

void datab_put_float(a661_data_buffer *b, a661_float v)
{
    union {
        a661_float f;
        a661_ulong i;
    } u;

    u.f = v;
    datab_put_uint32(b, u.i);
}


void datab_put_str(a661_data_buffer *b, const a661_string v, a661_ushort sz)
{
    a661_ushort i = 0U;

    if (sz <= b->alloc - b->count) {
        for (i = 0U; i < sz; i++) {
            b->b[b->count + i] = v[i];
        }
        b->count += sz;
    }
    else {
        b->count = b->alloc + 1U;
    }
}

void datab_put_pad(a661_data_buffer *b, a661_ushort n)
{
    a661_ushort i = 0U;

    if (n <= b->alloc - b->count) {
        for (i = 0U; i < n; i++) {
            b->b[b->count] = 0U;
            b->count++;
        }
    }
    else {
        b->count = b->alloc + 1U;
    }
}

void datab_put_align(a661_data_buffer *b, a661_ushort n)
{
    a661_ushort i = 0U;
    a661_ushort off = 0U;

    if (n > 0U) {
        off = (a661_ushort) ((n - (b->count % n)) % n);
        if (b->count <= b->alloc - off) {
            for (i = 0U; i < off; i++) {
                b->b[b->count] = 0U;
                b->count++;
            }
        }
        else {
            b->count = b->alloc + 1U;
        }
    }
}

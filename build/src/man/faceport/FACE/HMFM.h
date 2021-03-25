//! Source file: FACE/HMFM.h

#ifndef _FACE_HMFM_H
#define _FACE_HMFM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef int32_t    FACE_HMFM_long;
typedef uint32_t   FACE_HMFM_unsigned_long;
typedef int8_t     FACE_HMFM_char;

typedef enum {
    FACE_HMFM_NO_ERROR,
    FACE_HMFM_NO_ACTION,
    FACE_HMFM_NOT_AVAILABLE,
    FACE_HMFM_INVALID_PARAM,
    FACE_HMFM_INVALID_CONFIG,
    FACE_HMFM_INVALID_MODE,
    FACE_HMFM_TIMED_OUT,
    FACE_HMFM_ADDR_IN_USE,
    FACE_HMFM_PERMISSION_DENIED,
    FACE_HMFM_MESSAGE_STALE,
    FACE_HMFM_CONNECTION_IN_PROGRESS,
    FACE_HMFM_CONNECTION_CLOSED,
    FACE_HMFM_DATA_BUFFER_TOO_SMALL
} FACE_HMFM_RETURN_CODE_TYPE;

typedef void * FACE_HMFM_SYSTEM_ADDRESS_TYPE;

typedef FACE_HMFM_long FACE_HMFM_FAULT_MESSAGE_SIZE_TYPE;

typedef void * FACE_HMFM_FAULT_MESSAGE_ADDRESS_TYPE;

typedef uintptr_t FACE_HMFM_THREAD_ID_TYPE;

#define FACE_HMFM_FAULT_MESSAGE_MAXIMUM_SIZE ((FACE_HMFM_FAULT_MESSAGE_SIZE_TYPE) 128)

typedef FACE_HMFM_unsigned_long FACE_HMFM_STACK_SIZE_TYPE;

typedef FACE_HMFM_char FACE_HMFM_FAULT_MESSAGE_TYPE[FACE_HMFM_FAULT_MESSAGE_MAXIMUM_SIZE];

typedef enum {
    FACE_HMFM_DEADLINE_MISSED,
    FACE_HMFM_APPLICATION_ERROR,
    FACE_HMFM_NUMERIC_ERROR,
    FACE_HMFM_ILLEGAL_REQUEST,
    FACE_HMFM_STACK_OVERFLOW,
    FACE_HMFM_MEMORY_VIOLATION,
    FACE_HMFM_HARDWARE_FAULT,
    FACE_HMFM_POWER_FAIL
} FACE_HMFM_FAULT_CODE_TYPE;

typedef struct {
    FACE_HMFM_FAULT_CODE_TYPE CODE;
    FACE_HMFM_FAULT_MESSAGE_SIZE_TYPE LENGTH;
    FACE_HMFM_THREAD_ID_TYPE FAILED_THREAD_ID;
    FACE_HMFM_SYSTEM_ADDRESS_TYPE FAILED_ADDRESS;
    FACE_HMFM_FAULT_MESSAGE_TYPE MESSAGE;

} FACE_HMFM_FAULT_STATUS_TYPE;

typedef void (*FACE_HMFM_FAULT_HANDLER_ENTRY_TYPE) (void);

void FACE_HMFM_Initialize (
        /*    out */ FACE_HMFM_RETURN_CODE_TYPE *return_code
    );

void FACE_HMFM_Create_Fault_Handler (
        /* in     */ FACE_HMFM_FAULT_HANDLER_ENTRY_TYPE entry_point,
        /* in     */ FACE_HMFM_STACK_SIZE_TYPE stack_size,
        /*    out */ FACE_HMFM_RETURN_CODE_TYPE *return_code
    );

void FACE_HMFM_Report_Application_Message (
        /* in     */ FACE_HMFM_FAULT_MESSAGE_ADDRESS_TYPE fault,
        /* in     */ FACE_HMFM_FAULT_MESSAGE_SIZE_TYPE length,
        /*    out */ FACE_HMFM_RETURN_CODE_TYPE *return_code
    );

void FACE_HMFM_Get_Fault_Status (
        /*    out */ FACE_HMFM_FAULT_STATUS_TYPE *fault,
        /*    out */ FACE_HMFM_RETURN_CODE_TYPE *return_code
    );

void FACE_HMFM_Raise_Application_Fault (
        /* in     */ FACE_HMFM_FAULT_CODE_TYPE code,
        /* in     */ FACE_HMFM_FAULT_MESSAGE_ADDRESS_TYPE message,
        /* in     */ FACE_HMFM_FAULT_MESSAGE_SIZE_TYPE length,
        /*    out */ FACE_HMFM_RETURN_CODE_TYPE *return_code
    );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _FACE_HMFM_H */

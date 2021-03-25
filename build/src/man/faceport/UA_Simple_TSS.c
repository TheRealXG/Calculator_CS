/*+ FILE DESCRIPTION -------------------------------------------------------
FILENAME          : Simple_TSS.c
DESCRIPTION       : Server Simple TSS implementation
COPYRIGHT (C)     : 2020 ANSYS, Inc.  ALL RIGHTS RESERVED
This source file may be used and distributed without restriction provided that this copyright statement is not removed from the file and that any derivative work contains this copyright notice.

Warranty
ANSYS, Inc makes no warranty of any kind with regard to the use of this Software, either expressed or implied, including, but not limited to the fitness for a particular purpose
---------------------------------------------------------------------------- +*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "a661_data_buffer.h"
#include "a661_socket.h"
#include "UA_Simple_TSS.h"
#include "FACE/TSS/Base.h"
#include "FACE/TSS/DataModel/tCmdsInIDLS/TypedTS.h"
#include "FACE/TSS/DataModel/tCmdsOutIDLS/TypedTS.h"

#ifdef A661_DATA_BUFFER_FIXED_SIZE
#define A661_DATA_BUFFER_SIZE  A661_DATA_BUFFER_FIXED_SIZE
#else
#define A661_DATA_BUFFER_SIZE  1000000
#endif

/* ----------------------------------------------------------------------------------------------------------------- */
typedef struct _face_conn_t
{
    a661_socket_t context;
    a661_data_buffer tx;
    a661_data_buffer rx;
} face_conn_t;

/* ----------------------------------------------------------------------------------------------------------------- */

static FACE_interface_return UA_Simple_TSS_Base_Create_Connection(
    struct FACE_TSS_Base* this_obj, 
    const FACE_TSS_CONNECTION_NAME_TYPE* connection_name, 
    FACE_TIMEOUT_TYPE timeout, 
    FACE_TSS_CONNECTION_ID_TYPE* connection_id, 
    FACE_TSS_MESSAGE_SIZE_TYPE* max_message_size, 
    FACE_RETURN_CODE_TYPE* return_code)
{
    a661_socket_err_t sock_err;
    int appid = 1;
    uint16_t port = A661_BASE_PORT;
    face_conn_t* c = NULL;
    const char* pname = strchr(FACE_string_buffer(connection_name), ':');

    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    if (connection_name == NULL) return FACE_INTERFACE_NULL_PARAM;
    if (connection_id == NULL) return FACE_INTERFACE_NULL_PARAM;
    if (max_message_size == NULL) return FACE_INTERFACE_NULL_PARAM;
    if (return_code == NULL) return FACE_INTERFACE_NULL_PARAM;
    *return_code = FACE_RETURN_CODE_TYPE_NO_ERROR;

    if (pname == NULL) {
         pname = FACE_string_buffer(connection_name);
    }
    else {
        pname++;
        sscanf(pname, "%d", &appid);
        port += appid;
    }

    c = malloc(sizeof *c);
    if (c != NULL) {
        sock_err = a661_socket_open_client(&c->context, 
                                           0 /*udp*/, 
                                           A661_DEFAULT_HOSTNAME, 
                                           port);
        if (sock_err == A661_SOCKET_OK) {
            *max_message_size = A661_DATA_BUFFER_SIZE;
            *connection_id = (FACE_TSS_CONNECTION_ID_TYPE) c;
            a661_data_buffer_init(&c->tx, A661_DATA_BUFFER_SIZE);
            a661_data_buffer_init(&c->rx, A661_DATA_BUFFER_SIZE);
        }
        else {
            free(c);
            c = NULL;
        }
    }

    if (c == NULL) {
        *return_code = FACE_RETURN_CODE_TYPE_NOT_AVAILABLE;
        *max_message_size = 0;
        *connection_id = (FACE_TSS_CONNECTION_ID_TYPE) 0;
    }
    return FACE_INTERFACE_NO_ERROR;
}
/* ----------------------------------------------------------------------------------------------------------------- */
static FACE_interface_return UA_Simple_TSS_Base_Destroy_Connection(
    struct FACE_TSS_Base* this_obj, 
    FACE_TSS_CONNECTION_ID_TYPE connection_id, 
    FACE_RETURN_CODE_TYPE* return_code)
{
    face_conn_t* c = (face_conn_t*) connection_id;

    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    if (return_code == NULL) return FACE_INTERFACE_NULL_PARAM;
    *return_code = FACE_RETURN_CODE_TYPE_NO_ERROR;

    if (c != NULL) {
        a661_socket_close(&c->context);
        free(c);
    }
    return FACE_INTERFACE_NO_ERROR;
}
/* ----------------------------------------------------------------------------------------------------------------- */
static FACE_interface_return UA_Simple_TSS_DataModel_tCmdsInIDLS_TypedTS_Receive_Message(
    struct FACE_TSS_DataModel_tCmdsInIDLS_TypedTS* this_obj, 
    FACE_TSS_CONNECTION_ID_TYPE connection_id, 
    FACE_TIMEOUT_TYPE timeout, 
    FACE_TSS_TRANSACTION_ID_TYPE* transaction_id, 
    FACE_DM_DataModel_tCmdsInIDLS* message, 
    FACE_TSS_HEADER_TYPE* header, 
    FACE_TSS_QoS_EVENT_TYPE* qos_parameters, 
    FACE_RETURN_CODE_TYPE* return_code)
{
    ssize_t r = 0;
    face_conn_t *c = (face_conn_t *) connection_id;
    a661_uchar cont = 1U;

    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    if (transaction_id == NULL) return FACE_INTERFACE_NULL_PARAM;
    if (message == NULL) return FACE_INTERFACE_NULL_PARAM;
    if (header == NULL) return FACE_INTERFACE_NULL_PARAM;
    if (qos_parameters == NULL) return FACE_INTERFACE_NULL_PARAM;
    if (return_code == NULL) return FACE_INTERFACE_NULL_PARAM;
    *return_code = FACE_RETURN_CODE_TYPE_NO_ACTION;

    *transaction_id = 0;

    /* Receive data to form one complete command block. */
    /* Will also exit for connection lost or 0 byte receive (timeout). */
    while (cont == 1U) {
        /* Treat one complete command block previously received and exit loop */
        const a661_ulong MIN_BLOCK_SIZE = 16U;
        const a661_uchar A661_BEGIN_BLOCK = 0xB0;

        if ((c->rx.count >= MIN_BLOCK_SIZE) && (c->rx.b[0] == A661_BEGIN_BLOCK)) {
            /* Extract the A661 block size */
            FACE_unsigned_long bsize = (c->rx.b[4] << 3) + 
                                       (c->rx.b[5] << 2) + 
                                       (c->rx.b[6] << 1) + 
                                       (c->rx.b[7] << 0);

            if (bsize <= c->rx.count) {
                cont = false;  /* One or more entire blocks received; exit loop. */
                
                FACE_DM_DataModel_idlsA661CmdsElements_init_managed_data(&(message->pcA661CmdsInIDLS), c->rx.b, c->rx.count);
                header->instance_uid = 0;
                header->source_uid = 0;
                header->timestamp = 0;
                *return_code = FACE_RETURN_CODE_TYPE_NO_ERROR;

                a661_data_buffer_clear(&c->rx);
            }
        }
        
        if (cont) {
            a661_ulong start_pos = c->rx.count;

            a661_socket_err_t err = a661_socket_recv(&c->context, &c->rx);

            if (err != A661_SOCKET_OK) {
                /* TBD: separate check for actual "closed" ??????????????????????????? */
                cont = 0U;
                *return_code = FACE_RETURN_CODE_TYPE_NOT_AVAILABLE;
            }
            else if (start_pos == c->rx.count) {
                /* No new data received; exit loop. */
                /* Caller informed of "time out" although this is not an error. */
                /* Note that this is a normal occurrence on the non-blocking socket. */
                cont = 0U;
                *return_code = FACE_RETURN_CODE_TYPE_TIMED_OUT;
            }
            else if (c->rx.count >= c->rx.alloc) {
                /* Ran out of data bufferspace. */
                /* Attempt to find a next A661_BEGIN_BLOCK and flush */
                /* all data prior to that guard character to try processing again. */
                a661_ulong i;
                for (i = 1; i < c->rx.alloc; i++) {
                    if (c->rx.b[i] == A661_BEGIN_BLOCK) {
                        a661_data_buffer_remove(&c->rx, i);
                        break;
                    }
                }
                /* Break now to report the error to the caller. */
                /* Leftover data is preserved for next call to this function. */
                cont = 0U;
                *return_code = FACE_RETURN_CODE_TYPE_DATA_OVERFLOW;
            }
            else {
                /* Success - will loop around to attempt processing. */
                cont = 1U;
            }
        }
    }
    return FACE_INTERFACE_NO_ERROR;
}
/* ----------------------------------------------------------------------------------------------------------------- */
static FACE_interface_return UA_Simple_TSS_DataModel_tCmdsOutIDLS_TypedTS_Send_Message(
    struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS* this_obj, 
    FACE_TSS_CONNECTION_ID_TYPE connection_id, 
    FACE_TIMEOUT_TYPE timeout, 
    FACE_TSS_TRANSACTION_ID_TYPE* transaction_id, 
    const FACE_DM_DataModel_tCmdsOutIDLS* message, 
    FACE_RETURN_CODE_TYPE* return_code)
{
    face_conn_t* c = (face_conn_t*) connection_id;
    FACE_sequence_return sequence_code;
    FACE_unsigned_long length;
    char* buffer = NULL;

    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    if (transaction_id == NULL) return FACE_INTERFACE_NULL_PARAM;
    if (message == NULL) return FACE_INTERFACE_NULL_PARAM;
    if (return_code == NULL) return FACE_INTERFACE_NULL_PARAM;
    *return_code = FACE_RETURN_CODE_TYPE_NO_ACTION;

    *transaction_id = 0;

    buffer = (char*)FACE_DM_DataModel_idlsA661CmdsElements_buffer(&(message->pcA661CmdsOutIDLS));
    sequence_code = FACE_DM_DataModel_idlsA661CmdsElements_length(&(message->pcA661CmdsOutIDLS), &length);

    if (buffer == NULL) {
        *return_code = FACE_RETURN_CODE_TYPE_INVALID_PARAM;
    }
    else if (sequence_code != FACE_SEQUENCE_NO_ERROR) {
        *return_code = FACE_RETURN_CODE_TYPE_INVALID_PARAM;
    }
    else {
        a661_data_buffer_append(&c->tx, (a661_uchar*) buffer, (a661_ulong) length);

        if (c->tx.count > 0) {
            a661_socket_err_t err = a661_socket_send(&c->context, &c->tx);

            if (err != A661_SOCKET_OK) {
                /* TBD: separate check for actual "closed" ??????????????????????????? */
                *return_code = FACE_RETURN_CODE_TYPE_NOT_AVAILABLE;
            }
            else {
             
                *return_code = FACE_RETURN_CODE_TYPE_NO_ERROR;
            }
        }
    }
    return FACE_INTERFACE_NO_ERROR;
}

/* ----------------------------------------------------------------------------------------------------------------- */

static FACE_interface_return UA_Simple_TSS_Base_ctor(struct FACE_TSS_Base* this_obj)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    this_obj->data = NULL;
    return FACE_INTERFACE_NO_ERROR;
}

static FACE_interface_return UA_Simple_TSS_Base_dtor(struct FACE_TSS_Base* this_obj)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    this_obj->data = NULL;
    return FACE_INTERFACE_NO_ERROR;
}

static FACE_interface_return UA_Simple_TSS_DataModel_tCmdsInIDLS_TypedTS_ctor(
    struct FACE_TSS_DataModel_tCmdsInIDLS_TypedTS* this_obj)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    this_obj->data = NULL;
    return FACE_INTERFACE_NO_ERROR;
}

static FACE_interface_return UA_Simple_TSS_DataModel_tCmdsInIDLS_TypedTS_dtor(
    struct FACE_TSS_DataModel_tCmdsInIDLS_TypedTS* this_obj)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    this_obj->data = NULL;
    return FACE_INTERFACE_NO_ERROR;
}

static FACE_interface_return UA_Simple_TSS_DataModel_tCmdsOutIDLS_TypedTS_ctor(
    struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS* this_obj)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    this_obj->data = NULL;
    return FACE_INTERFACE_NO_ERROR;
}

static FACE_interface_return UA_Simple_TSS_DataModel_tCmdsOutIDLS_TypedTS_dtor(
    struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS* this_obj)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    this_obj->data = NULL;
    return FACE_INTERFACE_NO_ERROR;
}

static FACE_interface_return UA_Simple_TSS_Base_Initialize(
    struct FACE_TSS_Base* this_obj, 
    const FACE_CONFIGURATION_RESOURCE* configuration, 
    FACE_RETURN_CODE_TYPE* return_code)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    if (return_code == NULL) return FACE_INTERFACE_NULL_PARAM;
    *return_code = FACE_RETURN_CODE_TYPE_NO_ERROR;

    a661_socket_init();

    return FACE_INTERFACE_NO_ERROR;
}

/* Inject Simple_TSS as FACE_TSS */

static FACE_TSS_Base base_obj = {
    {UA_Simple_TSS_Base_ctor, 
     UA_Simple_TSS_Base_dtor,
     UA_Simple_TSS_Base_Initialize, 
     UA_Simple_TSS_Base_Create_Connection, 
     UA_Simple_TSS_Base_Destroy_Connection, 
     NULL},
    NULL
};

static FACE_TSS_DataModel_tCmdsInIDLS_TypedTS tCmdsInIDLS_obj = {
    {UA_Simple_TSS_DataModel_tCmdsInIDLS_TypedTS_ctor, 
     UA_Simple_TSS_DataModel_tCmdsInIDLS_TypedTS_dtor,
     UA_Simple_TSS_DataModel_tCmdsInIDLS_TypedTS_Receive_Message, 
     NULL, 
     NULL},
     NULL
};

static FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS tCmdsOutIDLS_obj = {
    {UA_Simple_TSS_DataModel_tCmdsOutIDLS_TypedTS_ctor, 
     UA_Simple_TSS_DataModel_tCmdsOutIDLS_TypedTS_dtor,
     NULL, 
     UA_Simple_TSS_DataModel_tCmdsOutIDLS_TypedTS_Send_Message, 
     NULL},
     NULL
};

void UA_Simple_TSS_Base_Inject(
    FACE_TSS_Base_Injectable_Injectable *injectable)
{
    FACE_RETURN_CODE_TYPE code = 0;
    FACE_STRING_TYPE interface_name = { 0 };
    FACE_string_init_unmanaged_bounded(&interface_name, "TSS_Base");
    FACE_TSS_Base_Injectable_Injectable_ctor(injectable);
    FACE_TSS_Base_Injectable_Injectable_Set_Reference(injectable, &interface_name, &base_obj, 0, &code);
}

void UA_Simple_TSS_DataModel_tCmdsInIDLS_TypedTS_Inject(
    FACE_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_Injectable *injectable)
{
    FACE_RETURN_CODE_TYPE code = 0;
    FACE_STRING_TYPE interface_name = { 0 };
    FACE_string_init_unmanaged_bounded(&interface_name, "TSS_DataModel_tCmdsInIDLS_TypedTS");
    FACE_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_Injectable_ctor(injectable);
    FACE_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_Injectable_Set_Reference(injectable, &interface_name, &tCmdsInIDLS_obj, 0, &code);
}


void UA_Simple_TSS_DataModel_tCmdsOutIDLS_TypedTS_Inject(
    FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_Injectable *injectable)
{
    FACE_RETURN_CODE_TYPE code = 0;
    FACE_STRING_TYPE interface_name = { 0 };
    FACE_string_init_unmanaged_bounded(&interface_name, "TSS_DataModel_tCmdsOutIDLS_TypedTS");
    FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_Injectable_ctor(injectable);
    FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_Injectable_Set_Reference(injectable, &interface_name, &tCmdsOutIDLS_obj, 0, &code);
}

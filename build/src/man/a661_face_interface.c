#include <string.h>
#include <stdio.h>

#include "a661_data_buffer.h"
#include "a661_face_interface.h"
#include "UA_Simple_TSS.h"

FACE_TSS_Base *base_obj = NULL;
FACE_TSS_DataModel_tCmdsInIDLS_TypedTS *tCmdsInIDLS_obj = NULL;
FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS *tCmdsOutIDLS_obj = NULL;

extern void a661_report_simple_error(const char_t * message, a661_ushort value);

// --------------------------------------------------------------------------------------------------------------------
// tCmdsInIDLS_TypedTS_Injectable
// --------------------------------------------------------------------------------------------------------------------
static FACE_interface_return Network_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_ctor(
    struct FACE_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_Injectable* this_obj)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    return FACE_INTERFACE_NO_ERROR;
}

static FACE_interface_return Network_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_dtor(
    struct FACE_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_Injectable* this_obj)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    return FACE_INTERFACE_NO_ERROR;
}

static FACE_interface_return Network_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_Set_Reference(
    struct FACE_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_Injectable* this_obj, 
    const FACE_STRING_TYPE* interface_name, 
    FACE_TSS_DataModel_tCmdsInIDLS_TypedTS* interface_reference, 
    FACE_GUID_TYPE id, 
    FACE_RETURN_CODE_TYPE* return_code)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    if ((interface_name == NULL) || (interface_reference == NULL) || (return_code == NULL)) return FACE_INTERFACE_NULL_PARAM;
    tCmdsInIDLS_obj = interface_reference;
    *return_code = FACE_RETURN_CODE_TYPE_NO_ERROR;
    return FACE_INTERFACE_NO_ERROR;
}

static FACE_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_Injectable tCmdsInIDLS_injectable = {
    { 
    Network_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_ctor, 
    Network_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_dtor, 
    Network_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_Set_Reference
    },
    NULL
};

FACE_TSS_DataModel_tCmdsInIDLS_TypedTS_Injectable_Injectable* 
    pscA661CDS_TSS_DataModel_tCmdsInIDLS_TypedTS = &tCmdsInIDLS_injectable;

// --------------------------------------------------------------------------------------------------------------------
// tCmdsOutIDLS_TypedTS_Injectable
// --------------------------------------------------------------------------------------------------------------------
static FACE_interface_return Network_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_ctor(
    struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_Injectable* this_obj)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    return FACE_INTERFACE_NO_ERROR;
}

static FACE_interface_return Network_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_dtor(
    struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_Injectable* this_obj)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    return FACE_INTERFACE_NO_ERROR;
}

static FACE_interface_return Network_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_Set_Reference(
    struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_Injectable* this_obj, 
    const FACE_STRING_TYPE* interface_name, 
    FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS* interface_reference, 
    FACE_GUID_TYPE id, 
    FACE_RETURN_CODE_TYPE* return_code)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    if ((interface_name == NULL) || (interface_reference == NULL) || (return_code == NULL)) return FACE_INTERFACE_NULL_PARAM;
    tCmdsOutIDLS_obj = interface_reference;
    *return_code = FACE_RETURN_CODE_TYPE_NO_ERROR;
    return FACE_INTERFACE_NO_ERROR;
}

static FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_Injectable tCmdsOutIDLS_injectable = {
    { 
    Network_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_ctor, 
    Network_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_dtor, 
    Network_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_Set_Reference
    },
    NULL
};

FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Injectable_Injectable* 
    pscA661CDS_TSS_DataModel_tCmdsOutIDLS_TypedTS = &tCmdsOutIDLS_injectable;

// --------------------------------------------------------------------------------------------------------------------
// Network_TSS_Base_Injectable
// --------------------------------------------------------------------------------------------------------------------
static FACE_interface_return Network_TSS_Base_Injectable_ctor(struct FACE_TSS_Base_Injectable_Injectable* this_obj)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    return FACE_INTERFACE_NO_ERROR;
}
// --------------------------------------------------------------------------------------------------------------------
static FACE_interface_return Network_TSS_Base_Injectable_dtor(struct FACE_TSS_Base_Injectable_Injectable* this_obj)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    return FACE_INTERFACE_NO_ERROR;
}
// --------------------------------------------------------------------------------------------------------------------
static FACE_interface_return Network_TSS_Base_Injectable_Set_Reference(
    struct FACE_TSS_Base_Injectable_Injectable* this_obj, 
    const FACE_STRING_TYPE* interface_name, 
    FACE_TSS_Base* interface_reference, 
    FACE_GUID_TYPE id, 
    FACE_RETURN_CODE_TYPE* return_code)
{
    if (this_obj == NULL) return FACE_INTERFACE_NULL_THIS;
    if ((interface_name == NULL) || (interface_reference == NULL) || (return_code == NULL)) return FACE_INTERFACE_NULL_PARAM;
    base_obj = interface_reference;
    *return_code = FACE_RETURN_CODE_TYPE_NO_ERROR;
    return FACE_INTERFACE_NO_ERROR;
}
// --------------------------------------------------------------------------------------------------------------------
static FACE_TSS_Base_Injectable_Injectable base_injectable = {
    { 
    Network_TSS_Base_Injectable_ctor, 
    Network_TSS_Base_Injectable_dtor, 
    Network_TSS_Base_Injectable_Set_Reference
    },
    NULL
};
FACE_TSS_Base_Injectable_Injectable* pscA661CDS_TSS_Base = &base_injectable;

// --------------------------------------------------------------------------------------------------------------------
// Init
// --------------------------------------------------------------------------------------------------------------------
void a661_face_init(void)
{
    /* Inject IOSS and TSS dependencies */
    UA_Simple_TSS_Base_Inject(pscA661CDS_TSS_Base);
    UA_Simple_TSS_DataModel_tCmdsInIDLS_TypedTS_Inject(pscA661CDS_TSS_DataModel_tCmdsInIDLS_TypedTS);
    UA_Simple_TSS_DataModel_tCmdsOutIDLS_TypedTS_Inject(pscA661CDS_TSS_DataModel_tCmdsOutIDLS_TypedTS);
}

// --------------------------------------------------------------------------------------------------------------------
// FACE UA object accessor functions
//   - setters are private to this module
//   - getters are public
// --------------------------------------------------------------------------------------------------------------------
static void ua_set_connected(a661_face_ua* ua, a661_uchar connected)
{
    ua->connected = connected;
}

static void ua_set_connection(a661_face_ua* ua, 
                       FACE_TSS_CONNECTION_ID_TYPE connection_id,
                       FACE_TSS_MESSAGE_SIZE_TYPE max_message_size)
{
    ua->connection_id = connection_id;
    ua->max_message_size = max_message_size;
}

a661_uchar ua_is_connected(a661_face_ua* ua)
{
    return ua->connected;
}

a661_ushort ua_get_appid(a661_face_ua* ua)
{
    return ua->appid;
}

FACE_TSS_CONNECTION_ID_TYPE ua_get_connection_id(a661_face_ua* ua)
{
    return ua->connection_id;
}
// --------------------------------------------------------------------------------------------------------------------
// FACE Socket Networking
// --------------------------------------------------------------------------------------------------------------------
a661_error a661_face_open_socket(a661_face_ua* ua, a661_uchar udp)
{
    a661_error err = A661_NO_ERROR;
    FACE_string_return string_code = 0;

    if (ua_is_connected(ua)) {
        a661_report_simple_error("TSS connection attempted twice for UA", ua_get_appid(ua));
        err = A661_ERR_BAD_COMMAND;
    }
    else {
        /* Compute a connection name */
        snprintf(ua->connection_name_cstr, 
                 sizeof(ua->connection_name_cstr), 
                 "UA:%d", ua_get_appid(ua));
        
        string_code = FACE_string_init_unmanaged(
                          &ua->connection_name, 
                          ua->connection_name_cstr, 
                          (FACE_unsigned_long)strlen(ua->connection_name_cstr), 
                          sizeof(ua->connection_name_cstr) - 1);

        /* Check errors */
        if (string_code != FACE_STRING_NO_ERROR) {
            a661_report_simple_error("TSS connection name failed for UA", ua_get_appid(ua));
            err = A661_ERR_MEMORY_OVERLOAD;
        }
        else {
            FACE_TIMEOUT_TYPE timeout = 0;
            FACE_TSS_CONNECTION_ID_TYPE connection_id = 0;
            FACE_TSS_MESSAGE_SIZE_TYPE max_message_size = 0;
            FACE_RETURN_CODE_TYPE return_code = 0;
            FACE_interface_return interface_code = 0;

            /* Create connection */
            interface_code = FACE_TSS_Base_Create_Connection(
                                 base_obj, 
                                 &ua->connection_name, 
                                 timeout, 
                                 &connection_id, 
                                 &max_message_size, 
                                 &return_code);

            if ((interface_code != FACE_INTERFACE_NO_ERROR) || 
                (return_code != FACE_RETURN_CODE_TYPE_NO_ERROR)) {
                ua_set_connected(ua, 0U);
                ua_set_connection(ua, 0, 0);
                a661_report_simple_error("TSS create connection failed for UA", ua_get_appid(ua));
                err = A661_ERR_BAD_COMMAND;
            }
            else {
                /* Not fully connected until first message is received. */
                ua_set_connected(ua, 0U);
                ua_set_connection(ua, connection_id, max_message_size);
            }
        }
    }
    return err;
}
// --------------------------------------------------------------------------------------------------------------------
a661_error a661_face_close_socket(a661_face_ua* ua)
{
    a661_error err = A661_NO_ERROR;

    if (ua_is_connected(ua)) {
        FACE_TSS_CONNECTION_ID_TYPE connection_id = ua_get_connection_id(ua);
        FACE_RETURN_CODE_TYPE return_code = 0;
        FACE_interface_return interface_code = 0;

        /* Destroy connection */
        interface_code = FACE_TSS_Base_Destroy_Connection(
                             base_obj, 
                             connection_id, 
                             &return_code);

        /* Check errors */
        if ((interface_code != FACE_INTERFACE_NO_ERROR) || 
            (return_code != FACE_RETURN_CODE_TYPE_NO_ERROR)) {
            a661_ushort appid = ua_get_appid(ua);
            a661_report_simple_error("TSS destroy connection failed for UA", appid);
            err = A661_ERR_BAD_COMMAND;
        }
        ua_set_connected(ua, 0U);
        ua_set_connection(ua, 0, 0);
    }
    return err;
}
// --------------------------------------------------------------------------------------------------------------------
a661_error a661_face_recv(a661_face_ua* ua, a661_data_buffer* recv_buf)
{
    a661_error err = A661_NO_ERROR;
    FACE_TIMEOUT_TYPE timeout = 0;
    FACE_TSS_TRANSACTION_ID_TYPE transaction_id = 0;
    FACE_DM_DataModel_tCmdsInIDLS message = { 0 }; /* sequence of bytes! */
    FACE_TSS_HEADER_TYPE header = { 0 };
    FACE_TSS_QoS_EVENT_TYPE qos_parameters = { 0 };
    FACE_RETURN_CODE_TYPE return_code = 0;
    FACE_interface_return interface_code = 0;

    /* Receive message */
    interface_code = FACE_TSS_DataModel_tCmdsInIDLS_TypedTS_Receive_Message(
                         tCmdsInIDLS_obj, 
                         ua_get_connection_id(ua), 
                         timeout, 
                         &transaction_id, 
                         &message, 
                         &header, 
                         &qos_parameters, 
                         &return_code);

    /* Check errors */
    if (interface_code != FACE_INTERFACE_NO_ERROR) {
        a661_report_simple_error("TSS receive failed for UA", ua_get_appid(ua));
        /* Bad connection */
        ua_set_connected(ua, 0U);
        err = A661_ERR_BAD_COMMAND;
    }
    else if (return_code == FACE_RETURN_CODE_TYPE_TIMED_OUT) {
        /* Good connection with no data received this frame. */
        ua_set_connected(ua, 1U);
    }
    else if (return_code != FACE_RETURN_CODE_TYPE_NO_ERROR) {
        /* Bad connection */
        ua_set_connected(ua, 0U);
        err = A661_ERR_BAD_COMMAND;
    }
    else {
        /* Good connection */
        ua_set_connected(ua, 1U);

        /* Access message buffer and length */
        FACE_sequence_return sequence_code = 0;
        FACE_unsigned_long length = 0;
        a661_uchar *buffer;

        buffer        = FACE_DM_DataModel_idlsA661CmdsElements_buffer(&(message.pcA661CmdsInIDLS));
        sequence_code = FACE_DM_DataModel_idlsA661CmdsElements_length(&(message.pcA661CmdsInIDLS), &length);

        if (buffer == NULL) {
            a661_report_simple_error("TSS receive: (NULL buffer) bad message for UA", ua_get_appid(ua));
            err = A661_ERR_BAD_COMMAND;
        }
        else if (sequence_code != FACE_SEQUENCE_NO_ERROR) {
            a661_report_simple_error("TSS receive: (error sequence code) bad message for UA", ua_get_appid(ua));
            err = A661_ERR_BAD_COMMAND;
        }
        else {
            a661_data_buffer_append(recv_buf, (a661_uchar*) buffer, (a661_ulong) length);
        }

        /* Cleanup message */
        FACE_DM_DataModel_idlsA661CmdsElements_free(&(message.pcA661CmdsInIDLS));
    }
    return err;
}
// --------------------------------------------------------------------------------------------------------------------
a661_error a661_face_send(a661_face_ua* ua, a661_data_buffer* send_buf)
{
    a661_error err = A661_NO_ERROR;
    a661_ushort appid = 0U;

    /* Prepare message */
    FACE_DM_DataModel_tCmdsOutIDLS message = { 0 }; /* sequence of bytes! */
    FACE_sequence_return sequence_code = 0;
    
    sequence_code = FACE_DM_DataModel_idlsA661CmdsElements_init_unmanaged(
                        &(message.pcA661CmdsOutIDLS), 
                        send_buf->b, 
                        send_buf->count, 
                        send_buf->alloc);

    if (sequence_code != FACE_SEQUENCE_NO_ERROR) {
        a661_report_simple_error("TSS send: bad message for UA", appid);
        err = A661_ERR_BAD_COMMAND;
    }
    else {
        FACE_TSS_CONNECTION_ID_TYPE connection_id = ua_get_connection_id(ua);
        FACE_TIMEOUT_TYPE timeout = 0;
        FACE_TSS_TRANSACTION_ID_TYPE transaction_id = 0;
        FACE_RETURN_CODE_TYPE return_code = 0;
        FACE_interface_return interface_code = 0;

        /* Send message */
        interface_code = FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Send_Message(
                             tCmdsOutIDLS_obj, 
                             connection_id, 
                             timeout, 
                             &transaction_id, 
                             &message, 
                             &return_code);

        /* Check errors */
        if (interface_code != FACE_INTERFACE_NO_ERROR) {
            a661_report_simple_error("TSS send failed for UA", appid);
            /* Bad connection */
            ua_set_connected(ua, 0U);
            err = A661_ERR_BAD_COMMAND;
        }
        else if (return_code != FACE_RETURN_CODE_TYPE_NO_ERROR) {
            if (return_code == FACE_RETURN_CODE_TYPE_TIMED_OUT) {
                /* Good connection */
                ua_set_connected(ua, 1U);
            }
            else {
                /* Bad connection */
                ua_set_connected(ua, 0U);
                err = A661_ERR_BAD_COMMAND;
            }
        }
        else {
            /* Good connection */
            ua_set_connected(ua, 1U);
            a661_data_buffer_clear(send_buf);
        }
    }
    return err;
}

#ifndef _A661_FACE_INTERFACE_H_
#define _A661_FACE_INTERFACE_H_

#include "a661_error.h"
#include "a661_data_buffer.h"
#include "a661_types.h"
#include "a661_face_interface.h"
#include "UA_Simple_TSS.h"

// --------------------------------------------------------------------------------------------------------------------
// Types
// --------------------------------------------------------------------------------------------------------------------
typedef struct _a661_face_ua {
    a661_ushort   appid;
    a661_uchar    connected;
    char          connection_name_cstr[128];
    
    FACE_TSS_CONNECTION_NAME_TYPE  connection_name;
    FACE_TSS_CONNECTION_ID_TYPE    connection_id;
    FACE_TSS_MESSAGE_SIZE_TYPE     max_message_size;
} a661_face_ua;

// --------------------------------------------------------------------------------------------------------------------
// Globals
// --------------------------------------------------------------------------------------------------------------------
extern FACE_TSS_Base *base_obj;

// --------------------------------------------------------------------------------------------------------------------
// Functions
// --------------------------------------------------------------------------------------------------------------------
void a661_face_init(void);

a661_error a661_face_open_socket(a661_face_ua* ua, a661_uchar udp);

a661_error a661_face_close_socket(a661_face_ua* ua);

a661_error a661_face_recv(a661_face_ua* ua, a661_data_buffer* recv_buf);

a661_error a661_face_send(a661_face_ua* ua, a661_data_buffer* send_buf);

a661_uchar ua_is_connected(a661_face_ua* ua);

a661_ushort ua_get_appid(a661_face_ua* ua);

FACE_TSS_CONNECTION_ID_TYPE ua_get_connection_id(a661_face_ua* ua);

#endif /* _A661_FACE_INTERFACE_H_ */
#ifndef _TSS_TYPED__TCMDSOUTIDLS_H
#define _TSS_TYPED__TCMDSOUTIDLS_H

#include <FACE/TSS/Common.h>
#include <FACE/DM/DataModel/tCmdsOutIDLS.h>

/* Interface FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback Begin */
struct FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback;

// initialize this_obj->data
typedef FACE_interface_return (*FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback_ctor_t)(struct FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback* this_obj);

// clean up this_obj->data
typedef FACE_interface_return (*FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback_dtor_t)(struct FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback* this_obj);

// 1. typedef defining alias for function pointer
//    corresponding to operation
typedef FACE_interface_return (*FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback_Callback_Handler_t)(struct FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback* this_obj, FACE_TSS_CONNECTION_ID_TYPE connection_id, FACE_TSS_TRANSACTION_ID_TYPE transaction_id, const FACE_DM_DataModel_tCmdsOutIDLS* message, const FACE_TSS_HEADER_TYPE* header, const FACE_TSS_QoS_EVENT_TYPE* qos_parameters, FACE_RETURN_CODE_TYPE* return_code);

typedef struct FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback_ops {
  FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback_ctor_t ctor;
  FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback_dtor_t dtor;
  
  // 2. operations table struct members corresponding to the operations
  FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback_Callback_Handler_t Callback_Handler;
} FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback_ops;

typedef struct FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback {
  FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback_ops ops;
  void* data;
} FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback;

#define FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback_ctor(_this_obj) \
  ((_this_obj)->ops.ctor)((_this_obj))
#define FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback_dtor(_this_obj) \
  ((_this_obj)->ops.dtor)((_this_obj))

// 3. Macros corresponding to the operations
#define FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback_Callback_Handler(_this_obj, _connection_id, _transaction_id, _message, _header, _qos_parameters, _return_code) \
  ((_this_obj)->ops.Callback_Handler)((_this_obj), (_connection_id), (_transaction_id), (_message), (_header), (_qos_parameters), (_return_code))

/* Interface FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback End */

/* Interface FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS Begin */
struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS;

// initialize this_obj->data
typedef FACE_interface_return (*FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_ctor_t)(struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS* this_obj);

// clean up this_obj->data
typedef FACE_interface_return (*FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_dtor_t)(struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS* this_obj);

// 1. typedef defining alias for function pointer
//    corresponding to operation
typedef FACE_interface_return (*FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Receive_Message_t)(struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS* this_obj, FACE_TSS_CONNECTION_ID_TYPE connection_id, FACE_TIMEOUT_TYPE timeout, FACE_TSS_TRANSACTION_ID_TYPE* transaction_id, FACE_DM_DataModel_tCmdsOutIDLS* message, FACE_TSS_HEADER_TYPE* header, FACE_TSS_QoS_EVENT_TYPE* qos_parameters, FACE_RETURN_CODE_TYPE* return_code);
typedef FACE_interface_return (*FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Send_Message_t)(struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS* this_obj, FACE_TSS_CONNECTION_ID_TYPE connection_id, FACE_TIMEOUT_TYPE timeout, FACE_TSS_TRANSACTION_ID_TYPE* transaction_id, const FACE_DM_DataModel_tCmdsOutIDLS* message, FACE_RETURN_CODE_TYPE* return_code);
typedef FACE_interface_return (*FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Register_Callback_t)(struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS* this_obj, FACE_TSS_CONNECTION_ID_TYPE connection_id, FACE_TSS_DataModel_tCmdsOutIDLS_Read_Callback* callback, FACE_RETURN_CODE_TYPE* return_code);

typedef struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_ops {
  FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_ctor_t ctor;
  FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_dtor_t dtor;
  
  // 2. operations table struct members corresponding to the operations
  FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Receive_Message_t Receive_Message;
  FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Send_Message_t Send_Message;
  FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Register_Callback_t Register_Callback;
} FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_ops;

typedef struct FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS {
  FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_ops ops;
  void* data;
} FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS;

#define FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_ctor(_this_obj) \
  ((_this_obj)->ops.ctor)((_this_obj))
#define FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_dtor(_this_obj) \
  ((_this_obj)->ops.dtor)((_this_obj))

// 3. Macros corresponding to the operations
#define FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Receive_Message(_this_obj, _connection_id, _timeout, _transaction_id, _message, _header, _qos_parameters, _return_code) \
  ((_this_obj)->ops.Receive_Message)((_this_obj), (_connection_id), (_timeout), (_transaction_id), (_message), (_header), (_qos_parameters), (_return_code))

#define FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Send_Message(_this_obj, _connection_id, _timeout, _transaction_id, _message, _return_code) \
  ((_this_obj)->ops.Send_Message)((_this_obj), (_connection_id), (_timeout), (_transaction_id), (_message), (_return_code))

#define FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS_Register_Callback(_this_obj, _connection_id, _callback, _return_code) \
  ((_this_obj)->ops.Register_Callback)((_this_obj), (_connection_id), (_callback), (_return_code))

/* Interface FACE_TSS_DataModel_tCmdsOutIDLS_TypedTS End */


#endif // _TSS_TYPED_SAMPLE_H

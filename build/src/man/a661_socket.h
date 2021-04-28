#ifndef A661_SOCKET_H
#define A661_SOCKET_H

#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#include "a661_types.h"
#include "a661_data_buffer.h"

#ifndef INVALID_SOCKET
#define INVALID_SOCKET (-1)
#endif

/* ----------------------------------------------------------------------------------------------------------------- */
#ifndef A661_HOSTNAME_SIZE
#define A661_HOSTNAME_SIZE  (256)
#endif

#ifndef A661_DEFAULT_HOSTNAME
#define A661_DEFAULT_HOSTNAME "10.18.0.2"
#endif

#ifndef A661_BASE_PORT
#define A661_BASE_PORT 1230
#endif

/* ----------------------------------------------------------------------------------------------------------------- */
typedef enum 
{
    A661_SOCKET_OK           = 0,
    A661_NOTCONNECTED_ERROR  = 1,
    A661_CONNECT_ERROR       = 2,
    A661_RECV_ERROR          = 3,
    A661_SEND_ERROR          = 4,
    A661_OTHER_ERROR         = 5
} a661_socket_err_t;

typedef struct 
{
    int         fd;
    a661_uchar  connected;
    a661_uchar  udp;
    char        hostname[A661_HOSTNAME_SIZE];
} a661_socket_t;

/* ----------------------------------------------------------------------------------------------------------------- */
void a661_socket_init(void);

a661_socket_err_t a661_socket_open_client(a661_socket_t* context, a661_uchar udp, 
                                          const char* hostname, a661_ushort port);

a661_socket_err_t a661_socket_open_server(a661_socket_t* context, a661_uchar udp, 
                                          const char* hostname, a661_ushort port);

a661_socket_err_t a661_socket_close(a661_socket_t* context);

a661_socket_err_t a661_socket_recv(a661_socket_t* context, a661_data_buffer* buf);

a661_socket_err_t a661_socket_send(a661_socket_t* context, a661_data_buffer* buf);

#endif /* A661_SOCKET_H */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <winsock.h>
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/ioctl.h>
#endif 

#include "a661_socket.h"

/* ----------------------------------------------------------------------------------------------------------------- */
static char_t* sock_error_msg(void)
{
#ifdef _WIN32
    static char_t msg[1024];
    int errcode = 0;

    errcode = WSAGetLastError();
    (void) FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
                         FORMAT_MESSAGE_MAX_WIDTH_MASK, NULL, errcode, 0, &msg[0], sizeof msg, NULL);
    return msg;
#else
    return strerror(errno);
#endif
}
/* ----------------------------------------------------------------------------------------------------------------- */
static void critical_error(const char_t * msg, const char_t * details)
{
    printf("## ERROR: %s (%s)\n", msg, details);
    fflush(stdout);
}
/* ----------------------------------------------------------------------------------------------------------------- */
static void set_socket_nonblocking(int fd)
{
#ifdef _WIN32
    u_long o = 1U;
    int r = ioctlsocket(fd, FIONBIO, &o);
    if (r != 0) {
        critical_error("set_socket_nonblocking", "setting socket non blocking");
    }
#else
    int r = fcntl(fd, F_GETFL, 0);
    if (r < 0) {
        critical_error("set_socket_nonblocking", "getting socket status");
    }
    r = fcntl(fd, F_SETFL, r | O_NONBLOCK);
    if (r < 0) {
        critical_error("set_socket_nonblocking", "setting socket non blocking");
    }
#endif
}
/* ----------------------------------------------------------------------------------------------------------------- */
void a661_socket_init(void)
{
#ifdef _WIN32
    WSADATA data;
    (void) WSAStartup(MAKEWORD(2, 2), &data);
#else
    (void) signal(SIGPIPE, SIG_IGN);
#endif
}
/* ----------------------------------------------------------------------------------------------------------------- */
a661_socket_err_t a661_socket_open_server(a661_socket_t* context, a661_uchar udp, 
                                          const char* hostname, a661_ushort port)
{
    int rc = A661_OTHER_ERROR;      //// TBD: not yet implemented
    return rc;
}
/* ----------------------------------------------------------------------------------------------------------------- */
a661_socket_err_t a661_socket_open_client(a661_socket_t* context, a661_uchar udp, 
                                          const char* hostname, a661_ushort port)
{
    a661_socket_err_t rc = A661_SOCKET_OK;
    struct sockaddr_in name;

    context->fd = 0;
    context->connected = 0;
    context->udp = udp;
    
    if (hostname == NULL || hostname[0] == 0) {
        strncpy(context->hostname, hostname, A661_HOSTNAME_SIZE-1);
        context->hostname[A661_HOSTNAME_SIZE-1] = 0;
    }
    else {
        strncpy(context->hostname, A661_DEFAULT_HOSTNAME, A661_HOSTNAME_SIZE-1);
        context->hostname[A661_HOSTNAME_SIZE-1] = 0;
    }
    
    context->fd = socket(PF_INET, (udp ? SOCK_DGRAM : SOCK_STREAM), 0);
    if (context->fd == INVALID_SOCKET) {
        critical_error("a661_socket_open_client: cannot create socket", sock_error_msg());
        rc = A661_CONNECT_ERROR;
    }
    else {
        int result;
        memset(&name, sizeof(name), 0);
        name.sin_family = AF_INET;
        name.sin_addr.s_addr = inet_addr(A661_DEFAULT_HOSTNAME);
        name.sin_port = htons(port);
        
        result = connect(context->fd, (void *) &name, (int) (sizeof name));
        if (result < 0) {
            printf("a661_socket_open_client: cannot connect socket to port %d: %s\n", 
                   port, sock_error_msg());
            rc = A661_CONNECT_ERROR;
        }
        else {
            set_socket_nonblocking(context->fd);
            context->connected = 1;
            printf("a661_socket_open_client: connected udp=%d port=%d\n", udp, port);
        }
    }
    return rc;
}
/* ----------------------------------------------------------------------------------------------------------------- */
a661_socket_err_t a661_socket_close(a661_socket_t* context)
{
    if (context) {
        shutdown(context->fd, 2);  /* 2 = SD_BOTH */
        memset(context, sizeof(context), 0);
    }
    return A661_SOCKET_OK;
}
/* ----------------------------------------------------------------------------------------------------------------- */
a661_socket_err_t a661_socket_recv(a661_socket_t* context, a661_data_buffer* buf)
{
    a661_socket_err_t rc = A661_SOCKET_OK;

    if (!context->connected) {
        rc = A661_NOTCONNECTED_ERROR;
    }
    else {
        int len = recv(context->fd, buf->b + buf->count, buf->alloc - buf->count, 0 /*flags*/);
        if (len < 0) {
            /* This will also occur for non-blocking socket with no data ready. */
            rc = A661_RECV_ERROR;
        }
        else {
            buf->count += len;
printf("a661_socket_recv --- len %d => count %d\n", len, buf->count);
a661_data_buffer_print(buf);
printf("\n");
        }
    }
    return rc;
}
/* ----------------------------------------------------------------------------------------------------------------- */
a661_socket_err_t a661_socket_send(a661_socket_t* context, a661_data_buffer* buf)
{
    a661_socket_err_t rc = A661_SOCKET_OK;

    if (!context->connected) {
        rc = A661_NOTCONNECTED_ERROR;
    }
    else if (buf->count > 0) {
        int len = send(context->fd, buf->b, buf->count, 0);
        if (len != buf->count) {
            rc = A661_SEND_ERROR;
        }
        else {
            a661_data_buffer_remove(buf, len);
        }
    }
    return rc;
}

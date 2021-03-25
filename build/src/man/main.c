#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a661_types.h"
#include "a661_error.h"
#include "a661_utils.h"
#include "a661_mem.h"
#include "a661_data_buffer.h"
#include "a661_error_mgmt.h"
#include "a661_socket.h"
#include "a661_face_interface.h"

#include "Calc_A661_Root.h"   // SCADE Suite KCG include
#include "Operator1_UAA.h"   // UA Adaptor include

/* Support package hierarchy:

main ----------------------------------  Suite & UAA generated code
  a661_face_interface
    UA_Simple_TSS
      a661_socket
        a661_data_buffer
*/


// -------------------------------------------------------------------------------------- 
#define NET_BUFFER_SZ (100000)

#ifndef _WIN32
    #include <time.h>
    struct timespec ts = { .tv_sec = 0, .tv_nsec = 200 * 1000000 };
#endif

// -------------------------------------------------------------------------------------- 
typedef struct _a661_ua
{
    char          appname[128];
    a661_uchar    udp;           /* 0=TCP; 1=UDP */
    a661_ushort   baseport;
    a661_face_ua  face_ua;
} a661_ua;

// -------------------------------------------------------------------------------------- 
a661_ua g_ua = { "", 1U, 0U, A661_BASE_PORT };

a661_data_buffer recv_buffer;
a661_data_buffer send_buffer;

inC_Calc_A661_Root inC;
outC_Calc_A661_Root outC;

// -------------------------------------------------------------------------------------- 
void uaport_exit(int code)
{
    exit(code);
}
// -------------------------------------------------------------------------------------- 
void uaport_flush_logfile()
{
    // Stub for Simple_TSS
}
// -------------------------------------------------------------------------------------- 
void a661_report_simple_error(const char_t * message, a661_ushort value)
{
    printf("%s (%d)\n", message, value);
    fflush(stdout);
}
// -------------------------------------------------------------------------------------- 
void a661_report_simple_error_format1(const char_t * message, char_t * name, a661_long value1)
{
    printf(message, name, value1);
}
// -------------------------------------------------------------------------------------- 
void suite_init(void)
{
    a661_data_buffer_init(&send_buffer, NET_BUFFER_SZ);
    a661_data_buffer_init(&recv_buffer, NET_BUFFER_SZ);

    Calc_A661_Root_reset(&outC);
}
// -------------------------------------------------------------------------------------- 
a661_ulong next_block_size(a661_data_buffer* buf)
{
    a661_ulong count = a661_data_buffer_count(buf);
    a661_ulong block_size = 0;
    const a661_ulong MIN_SIZE = 8U;
  
    if (count < MIN_SIZE) {
        block_size = 0;
    }
    else {
        block_size = (buf->b[4] << 3) + 
                     (buf->b[5] << 2) + 
                     (buf->b[6] << 1) + 
                     (buf->b[7] << 0);

        if (block_size > count) {
            block_size = 0;
        }
        /* TBD: also validate A661_END_BLOCK word */
    }
    return block_size;
}
// -------------------------------------------------------------------------------------- 
void FACE_UoP_entry(a661_ua* ua)
{
    FACE_RETURN_CODE_TYPE return_code;
    a661_error err = A661_NO_ERROR;

    printf("FACE_UoP_init  appid=%d\n", ua->face_ua.appid);
    fflush(stdout);
    
    suite_init();
    a661_socket_init();
    a661_face_init();
    
    err = a661_face_open_socket(&ua->face_ua, ua->udp);
    
    if (err) {
        // TBD
    }
    else {
        while (1) {
            /* Note: this function always returns exactly 1 A661 block, if any. */
            a661_error err = a661_face_recv(&ua->face_ua, &recv_buffer);

            if (a661_data_buffer_count(&recv_buffer) > 0) {
                /* Call UAA receive function to decode each received A661 block. */
                a661_ulong block_size = next_block_size(&recv_buffer);
                while (block_size > 0) {
                    Operator1_UAA_receive(recv_buffer.b, (uaa_size) block_size, &inC, NULL);
                    a661_data_buffer_remove(&recv_buffer, block_size);
                    block_size = next_block_size(&recv_buffer);
                }
                a661_data_buffer_clear(&recv_buffer);
            }
            
            Calc_A661_Root(&inC, &outC);

            Operator1_UAA_receive_clear(&inC, NULL);

            send_buffer.count = Operator1_UAA_send(send_buffer.b, &outC, NULL);
            if (a661_data_buffer_count(&send_buffer) > 0) {
                /* Note: this function will remove any sent data from the buffer. */
                a661_face_send(&ua->face_ua, &send_buffer);
            }
            
            #ifdef _WIN32
              Sleep(200);
            #else
              nanosleep(&ts, &ts);
            #endif
            
        }
        a661_face_close_socket(&ua->face_ua);
    }
    printf("END FACE_UoP_init\n");
}

// -------------------------------------------------------------------------------------- 
static void usage(char* argv0)
{
    printf("Usage: %s [-help] [-udp] [-baseport <%d>] [-appid <1>] [-name <appname>]\n", 
            argv0, A661_BASE_PORT);
    uaport_exit(1);
}
// -------------------------------------------------------------------------------------- 
int main(int argc, char **argv)
{
    a661_ushort i;
    a661_uchar  udp          = 0U;
    a661_ushort baseport     = A661_BASE_PORT;
    a661_ushort appid        = 1U;
    char        appname[256] = "";
    a661_uchar  usage_flag   = 0U;

#ifdef _WIN32
    /* Workaround for buffering issues with Cygwin-based terminals: */
    /* disable all buffering for stdout and stderr. */
    (void) setvbuf(stdout, NULL, _IONBF, 0U);
    (void) setvbuf(stderr, NULL, _IONBF, 0U);
#endif
     
    /* Parse arguments */
    for (i = 1U; (i < argc); i++) {
        if (a661_streq(argv[i], "-udp")) {
            udp = 1U;
        }
        else if (a661_streq(argv[i], "-baseport") && ((i + 1) < argc)) {
            i += 1;
            baseport = (a661_ushort) atoi(argv[i]);
        }
        else if (a661_streq(argv[i], "-appid") && ((i + 1) < argc)) {
            i += 1;
            appid = (a661_ushort) atoi(argv[i]);
        }
        else if (a661_streq(argv[i], "-name") && ((i + 1) < argc)) {
            i += 1;
            memset(appname, sizeof(appname), 0);
            snprintf(appname, sizeof(appname)-1, "%s", argv[i]);
        }
        else if (a661_streq(argv[i], "-h") || a661_streq(argv[i], "-help")) {
            usage_flag = 1U;
        }
        else {
            printf("Error: unknown option \"%s\".\n", argv[i]);
            usage_flag = 1U;
        }
    }
    if (usage_flag == 1) {
        /* Note: usage() will exit the application. */
        usage(argv[0]);
    }
    
    /* Validate command line arguments and apply to global UA object. */
    
    if (udp == 0 || udp == 1) {
        g_ua.udp = udp;
    }
    else {
        printf("## Warning: invalid -udp (%d). Using default (%d) instead...\n", udp, g_ua.udp);
        fflush(stdout);
    }

    if (baseport > 0) {
        g_ua.baseport = baseport;
    }
    else {
        printf("## Warning: invalid -baseport (%d). Using default (%d) instead...\n", baseport, g_ua.baseport);
        fflush(stdout);
    }

    if (appid > 0) {
        g_ua.face_ua.appid = appid;
    }
    else {
        g_ua.face_ua.appid = 1;
        printf("## Warning: invalid -appid (%d). Using default (%d) instead...\n", appid, g_ua.face_ua.appid);
        fflush(stdout);
    }

    if (appname[0] != 0) {
        memset(g_ua.appname, sizeof(g_ua.appname), 0);
        strncpy(g_ua.appname, appname, sizeof(g_ua.appname)-1);
    }
    
    FACE_UoP_entry(&g_ua);

    return 0;
}

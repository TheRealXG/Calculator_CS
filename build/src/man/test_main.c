/**
 * @file
 *
 * @brief Code used to test the Media Manager.
 *
 * Telnet daemon (telnetd) and FTP daemon (ftpd) are started. Events are recorded.
 */

/*
 * Copyright (c) 2010-2016 embedded brains GmbH.  All rights reserved.
 *
 *  embedded brains GmbH
 *  Dornierstr. 4
 *  82178 Puchheim
 *  Germany
 *  <rtems@embedded-brains.de>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rtems/bdbuf.h>
#include <rtems/console.h>
#include <rtems/ftpd.h>
#include <rtems/media.h>
#include <rtems/record.h>
#include <rtems/recordserver.h>
#include <rtems/shell.h>
#include <rtems/telnetd.h>

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

#define TEST_NAME "LIBBSD MEDIA 1"
#define TEST_STATE_USER_INPUT 1

#define NET_BUFFER_SZ (100000)

#include <time.h>
struct timespec ts = { .tv_sec = 0, .tv_nsec = 200 * 1000000 };

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

struct rtems_ftpd_configuration rtems_ftpd_configuration = {
	/* FTPD task priority */
	.priority = 100,

	/* Maximum buffersize for hooks */
	.max_hook_filesize = 0,

	/* Well-known port */
	.port = 21,

	/* List of hooks */
	.hooks = NULL,

	/* Root for FTPD or NULL for "/" */
	.root = NULL,

	/* Max. connections depending on processor count */
	.tasks_count = 0,

	/* Idle timeout in seconds  or 0 for no (infinite) timeout */
	.idle = 5 * 60,

	/* Access: 0 - r/w, 1 - read-only, 2 - write-only, 3 - browse-only */
	.access = 0
};

static rtems_status_code
media_listener(rtems_media_event event, rtems_media_state state,
    const char *src, const char *dest, void *arg)
{
	if (dest == NULL) {
		dest = "NULL";
	}

	printf(
		"media listener: event = %s, state = %s, src = %s, dest = %s\n",
		rtems_media_event_description(event),
		rtems_media_state_description(state),
		src,
		dest
	);

	if (event == RTEMS_MEDIA_EVENT_MOUNT && state == RTEMS_MEDIA_STATE_SUCCESS) {
		char name[256];
		int n = snprintf(&name[0], sizeof(name), "%s/test.txt", dest);
		FILE *file;

		assert(n < (int) sizeof(name));

		printf("write file %s\n", &name[0]);
		file = fopen(&name[0], "w");
		if (file != NULL) {
			const char hello[] = "Hello, world!\n";

			fwrite(&hello[0], sizeof(hello) - 1, 1, file);
			fclose(file);
		}
	}

	return RTEMS_SUCCESSFUL;
}

static void
telnet_shell(char *name, void *arg)
{
	rtems_shell_env_t env;

	rtems_shell_dup_current_env(&env);

	env.devname = name;
	env.taskname = "TLNT";
	env.login_check = NULL;
	env.forever = false;

	rtems_shell_main_loop(&env);
}

rtems_telnetd_config_table rtems_telnetd_config = {
	.command = telnet_shell,
	.arg = NULL,
	.priority = 0,
	.stack_size = 0,
	.login_check = NULL,
	.keep_stdio = false
};

void
uaport_exit(int code)
{
    exit(code);
}

static void
usage(char* argv0)
{
    printf("Usage: %s [-help] [-udp] [-baseport <%d>] [-appid <1>] [-name <appname>]\n", 
            argv0, A661_BASE_PORT);
    uaport_exit(1);
}

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

void suite_init(void)
{
    a661_data_buffer_init(&send_buffer, NET_BUFFER_SZ);
    a661_data_buffer_init(&recv_buffer, NET_BUFFER_SZ);

    Calc_A661_Root_reset(&outC);
}

void a661_report_simple_error(const char_t * message, a661_ushort value)
{
    printf("%s (%d)\n", message, value);
    fflush(stdout);
}

void FACE_UoP_entry(a661_ua* ua)
{
    FACE_RETURN_CODE_TYPE return_code;
    a661_error err = A661_NO_ERROR;

    printf("FACE_UoP_init  appid=%d\n", ua->face_ua.appid);
    fflush(stdout);
    
    printf("Suite init\n");
    suite_init();
    printf("End Suite init. Socket init.\n");
    a661_socket_init();
    printf("End socket init. face init.\n");
    a661_face_init();
    printf("End face init.\n");
    
    err = a661_face_open_socket(&ua->face_ua, ua->udp);
    printf("Open face socket\n");
    
    if (err) {
        // TBD
        printf("Error opening face socket.\n");
    }
    else {
        while (1) {
        	printf("Wait for buffer\n");
            /* Note: this function always returns exactly 1 A661 block, if any. */
            a661_error err = a661_face_recv(&ua->face_ua, &recv_buffer);
            printf("Got buffer\n");
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
            printf("Try to calculate\n");
            Calc_A661_Root(&inC, &outC);

            Operator1_UAA_receive_clear(&inC, NULL);

            send_buffer.count = Operator1_UAA_send(send_buffer.b, &outC, NULL);
            if (a661_data_buffer_count(&send_buffer) > 0) {
                /* Note: this function will remove any sent data from the buffer. */
                a661_face_send(&ua->face_ua, &send_buffer);
            }

            nanosleep(&ts, &ts);
            
        }
        a661_face_close_socket(&ua->face_ua);
    }
    printf("END FACE_UoP_init\n");
}

static void
test_main(void)
{
//	int rv;
	rtems_status_code sc;

//	rtems_ftpd_configuration.tasks_count = MAX(4,
//	    rtems_scheduler_get_processor_maximum());
//	rv = rtems_initialize_ftpd();
//	assert(rv == 0);

//	sc = rtems_telnetd_initialize();
//	assert(sc == RTEMS_SUCCESSFUL);

//	sc = rtems_record_start_server(1, 1234, 1);
//	assert(sc == RTEMS_SUCCESSFUL);
	
	sc = rtems_shell_init("SHLL", 16 * 1024, 1, CONSOLE_DEVICE_NAME,
	    false, true, NULL);
	assert(sc == RTEMS_SUCCESSFUL);

	printf("***!!!START UA INIT!!!***\n");


    a661_ushort i;
    a661_uchar  udp          = 0U;
    a661_ushort baseport     = A661_BASE_PORT;
    a661_ushort appid        = 1U;
    char        appname[256] = "";
    a661_uchar  usage_flag   = 0U;

    int argc = 0; //Old main.c function had this, just 0 out to skip for loop below.
    char **argv; //Old main.c function had, just declare so it will compile.

     
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

	printf("***!!!FINISH UA INIT!!!***\n");
	exit(0);
}

#define DEFAULT_EARLY_INITIALIZATION

static void
early_initialization(void)
{
	rtems_status_code sc;

	sc = rtems_bdbuf_init();
	assert(sc == RTEMS_SUCCESSFUL);

	sc = rtems_media_initialize();
	assert(sc == RTEMS_SUCCESSFUL);

	sc = rtems_media_listener_add(media_listener, NULL);
	assert(sc == RTEMS_SUCCESSFUL);

	sc = rtems_media_server_initialize(
		200,
		32 * 1024,
		RTEMS_DEFAULT_MODES,
		RTEMS_DEFAULT_ATTRIBUTES
	);
	assert(sc == RTEMS_SUCCESSFUL);
}

#define DEFAULT_NETWORK_DHCPCD_ENABLE

#define CONFIGURE_MICROSECONDS_PER_TICK 1000

#define CONFIGURE_MAXIMUM_DRIVERS 32

#define CONFIGURE_FILESYSTEM_DOSFS

#define CONFIGURE_MAXIMUM_PROCESSORS 32

#define CONFIGURE_RECORD_PER_PROCESSOR_ITEMS 4096

#define CONFIGURE_RECORD_EXTENSIONS_ENABLED

#include <rtems/bsd/test/default-network-init.h>

#define CONFIGURE_SHELL_COMMANDS_INIT

#include <bsp/irq-info.h>

#include <rtems/netcmds-config.h>

#ifdef RTEMS_BSD_MODULE_USR_SBIN_WPA_SUPPLICANT
  #define SHELL_WPA_SUPPLICANT_COMMANDS \
    &rtems_shell_WPA_SUPPLICANT_Command, \
    &rtems_shell_WPA_SUPPLICANT_FORK_Command,
#else
  #define SHELL_WPA_SUPPLICANT_COMMANDS
#endif

#ifdef RTEMS_BSD_MODULE_NETIPSEC
  #define SHELL_NETIPSEC_COMMANDS \
    &rtems_shell_RACOON_Command, \
    &rtems_shell_SETKEY_Command,
#else
  #define SHELL_NETIPSEC_COMMANDS
#endif

#define CONFIGURE_SHELL_USER_COMMANDS \
  SHELL_WPA_SUPPLICANT_COMMANDS \
  SHELL_NETIPSEC_COMMANDS \
  &bsp_interrupt_shell_command, \
  &rtems_shell_ARP_Command, \
  &rtems_shell_HOSTNAME_Command, \
  &rtems_shell_PING_Command, \
  &rtems_shell_ROUTE_Command, \
  &rtems_shell_NETSTAT_Command, \
  &rtems_shell_SYSCTL_Command, \
  &rtems_shell_IFCONFIG_Command, \
  &rtems_shell_IFMCSTAT_Command, \
  &rtems_shell_VMSTAT_Command

#define CONFIGURE_SHELL_COMMAND_CPUINFO
#define CONFIGURE_SHELL_COMMAND_CPUUSE
#define CONFIGURE_SHELL_COMMAND_PERIODUSE
#define CONFIGURE_SHELL_COMMAND_STACKUSE
#define CONFIGURE_SHELL_COMMAND_PROFREPORT

#define CONFIGURE_SHELL_COMMAND_CP
#define CONFIGURE_SHELL_COMMAND_PWD
#define CONFIGURE_SHELL_COMMAND_LS
#define CONFIGURE_SHELL_COMMAND_LN
#define CONFIGURE_SHELL_COMMAND_LSOF
#define CONFIGURE_SHELL_COMMAND_CHDIR
#define CONFIGURE_SHELL_COMMAND_CD
#define CONFIGURE_SHELL_COMMAND_MKDIR
#define CONFIGURE_SHELL_COMMAND_RMDIR
#define CONFIGURE_SHELL_COMMAND_CAT
#define CONFIGURE_SHELL_COMMAND_MV
#define CONFIGURE_SHELL_COMMAND_RM
#define CONFIGURE_SHELL_COMMAND_MALLOC_INFO
#define CONFIGURE_SHELL_COMMAND_MD5

#define CONFIGURE_SHELL_COMMAND_FDISK
#define CONFIGURE_SHELL_COMMAND_BLKSTATS
#define CONFIGURE_SHELL_COMMAND_BLKSYNC
#define CONFIGURE_SHELL_COMMAND_MSDOSFMT
#define CONFIGURE_SHELL_COMMAND_DF
#define CONFIGURE_SHELL_COMMAND_MOUNT
#define CONFIGURE_SHELL_COMMAND_UNMOUNT
#define CONFIGURE_SHELL_COMMAND_MSDOSFMT

#include <rtems/shellconfig.h>

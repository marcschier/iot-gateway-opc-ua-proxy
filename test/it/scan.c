// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "util_mem.h"
#include "prx_log.h"
#include "pal.h"
#include "pal_scan.h"
#include "util_string.h"
#include "util_signal.h"
#include <stdio.h>


typedef struct scan_ctx
{
    signal_t* signal;
    log_t log;
}
scan_ctx_t;

//
// Callback
//
int32_t test_scan_cb(
    void *context,
    uint64_t itf_index,
    int32_t error,
    prx_socket_address_t *addr
)
{
    scan_ctx_t* scanner = (scan_ctx_t*)context;

    (void)itf_index;

    if (error == er_ok)
    {
        if (addr->un.family == prx_address_family_inet6)
        {
            log_info(scanner->log, "Found: [%x:%x:%x:%x:%x:%x:%x:%x]:%d",
                addr->un.ip.un.in6.un.u16[0], addr->un.ip.un.in6.un.u16[1],
                addr->un.ip.un.in6.un.u16[2], addr->un.ip.un.in6.un.u16[3],
                addr->un.ip.un.in6.un.u16[4], addr->un.ip.un.in6.un.u16[5],
                addr->un.ip.un.in6.un.u16[6], addr->un.ip.un.in6.un.u16[7],
                addr->un.ip.port);
        }
        else
        {
            dbg_assert(addr->un.family == prx_address_family_inet, "af wrong");
            log_info(scanner->log, "Found: %d.%d.%d.%d:%d",
                addr->un.ip.un.in4.un.u8[0], addr->un.ip.un.in4.un.u8[1],
                addr->un.ip.un.in4.un.u8[2], addr->un.ip.un.in4.un.u8[3],
                addr->un.ip.port);

        }
    }
    else
    {
        if (error != er_nomore)
        {
            log_error(scanner->log, "Error scanning (%s)", prx_err_string(error));
        }
        signal_set(scanner->signal);
    }

    return er_ok;
}

//
// Subnet scan test utility
//
int main_scan(int argc, char *argv[])
{
    int32_t result;
    const char* port = NULL;
    scan_ctx_t ctx, *scanner = &ctx;

    if (argc <= 1)
        return er_arg;


    while (argc > 1)
    {
        argv++;
        argc--;

        /**/ if (!port)
            port = argv[0];
    }

    if (!port)
        port = "4840";

    result = pal_init();
    if (result != er_ok)
        return result;
    do
    {
        memset(scanner, 0, sizeof(scan_ctx_t));
        scanner->log = log_get("test.scan");

        result = signal_create(true, false, &scanner->signal);
        if (result != er_ok)
            break;

        result = pal_ipscan(0, (uint16_t)atoi(port), test_scan_cb, scanner);
        if (result != er_ok)
            break;

        signal_wait(scanner->signal, -1);
    }
    while (0);

    signal_free(scanner->signal);
    pal_deinit();
    return result;
}

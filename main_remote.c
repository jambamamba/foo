/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rpmsg_lite.h"
#include "rpmsg_queue.h"
#include "rpmsg_ns.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "task.h"

#include "fsl_uart.h"
#include "rsc_table.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define RPMSG_LITE_SHMEM_BASE         (VDEV0_VRING_BASE)
#define RPMSG_LITE_LINK_ID            (RL_PLATFORM_IMX8MM_M4_USER_LINK_ID)
#define APP_TASK_STACK_SIZE (256)

struct RpmsgChannel {
    struct rpmsg_lite_instance *volatile _rpmsg;
    struct rpmsg_lite_endpoint *volatile _ept;
    volatile rpmsg_queue_handle _queue;
    uint32_t _ept_address;
};

/* Globals */
static struct RpmsgChannel _channels[10];
static TaskHandle_t _app_task_handle = NULL;


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void RpmsgChannel_Init(struct RpmsgChannel *channel, int idx, struct rpmsg_lite_instance *volatile rpmsg_instance)
{
    // assert(idx > -1 && idx < sizeof(_channels)/sizeof(_channels[0]));
    static int ept_address = 30;
    channel[idx]._rpmsg = rpmsg_instance;
    channel[idx]._queue = rpmsg_queue_create(channel[idx]._rpmsg);
    channel[idx]._ept   = rpmsg_lite_create_ept(channel[idx]._rpmsg, ept_address + 10*idx, rpmsg_queue_rx_cb, channel[idx]._queue);
    static const char announcement_string[] = "rpmsg-virtual-tty-channel";
    (void)rpmsg_ns_announce(channel[idx]._rpmsg, channel[idx]._ept, announcement_string, RL_NS_CREATE);
}

static void PrepareBufferToSend(char *buf, uint32_t *len)
{
    static int i = 0;
    sprintf(buf, "hello %i\r\n", i++);
    *len = strlen(buf);
}

static void CopyReceivedMessage(
    struct rpmsg_lite_instance *volatile rpmsg_instance,
    char *out_buf,
    uint32_t buflen,
    uint32_t len,
    void *rx_buf,
    struct rpmsg_lite_endpoint *volatile ept,
    volatile uint32_t remote_addr)
{
    assert(len < buflen);
    memcpy(out_buf, rx_buf, len);
    out_buf[len] = 0; /* End string by '\0' */

    if ((len == 2) && (out_buf[0] == 0xd) && (out_buf[1] == 0xa))
        PRINTF("Get New Line From Master Side\r\n");
    else
        PRINTF("Get Message From Master Side : \"%s\" [len : %d]\r\n", out_buf, len);
}

static void EchoMessageToIMX(
    struct rpmsg_lite_instance *volatile rpmsg_instance,
    char *buf,
    uint32_t buflen,
    uint32_t len,
    struct rpmsg_lite_endpoint *volatile ept,
    volatile uint32_t remote_addr)
{
    uint32_t size;
    void *tx_buf = rpmsg_lite_alloc_tx_buffer(rpmsg_instance, &size, RL_BLOCK);
    assert(tx_buf);
    assert(size < buflen);

    len = buflen;
    PrepareBufferToSend(buf, &len);
    /* Copy string to RPMsg tx buffer */
    memcpy(tx_buf, buf, len);

    /* Echo back received message with nocopy send */
    int32_t result = rpmsg_lite_send_nocopy(rpmsg_instance, ept, remote_addr, tx_buf, len);
    if (result != 0)
    {
        assert(false);
    }
}
void ReleaseRpmsgRxBuffer(
    struct rpmsg_lite_instance *volatile rpmsg_instance,
    void *rx_buf)
{
    int result = rpmsg_queue_nocopy_free(rpmsg_instance, rx_buf);
    if (result != 0)
    {
        assert(false);
    }
}

static void app_task(void *param)
{
    /* Print the initial banner */
    PRINTF("\r\nRPMSG String Echo FreeRTOS RTOS API Demo...\r\n");

    struct rpmsg_lite_instance *volatile rpmsg_instance = rpmsg_lite_remote_init((void *)RPMSG_LITE_SHMEM_BASE, RPMSG_LITE_LINK_ID, RL_NO_FLAGS);

    while (0 == rpmsg_lite_is_link_up(rpmsg_instance))
        ;

    const int num_channels = sizeof(_channels)/sizeof(_channels[0]);
    for(int idx = 0; idx < num_channels; ++idx)
    {
        RpmsgChannel_Init(_channels, idx, rpmsg_instance);
    }

    PRINTF("\r\nNameservice sent, ready for incoming messages...\r\n");

    for (;;)
    {
        void *rx_buf;
        uint32_t len;
        volatile uint32_t remote_addr;

        for(int idx = 0; idx < num_channels; ++idx)
        {
            int32_t result = rpmsg_queue_recv_nocopy(rpmsg_instance, _channels[idx]._queue, (uint32_t *)&remote_addr, (char **)&rx_buf, &len, RL_DONT_BLOCK);
            if (result == 0)
            {
                static char app_buf[512]; /* Each RPMSG buffer can carry less than 512 payload */
                CopyReceivedMessage(rpmsg_instance, app_buf, sizeof(app_buf), len, rx_buf, _channels[idx]._ept, remote_addr);
                EchoMessageToIMX(rpmsg_instance, app_buf, sizeof(app_buf), len, _channels[idx]._ept, remote_addr);
                ReleaseRpmsgRxBuffer(rpmsg_instance, rx_buf);
            }
        }
   }
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Initialize standard SDK demo application pins */
    /* Board specific RDC settings */
    BOARD_RdcInit();

    BOARD_InitBootPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
    BOARD_InitMemory();

    copyResourceTable();

    if (xTaskCreate(app_task, "APP_TASK", APP_TASK_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &_app_task_handle) != pdPASS)
    {
        PRINTF("\r\nFailed to create application task\r\n");
        for (;;)
            ;
    }

    vTaskStartScheduler();

    PRINTF("Failed to start FreeRTOS on core0.\n");
    for (;;)
        ;
}

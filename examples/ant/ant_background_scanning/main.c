/*
This software is subject to the license described in the license.txt file
included with this software distribution. You may not use this file except in compliance
with this license.

Copyright (c) Dynastream Innovations Inc. 2013
All rights reserved.
*/

/**@file
 * @defgroup nrf_ant_background_scanning_demo ANT Background Scanning Example
 * @{
 * @ingroup nrf_ant_background_scanning_demo
 *
 * @brief Example of ANT Background Scanning implementation.
 *
 * Before compiling this example for NRF52, complete the following steps:
 * - Download the S212 SoftDevice from <a href="https://www.thisisant.com/developer/components/nrf52832" target="_blank">thisisant.com</a>.
 * - Extract the downloaded zip file and copy the S212 SoftDevice headers to <tt>\<InstallFolder\>/components/softdevice/s212/headers</tt>.
 * If you are using Keil packs, copy the files into a @c headers folder in your example folder.
 * - Make sure that @ref ANT_LICENSE_KEY in @c nrf_sdm.h is uncommented.
 */

#include <stdio.h>
#include <stdlib.h>
#include "nrf.h"
#include "bsp.h"
#include "ant_interface.h"
#include "ant_parameters.h"
#include "nrf_soc.h"
#include "nrf_sdm.h"
#include "app_error.h"
#include "app_util.h"
#include "nordic_common.h"
#include "ant_stack_config.h"
#include "ant_channel_config.h"
#include "ant_search_config.h"
#include "app_trace.h"
#include "app_timer.h"
#include "softdevice_handler.h"

#define APP_TIMER_PRESCALER         0x00                                /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_OP_QUEUE_SIZE     0x04                                /**< Size of timer operation queues. */

#define ANT_MS_CHANNEL_NUMBER       ((uint8_t) 1)                       /**< Master channel. */
#define ANT_BS_CHANNEL_NUMBER       ((uint8_t) 0)                       /**< Background scanning channel. */

#define ANT_NETWORK_NUMBER          ((uint8_t) 0)                       /**< Default public network number. */

#define ANT_MS_CHANNEL_TYPE         CHANNEL_TYPE_MASTER                 /**< Bi-directional master. */
#define ANT_BS_CHANNEL_TYPE         CHANNEL_TYPE_SLAVE                  /**< Bi-directional slave. */

#define ANT_BS_DEVICE_NUMBER        ((uint16_t) 0)                      /**< Wild-card. */

#define ANT_DEVICE_TYPE             ((uint8_t) 1)                       /**< Device type. */
#define ANT_TRANSMISSION_TYPE       ((uint8_t) 5)                       /**< Transmission type. */
#define ANT_FREQUENCY               ((uint8_t) 77)                      /**< 2477 MHz. */

#define ANT_CHANNEL_PERIOD          ((uint16_t) 2048)                   /**< 16 Hz. */
#define ANT_CHANNEL_PERIOD_NONE     ((uint16_t) 0x00)                   /**< This is not taken into account. */

#define ANT_BEACON_PAGE             ((uint8_t) 1)

void ant_message_send(void);
void background_scanner_process(ant_evt_t * p_ant_evt);
void master_beacon_process(ant_evt_t * p_ant_evt);

static uint8_t m_last_rssi       = 0;
static uint16_t m_last_device_id = 0;
static uint8_t m_recieved        = 0;

/**< Derive from device serial number. */
static uint16_t ant_ms_dev_num_get(void)
{
    return ((uint16_t) (NRF_FICR->DEVICEID[0]));
}


/**@brief Function for dispatching an ANT stack event to all modules with an ANT stack event handler.
 *
 * @details This function is called from the ANT stack event interrupt handler after an ANT stack
 *          event has been received.
 *
 * @param[in] p_ant_evt  ANT stack event.
 */
void ant_evt_dispatch(ant_evt_t * p_ant_evt)
{
    switch (p_ant_evt->channel)
    {
        case ANT_BS_CHANNEL_NUMBER:
            background_scanner_process(p_ant_evt);
            break;

        case ANT_MS_CHANNEL_NUMBER:
            master_beacon_process(p_ant_evt);
            break;

        default:
            break;
    }
}


/**@brief Initialize application.
 */
static void application_initialize()
{
    /* Set library config to report RSSI and Device ID */
    uint32_t err_code = sd_ant_lib_config_set(ANT_LIB_CONFIG_MESG_OUT_INC_RSSI
                                            | ANT_LIB_CONFIG_MESG_OUT_INC_DEVICE_ID);
    APP_ERROR_CHECK(err_code);

    const uint16_t dev_num = ant_ms_dev_num_get();

    const ant_channel_config_t ms_channel_config =
    {
        .channel_number    = ANT_MS_CHANNEL_NUMBER,
        .channel_type      = ANT_MS_CHANNEL_TYPE,
        .ext_assign        = 0x00,
        .rf_freq           = ANT_FREQUENCY,
        .transmission_type = ANT_TRANSMISSION_TYPE,
        .device_type       = ANT_DEVICE_TYPE,
        .device_number     = dev_num,
        .channel_period    = ANT_CHANNEL_PERIOD,
        .network_number    = ANT_NETWORK_NUMBER,
    };

    const ant_channel_config_t bs_channel_config =
    {
        .channel_number    = ANT_BS_CHANNEL_NUMBER,
        .channel_type      = ANT_BS_CHANNEL_TYPE,
        .ext_assign        = EXT_PARAM_ALWAYS_SEARCH,
        .rf_freq           = ANT_FREQUENCY,
        .transmission_type = ANT_TRANSMISSION_TYPE,
        .device_type       = ANT_DEVICE_TYPE,
        .device_number     = ANT_BS_DEVICE_NUMBER,
        .channel_period    = ANT_CHANNEL_PERIOD_NONE,
        .network_number    = ANT_NETWORK_NUMBER,
    };

    const ant_search_config_t bs_search_config =
    {
        .channel_number        = ANT_BS_CHANNEL_NUMBER,
        .low_priority_timeout  = ANT_LOW_PRIORITY_TIMEOUT_DISABLE,
        .high_priority_timeout = ANT_HIGH_PRIORITY_SEARCH_DISABLE,
        .search_sharing_cycles = ANT_SEARCH_SHARING_CYCLES_DISABLE,
        .search_priority       = ANT_SEARCH_PRIORITY_DEFAULT,
        .waveform              = ANT_WAVEFORM_DEFAULT,
    };

    err_code = ant_channel_init(&ms_channel_config);
    APP_ERROR_CHECK(err_code);

    err_code = ant_channel_init(&bs_channel_config);
    APP_ERROR_CHECK(err_code);

    err_code = ant_search_init(&bs_search_config);
    APP_ERROR_CHECK(err_code);

    // Fill tx buffer for the first frame
    ant_message_send();

    err_code = sd_ant_channel_open(ANT_MS_CHANNEL_NUMBER);
    APP_ERROR_CHECK(err_code);

    err_code = sd_ant_channel_open(ANT_BS_CHANNEL_NUMBER);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for the Tracer initialization.
 */
static void utils_setup(void)
{
    uint32_t err_code;

    app_trace_init();

    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);
    err_code = bsp_init(BSP_INIT_LED,
                        APP_TIMER_TICKS(100, APP_TIMER_PRESCALER),
                        NULL);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for ANT stack initialization.
 *
 * @details Initializes the SoftDevice and the ANT event interrupt.
 */
static void softdevice_setup(void)
{
    uint32_t err_code;

    nrf_clock_lf_cfg_t clock_lf_cfg = NRF_CLOCK_LFCLKSRC;

    err_code = softdevice_ant_evt_handler_set(ant_evt_dispatch);
    APP_ERROR_CHECK(err_code);

    err_code = softdevice_handler_init(&clock_lf_cfg, NULL, 0, NULL);
    APP_ERROR_CHECK(err_code);

    err_code = ant_stack_static_config();
    APP_ERROR_CHECK(err_code);
}


/**@brief Process ANT message on ANT background scanning channel.
 *
 * @param[in] p_ant_event ANT message content.
 */
void background_scanner_process(ant_evt_t * p_ant_evt)
{
    uint32_t      err_code;
    ANT_MESSAGE * p_ant_message = (ANT_MESSAGE*)p_ant_evt->msg.evt_buffer;

    switch(p_ant_evt->event)
    {
        case EVENT_RX:
        {
            err_code = bsp_indication_set(BSP_INDICATE_RCV_OK);
            APP_ERROR_CHECK(err_code);

            if(p_ant_message->ANT_MESSAGE_stExtMesgBF.bANTDeviceID)
            {
                m_last_device_id = uint16_decode(p_ant_message->ANT_MESSAGE_aucExtData);
            }

            if(p_ant_message->ANT_MESSAGE_stExtMesgBF.bANTRssi)
            {
                m_last_rssi = p_ant_message->ANT_MESSAGE_aucExtData[5];
            }

            app_trace_log("Message number %d\n\r", m_recieved);
            app_trace_log("Device ID:     %d\n\r", m_last_device_id);
            app_trace_log("RSSI:          %d\n\r\n\r", m_last_rssi);

            m_recieved++;
            break;
        }
        default:
        {
            break;
        }
    }
}


/**@brief Function for setting payload for ANT message and sending it via
 *        ANT master beacon channel.
 *
 *
 * @details   ANT_BEACON_PAGE message is queued. The format is:
 *            byte[0]   = page (1 = ANT_BEACON_PAGE)
 *            byte[1]   = last RSSI value received
 *            byte[2-3] = channel ID of device corresponding to last RSSI value (little endian)
 *            byte[6]   = counter that increases with every message period
 *            byte[7]   = number of messages received on background scanning channel
 */
void ant_message_send()
{
    uint32_t       err_code;
    uint8_t        tx_buffer[ANT_STANDARD_DATA_PAYLOAD_SIZE];
    static uint8_t counter = 0;

    tx_buffer[0] = ANT_BEACON_PAGE;
    tx_buffer[1] = m_last_rssi;
    tx_buffer[2] = (uint8_t) m_last_device_id;        // LSB
    tx_buffer[3] = (uint8_t) (m_last_device_id >> 8); // MSB
    tx_buffer[6] = counter++;
    tx_buffer[7] = m_recieved;

    err_code = sd_ant_broadcast_message_tx(ANT_MS_CHANNEL_NUMBER,
                                           ANT_STANDARD_DATA_PAYLOAD_SIZE,
                                           tx_buffer);
    APP_ERROR_CHECK(err_code);
}


/**@brief Process ANT message on ANT master beacon channel.
 *
 *
 * @details   This function handles all events on the master beacon channel.
 *            On EVENT_TX an ANT_BEACON_PAGE message is queued.
 *
 * @param[in] p_ant_event ANT message content.
 */
void master_beacon_process(ant_evt_t * p_ant_evt)
{
    switch(p_ant_evt->event)
    {
        case EVENT_TX:
            ant_message_send();
            break;

        default:
            break;
    }

}


/* Main function */
int main(void)
{
    uint32_t err_code;

    utils_setup();
    softdevice_setup();
    application_initialize();

    // Enter main loop
    for (;;)
    {
        err_code = sd_app_evt_wait();
        APP_ERROR_CHECK(err_code);
    }
}
/**
 *@}
 **/

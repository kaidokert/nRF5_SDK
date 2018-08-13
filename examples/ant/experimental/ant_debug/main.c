/*
This software is subject to the license described in the License.txt file
included with this software distribution. You may not use this file except in compliance
with this license.

Copyright (c) Dynastream Innovations Inc. 2015
All rights reserved.
*/

#include <stdint.h>
#include <string.h>
#include "nrf.h"
#include "app_error.h"
#include "app_timer.h"
#include "bsp.h"
#include "boards.h"
#include "softdevice_handler.h"
#include "ant_stack_config.h"
#include "application.h"
#include "debug.h"

#define APP_TIMER_PRESCALER             0                    /**< Value of the RTC1 PRESCALER register. */
#define APP_TIMER_OP_QUEUE_SIZE         2u                   /**< Size of timer operation queues. */


/**@brief Function for error handling, which demonstrates usage of the ANT debug
 * module to output debug information over the debug channel on an assertion
 *
 * @param[in] error_code  Error code supplied to the handler.
 * @param[in] line_num    Line number where the handler is called.
 * @param[in] p_file_name Pointer to the file name.
 */
void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info)
{
    #if defined(INCLUDE_DEBUG_CHANNEL)
    error_info_t * p_error_info = (error_info_t *)info;
    char     file_name[2];
    uint32_t file_name_len = strlen((char *)p_error_info->p_file_name);

    file_name[0] = '\0';
    file_name[1] = '\0';

    for (uint32_t i = 0; i < file_name_len; i++)
    {
        if ((p_error_info->p_file_name[i] != '.')
         && (p_error_info->p_file_name[i] != '/')
         && (p_error_info->p_file_name[i] != '\\'))
        {
            file_name[0] = p_error_info->p_file_name[i + 1];
            file_name[1] = p_error_info->p_file_name[i];
            break;
        }
    }

    ad_force_error_page((uint8_t)p_error_info->err_code, (uint16_t)p_error_info->line_num, file_name);
    #endif

    LEDS_ON(LEDS_MASK);

    for (;;)
    {
        // No implementation needed.
    }
}


/**@brief Function for dispatching a ANT stack event to all modules with a ANT stack event handler.
 *
 * @details This function is called from the ANT Stack event interrupt handler after a ANT stack
 *          event has been received.
 *
 * @param[in] p_ant_evt  ANT stack event.
 */
void ant_evt_dispatch(ant_evt_t * p_ant_evt)
{
    switch(p_ant_evt->channel)
    {
        case APPLICATION_CHANNEL:
            app_channel_event_handler(p_ant_evt);
            break;

    #ifdef INCLUDE_DEBUG_CHANNEL
        case DEBUG_CHANNEL:
            // Transmit GPIO register values on debug channel
            ad_set_debug_field( ANT_DEBUG_FIELD_GPIO_REGISTER_LOW, (uint16_t)(NRF_GPIO->IN));
            ad_set_debug_field( ANT_DEBUG_FIELD_GPIO_REGISTER_HIGH, (uint16_t)(NRF_GPIO->IN >> 16) );

            // If event is from debug channel, let the debug handler handle it
            ad_process_ant_event(p_ant_evt);
            break;
    #endif

        default:
            break;
    }
}

/**@brief Function for the Timer and BSP initialization.
 */
static void utils_setup(void)
{
    uint32_t err_code;

    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);
    err_code = bsp_init(BSP_INIT_LED | BSP_INIT_BUTTONS,
                        APP_TIMER_TICKS(100, APP_TIMER_PRESCALER),
                        NULL);
    APP_ERROR_CHECK(err_code);
}


/**@brief Function for application main entry. Does not return.
 */
int main(void)
{
    uint32_t err_code;
    nrf_clock_lf_cfg_t clock_lf_cfg = NRF_CLOCK_LFCLKSRC;

    utils_setup();

    // Enable SoftDevice.
    err_code = softdevice_ant_evt_handler_set(ant_evt_dispatch);
    APP_ERROR_CHECK(err_code);

    err_code = softdevice_handler_init(&clock_lf_cfg, NULL, 0, NULL);
    APP_ERROR_CHECK(err_code);

    err_code = ant_stack_static_config();
    APP_ERROR_CHECK(err_code);

    // Setup and open Channel_0 as a Bidirectional Master.
    app_channel_setup();

    #ifdef INCLUDE_DEBUG_CHANNEL
    // Setup and open Debug Channel
    ad_init();
    ad_register_custom_command_callback(app_custom_debug_command_handler);
    #endif

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

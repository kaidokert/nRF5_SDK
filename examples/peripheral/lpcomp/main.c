/**
 * Copyright (c) 2014 - 2017, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** @file
 * @defgroup nrf_lpcomp_example main.c
 * @{
 * @ingroup nrf_lpcomp_example
 * @brief LPCOMP example application main file.
 *
 * This is an example low power comparator application.
 * The example requires that LPCOMP A,B inputs are connected with QENC A,B outputs and
 * LPCOMP LED output is connected with LPCOMP LED input.
 *
 * Example uses software quadrature encoder simulator QENC.
 * Quadrature encoder simulator uses one channel of GPIOTE module.
 * The state of the encoder changes on the inactive edge of the sampling clock generated by LED output.
 *
 * In a infinite loop QENC produces variable number of positive and negative pulses
 * synchronously with bursts of clock impulses generated by LPCOMP at LED output.
 * The pulses are counted by LPCOMP operating in a REPORT mode.
 * Pulses counted by LPCOMP are compared with pulses generated by QENC.
 * The tests stops if there is a difference between number of pulses counted and generated.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_drv_lpcomp.h"
#include "nrf_error.h"
#include "app_error.h"
#include "boards.h"

#define NRF_LOG_MODULE_NAME "APP"
#include "nrf_log.h"
#include "nrf_log_ctrl.h"

#define WAVE_ON_PIN_NUMBER 2

static volatile uint32_t voltage_falls_detected = 0;
static volatile uint32_t voltage_falls_total    = 0;

/**
 * @brief LPCOMP event handler is called when LPCOMP detects voltage drop.
 *
 * This function is called from interrupt context so it is very important
 * to return quickly. Don't put busy loops or any other CPU intensive actions here.
 * It is also not allowed to call soft device functions from it (if LPCOMP IRQ
 * priority is set to APP_IRQ_PRIORITY_HIGH).
 */
static void lpcomp_event_handler(nrf_lpcomp_event_t event)
{
    if (event == NRF_LPCOMP_EVENT_DOWN)
    {
        bsp_board_led_invert(BSP_BOARD_LED_0); // just change state of first LED
        voltage_falls_detected++;
        voltage_falls_total++;
    }
}


/**
 * @brief Print out detection statistics.
 */
static void print_statistics(void)
{
    while (voltage_falls_detected)
    {
        voltage_falls_detected--;
        NRF_LOG_INFO("#%d fall detected\r\n", (int)voltage_falls_total);
    }
}


/**
 * @brief Initialize LPCOMP driver.
 */
static void lpcomp_init(void)
{
    uint32_t                err_code;

    nrf_drv_lpcomp_config_t config = NRF_DRV_LPCOMP_DEFAULT_CONFIG;
    config.input = NRF_LPCOMP_INPUT_2;
    // initialize LPCOMP driver, from this point LPCOMP will be active and provided
    // event handler will be executed when defined action is detected
    err_code = nrf_drv_lpcomp_init(&config, lpcomp_event_handler);
    APP_ERROR_CHECK(err_code);
    nrf_drv_lpcomp_enable();
}


int main(void)
{
    bsp_board_leds_init();

    nrf_gpio_cfg_output(WAVE_ON_PIN_NUMBER); // on this pin 2Hz wave will be generated

#ifdef BSP_BUTTON_0
    // configure pull-up on first button
    nrf_gpio_cfg_input(BSP_BUTTON_0, NRF_GPIO_PIN_PULLUP);
#endif

    uint32_t err_code = NRF_LOG_INIT(NULL);
    APP_ERROR_CHECK(err_code);

    lpcomp_init();

    NRF_LOG_INFO("LPCOMP driver usage example\r\n");

    while (true)
    {
        print_statistics();
        bsp_board_led_on(BSP_BOARD_LED_1);
        NRF_GPIO->OUTCLR = (1 << WAVE_ON_PIN_NUMBER);
        nrf_delay_ms(100); // generate 100 ms pulse on selected pin
        print_statistics();
        bsp_board_led_off(BSP_BOARD_LED_1);
        NRF_GPIO->OUTSET = (1 << WAVE_ON_PIN_NUMBER);
        nrf_delay_ms(400);
        NRF_LOG_FLUSH();
    }
}


/** @} */

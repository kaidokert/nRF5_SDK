/* Copyright (c) 2014 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

#include "ble_gap_app.h"
#include "ble_serialization.h"
#include "app_util.h"

uint32_t ble_gap_rssi_start_req_enc(uint16_t         conn_handle,
                                    uint8_t          threshold_dbm,
                                    uint8_t          skip_count,
                                    uint8_t * const  p_buf,
                                    uint32_t * const p_buf_len)
{
    SER_ASSERT_NOT_NULL(p_buf);
    SER_ASSERT_NOT_NULL(p_buf_len);

    uint8_t  op_code  = SD_BLE_GAP_RSSI_START;
    uint32_t err_code = NRF_SUCCESS;
    uint32_t buf_len  = *p_buf_len;
    uint32_t index    = 0;

    err_code = uint8_t_enc(&op_code, p_buf, buf_len, &index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint16_t_enc(&conn_handle, p_buf, buf_len, &index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint8_t_enc(&threshold_dbm, p_buf, buf_len, &index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    err_code = uint8_t_enc(&skip_count, p_buf, buf_len, &index);
    SER_ASSERT(err_code == NRF_SUCCESS, err_code);

    *p_buf_len = index;

    return err_code;
}

uint32_t ble_gap_rssi_start_rsp_dec(uint8_t const * const p_buf,
                                    uint32_t              packet_len,
                                    uint32_t * const      p_result_code)
{
    return ser_ble_cmd_rsp_dec(p_buf, packet_len, SD_BLE_GAP_RSSI_START, p_result_code);
}

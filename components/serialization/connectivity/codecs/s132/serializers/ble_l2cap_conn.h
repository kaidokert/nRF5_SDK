/**
 * Copyright (c) 2013 - 2017, Nordic Semiconductor ASA
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


/**
 * @addtogroup ser_codecs Serialization codecs
 * @ingroup ble_sdk_lib_serialization
 */

/**
 * @addtogroup ser_conn_s130_codecs Connectivity S132 codecs
 * @ingroup ser_codecs
 */

/**@file
 *
 * @defgroup ble_l2cap_conn L2CAP Connectivity command request decoders and command response encoders
 * @{
 * @ingroup  ser_conn_s130_codecs
 *
 * @brief    L2CAP Connectivity command request decoders and command response encoders.
 */

#ifndef BLE_L2CAP_CONN_H__
#define BLE_L2CAP_CON__H__

#include "ble.h"
#include "ble_types.h"
#include "ble_ranges.h"
#include "ble_err.h"
#include "ble_l2cap.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Decodes @ref sd_ble_l2cap_cid_register command request.
 *
 * @sa @ref ble_l2cap_cid_register_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] buf_len         Length (in bytes) of response packet.
 * @param[in] p_cid           Pointer to L2CAP CID.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_l2cap_cid_register_req_dec(uint8_t const * const p_buf,
                                        uint32_t              buf_len,
                                        uint16_t *            p_cid);

/**@brief Encodes @ref sd_ble_l2cap_cid_register command response.
 *
 * @sa @ref ble_l2cap_cid_register_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_l2cap_cid_register_rsp_enc(uint32_t         return_code,
                                        uint8_t * const  p_buf,
                                        uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_l2cap_cid_unregister command request.
 *
 * @sa @ref ble_l2cap_cid_unregister_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] buf_len         Length (in bytes) of response packet.
 * @param[in] p_cid           Pointer to L2CAP CID.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_l2cap_cid_unregister_req_dec(uint8_t const * const p_buf,
                                          uint32_t              buf_len,
                                          uint16_t *            p_cid);

/**@brief Encodes @ref sd_ble_l2cap_cid_unregister command response.
 *
 * @sa @ref ble_l2cap_cid_unregister_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_l2cap_cid_unregister_rsp_enc(uint32_t         return_code,
                                          uint8_t * const  p_buf,
                                          uint32_t * const p_buf_len);

/**@brief Decodes @ref sd_ble_l2cap_tx command request.
 *
 * @sa @ref ble_l2cap_tx_rsp_enc for response encoding.
 *
 * @param[in] p_buf           Pointer to beginning of command request packet.
 * @param[in] buf_len         Length (in bytes) of response packet.
 * @param[in] p_conn_handle   Pointer to connection handle.
 * @param[in] pp_l2cap_header Pointer to pointer to L2CAP header.
 * @param[in] pp_data         Pointer to pointer L2CAP data.
 *
 * @retval NRF_SUCCESS                Decoding success.
 * @retval NRF_ERROR_NULL             Decoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Decoding failure. Incorrect buffer length.
 * @retval NRF_ERROR_INVALID_PARAM    Decoding failure. Invalid operation type.
 */
uint32_t ble_l2cap_tx_req_dec(uint8_t const * const        p_buf,
                              uint32_t const               buf_len,
                              uint16_t *                   p_conn_handle,
                              ble_l2cap_header_t * * const pp_l2cap_header,
                              uint8_t const * *            pp_data);

/**@brief Encodes @ref sd_ble_l2cap_tx command response.
 *
 * @sa @ref ble_l2cap_tx_req_dec for request decoding.
 *
 * @param[in] return_code         Return code indicating if command was successful or not.
 * @param[out] p_buf              Pointer to buffer where encoded data command response will be
 *                                returned.
 * @param[in,out] p_buf_len       \c in: size of \p p_buf buffer.
 *                                \c out: Length of encoded command response packet.
 *
 * @retval NRF_SUCCESS                Encoding success.
 * @retval NRF_ERROR_NULL             Encoding failure. NULL pointer supplied.
 * @retval NRF_ERROR_INVALID_LENGTH   Encoding failure. Incorrect buffer length.
 */
uint32_t ble_l2cap_tx_rsp_enc(uint32_t         return_code,
                              uint8_t * const  p_buf,
                              uint32_t * const p_buf_len);


#ifdef __cplusplus
}
#endif

#endif //BLE_L2CAP_CONN_H__

/**
   @}
 */

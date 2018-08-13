//-----------------------------------------------------------------------------------
//    The confidential and proprietary information contained in this file may
//    only be used by a person authorised under and to the extent permitted
//    by a subsisting licensing agreement from ARM Limited or its affiliates
//    or between you and a party authorised by ARM
//
//           (C) COPYRIGHT [2016] ARM Limited or its affiliates
//               ALL RIGHT RESERVED
//
//    This entire notice must be reproduced on all copies of this file
//    and copies of this files may only be made by a person if such person is
//    permitted to do so under the terms of a subsisting license agreement
//    from ARM Limited or its affiliates or between you and a party authorised by ARM
//-----------------------------------------------------------------------------------


#ifndef CRYS_RSA_SCHEMES_H
#define CRYS_RSA_SCHEMES_H


#include "crys_error.h"
#include "crys_rsa_types.h"
#include "crys_rnd.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*!
@file
@brief This module defines APIs that support [PKCS1_1.5] and [PKCS1_2.1] encryption and signature schemes.
*/

/**********************************************************************************************************/
/*!
@brief This function implements the Encrypt algorithm, as defined in [PKCS1_2.1] and [PKCS1_1.5].

It should not be called directly. Instead, use macros ::CRYS_RSA_OAEP_Encrypt or ::CRYS_RSA_PKCS1v15_Encrypt.

@return CRYS_OK on success.
@return A non-zero value from crys_rsa_error.h on failure.
*/
CIMPORT_C CRYSError_t SaSi_RsaSchemesEncrypt(
                        CRYS_RND_Context_t *rndContext_ptr,         /*!< [in/out] Pointer to the RND context buffer. */
                        CRYS_RSAUserPubKey_t  *UserPubKey_ptr,      /*!< [in]  Pointer to the public key data structure. */
                        CRYS_RSAPrimeData_t   *PrimeData_ptr,       /*!< [in]  Pointer to a temporary structure that is internally used as workspace for the
									       Encryption operation. */
                        CRYS_RSA_HASH_OpMode_t hashFunc,            /*!< [in]  The HASH function to be used. One of the supported SHA-x HASH modes, as defined
									       in ::CRYS_RSA_HASH_OpMode_t (MD5 is not supported).*/
                        uint8_t  *L,                                /*!< [in]  The label input pointer. Relevant for [PKCS1_2.1] only. NULL by default.
									       NULL for [PKCS1_1.5]. */
                        uint16_t  Llen,                             /*!< [in]  The label length. Relevant for [PKCS1_2.1] only. Zero by default.
									       Must be <=2048. Zero for [PKCS1_1.5]. */
                        CRYS_PKCS1_MGF_t MGF,                       /*!< [in]  The mask generation function. [PKCS1_2.1] defines MGF1, so the only value
									       allowed here is CRYS_PKCS1_MGF1. */
                        uint8_t   *DataIn_ptr,                      /*!< [in]  Pointer to the data to encrypt. */
                        uint16_t   DataInSize,                      /*!< [in]  The size (in bytes) of the data to encrypt. The data size must be:
                                                                                - For [PKCS1_2.1], DataSize <= modulus size - 2*HashLen - 2.
                                                                                - For [PKCS1_1.5], DataSize <= modulus size - 11. */
                        uint8_t   *Output_ptr,                      /*!< [out] Pointer to the encrypted data. The buffer must be at least modulus size bytes long. */
                        CRYS_PKCS1_version  PKCS1_ver               /*!< [in]  [PKCS1_1.5] or [PKCS1_2.1], according to the functionality required. */
);

/*!
   @brief
   CRYS_RSA_OAEP_PSS21_Encrypt implements the RSAES-OAEP algorithm
   as defined in PKCS#1 v2.1 8.1.

   \note It is not recommended to use hash MD5 in OAEP PKCS1 ver 2.1, therefore
   	it is not supported.

   This function combines the RSA encryption primitive and the
   EME-OAEP encoding method, to provide an RSA-based encryption
   method that is semantically secure against adaptive
   chosen-ciphertext attacks. For additional details, please refer to
   the PKCS#1 standard.
*/
#define CRYS_RSA_OAEP_Encrypt(rndContext_ptr, UserPubKey_ptr,PrimeData_ptr,HashMode,L,Llen,MGF,Data_ptr,DataSize,Output_ptr)\
		SaSi_RsaSchemesEncrypt(rndContext_ptr, UserPubKey_ptr,PrimeData_ptr,HashMode,L,Llen,MGF,Data_ptr,DataSize,Output_ptr,CRYS_PKCS1_VER21)

/*!
   @brief
   CRYS_RSA_PKCS1v15_Encrypt implements the RSAES-PKCS1v15 algorithm
   as defined in PKCS#1 v2.1 8.2.
*/
#define CRYS_RSA_PKCS1v15_Encrypt(rndContext_ptr, UserPubKey_ptr,PrimeData_ptr,DataIn_ptr,DataInSize,Output_ptr)\
		SaSi_RsaSchemesEncrypt(rndContext_ptr, UserPubKey_ptr,PrimeData_ptr,CRYS_RSA_HASH_NO_HASH_mode,NULL,0,CRYS_PKCS1_NO_MGF,DataIn_ptr, \
		DataInSize, Output_ptr,CRYS_PKCS1_VER15)


/**********************************************************************************************************/
/*!
@brief This function implements the Decrypt algorithm, as defined in [PKCS1_2.1] and [PKCS1_1.5].

It should not be called directly. Instead, use macros ::CRYS_RSA_OAEP_Decrypt or ::CRYS_RSA_PKCS1v15_Decrypt.

@return CRYS_OK on success.
@return A non-zero value from crys_rsa_error.h on failure.
*/
CIMPORT_C CRYSError_t SaSi_RsaSchemesDecrypt(
                                CRYS_RSAUserPrivKey_t  *UserPrivKey_ptr,    /*!< [in]  Pointer to the private key data structure of the user. */
                                CRYS_RSAPrimeData_t    *PrimeData_ptr,      /*!< [in]  Pointer to a temporary structure that is internally used as workspace
										       for the decryption operation. */
                                CRYS_RSA_HASH_OpMode_t  hashFunc,           /*!< [in]  The HASH function to be used. One of the supported SHA-x HASH modes,
										       as defined in ::CRYS_RSA_HASH_OpMode_t (MD5 is not supported). */
                                uint8_t                 *L,                 /*!< [in]  The label input pointer. Relevant for [PKCS1_2.1] only. NULL by default.
										       NULL for [PKCS1_1.5]. */
                                uint16_t              Llen,                 /*!< [in]  The label length. Relevant for [PKCS1_2.1] only. Zero by default.
										       Zero for [PKCS1_1.5]. */
                                CRYS_PKCS1_MGF_t        MGF,                /*!< [in]  The mask generation function. [PKCS1_2.1] defines MGF1, so the only
										       value allowed here is CRYS_PKCS1_MGF1. */
                                uint8_t              *DataIn_ptr,           /*!< [in]  Pointer to the data to decrypt. */
                                uint16_t              DataInSize,           /*!< [in]  The size (in bytes) of the data to decrypt. DataSize must be &le;
										       the modulus size. */
                                uint8_t              *Output_ptr,           /*!< [in]  Pointer to the decrypted data. The buffer must be at least
										       PrivKey_ptr->N.len bytes long (i.e. the modulus size in bytes). */
                                uint16_t             *OutputSize_ptr,       /*!< [in]  Pointer to the byte size of the buffer pointed to by Output_buffer.
										       The size must be:
                                                                                       <ul><li> For PKCS #1 v2.1: Modulus size > OutputSize >=
												(modulus size - 2*HashLen - 2).</li>
                                                                                       <li> For PKCS #1 v1.5: Modulus size > OutputSize >= (modulus size - 11).
                                                                                        The value pointed by OutputSize_ptr is updated after decryption with
											the actual number of bytes that are loaded to Output_ptr.</li></ul> */
                                CRYS_PKCS1_version      PKCS1_ver           /*!< [in]  [PKCS1_1.5] or [PKCS1_2.1], according to the functionality required. */
);

/**********************************************************************************************************/
/**
   @brief
   CRYS_RSA_OAEP_Decrypt implements the RSAES-OAEP algorithm
   as defined in PKCS#1 v2.1 8.1.

   \note It is not recommended to use hash MD5 in OAEP PKCS1 ver 2.1, therefore
   it is not supported.

   This function combines the RSA decryption primitive and the
   EME-OAEP encoding method, to provide an RSA-based decryption
   method that is semantically secure against adaptive
   chosen-ciphertext attacks. For more details, please refer to
   the PKCS#1 standard.

*/
#define CRYS_RSA_OAEP_Decrypt(UserPrivKey_ptr,PrimeData_ptr,HashMode,L,Llen,MGF,Data_ptr,DataSize,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSchemesDecrypt(UserPrivKey_ptr,PrimeData_ptr,HashMode,L,Llen,MGF,Data_ptr,DataSize,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/**
   @brief
   CRYS_RSA_PKCS1v15_Decrypt implements the RSAES-PKCS1v15 algorithm as defined
   in PKCS#1 v2.1 8.2.
*/
#define CRYS_RSA_PKCS1v15_Decrypt(UserPrivKey_ptr,PrimeData_ptr,DataIn_ptr,DataInSize,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSchemesDecrypt(UserPrivKey_ptr,PrimeData_ptr,CRYS_RSA_HASH_NO_HASH_mode,NULL,0,CRYS_PKCS1_NO_MGF,DataIn_ptr,DataInSize,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER15)


/**********************************************************************************************************/
/*!
@brief Implements the Signing algorithm, as defined in [PKCS1_1.5] or [PKCS1_2.1], using a single function.

@return CRYS_OK on success.
@return A non-zero value from crys_rsa_error.h on failure.
*/
CIMPORT_C CRYSError_t SaSi_RsaSign(
                   CRYS_RND_Context_t *rndContext_ptr,              /*!< [in/out] Pointer to the RND context buffer. */
                   CRYS_RSAPrivUserContext_t *UserContext_ptr,      /*!< [in]  Pointer to a temporary context for internal use. */
                   CRYS_RSAUserPrivKey_t *UserPrivKey_ptr,          /*!< [in]  Pointer to the private key data structure of the user.
                                                                               The representation (pair or quintuple) and hence the algorithm (CRT or not CRT)
									       is determined by the Private Key build function -
                                                                               ::CRYS_RSA_Build_PrivKey or ::CRYS_RSA_Build_PrivKeyCRT. */
                   CRYS_RSA_HASH_OpMode_t rsaHashMode,              /*!< [in]  One of the supported SHA-x HASH modes, as defined in ::CRYS_RSA_HASH_OpMode_t.
									       (MD5 is not supported). */
                   CRYS_PKCS1_MGF_t MGF,                            /*!< [in]  The mask generation function. [PKCS1_2.1] defines only MGF1, so the only value
									       allowed for [PKCS1_2.1] is CRYS_PKCS1_MGF1. */
                   uint16_t     SaltLen,                            /*!< [in]  The Length of the Salt buffer (relevant for PKCS#1 Ver 2.1 only, typically lengths is 0 or hash Len).
                                                                               FIPS 186-4 requires, that SaltLen <= hash len. If SaltLen > KeySize - hash Len - 2, the function
                                                                               returns an error.  */
                   uint8_t     *DataIn_ptr,                         /*!< [in]  Pointer to the input data to be signed.
                                                                               The size of the scatter/gather list representing the data buffer is limited to 128
									       entries, and the size of each entry is limited to 64KB (fragments larger than
									       64KB are broken into fragments <= 64KB). */
                   uint32_t     DataInSize,                         /*!< [in]  The size (in bytes) of the data to sign. */
                   uint8_t     *Output_ptr,                         /*!< [out] Pointer to the signature. The buffer must be at least PrivKey_ptr->N.len bytes
									       long (i.e. the modulus size in bytes). */
                   uint16_t    *OutputSize_ptr,                     /*!< [in/out] Pointer to the signature size value - the input value is the signature
										  buffer size allocated, the output value is the signature size used.
                                                                                  he buffer must be equal to PrivKey_ptr->N.len bytes long
										  (i.e. the modulus size in bytes). */
                   CRYS_PKCS1_version PKCS1_ver                     /*!< [in]  [PKCS1_1.5] or [PKCS1_2.1], according to the functionality required. */
);


/*!
@brief CRYS_RSA_PKCS1v15_Sign implements the RSASSA-PKCS1v15 algorithm as defined in PKCS#1 v1.5.

This function combines the RSASP1 signature primitive and the EMSA-PKCS1v15 encoding method, to provide an RSA-based signature scheme.
For more details, please refer to the PKCS#1 standard.
 */

#define CRYS_RSA_PKCS1v15_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,hashFunc,DataIn_ptr,DataInSize,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, (UserContext_ptr),(UserPrivKey_ptr),(hashFunc),(CRYS_PKCS1_NO_MGF),0,(DataIn_ptr),(DataInSize),(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)


/*!
@brief CRYS_RSA_PKCS1v15_SHA1_Sign implements the RSASSA-PKCS1v15 algorithm as defined in PKCS#1 v1.5, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-1.

\note The data_in size is already known after the Hash.
*/
#define CRYS_RSA_PKCS1v15_SHA1_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,DataIn_ptr,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, (UserContext_ptr),(UserPrivKey_ptr),(CRYS_RSA_After_SHA1_mode),(CRYS_PKCS1_NO_MGF),0,(DataIn_ptr),CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES,(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PKCS1v15_MD5_Sign implements the RSASSA-PKCS1v15 algorithm as defined in PKCS#1 v1.5, but without performing a HASH function -
it assumes that the data in has already been hashed using MD5.

\note The data_in size is already known after the Hash.
*/

#define CRYS_RSA_PKCS1v15_MD5_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,DataIn_ptr,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, (UserContext_ptr),(UserPrivKey_ptr),CRYS_RSA_After_MD5_mode,CRYS_PKCS1_NO_MGF,0,(DataIn_ptr),CRYS_HASH_MD5_DIGEST_SIZE_IN_BYTES,(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)


/*!
@brief CRYS_RSA_PKCS1v15_SHA224_Sign implements the RSASSA-PKCS1v15 algorithm as defined in PKCS#1 v1.5, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-224.

\note The data_in size is already known after the Hash.
*/
#define CRYS_RSA_PKCS1v15_SHA224_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,DataIn_ptr,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, (UserContext_ptr),(UserPrivKey_ptr),(CRYS_RSA_After_SHA224_mode),(CRYS_PKCS1_NO_MGF),0,(DataIn_ptr),CRYS_HASH_SHA224_DIGEST_SIZE_IN_BYTES,(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)


/*!
@brief CRYS_RSA_PKCS1v15_SHA256_Sign implements the RSASSA-PKCS1v15 algorithm as defined in PKCS#1 v1.5, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-256.

\note The data_in size is already known after the Hash.
*/
#define CRYS_RSA_PKCS1v15_SHA256_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,DataIn_ptr,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, (UserContext_ptr),(UserPrivKey_ptr),(CRYS_RSA_After_SHA256_mode),(CRYS_PKCS1_NO_MGF),0,(DataIn_ptr),CRYS_HASH_SHA256_DIGEST_SIZE_IN_BYTES,(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PKCS1v15_SHA1_Sign implements the RSASSA-PKCS1v15 algorithm as defined in PKCS#1 v1.5, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-384.

\note The data_in size is already known after the Hash.
*/
#define CRYS_RSA_PKCS1v15_SHA384_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,DataIn_ptr,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, (UserContext_ptr),(UserPrivKey_ptr),(CRYS_RSA_After_SHA384_mode),(CRYS_PKCS1_NO_MGF),0,(DataIn_ptr),CRYS_HASH_SHA384_DIGEST_SIZE_IN_BYTES,(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)


/*!
@brief CRYS_RSA_PKCS1v15_SHA512_Sign implements the RSASSA-PKCS1v15 algorithm  as defined in PKCS#1 v1.5, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-512.

\note The data_in size is already known after the Hash.
*/
#define CRYS_RSA_PKCS1v15_SHA512_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,DataIn_ptr,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, (UserContext_ptr),(UserPrivKey_ptr),(CRYS_RSA_After_SHA512_mode),(CRYS_PKCS1_NO_MGF),0,(DataIn_ptr),CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES,(Output_ptr),(OutputSize_ptr),CRYS_PKCS1_VER15)



/*!
@brief CRYS_RSA_PSS_Sign implements the RSASSA-PSS algorithm as defined in PKCS#1 v2.1 9.1, in a single function call.

\note According to the PKCS#1 ver2.1 it is not recommended to use MD5 Hash, therefore it is not supported.

The actual macro that is used by the user is ::CRYS_RSA_PSS_Sign.
*/

#define CRYS_RSA_PSS_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,hashFunc,MGF,SaltLen,DataIn_ptr,DataInSize,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,hashFunc,MGF,SaltLen,DataIn_ptr,DataInSize,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA1_Sign implements the RSASSA-PSS algorithm as defined in PKCS#1 v2.1 9.1 in a single function call, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-1.

\note The data_in size is already known after the Hash.

The actual macro that is used by the users is ::CRYS_RSA_PSS_SHA1_Sign.
*/

#define CRYS_RSA_PSS_SHA1_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,MGF,SaltLen,DataIn_ptr,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,CRYS_RSA_After_SHA1_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA224_Sign implements the RSASSA-PSS algorithm as defined in PKCS#1 v2.1 9.1 in a single function call, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-224.

\note The data_in size is already known after the Hash.

The actual macro that is used by the users is ::CRYS_RSA_PSS_SHA224_Sign.
*/

#define CRYS_RSA_PSS_SHA224_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,MGF,SaltLen,DataIn_ptr,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,CRYS_RSA_After_SHA224_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA224_DIGEST_SIZE_IN_BYTES,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA256_Sign implements the RSASSA-PSS algorithm as defined in PKCS#1 v2.1 9.1 in a single function call, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-256.

\note The data_in size is already known after the Hash.

The actual macro that is used by the users is ::CRYS_RSA_PSS_SHA256_Sign.
*/

#define CRYS_RSA_PSS_SHA256_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,MGF,SaltLen,DataIn_ptr,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,CRYS_RSA_After_SHA256_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA256_DIGEST_SIZE_IN_BYTES,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA384_Sign implements the RSASSA-PSS algorithm as defined in PKCS#1 v2.1 9.1 in a single function call, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-384.

\note The data_in size is already known after the Hash.

The actual macro that is used by the users is ::CRYS_RSA_PSS_SHA384_Sign.
*/

#define CRYS_RSA_PSS_SHA384_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,MGF,SaltLen,DataIn_ptr,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,CRYS_RSA_After_SHA384_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA384_DIGEST_SIZE_IN_BYTES,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA512_Sign implements the RSASSA-PSS algorithm as defined in PKCS#1 v2.1 9.1 in a single function call, but without performing a HASH function -
it assumes that the data in has already been hashed using SHA-512.

\note The data_in size is already known after the Hash.

The actual macro that is used by the users is ::CRYS_RSA_PSS_SHA512_Sign.
*/

#define CRYS_RSA_PSS_SHA512_Sign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,MGF,SaltLen,DataIn_ptr,Output_ptr,OutputSize_ptr)\
		SaSi_RsaSign(rndContext_ptr, UserContext_ptr,UserPrivKey_ptr,CRYS_RSA_After_SHA512_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES,Output_ptr,OutputSize_ptr,CRYS_PKCS1_VER21)


/**********************************************************************************************************/
/*!
@brief Implements the RSA signature verification algorithms, in a single function call, as defined in referenced standards [PKCS1_1.5]
and [PKCS1_2.1].

@return CRYS_OK on success.
@return A non-zero value from crys_rsa_error.h on failure.
*/

CIMPORT_C CRYSError_t SaSi_RsaVerify(
                            CRYS_RSAPubUserContext_t *UserContext_ptr,      /*!< [in]  Pointer to a temporary context for internal use. */
                            CRYS_RSAUserPubKey_t *UserPubKey_ptr,           /*!< [in]  Pointer to the public key data structure of the user. */
                            CRYS_RSA_HASH_OpMode_t rsaHashMode,             /*!< [in]  One of the supported SHA-x HASH modes, as defined in ::CRYS_RSA_HASH_OpMode_t.
										       (MD5 is not supported). */
                            CRYS_PKCS1_MGF_t MGF,                           /*!< [in]  The mask generation function. [PKCS1_2.1] defines only MGF1, so the only
										       value allowed for [PKCS_2.1] is CRYS_PKCS1_MGF1. */
                            uint16_t SaltLen,                               /*!< [in]  The Length of the Salt buffer. Relevant only for [PKCS1_2.1].
										       Typical lengths are 0 or hash Len (20 for SHA-1).
                                                                                       The maximum length allowed is [modulus size - hash Len - 2]. */
                            uint8_t     *DataIn_ptr,                        /*!< [in]  Pointer to the input data to be verified.
                                                                                        The size of the scatter/gather list representing the data buffer is
											limited to 128 entries, and the size of each entry is limited to 64KB
											(fragments larger than 64KB are broken into fragments <= 64KB). */
                            uint32_t     DataInSize,                        /*!< [in]  The size (in bytes) of the data whose signature is to be verified. */
                            uint8_t     *Sig_ptr,                           /*!< [in]  Pointer to the signature to be verified.
                                                                                       The length of the signature is PubKey_ptr->N.len bytes
										       (i.e. the modulus size in bytes). */
                            CRYS_PKCS1_version PKCS1_ver                    /*!< [in]  [PKCS1_1.5] or [PKCS1_2.1], according to the functionality required. */
);

#define CRYS_RSA_PKCS1v15_Verify(UserContext_ptr,UserPubKey_ptr,hashFunc,DataIn_ptr,DataInSize,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,hashFunc,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,DataInSize,Sig_ptr,CRYS_PKCS1_VER15)


/*!
@brief CRYS_RSA_PKCS1v15_MD5_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5, but without operating the HASH function -
it assumes the DataIn_ptr data has already been hashed using MD5.
*/

#define CRYS_RSA_PKCS1v15_MD5_Verify(UserContext_ptr,UserPubKey_ptr,DataIn_ptr,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_MD5_mode,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,CRYS_HASH_MD5_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER15)


/*!
@brief CRYS_RSA_PKCS1v15_SHA1_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5, but without operating the HASH function -
it assumes that the DataIn_ptr data has already been hashed using SHA1.

*/
#define CRYS_RSA_PKCS1v15_SHA1_Verify(UserContext_ptr,UserPubKey_ptr,DataIn_ptr,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA1_mode,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PKCS1v15_SHA224_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5, but without operating the HASH function -
it assumes that the DataIn_ptr data has already been hashed using SHA224.

*/
#define CRYS_RSA_PKCS1v15_SHA224_Verify(UserContext_ptr,UserPubKey_ptr,DataIn_ptr,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA224_mode,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,CRYS_HASH_SHA224_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PKCS1v15_SHA256_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5, but without operating the HASH function -
it assumes that the DataIn_ptr data has already been hashed using SHA256.

*/
#define CRYS_RSA_PKCS1v15_SHA256_Verify(UserContext_ptr,UserPubKey_ptr,DataIn_ptr,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA256_mode,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,CRYS_HASH_SHA256_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PKCS1v15_SHA384_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5, but without operating the HASH function -
it assumes that the DataIn_ptr data has already been hashed using SHA384.

*/
#define CRYS_RSA_PKCS1v15_SHA384_Verify(UserContext_ptr,UserPubKey_ptr,DataIn_ptr,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA384_mode,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,CRYS_HASH_SHA384_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PKCS1v15_SHA512_Verify implements the RSASSA-PKCS1v15 Verify algorithm as defined in PKCS#1 v1.5, but without operating the HASH function -
it assumes that the DataIn_ptr data has already been hashed using SHA512.

*/
#define CRYS_RSA_PKCS1v15_SHA512_Verify(UserContext_ptr,UserPubKey_ptr,DataIn_ptr,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA512_mode,CRYS_PKCS1_NO_MGF,0,DataIn_ptr,CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER15)

/*!
@brief CRYS_RSA_PSS_Verify implements the RSASSA-PKCS1v21 Verify algorithm as defined in PKCS#1 v2.1.
*/

#define CRYS_RSA_PSS_Verify(UserContext_ptr,UserPubKey_ptr,hashFunc,MGF,SaltLen,DataIn_ptr,DataInSize,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,hashFunc,MGF,SaltLen,DataIn_ptr,DataInSize,Sig_ptr,CRYS_PKCS1_VER21)

			      /*!
@brief CRYS_RSA_PSS_SHA1_Verify implements the PKCS1v21 Verify algorithm as defined in PKCS#1 v2.1, but without operating the HASH function -
it assumes the DataIn_ptr has already been hashed using SHA1.

*/

#define CRYS_RSA_PSS_SHA1_Verify(UserContext_ptr,UserPubKey_ptr,MGF,SaltLen,DataIn_ptr,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA1_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA1_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA224_Verify implements the PKCS1v21 Verify algorithm as defined in PKCS#1 v2.1, but without operating the HASH function -
it assumes the DataIn_ptr has already been hashed using SHA224.
*/

#define CRYS_RSA_PSS_SHA224_Verify(UserContext_ptr,UserPubKey_ptr,MGF,SaltLen,DataIn_ptr,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA224_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA224_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER21)

/*!
@brief CRYS_RSA_PSS_SHA256_Verify implements the PKCS1v21 Verify algorithm as defined in PKCS#1 v2.1, but without operating the HASH function -
it assumes the DataIn_ptr has already been hashed using SHA256.

*/

#define CRYS_RSA_PSS_SHA256_Verify(UserContext_ptr,UserPubKey_ptr,MGF,SaltLen,DataIn_ptr,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA256_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA256_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA384_Verify implements the PKCS1v21 Verify algorithm as defined in PKCS#1 v2.1, but without operating the HASH function -
it assumes the DataIn_ptr has already been hashed using SHA384.

*/

#define CRYS_RSA_PSS_SHA384_Verify(UserContext_ptr,UserPubKey_ptr,MGF,SaltLen,DataIn_ptr,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA384_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA384_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER21)


/*!
@brief CRYS_RSA_PSS_SHA512_Verify implements the PKCS1v21 Verify algorithm as defined in PKCS#1 v2.1, but without operating the HASH function -
it assumes the DataIn_ptr has already been hashed using SHA512.
*/

#define CRYS_RSA_PSS_SHA512_Verify(UserContext_ptr,UserPubKey_ptr,MGF,SaltLen,DataIn_ptr,Sig_ptr)\
		SaSi_RsaVerify(UserContext_ptr,UserPubKey_ptr,CRYS_RSA_After_SHA512_mode,MGF,SaltLen,DataIn_ptr,CRYS_HASH_SHA512_DIGEST_SIZE_IN_BYTES,Sig_ptr,CRYS_PKCS1_VER21)

/**********************************************************************************************************/


#ifdef __cplusplus
}
#endif

#endif
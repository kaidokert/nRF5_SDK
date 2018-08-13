
/* This file was automatically generated by nrfutil on 2016-08-31 (YY-MM-DD) at 22:37:19 */

#include "stdint.h"
#include "compiler_abstraction.h"

/* This file was generated with a throwaway private key, that is only inteded for a debug version of the DFU project.
  Please see https://github.com/NordicSemiconductor/pc-nrfutil/blob/master/README.md to generate a valid public key. */

#ifdef NRF_DFU_DEBUG_VERSION

/** @brief Public key used to verify DFU images */
__ALIGN(4) const uint8_t pk[64] =
{
    0x31, 0x91, 0x5e, 0x22, 0x2b, 0xe9, 0xc6, 0x24, 0x98, 0x48, 0x71, 0x66, 0x47, 0xbd, 0xb4, 0x32, 0x3f, 0xf6, 0xdf, 0x3b, 0x27, 0x0a, 0x87, 0x49, 0x7e, 0x17, 0xf4, 0x68, 0x43, 0x43, 0xfc, 0x21,
    0x69, 0x88, 0x2b, 0xbb, 0x78, 0xd2, 0xb2, 0xee, 0xc5, 0x0a, 0x5d, 0x25, 0x73, 0xfd, 0xf5, 0xb0, 0x84, 0x38, 0x95, 0x97, 0x59, 0x16, 0xde, 0x8b, 0x28, 0x57, 0x52, 0xc6, 0xc6, 0x98, 0xcb, 0x8a
};

#else
#error "Debug public key not valid for production. Please see https://github.com/NordicSemiconductor/pc-nrfutil/blob/master/README.md to generate it"
#endif

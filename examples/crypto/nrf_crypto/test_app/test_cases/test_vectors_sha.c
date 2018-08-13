/**
 * Copyright (c) 2018 - 2018, Nordic Semiconductor ASA
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

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stddef.h>
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_error.h"
#include "app_util.h"
#include "nrf_section.h"
#include "nrf_crypto.h"
#include "common_test.h"

/**@brief SHA test vectors can be found on NIST web pages.
 *
 * https://csrc.nist.gov/Projects/Cryptographic-Algorithm-Validation-Program/Secure-Hashing
 */

#if NRF_MODULE_ENABLED(NRF_CRYPTO_HASH)

/*lint -save -e91 */

const char flash_data[4096] = { "1234567890" };

#if NRF_MODULE_ENABLED(NRF_CRYPTO_HASH_SHA256)

// SHA256 - Based on NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha256_invalid) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha256_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_FAIL,
    .p_test_vector_name = "SHA256 invalid hash",
    .p_input            = "6a86b737eaea8ee976a0a24da63e7ed7eefad18a101c1211e2b3650c5187c2a8a650547208251f6d4237e661c7bf4c77f335390394c37fa1a9f9be836ac28509",
    .p_expected_output  = "42e61e174fbb3897d6dd6cef3dd2802fe67b331953b06114a65c772859dfc1aa"
};

// SHA256 - NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha256_0) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha256_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .p_test_vector_name = "SHA256 message_len=0",
    .p_input            = "",
    .p_expected_output  = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
};

// SHA256 - NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha256_4) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha256_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .p_test_vector_name = "SHA256 message_len=4",
    .p_input            = "c98c8e55",
    .p_expected_output  = "7abc22c0ae5af26ce93dbb94433a0e0b2e119d014f8e7f65bd56c61ccccd9504"
};

// SHA256 - NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha256_64) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha256_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .p_test_vector_name = "SHA256 message_len=64",
    .p_input            = "5a86b737eaea8ee976a0a24da63e7ed7eefad18a101c1211e2b3650c5187c2a8a650547208251f6d4237e661c7bf4c77f335390394c37fa1a9f9be836ac28509",
    .p_expected_output  = "42e61e174fbb3897d6dd6cef3dd2802fe67b331953b06114a65c772859dfc1aa"
};

// SHA256 - NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha256_361) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha256_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .p_test_vector_name = "SHA256 message_len=361",
    .p_input            = "82829690aa3733c62b90d3297886952fc1dc473d67bb7d6bb299e088c65fc95ed3ca0f368d111d9fdcc9476cd4065efce7c481be598537f3f53bbbb6ff67973a69837454499e31398b463288e3aafb8b0600fdba1a25af806b83e1425f384e9eac7570f0c823981ba2cd3d868fba94648759623991e30f997c3bfb33d019150f0467a914f1eb79cd8727106dbf7d5310d0975943a6067cc79029b09239511417d922c7c7ac3dfdd8a41c52455b3c5e164b8289e141d820910f17a9668129743d936f7312e1604bc35f73ab164a3fddfe5fe19b1a4a9f237f61cb8eb792e95d099a1455fb789d8d1622f6c5e976cef951737e36f7a9a4ad19ee0d068e53d9f60457d9148d5a3ce85a546b45c5c631d995f11f037e472fe4e81fa7b9f2ac4068b5308858cd6d8586165c9bd6b322afa755408da9b90a87f3735a5f50eb8568daa58ee7cbc59abf8fd2a44e1eba72928816c890d1b0dbf6004208ff7381c697755adac0137cca342b1693",
    .p_expected_output  = "5f4e16a72d6c9857da0ba009ccacd4f26d7f6bf6c1b78a2ed35e68fcb15b8e40"
};

// SHA256 - NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha256_955) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha256_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .p_test_vector_name = "SHA256 message_len=955",
    .p_input            = "8390cf0be07661cc7669aac54ce09a37733a629d45f5d983ef201f9b2d13800e555d9b1097fec3b783d7a50dcb5e2b644b96a1e9463f177cf34906bf388f366db5c2deee04a30e283f764a97c3b377a034fefc22c259214faa99babaff160ab0aaa7e2ccb0ce09c6b32fe08cbc474694375aba703fadbfa31cf685b30a11c57f3cf4edd321e57d3ae6ebb1133c8260e75b9224fa47a2bb205249add2e2e62f817491482ae152322be0900355cdcc8d42a98f82e961a0dc6f537b7b410eff105f59673bfb787bf042aa071f7af68d944d27371c64160fe9382772372516c230c1f45c0d6b6cca7f274b394da9402d3eafdf733994ec58ab22d71829a98399574d4b5908a447a5a681cb0dd50a31145311d92c22a16de1ead66a5499f2dceb4cae694772ce90762ef8336afec653aa9b1a1c4820b221136dfce80dce2ba920d88a530c9410d0a4e0358a3a11052e58dd73b0b179ef8f56fe3b5a2d117a73a0c38a1392b6938e9782e0d86456ee4884e3c39d4d75813f13633bc79baa07c0d2d555afbf207f52b7dca126d015aa2b9873b3eb065e90b9b065a5373fe1fb1b20d594327d19fba56cb81e7b6696605ffa56eba3c27a438697cc21b201fd7e09f18deea1b3ea2f0d1edc02df0e20396a145412cd6b13c32d2e605641c948b714aec30c0649dc44143511f35ab0fd5dd64c34d06fe86f3836dfe9edeb7f08cfc3bd40956826356242191f99f53473f32b0cc0cf9321d6c92a112e8db90b86ee9e87cc32d0343db01e32ce9eb782cb24efbbbeb440fe929e8f2bf8dfb1550a3a2e742e8b455a3e5730e9e6a7a9824d17acc0f72a7f67eae0f0970f8bde46dcdefaed3047cf807e7f00a42e5fd11d40f5e98533d7574425b7d2bc3b3845c443008b58980e768e464e17cc6f6b3939eee52f713963d07d8c4abf02448ef0b889c9671e2f8a436ddeeffcca7176e9bf9d1005ecd377f2fa67c23ed1f137e60bf46018a8bd613d038e883704fc26e798969df35ec7bbc6a4fe46d8910bd82fa3cded265d0a3b6d399e4251e4d8233daa21b5812fded6536198ff13aa5a1cd46a5b9a17a4ddc1d9f85544d1d1cc16f3df858038c8e071a11a7e157a85a6a8dc47e88d75e7009a8b26fdb73f33a2a70f1e0c259f8f9533b9b8f9af9288b7274f21baeec78d396f8bacdcc22471207d9b4efccd3fedc5c5a2214ff5e51c553f35e21ae696fe51e8df733a8e06f50f419e599e9f9e4b37ce643fc810faaa47989771509d69a110ac916261427026369a21263ac4460fb4f708f8ae28599856db7cb6a43ac8e03d64a9609807e76c5f312b9d1863bfa304e8953647648b4f4ab0ed995e",
    .p_expected_output  = "4109cdbec3240ad74cc6c37f39300f70fede16e21efc77f7865998714aad0b5e"
};

// SHA256 - NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha256_1945) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha256_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .p_test_vector_name = "SHA256 message_len=1945",
    .p_input            = "eeb1a4c660be97e365dfe42a4d3400c6e661caaca02accd2ef41be9bf15b4c9651891a696bc60408b0ccaa2b4c2d2cfe079e321a699630b42218e814a9cc30492255f51c85df8042fdf7f8d68ea02806fba3830ce72665603a809c2bc64c27ff2bbc3dc6f73192f91208d5135ab67d448a17c5696003f53cff23e4c89202bb213267fb510ae3c295b8a64acaf796b2227ba3011b1d5468b238a6c7d35317731500fe37a4031d987eb7795de3ae6a4f0698ee3e0966424428afb44e3552b3d7445d28f7a72d099d1dd72a1846c757dd5aa7a1841b83f513082af37fd4d7fc7016108d4542cfcc58d8e06183db8a87e3857163db39bb945cb9720b6499291dc5f4e3d6285d3091511899c5a58b3e22e9efbedd4c4b5748a8a34fa5056c923c5f449caba9e0997e1146cbff863c2d4f770056b6de399f387e2e886968365882c46f04b3ceb352bb1fc83eb72ed79d37162000979aebdb8d66c2e7fe97ddc4167edee397a1bfa3710308ba94a645d7024db78628864a536ee8c7320d9a4b1e2015f801ff2aead4c8466c073ef56c23d7a52dae10ad3c4f048da5323d7766aeca0f242591701d2ce76f5eec5e2336c8dea5ea41f814aa1676dcc4af373818bb3af6cc19f87b41f4f70645339c398a1041d5560687c57df1ed5e8d71a2e5488f985157a3da533c751f9489a29f3e4f4125bddac766c79b289199663f2784de700da92d8ce001f8f488a09102103a6fa4b4e6dc4a3c22ee038917b8e26e1fc1a7c185b69bb18c5bbc59b2c71a9635d18116d7c658b2de5dc9fe60ec231ebddb7cdb6d599af6fc4f14bb5292b4da385d207318feb97004cfc417fa68c8df67133683e9814f5659bb43d6095a96834afbc8f232ee351d9c2e3afd6f96995b24511fe38293847aac8692d15e88893a7493c3bbacfc9461ac6174d747dd6037fc7d7d20bff8ff09fd9a49d5da8255a7bd0d57f70e929de63e50bace08a4e31ef7809965291889ac52deb00903b1c2712d51cdcee117195159e3540a3c55ebb61e40bbd8465be90bb53a0e96647d9841cc486d67abf3d14d060289b26a5740a778a62ba1a12ae9cd2d96ada3824f9ebea3d87eebf78d8a804c95a2ef1b12aa9a0d9a30e9bfeb4f9ac2dad359e78d9d91b9ea4a814a4f0f923384e7e8d6eef137e60513d82a08e41c7defc9e01aa15e61166717522ea0272cc3b7a0c62353dc250acd1d9569e770f865bbd75fa3f1a6d7c3352e862ae899f6051615b08aa9350d81dc934904f2bbd9832744fe0be7409bc73ed744c7902e97008a8ecf9458c2965418c01b838f8c65dd1b5ae7d8e9f3542a6859b48bfeaeb8bcf9524ac8c84c698a6beb346f28ac447e805f3f956186aaf59dfeff009be100424daa4aaf619a2d2bbc5bbb5024e41f6b3c9c31c7b6c2472fc40c4daecf8e18996cdef7cf8c768b40f259d9acebfa9ead3959e2f8506fd0e0c5ccc51c037fa7c9403678b3afa62bd0f72db60de5b6684d5dde7daf9755f010888690d29d7a56dbaff9f6e034f3b4e3b21f79fa7ae2265392722875f33b4dc8f482d5580748cdd6a37198e08125cf810b774bfc12447fc5bf5e0bd1ccea8f0ff307bd37a7b1b3c203e48739000423b3ea7c539a15a61cadcceb504b8a2b5fee6d5e70f6e77cb0a8b79bea76175759803777ba5cebcea412a05e1c6b95c4656c48d0151d2e736e8fa6deea1c30e818f1dab0a7cafc84c0fd25029aba557d48916da3d534e35c927fbaf5afb5b27d090dbc6f436db0921875421eefbf3320b065c41fd7c47000c780da2760c905dfd3dcc3fcb5cc70bf5382dff94602957347f1358e44543c27b39beebd26de91d61f66d89e266fa2d21a2ce5dcc50ce440b23ca936436daf98fed7dfff287ebd2a95b4e49fbedfb094147c3a0f9464894d9c4e0661fd96311d513d93358f30f3a2dccdcd45a4a300cdea79c7dadc92ea62ab30365599572a7c54d3f3a7827d9b079db97dd90143fc44432c7485c51f714987e91f5a4038027eaea3e79d2aeb1b217f81daa2fc480ac3c89b2a57769285c9d981abba1ac221eb07b5585eae04dcb82b2cceeabe39941021d0cf9918738da94901c1bb4e7cf08b090f2c333750469448c240f76f9e01f4f5d34c94d24bf3b27e7048a705efd5265abb4d64ed56c27c7f4c17133500b937ecaa8a8dcda11eac21d62ac466a13983a2c1a139f79eb63a78d03d843be524a1af5f70cf30fd765fd93c4e5b9a1c856b8a2712f97eb08b94da599992a7d8aafae6fae5a124e763924fa99cb3c8e81fa6b9f787eea915aa534eec1387a25eb3093981d34ad1e84d0f2b25fc16198b71fcd939e75ea154793f7b9393a95301a7974efe21135e879c9c14b856cab58fe1358ff31c928df5621f0a550142e348ee6cd078b744f44db802b26b9218c37cd918852f0dd29680ccbca23b459879bbf05065f87d25bac10a08ae4598486bd8c06e63f4a266e47e1fdfec4b48f33ee3150bb5855bfdd96bf878b04e50a2d72dfeffd04bc3959e77c24e8f8ff09d5a47c6646927391678d3eb195f8fa36e2c02fb93753a58a8edf11fd2340f26ddf470692529e6ffb6c0824cb2640f77f395e01ef2facc49e7f8769d3283d2d3fa34e468149ccb9526d9ff810c66d7b67a384ed1e306067e9ae88da43823e0dd3d432d29fa6bdde3aeead2f4ef0eed464b3dd47c3041f2e009e4bf9caabd412eee49d3169e3e25d1951b840b22045b11aecdfa859f5597557c1592ed51",
    .p_expected_output  = "07ddd5dafcf04956cc36c1ff290f07c1c0e5832cc8dd9aea502da677ea04fe64"
};

// SHA256 - NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha256_4123) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha256_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .p_test_vector_name = "SHA256 message_len=4123",
    .p_input            = "0f5452e6b51540cf219998590995cd7f8785fa40b4f217fc79f07322a2ec5e0834a4261a0177463779dfd958c33c55730dd3759f20167778372688c511967d584572c336d67f99f807c57c71704be39152222d8928a4d8307efef3a606ecd637e9c410825bb6a1da72526aec384ae1a2ff7a0948f425a2eef7829c0daa77d26dc8a4f545b9a3c6a5638e891142c2b66ebbe3f123ad213c784ab96c4125bed9c18b195ac917cf71208182c227b73bcabd2f66cd617b1e10961eab498c9e4954fcda2b27549ec008147535fe78be3b8557020a854b85a685121b611c343da1a9e65ce3442f7500f549e6af234a804c4f04ddd80229f44003b3eae2ce822c4d4247ba489aa2c6179e877df91ae625f5908b68d62a43ef75f240333645be90d585e79c630ff4b68b6d96e21acc94d4bfb0b54a0ee6e09fcbbb829d666b3094c2dc8ea83a8c6f6fe6c83dbc1a209cb530174a2c881f492cccc441d17927205d9bae0389d8fa5919af1945b302fd45f1d22d12b54bbbc7bd007644777760d516e8630fe5423ffbdb6fc77770d94dd8b02d5bd48e5fa4a07aee395536690098e532637a6582459ddead3a999ba7f79d19c7075a5eccc01c8c1e763ab656eeb1f2ff150cb09ef2874af1da73dc75e3dc552a9b6ace9af9851b1893bca046126866dae38c6fa1300046c40fcfd94af9dd8bde7dcd86d235214e65faa39c415404694834c44990e651faac41733d2e21e7e469174b2d7c5e3a4e8c11b751509ccf22d3717ae775fcc38f33d828ae2943448855cfab6b9e5b16431542c0687ad20fba020077f057599c2de13cb6d444473a9e2a0fb7ea4214fd5489f48588c8de0d595d4a830d3fe724fb3dd5e5598615124f6e3e354f6f7139a96e8ecf5a40a811256db765e6348da522cf0c7de2f89514c2abc3ee452e5a116b4f7a6686ed196349b9b0e7223e3365ca1f47451aa0b087206808aa7286b7ccc2b11f12b3d4174aebca9bcf6965c1ad19b6ef06a6884cb5902e74307e7f70b3d51ee59b89ff8b103426e1e665b220c53a1b6d8831b852e43b846f4a12216d0ecd1d34c8b2755efb4b57ebf4bc2c36f553d627936136ab5d48f261bed6759725d1377462d33e765458e520c116dcec858d7087efde0c3d68e000b2557182d43f0af20d319763bd628556e7141cc82bbc0f70f4635142f24c2b37cbd78c500da5a0d968fda3eb1a6ff834aab775fad9e4025ed6b962deb153501e120ccee82ba0ba71eb8ea2de74c1d906d070ca7adf438dc394b7b8ea61c3783ef0bce05114768044ffac3a44b5a15155c108c34e2621d9259826fc6dece5ca1dceae6993b26f1bd90d1e1326c45788a8e447078095c80d0f49cdd57039016f4512ab12b7ebd5b3b87badd68b892ba587a3f43f18137f52060f76ecfa305f8e3e267b83c4a9ee6f6ab2212b7cec65d07a65d9121c8a8dd09452e7e813b946508e70e663c2d30478761b42b900d54c330a93bc2996e13bae407ae973c3bc00ddbf5ab45aba515df6641dd7291f2c29f3be93662b8d00d11592ef44321321d35c594aac12b30b4110bd1faa22e1d9443b1fce9fc10acf972c131ac0cf0ad008f5e2aa9730b5e8faee078b814d4fc4e531b4ac2e931435d41c4a6125f2b1b2e6d2e4e13d5fc8d3cfb9cdc8255270d654fd0596dd48b31dd20cc02d3a420eadb718e6576645f5b10799943e5ed84df5d8c89af27289ef6cd725fbe7c8682caac1f27174da8a436bebb5e655f387ec0abbbafc29b6fdd10b2c8e85f5970b10924e860ca060d7bbe9c3364a75ae0957fe43fab2a4714d60e21970e6c16fd4c44ba4fc3f43c2d46313d7434906550396b7b9b144ca6b20a5d9e5f3a4b1186b4fbf0b7d92c5c62845d16e056a70b120af1f65063b026b1fa6d9da3e492f5977b9d4cd318e8e357b690cd1a4351b8a05ac1d8e221db63bf26dc83e7a5da2fca10a74313fba06d677d5aa49473270a85d94987d2c754da14002905ace6672c7904b867ecf9e9673c293951c16ead5d2ce707a7b4dc82f66b16b177663ee0683ec84f2fd0bc3a4d204abb3923ae4b3d20047aaceada0c352eeb247da617cc8f85fbba0f619b09abce623eef5dba8736e9d2110be7384732c9fdf06cdef991fed8ffa78b021eddef90f052d8b20bf7b6f4a079495c8fda7be6cf83e9835cb732b244861754c03da512959589e32b0359cb1ff1e99d392c5cefb07d6845c9d2d7bc7ae468bc179f48cd9255674390307bf7a149614bdcb3625f713b6d78c94b3a320320c3ba9d79671c97311555c415b9e4d4be44cad30628b0625c6d9ec3a6e6bd6df9ccd2ca627caa14a708bc3f19803d0aef08acc4ab1c7d044eed4a516c69d92bade89716d0f5d08b35b5d979b26b4ae44a21541a08ca3fe78160edeb024fffbcdbab7a1b4b5f3a7b4ba1200c76d798d15e33735ba59e538c926d0c091ee5bba1f199ee3048353265875f325fed51c162a9936d02181562540066273408e7776b8e18760e3e0472ca475482fc7c663f08aae5b395c6dbe6ee49e0c1e456a1bd8a1fcba40dc349561a2a05945aba818c33d08ee99f384e5bbbed616ea29ec1187e1507faa74e8066f59df6d9031e301394c9137176f2d92b3d497c7fe737a202c80c71ec6356262fbd11bcd38e1dfe7f8be2f7ddc57d28ffe30c76983ab7e0f6f8748debda60b71b0133ac264430491a89bcc0a1033daa245da5042a05a5fa7f7fdba09b74f4bfa332626923ce0bbc9f2ec4f24d98cad9430d8189b7e0785b06dea07e5dbb98bc72f12c585e93f6a557eb8a01462e8b32c663409bb443a58f2785616bb526b319e4ae001e593e87bfef307a722d1d2543490f60aec1b7b4034c14acfd244eda7482c97c0f86164548cf9e14c954fcff872552402742b53a540f0cd1a74d8c8538d7e3fec087c3a5fc73a4f77b7036907b05ec8db9c9b49efdcace8dfe736839f34e8e16c5b0cf202775b5810ce1627e9b452e97cac94e686d19da2067487a6f207118328393815a7630705ff23af910646da90cdec3db0d2e66c037763f3bab3cca23008ec282ab554e45d2cfef730c6309ec4b6a3bf313ce5c1131bfca1464c4c42edf4bb05b994129a687fa6168b9239458d1f1b41f12a9443dbd887bad2244f9ac4d4edf74aab65d22ee165332bd02878f3f09aec7705bd9b62974b65e6a39d52bc90cb2566641534b838817696eac6deff1169e74b362671b04191cb0b31fd11dd109db89426e9670d6e43085646db20b86ad05bf523986ccebca113c836387f303dabd75d5aaa143569f311f34e2fe527e41670fd36da34c3f2c366a61a1645bcfd3cab486620e23913d9b8f36889d65265854decd6b67297c93fec2c455f0b8a39995cddb3137a20523d26e0feb29a43d6631b4a6af2ce532b5ccce220db78a0da0b11a4a94b83f2106683417773da0220f9019d5c57effeff632f5011523508c6d8f226b08fa6b7349df69f3b923e95298f286f13ad7ea02d9c3cff818beacae74828ea31a98b78a62aa781b2d76d06db6db847f7bc22429c4f1c76d94f3eec23a5db78925fd93d4e55bf6f440c105d1ddad8ae704b84ea36c4f63d7f66d978643532593d7a380c146666f159f7cea0d620b02be6244ba3e243f3dddd9864759142561498c252efe0a4c390596250d9f0856946c10d207288133bdd59ad87ec92126f310dfecced9a58ffd3ac133e0f52522b8769cfab61117df5c55d6ce9e44feda43903f8510e2aca4143bad23f4be4ce1d774732937763c94a1e509e3365af1d1db3e276875b7842b266eb69fb948e43689dc1fd81bc673f616e9a0b0c789de90327114116db6c087ac7a89e1bf238f7338140fa1c3905266340a37b1d23fe987e1dfa21a797ef63c0eb573b476dca33a7ac2def0df526c87719d2b60e70bb73b51e04dde295e79dac5c6206260e2c3feca5eea5fbf8b06bc68391838667bcc2d1b1973f6edf3efc68a12fc861dc476329f4ede48f4b8d58770548ac2d0fe9cdf95f1b0df47ddac9194228489fdf01e78722907371f5a3d7b3285df7ac702adb56aff8101b75a54beac7b350892043122db6411c48fedc2fa272392dab926835102997108cd185cc01b93aa6c7a6f62e433867a5bc6f1eaa6b6d4416d17e89244e555ed5ee99649286a02413007a0081f33169d7774f538e37a1e679c73b77ee38bcb626ead329e6a202d95fdca24b546328b17a1ea662242d95881f35d118dbf7e508cc2889bc107c69c1520528bdeebba5a6565c7d33b476d190d1c1495635b358ba904fc205583e5c44b4201340992430b032d6dbae8639dd685516aa1842939e36380787eb060d64ca4cd86cbb9bc65237d837c8bbe19f427673dafc454cc03ee28cfadf59611408bbe3d23a153dc892a30e254c420fd08724f5b647c79962c02856ced234b278d07f41b98538c752795d9d48702b56f334d9a151948571a0ad6f5c2b68654164447e2e33560b818e8ecb4d4a3b5eff30d1fc4154ea671ea28c1e67baaad456feed2072e8b476b2a25956e5d0b6c351b0e7f79b665255e791e59f3f229f69396e52ced482a761a4b662662f85e743969bfd317830d33713954159ac0c4f0d31ddfbee1ea637b49df33264f10ed8c414199c129f5975f5ebd526b47620c3a6887371ea16fe6d57e68050b6f416912f15504b02da8a4078b77a1f186405021d84573b2885325033c78644c60043186ddf6b9269ef6b3da6bfabb1ed4064145b6eb2e11232eae82e872d97fbdd3d7765ba90f9afa7a373684a91669bd0e402478eabec0ee7cd3e31709cd0bc52adb6fef0e8093ccadbeba7a153c58add2ed3c82b6be3866a835925c8fc7773283bdb22c89a497920baab490d1b56232ee98fc88e194ee184b542f0d8741487278ef0b889ce42cc70e9bd37d40ea2cc8dbe3f2e00deb687fd0bff7ce82d3060174ffca77cae7a9e840f285a3e5630eec055eae2c7e2a1e09d2c9aaf404f5266c02508d9e95f7b5822d5f599951b88f2905598cb2b4c9a542cc11a7327010301eab91b35180ccd6013e32bdb1f84333ec56751d37644264b717188afe76bca995cb33da350dbf6201fe0d20a26bab83c27321ee1eef4cf2d35e5eb4bc6b62f96dfba760bdaf480fe0d75f30df0e59f537d5f06dedd821c6240c44b2e0d0aba603b76cf55fe80f364a74995ccc52b71ea919512b0891695525ab7b142038ef45f38904f6a04a7d5b9b305c02fefb7b56b297d49403bd9c3654b66236ef26b64fb9db0ff303490b065fa507c1eb5aff33d0ebeb3763af22d04da78ac9a20c8939d347de590d6640bd044d3d2815e3cb4c80801583ad08a5c95d19651aed6ce07abc3a00b72314a6f625935c94033857e74dfee417543c9d682f6671c935ca54a8f13c079bf8e6b6383001f6a437cb3dca95a2c750ddcd625311294142ffa74e4afec86365d35ef6f9b0339bc7281ed53cf4264fcece3dad00cecc4416bf8635b75169a4a366efd1b12282ac7b6895c6d4e5f3ddff8a0fc60794ea0ac309d9c394858a3bd3181bdf050389b93f5dd27b18e7960251b5a655ce2fecf5c643344058f7b4a9735b55875bdfa332919c678a7f85874d63c5b3c4caec5fa59f0008648b44836e12c54f633c1389b90088a74d8f2c322fb43e9aab9456bc9acbd4d88891e840fa3fda4beb0c5b87ad0ac7145cbe584129a174dd72a0fb8e35cb261725035fa7fe390eed9762f4379f2ebc513083a61ebbea2cfea277474f171b6866d2661712cabcd796f0d69a140fcafcc05185723566ccbb60c38dc669af4b302a1910ab0be029c8fa7fbd99a76f9dfd04482a692faae7a",
    .p_expected_output  = "f98918c63e3a9238e78dbd5bebe4e47eaeec0ae1627387dcd2a5ae4725f7e47c"
};

NRF_SECTION_ITEM_REGISTER(test_vector_hash_long_data, test_vector_hash_t test_vector_sha256_long) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha256_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .mode               = NO_MODE,
    .chunk_length       = 4096,
    .update_iterations  = 256,
    .p_test_vector_name = "SHA256 message_len=1048576",
    .p_input            = flash_data,
    .p_expected_output  = "7b09661bdd3dc086e9303102e0c1da76eef506e403419f722947e377a6edec00"
};

NRF_SECTION_ITEM_REGISTER(test_vector_hash_long_data, test_vector_hash_t test_vector_sha256_long_flash) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha256_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .mode               = DO_MEMCPY,
    .chunk_length       = 4096,
    .update_iterations  = 256,
    .p_test_vector_name = "SHA256 flash memcpy message_len=1048576",
    .p_input            = flash_data,
    .p_expected_output  = "7b09661bdd3dc086e9303102e0c1da76eef506e403419f722947e377a6edec00"
};
#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_HASH_SHA256)


#if NRF_MODULE_ENABLED(NRF_CRYPTO_HASH_SHA512)

// SHA512 - Based on NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha512_invalid) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha512_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_FAIL,
    .p_test_vector_name = "SHA512 invalid hash",
    .p_input            = "d1ca70ae1279ba0b918157558b4920d6b7fba8a06be515170f202fafd36fb7f79d69fad745dba6150568db1e2b728504113eeac34f527fc82f2200b462ecbf5d",
    .p_expected_output  = "046e46623912b3932b8d662ab42583423843206301b58bf20ab6d76fd47f1cbbcf421df536ecd7e56db5354e7e0f98822d2129c197f6f0f222b8ec5231f3967d"
};

// SHA512 - NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha512_0) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha512_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .p_test_vector_name = "SHA512 message_len=0",
    .p_input            = "",
    .p_expected_output  = "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e"
};

// SHA512 - NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha512_4) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha512_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .p_test_vector_name = "SHA512 message_len=4",
    .p_input            = "a801e94b",
    .p_expected_output  = "dadb1b5a27f9fece8d86adb2a51879beb1787ff28f4e8ce162cad7fee0f942efcabbf738bc6f797fc7cc79a3a75048cd4c82ca0757a324695bfb19a557e56e2f"
};

// SHA512 - NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha512_64) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha512_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .p_test_vector_name = "SHA512 message_len=64",
    .p_input            = "c1ca70ae1279ba0b918157558b4920d6b7fba8a06be515170f202fafd36fb7f79d69fad745dba6150568db1e2b728504113eeac34f527fc82f2200b462ecbf5d",
    .p_expected_output  = "046e46623912b3932b8d662ab42583423843206301b58bf20ab6d76fd47f1cbbcf421df536ecd7e56db5354e7e0f98822d2129c197f6f0f222b8ec5231f3967d"
};

// SHA512 - NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha512_955) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha512_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .p_test_vector_name = "SHA512 message_len=955",
    .p_input            = "990d1ae71a62d7bda9bfdaa1762a68d296eee72a4cd946f287a898fbabc002ea941fd8d4d991030b4d27a637cce501a834bb95eab1b7889a3e784c7968e67cbf552006b206b68f76d9191327524fcc251aeb56af483d10b4e0c6c5e599ee8c0fe4faeca8293844a8547c6a9a90d093f2526873a19ad4a5e776794c68c742fb834793d2dfcb7fea46c63af4b70fd11cb6e41834e72ee40edb067b292a794990c288d5007e73f349fb383af6a756b8301ad6e5e0aa8cd614399bb3a452376b1575afa6bdaeaafc286cb064bb91edef97c632b6c1113d107fa93a0905098a105043c2f05397f702514439a08a9e5ddc196100721d45c8fc17d2ed659376f8a00bd5cb9a0860e26d8a29d8d6aaf52de97e9346033d6db501a35dbbaf97c20b830cd2d18c2532f3a59cc497ee64c0e57d8d060e5069b28d86edf1adcf59144b221ce3ddaef134b3124fbc7dd000240eff0f5f5f41e83cd7f5bb37c9ae21953fe302b0f6e8b68fa91c6ab99265c64b2fd9cd4942be04321bb5d6d71932376c6f2f88e02422ba6a5e2cb765df93fd5dd0728c6abdaf03bce22e0678a544e2c3636f741b6f4447ee58a8fc656b43ef817932176adbfc2e04b2c812c273cd6cbfa4098f0be036a34221fa02643f5ee2e0b38135f2a18ecd2f16ebc45f8eb31b8ab967a1567ee016904188910861ca1fa205c7adaa194b286893ffe2f4fbe0384c2aef72a4522aeafd3ebc71f9db71eeeef86c48394a1c86d5b36c352cc33a0a2c800bc99e62fd65b3a2fd69e0b53996ec13d8ce483ce9319efd9a85acefabdb5342226febb83fd1daf4b24265f50c61c6de74077ef89b6fecf9f29a1f871af1e9f89b2d345cda7499bd45c42fa5d195a1e1a6ba84851889e730da3b2b916e96152ae0c92154b49719841db7e7cc707ba8a5d7b101eb4ac7b629bb327817910fff61580b59aab78182d1a2e33473d05b00b170b29e331870826cfe45af206aa7d0246bbd8566ca7cfb2d3c10bfa1db7dd48dd786036469ce7282093d78b5e1a5b0fc81a54c8ed4ceac1e5305305e78284ac276f5d7862727aff246e17addde50c670028d572cbfc0be2e4f8b2eb28fa68ad7b4c6c2a239c460441bfb5ea049f23b08563b4e47729a59e5986a61a6093dbd54f8c36ebe87edae01f251cb060ad1364ce677d7e8d5a4a4ca966a7241cc360bc2acb280e5f9e9c1b032ad6a180a35e0c5180b9d16d026c865b252098cc1d99ba7375ca31c7702c0d943d5e3dd2f6861fa55bd46d94b67ed3e52eccd8dd06d968e01897d6de97ed3058d91dd",
    .p_expected_output  = "8e4bc6f8b8c60fe4d68c61d9b159c8693c3151c46749af58da228442d927f23359bd6ccd6c2ec8fa3f00a86cecbfa728e1ad60b821ed22fcd309ba91a4138bc9"
};

// SHA512 - NIST CAVS 11.0
NRF_SECTION_ITEM_REGISTER(test_vector_hash_data, test_vector_hash_t test_vector_sha512_4088) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha512_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .p_test_vector_name = "SHA512 message_len=4088",
    .p_input            = "c8e2e36403ad4ff9f60010cb877a57139ac1463a8522059cc377128dec4ed899e447841053be14c356aab00875c53e04d4ee3129adcba1fdfdb2a11d7ecacd82d66d22040ed1131c45e8d8eea6840a8797bf6d63339a0d32fbe48cdbc85ebac2051c66471a2e748f2b80308603ffe2244bfda3f000d76ec324d57acfb351c7dfd81cf7e0611d60a1713b5fd7747eef6458707ad9fbcaef39df4c140025ed1e63b9347fdacae6ffdc7de10ee9e24858ce27e09b250bbab51b961302760778e4d60f2ea33a3cd078c7b83ae4c533a646eb1e15addc1af1ebf1b0f0eb39423b44be41d00d0aa124f4ea8a0d8a7251e0e141a6d659070fb5b74495ac7752bc7e64a5b9e36552e02b9ace5c24a7f8223e505a28ed47acd14f419aac0f4fc85f896c12de2e5218e12a93fa9445e4609007bcbe0a201ed64a07b27e5fe01ba312a3858e187b7d668c6c06f69c39e9b182854cf3b638868a6124327515e982ebbc15d7a0cf908e43c9381c4bdac85df3dffe298392fd29d2fef0e80937f02da9472889d06b362cb880d5fc80b8b9e92f91bb7af60836acb509b1fdc12bbec4e59a21c3a65435ffcb998cd01d9cd6346c7f0468d27eadba3c6bb099255a1beea59d4bafabf355b086fca5bdabf0e5e7b291211ba15e28f96d0a35e2be2cce53f338ed7266ae5ee7f19168edb11bafa909af59baea0f701152cf8703130aa19cd6534e375fee174b13411c88b785fc237ac1f56e36f94dabf3a2f022ad5a5a7157d6b7241f1c4985f4f20bb5459694fc0caf3d5e0c84866f566cb6681285c2797ca970612d9ebc3d9c8d7b9de4b63eddc86179b3f418e504851322fcccf4a15d4fb5c11711de381a14fbb5681b4dc46eb4c0f194761d301388817c06630ebfc5d8e0f26e544285c46322013d73c3ec56dbb2ed2a1bfb3043659c0cb05d3ae3571e134a8d7d346ae491eca64473807f3e4220b49c6a1aad3d264e192044e2d7be2937129d141bb122a740eea7a3ec44cdf3f38f13ece36fa8d37eed7e9f6d61a0013293c5a25f2025ac051f8b8b7005acf511c6b727bc3d2d7214cef3f7434aa6afee122eae678096a825821ab47288825064a1afa50ee0740df705a7d3cc59773a51daffc09d981ca3875f7ca55c96f80cd36724ee422124ab11dac1bb6f58bcaa45326160683260a613fed9e694f7b63245623d88bec6e55549946937970d1c07b1617c17301409b8b1a65800847363caa4d823fdec976112877dc9d0a942405a7cb0776c5e07c0e249a1217a92d2a7dad712fdd5335e3deab3db060d0ebdcfab90677be858d32d2bc3355ddc28db2c6cc658f496fae124e5b6f74b772e477200d4ceaf118740f79b07ab34afad57978759f230caabe9bc0c7619be9471a7d163302c3c725316c73afe4bcd79890f93347827d8f8ad3ead66dc8987ef40a793db8ccb4990251c44118e5c51c523c8c67a0b4015a968a8a0fbd08ecf0d010d6070d0f1fff5631b1727a028e718e54dd861fa850e6444ef3dd43b71be781ea2e22be5e7862877dce7841df5b8fc366572f12d3eecb1a9da2bf8037b7bb7fd2ebe13b1f505b1c7245d31eb0cecf87ed73c338cb3d618ff33136f12f12f5208799f311d62a419bdbe2135f4b5aa95266cdd2e002cf522aec09c424e1e01d1a54a2b8b11788de6bf71da981e371a5994ecfeea6ff070561e4a6f78a1491abd3e6a0a2c767de5a33704306353dc65ce311f4670c348703db7983319f2b9a19e3aa2e51932bad7d58c40cd9d7aeab37c65cc5ec7e27c1d5de274912e28b7bffa01b8645b2f77880626ed564e7baa2bea99bdedf7b6d49e4105a431be2d8b9c5bfb742efb53fc23bd6dd3767e3e64f6a033b89c0925971c6e8af1bad1e87d5f4890a0ec018890ce83c9b9d336aa603b269d861304190fbe6ed723d56f41d5314a28024573b57cb1dfa268157da9e523053deff9f07982adc7560229a120da39e82b64e25bc209f65960a9e55c233cd6c47dbaf6d62d3910046d555f6e6dd5a0aa018c6ac0967cc2796b42ebdafeae7bebc4b1b4bd1c7c10aa86e61edf100e8d18124286ab1b2040c82bfbceff23813b02799ad8ad3093d543087b0ffbf2cd29bbc650de23383c95cd099e36d37afd3d92063e0dae50c586575bddd9caf95a9b1a867d1930d517ec106bf1cd5feb6caa22d265f9c9645b4c6ce7d425540efc0cbdb890e0dadbfa6b1ababe38aa5f14a93b45d64405559d4e0c13289ba21afda42dc652da2a302d3a725fcb22bcbc3f6364c75b976b09d3b5be49a0e2bb03a38af1168bb027bdf882a0c0e0319eec33ff25c0ba9a016945a80bf105a3a7b337e791120209da6aa36b2d47c70d57d538a60698bcf4d15d3b5079711f856f1000e29620818e4920751ca05b475fef61988090b7294de3cefcd49232b6311a0448a487aacee77ec5b7be816327cf6f7799b44a86c94f3da2d15dde9c924eb0765555ec17b2bb8142b27859c93004defe856bbd6b64a0e9c30213e4187a853a4d711b4ecff5b25880ab73aff42aa744e0a2cc6fcfc1e8ef17d71d2c0c387ebe73e221333a5f750d66edd60b4cdd5faa043900ea1ba9d0558897a43ee192e047cff08d26c0b8aca8dbbfcaf53910d51752912eb6b5e4ff25fd8ccfa3005154da49e588acc9c7ff2fc96877f6238db193b2f47f59073a1f675dfcc7e2cf3d8181c907394fbd5514ac17310495721a9a260ca81b5d7773d5219230b383b81d104337a0c996042a9626ad629a5b8e8038d948f6294a6f56cb5d8370bc0e22baa8297bf65f09060e2ba6734360cfe08634b34e26d1a656aca92218040a0c75ddf2397e5124312bc97b33511b7f79cef636bc06803dfb943d16793933c405184c957d26fb4095dc222fd52f341ee1c197e5fd594c92d091d1bb68ce46137f75d03afd5c3bdabe7fe3ef94f5d466902230ea7d2dd1fbaeb43040fabf851e04f33089c009581a327ed262798b447f0d578aec456c589e1c67214c34f4380e1bfa3629ce139b297b3fb8318bd9cc90e0ca6d945bfc29a3a2126e872056a70a4df2a8c32f644c2f212c5c04d3c7b3c192e1a08ac9c78c33c81bdd9bc5cb1a3b20434ffeece2b353aaab8881573e433caa06ed7597b3c97617eb372d2b3cd8c81e56f3830b7717bea02602532124c226b0a01afecbaa279316ea43e85b922adacf915cf9970ac2988a049320396379aa2c17f0cc6f93efb24e80cb715cb35899ba5d51099582fa08f1ad0391a5e1b0eda7d237888a556afd451695733689aa2c67239b5b0fc908365c891a4d6f88af1aa93bb7d925dadd9a85126b94f2fb67bc5e4902960cc6344b5300a0fd9f3ebd57b8b93768470993b196de137c97f0d97028394e639561c56f5e7a5c483bed23cc5eb481dcf8cad36bfee055d42d5246714c594769b18205c9065f17d74d7c2aa322945bde4005e4ef4782fb44bd08f7e65213b55168113a82d2179951dcd317018cc28e1628a20f66f82bcb734dfa34f8c3ce5fc2c2f6adc14b0aaa5ff1da351025a4e22bb78a9cf89a428f0ae81045cf25f10e65c819a6aff7a012a99379cbf874a31ec6f6a3d3ccb4310db09332719203e68ae281636c74604298d6ca9820e102280c8eebd6fb0bce5f0e0e5848016ae2149be0f6ba49370e56068e9e1f7df25599722ca00c5edc713459cc3e3a3d7e4ce309072d0883208846227b18f62a53f75f19471d2b42682318b8914df06df7c8bb9b00303363595678b5433f056f2d70e3c988681cf0d76f73f1058e52d9fcdf041a73072431070056868e1c3594a8468c49968bc8b050daadcdd10849c9b617264f07b8c435550e465f05b56ce0eb03c1631b8e16cafbee2e149dc4bb844cfb89ff654dfab76909b2064f14939c1f2eecddbc77ed8501325f8e10c89253e71096f535cdadfe6b790144154193116b5074802350372a8a2ea602d31eb47eafe0b3f81e41c75384e49be1ff425284f8f0c114f821db01bd6b6c3a8ece0b4dcbf249cfc8b02ffedbd4e8a5b421ba40ed963b61e2f0c152c3701afce8de7d0764cec143dc22cd479ad05058dde6b28c73cb4a2e8ac7d165c4c516118958f4f6a1fd811c02a08975e6613bc1219721afb215564598adf381e7f3ca411a435760ab06f322e1304bd2ea0d11a9293ef1f2d1ffc76cb3ab0ff054819c5343a88e8ea9717e1c22ddfba4cb5f3ad89de2099df90e056c83c70df834f7f611ab8e80c8c4c789d46cac8134b4dc1e16248c51f851cc780db10bd5e2afde3f41fbfd1756248e7e1068a7c5cacb0e252b6643b14a02c08816e57f4ff6ecbddfacdafe3a7ff051c499bed5b0ae387cb8de0c0f11dd33729e51c62a647b141c3e1af197d18c5195c337153e282724ae3df8bef859f70d6b2084fd14fabb4e83c453e8d2c5c56ee4e3b115eb167eb72d1e42230771e1b83278783245fafcc37bd91e66b7fc7270c58cd167e363fc1880c181e44341e35b4f0cf50cc64d879a8be544134d5fdb7ec1265db32ef5e6702f9080a8b5b2441e4b46c3339ed9a4fc3c508e989cd648c15f191ea0d5b687e6c3f1061863aa4e2aad8da950d5889a111582c19dac4a006027cddcd7df8d26a3c34edadc571247a7fd48700b7441b3009ee3a8c986a14c84a1ab5f0054610aceb70ec59b99d378bdc4e1e00b81eb35f25fdc0ac531c5745556196ec23d1c7c9027998ffd2fd3299288bfc1f90770690ee1d3ae38b59cc0facd80d3c5a1a5c4119c5700ac23fca251d44adb7c0bb7977dab315dcb1b10779c8e4954b288e42a789eb0df4d7d352a202deaf63d97a80766455fdf266a08e36222daba31fac1f6eeb30cf68b43650a271d07d9e3b22b00f238c3fcf0aa6b4a75109dcce900246f9a65d30b0b7f768b902b094d176528cc490bc77cd2e323f5fce0f85483a1f5dea53b6de778384ff380e0581a81b787b19246d226731e172c201b5518a6e61c8b36bd42527877d88a21c25c08c8b030f8f6724bc37c632f3709481be2fbd581be7674ba14b343f99a9b5b7ede95580ce89c169c1b94b8535ddeefb2782a790dbf8ce73ef4d3a49a69163324668fb801cbacba2cf664276be7c89882a2dad7a6d5a19f34bb7da2a340b9d0b8665fd7f8e750e6631c93b75f1deeccf32ab3f9354add2206315b46fc67acbca0a7acbdda86ae23a955ca70174779126dd75fe6a36467fa1a1e15978e26187f46f11f738deeeef86668b15b7cad90f3587083a6d66c68aeda4a539d3fc5259f100c6000fb6739ee021eef7f74975cf61cbeca42b8a907c7ad7dbc61f88bfaa668bf166c0a3bb78ce53f2de5e84c04a32189d9c130656dccfa7ef8eaa2c2c01cb5d3e9c0a4b08f5a78931293c115b182cf985b2b25e6c1452b16b04123b09e875e118303b010eae021e14793e53a8b1c8fb5f68881762cbba70d8c6c659dbd71cd3e893d16a1efa749f373ed3e03b9f8c7a652e12b5bd6b5d62b33754ed344616925a676beacc736598f3fa7b3b7649ee134183d0bdde6bb20374e63c8995ce09a8d80b790789915b77e53cb2ba0b3974327f0a509468555edfb843fba362d75c83dbf07744f8ecdcd8756609004cf6a574781200ddcda0ca53d7e100bf3dea85bfe0c6f5277cee50274f16fc92cdf9f835c74b6ffe90e67b0c6e3dea5189801bb980ff6123980e5bd0ccbffbe600cbf312d706fc7b348ef765e5cb26fed820951d36fa49cddcc5568168d1857e87e51c8831e544d83b12a60cc919351b9c5478377d481d8abdbbe6a5bdec27c0b5cddb026266c7aa071a2",
    .p_expected_output  = "e8e09fc57bd3b8e18b2726418836852cf1544eb2cf28c18f5b98436382d0b621953d2faa60d155dd28c2cb76c00ee93d3de56289b399c22a4fd82f00dd35ef27"
};

NRF_SECTION_ITEM_REGISTER(test_vector_hash_long_data, test_vector_hash_t test_vector_sha512_long) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha512_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .mode               = NO_MODE,
    .chunk_length       = 4096,
    .update_iterations  = 256,
    .p_test_vector_name = "SHA512 message_len=1048576",
    .p_input            = flash_data,
    .p_expected_output  = "4f544f809b8a0a7052eca55df04ba4b19c3ecd2dca6c721ab7e88d94574d663cbde4ca3dc114f92c827226184899c5c48c706b20d66cb056f97e0a21cf2979f5"
};

NRF_SECTION_ITEM_REGISTER(test_vector_hash_long_data, test_vector_hash_t test_vector_sha512_long_flash) =
{
    .p_hash_info        = &g_nrf_crypto_hash_sha512_info,
    .expected_err_code  = NRF_SUCCESS,
    .expected_result    = EXPECTED_TO_PASS,
    .mode               = DO_MEMCPY,
    .chunk_length       = 4096,
    .update_iterations  = 256,
    .p_test_vector_name = "SHA512 flash memcpy message_len=1048576",
    .p_input            = flash_data,
    .p_expected_output  = "4f544f809b8a0a7052eca55df04ba4b19c3ecd2dca6c721ab7e88d94574d663cbde4ca3dc114f92c827226184899c5c48c706b20d66cb056f97e0a21cf2979f5"
};

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_HASH_SHA512)

/*lint -restore */

#endif // NRF_MODULE_ENABLED(NRF_CRYPTO_HASH)

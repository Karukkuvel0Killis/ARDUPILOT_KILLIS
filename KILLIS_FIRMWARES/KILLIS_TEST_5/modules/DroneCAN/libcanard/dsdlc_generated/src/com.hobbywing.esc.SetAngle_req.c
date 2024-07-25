#define CANARD_DSDLC_INTERNAL
#include <com.hobbywing.esc.SetAngle_req.h>
#include <com.hobbywing.esc.SetAngle_res.h>
#include <string.h>

#ifdef CANARD_DSDLC_TEST_BUILD
#include <test_helpers.h>
#endif

uint32_t com_hobbywing_esc_SetAngleRequest_encode(struct com_hobbywing_esc_SetAngleRequest* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
) {
    uint32_t bit_ofs = 0;
    memset(buffer, 0, COM_HOBBYWING_ESC_SETANGLE_REQUEST_MAX_SIZE);
    _com_hobbywing_esc_SetAngleRequest_encode(buffer, &bit_ofs, msg, 
#if CANARD_ENABLE_TAO_OPTION
    tao
#else
    true
#endif
    );
    return ((bit_ofs+7)/8);
}

/*
  return true if the decode is invalid
 */
bool com_hobbywing_esc_SetAngleRequest_decode(const CanardRxTransfer* transfer, struct com_hobbywing_esc_SetAngleRequest* msg) {
#if CANARD_ENABLE_TAO_OPTION
    if (transfer->tao && (transfer->payload_len > COM_HOBBYWING_ESC_SETANGLE_REQUEST_MAX_SIZE)) {
        return true; /* invalid payload length */
    }
#endif
    uint32_t bit_ofs = 0;
    if (_com_hobbywing_esc_SetAngleRequest_decode(transfer, &bit_ofs, msg,
#if CANARD_ENABLE_TAO_OPTION
    transfer->tao
#else
    true
#endif
    )) {
        return true; /* invalid payload */
    }

    const uint32_t byte_len = (bit_ofs+7U)/8U;
#if CANARD_ENABLE_TAO_OPTION
    // if this could be CANFD then the dlc could indicating more bytes than
    // we actually have
    if (!transfer->tao) {
        return byte_len > transfer->payload_len;
    }
#endif
    return byte_len != transfer->payload_len;
}

#ifdef CANARD_DSDLC_TEST_BUILD
struct com_hobbywing_esc_SetAngleRequest sample_com_hobbywing_esc_SetAngleRequest_msg(void) {
    struct com_hobbywing_esc_SetAngleRequest msg;

    msg.option = (uint8_t)random_bitlen_unsigned_val(8);
    msg.angle = (uint16_t)random_bitlen_unsigned_val(16);
    return msg;
}
#endif

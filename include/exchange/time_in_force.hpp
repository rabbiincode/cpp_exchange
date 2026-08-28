#pragma once

#include <cstdint>

namespace exchange {

    enum class TimeInForce : std::uint8_t
    {
        gtc, // Good Till Cancelled. Any unfilled quantity may remain in the order book.
        ioc, // Immediate Or Cancel. Execute immediately where possible, then cancel the remainder.
        fok  // Fill Or Kill. Execute the entire quantity immediately or execute none of it.
    };

}  // namespace exchange

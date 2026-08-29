#pragma once

#include <cstdint>

namespace exchange
{

    enum class OrderStatus : std::uint8_t
    {
        pending,          // Order has been received but not yet processed
        open,             // Order is active and waiting to be filled
        partially_filled, // Order has been partially filled, but not completely
        filled,           // Order has been completely filled
        cancelled,        // Order has been cancelled by the user or the system
        rejected,         // Order has been rejected due to invalid parameters or insufficient funds
    };

}

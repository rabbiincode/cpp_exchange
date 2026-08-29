#pragma once

#include <exchange/order_status.hpp>

namespace exchange
{
    inline bool is_terminal(OrderStatus status)
    {
        return status == OrderStatus::filled || status == OrderStatus::cancelled || status == OrderStatus::rejected;
    }
}

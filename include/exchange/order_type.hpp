#pragma once

#include <cstdint>

namespace exchange {

enum class OrderType : std::uint8_t {
    limit,
    market
};

}  // namespace exchange

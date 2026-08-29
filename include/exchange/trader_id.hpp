#pragma once

#include <cstdint>

namespace exchange {

class TraderId {
public:
    explicit TraderId(std::uint64_t value)
        : value_{value}
    {
    }

    std::uint64_t value() const
    {
        return value_;
    }

    bool operator==(const TraderId& other) const
    {
        return value_ == other.value_;
    }

private:
    std::uint64_t value_;
};

}

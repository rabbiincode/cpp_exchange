#pragma once

#include <cstdint>

namespace exchange
{
    class OrderId
    {
    public:
        explicit OrderId(std::uint64_t value)
            : value_{value}
        {
        }

        std::uint64_t value() const
        {
            return value_;
        }

        bool operator==(const OrderId &other) const
        {
            return value_ == other.value_;
        }

    private:
        std::uint64_t value_;
    };
}

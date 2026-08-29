#pragma once

#include <cstdint>

namespace exchange
{

    class TradeId
    {
    public:
        explicit TradeId(std::uint64_t value)
            : value_{value}
        {
        }

        std::uint64_t value() const
        {
            return value_;
        }

        bool operator==(const TradeId &other) const
        {
            return value_ == other.value_;
        }

    private:
        std::uint64_t value_;
    };

}

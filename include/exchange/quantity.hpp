#pragma once

#include <cstdint>
#include <stdexcept>

namespace exchange
{

    class Quantity
    {
    public:
        explicit Quantity(std::uint64_t value)
            : value_{value}
        {
            if (value_ == 0)
            {
                throw std::invalid_argument("Quantity must be greater than zero");
            }
        }

        std::uint64_t value() const
        {
            return value_;
        }

        bool operator==(const Quantity &other) const
        {
            return value_ == other.value_;
        }

    private:
        std::uint64_t value_;
    };

}

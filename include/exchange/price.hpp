#pragma once

#include <cstdint>
#include <stdexcept>

namespace exchange {

class Price {
public:
    explicit Price(std::uint64_t value)
        : value_{value}
    {
        if (value_ == 0) {
            throw std::invalid_argument("Price must be greater than zero");
        }
    }

    std::uint64_t value() const
    {
        return value_;
    }

    bool operator==(const Price& other) const
    {
        return value_ == other.value_;
    }

private:
    std::uint64_t value_;
};

}

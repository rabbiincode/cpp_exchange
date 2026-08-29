#pragma once

#include <string>
#include <utility>
#include <stdexcept>

namespace exchange
{

    class Symbol
    {
    public:
        explicit Symbol(std::string value)
            : value_{value} // std::move(value) - Can be used but not ideal now.
        {
            if (value_.empty())
            {
                throw std::invalid_argument("Symbol cannot be empty");
            }
        }

        const std::string& value() const
        {
            return value_;
        }

        bool operator==(const Symbol &other) const
        {
            return value_ == other.value_;
        }

    private:
        std::string value_;
    };

} // namespace exchange

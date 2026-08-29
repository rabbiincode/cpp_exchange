#include <exchange/order.hpp>
#include <exchange/price.hpp>
#include <exchange/quantity.hpp>
#include <exchange/symbol.hpp>
#include <exchange/trade.hpp>
#include <exchange/order_status_helpers.hpp>

#include <iostream>
#include <stdexcept>

namespace
{

    int failures = 0;

    void check(bool condition, const char *message)
    {
        if (!condition)
        {
            std::cerr << "FAILED: " << message << '\n';
            ++failures;
        }
    }

    bool rejects_zero_quantity()
    {
        try
        {
            const exchange::Quantity quantity{0};
        }
        catch (const std::invalid_argument &)
        {
            return true;
        }
        catch (...)
        {
            return false;
        }

        return false;
    }

    bool rejects_zero_price()
    {
        try
        {
            const exchange::Price price{0};
        }
        catch (const std::invalid_argument &)
        {
            return true;
        }
        catch (...)
        {
            return false;
        }

        return false;
    }

    bool rejects_empty_symbol()
    {
        try
        {
            const exchange::Symbol symbol{""};
        }
        catch (const std::invalid_argument &)
        {
            return true;
        }
        catch (...)
        {
            return false;
        }

        return false;
    }

}

int main()
{
    check(rejects_zero_quantity(), "Quantity rejects zero");
    check(rejects_zero_price(), "Price rejects zero");
    check(rejects_empty_symbol(), "Symbol rejects an empty value");

    const exchange::Quantity quantity{100};
    const exchange::Price price{95};
    const exchange::Symbol symbol{"BTCUSD"};
    const exchange::OrderId buy_order_id{42};
    const exchange::OrderId sell_order_id{43};
    const exchange::TraderId trader_id{7};

    check(quantity.value() == 100, "Quantity retains its value");
    check(price.value() == 95, "Price retains its value");
    check(symbol.value() == "BTCUSD", "Symbol retains its value");

    exchange::Order order{
        buy_order_id,
        trader_id,
        symbol,
        exchange::Side::buy,
        price,
        quantity,
        exchange::TimeInForce::gtc};

    check(order.status() == exchange::OrderStatus::pending,
          "A new order starts pending");
    check(order.accept(), "A pending order can be accepted");
    check(order.status() == exchange::OrderStatus::open,
          "An accepted order becomes open");
    check(!order.accept(), "An open order cannot be accepted again");
    check(order.status() == exchange::OrderStatus::open,
          "Failed acceptance leaves an order open");

    const exchange::Trade trade{
        exchange::TradeId{702},
        buy_order_id,
        sell_order_id,
        symbol,
        price,
        quantity};

    check(trade.buy_order_id() == buy_order_id,
          "Trade retains the buy order ID");
    check(trade.sell_order_id() == sell_order_id,
          "Trade retains the sell order ID");

    check(!exchange::is_terminal(exchange::OrderStatus::pending),
          "Pending order is not terminal");

    check(!exchange::is_terminal(exchange::OrderStatus::open),
          "Open order is not terminal");

    check(!exchange::is_terminal(exchange::OrderStatus::partially_filled),
          "Partially filled order is not terminal");

    check(exchange::is_terminal(exchange::OrderStatus::filled),
          "Filled order is terminal");

    check(exchange::is_terminal(exchange::OrderStatus::cancelled),
          "Cancelled order is terminal");

    check(exchange::is_terminal(exchange::OrderStatus::rejected),
          "Rejected order is terminal");

    if (failures == 0)
    {
        std::cout << "All domain tests passed\n";
    }

    return failures;
}

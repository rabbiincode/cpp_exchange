#include <exchange/order.hpp>
#include <exchange/order_id.hpp>
#include <exchange/side.hpp>
#include <exchange/trader_id.hpp>
#include <exchange/quantity.hpp>
#include <exchange/price.hpp>
#include <exchange/symbol.hpp>
#include <exchange/order_type.hpp>
#include <exchange/time_in_force.hpp>
#include <exchange/order_status.hpp>
#include <exchange/trade_id.hpp>
#include <exchange/trade.hpp>

#include <iostream>

bool is_buy(exchange::Side side)
{
    return side == exchange::Side::buy;
}

bool is_limit(exchange::OrderType type)
{
    return type == exchange::OrderType::limit;
}

int main()
{
    const exchange::Side buy_side{exchange::Side::buy};
    const exchange::Side sell_side{exchange::Side::sell};

    std::cout << std::boolalpha
              << "Buy and sell are different sides: "
              << (buy_side != sell_side) << '\n';

    std::cout << "buy: " << is_buy(buy_side) << '\n';
    std::cout << "sell: " << is_buy(sell_side) << '\n';

    const exchange::OrderId first_order{42};
    const exchange::OrderId same_order{42};
    const exchange::OrderId different_order{43};

    std::cout << "Equal IDs compare equal: "
              << (first_order == same_order) << '\n';
    std::cout << "Different IDs compare unequal: "
              << !(first_order == different_order) << '\n';
    std::cout << "First order's stored value: "
              << first_order.value() << '\n';

    const exchange::TraderId trader{7};
    std::cout << "Trader ID: " << trader.value() << '\n';

    const exchange::Quantity quantity{100};
    std::cout << "Order Quantity: " << quantity.value() << '\n';

    const exchange::Price price{95};
    std::cout << "Order Price: " << price.value() << '\n';

    const exchange::Symbol symbol{"BTCUSD"};
    std::cout << "Symbol: " << symbol.value() << '\n';

    const exchange::OrderType limit_type{exchange::OrderType::limit};
    const exchange::OrderType market_type{exchange::OrderType::market};

    std::cout << "Limit and market order are different types of orders: "
              << (limit_type != market_type) << '\n';

    std::cout << "limit: " << is_limit(limit_type) << '\n';
    std::cout << "market: " << is_limit(market_type) << '\n';

    const exchange::TimeInForce gtc{exchange::TimeInForce::gtc};
    const exchange::TimeInForce ioc{exchange::TimeInForce::ioc};
    const exchange::TimeInForce fok{exchange::TimeInForce::fok};

    const bool time_in_force_values_are_distinct =
        gtc != ioc && gtc != fok && ioc != fok;

    std::cout << "GTC, IOC, and FOK are distinct: "
              << time_in_force_values_are_distinct << '\n';

    const exchange::OrderStatus pending{exchange::OrderStatus::pending};
    const exchange::OrderStatus filled{exchange::OrderStatus::filled};

    const bool order_status_values_are_distinct =
        pending != filled;

    std::cout << "Pending and Filled are distinct: "
              << order_status_values_are_distinct << '\n';

    const exchange::Order order{
        first_order,
        trader,
        symbol,
        buy_side,
        price,
        quantity,
        gtc};

    std::cout << "Order ID: " << order.id().value() << '\n';
    std::cout << "Order symbol: " << order.symbol().value() << '\n';
    std::cout << "Order starts pending: "
              << (order.status() == exchange::OrderStatus::pending) << '\n';

    const exchange::TradeId trade_id{702};

    const exchange::OrderId buy_order_id{42};
    const exchange::OrderId sell_order_id{43};

    const exchange::Trade trade{
        trade_id,
        buy_order_id,
        sell_order_id,
        symbol,
        price,
        quantity};

    std::cout << "Trade ID: " << trade.trade_id().value() << '\n';
    std::cout << "Buy order ID: " << trade.buy_order_id().value() << '\n';
    std::cout << "Sell order ID: " << trade.sell_order_id().value() << '\n';
    std::cout << "Trade symbol: " << trade.symbol().value() << '\n';
    return 0;
}

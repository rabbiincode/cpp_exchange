#pragma once

#include <exchange/order_id.hpp>
#include <exchange/order_status.hpp>
#include <exchange/price.hpp>
#include <exchange/quantity.hpp>
#include <exchange/side.hpp>
#include <exchange/symbol.hpp>
#include <exchange/time_in_force.hpp>
#include <exchange/trader_id.hpp>

namespace exchange {

class Order {
public:
    Order(OrderId id,
          TraderId trader_id,
          const Symbol& symbol,
          Side side,
          Price price,
          Quantity quantity,
          TimeInForce time_in_force)
        : id_{id},
          trader_id_{trader_id},
          symbol_{symbol},
          side_{side},
          price_{price},
          quantity_{quantity},
          time_in_force_{time_in_force},
          status_{OrderStatus::pending}
    {
    }

    OrderId id() const { return id_; }
    TraderId trader_id() const { return trader_id_; }
    const Symbol& symbol() const { return symbol_; }
    Side side() const { return side_; }
    Price price() const { return price_; }
    Quantity quantity() const { return quantity_; }
    TimeInForce time_in_force() const { return time_in_force_; }
    OrderStatus status() const { return status_; }

private:
    OrderId id_;
    TraderId trader_id_;
    Symbol symbol_;
    Side side_;
    Price price_;
    Quantity quantity_;
    TimeInForce time_in_force_;
    OrderStatus status_;
};

}  // namespace exchange

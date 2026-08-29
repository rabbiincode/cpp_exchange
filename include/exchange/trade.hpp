#pragma once

#include <exchange/order_id.hpp>
#include <exchange/price.hpp>
#include <exchange/quantity.hpp>
#include <exchange/symbol.hpp>
#include <exchange/trade_id.hpp>

namespace exchange {

class Trade {
public:
  Trade(
      TradeId trade_id,
      OrderId buy_order_id,
      OrderId sell_order_id,
      const Symbol &symbol,
      Price price,
      Quantity quantity)
      : trade_id_{trade_id},
        buy_order_id_{buy_order_id},
        sell_order_id_{sell_order_id},
        symbol_{symbol},
        price_{price},
        quantity_{quantity}
  {
  }

  TradeId trade_id() const { return trade_id_; }
  OrderId buy_order_id() const { return buy_order_id_; }
  OrderId sell_order_id() const { return sell_order_id_; }
  const Symbol &symbol() const { return symbol_; }
  Price price() const { return price_; }
  Quantity quantity() const { return quantity_; }

private:
  TradeId trade_id_;
  OrderId buy_order_id_;
  OrderId sell_order_id_;
  Symbol symbol_;
  Price price_;
  Quantity quantity_;
};

}

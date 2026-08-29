# Milestone 1 — Exchange Domain Model

## What I Built

I built the first domain model for a C++ trading exchange. It contains:

- Strong identifiers for orders, traders, and trades
- `Side`, `OrderType`, `TimeInForce`, and `OrderStatus` enums
- Validated `Price`, `Quantity`, and `Symbol` types
- A basic limit `Order`
- A `Trade` connecting a buy order and a sell order
- Automated domain tests

## Why It Exists

These types provide the vocabulary used by later exchange components. Order
management, risk checks, matching, persistence, and market data will all depend
on them.

Strong domain types help prevent unrelated values from being mixed. For
example, `OrderId` and `TraderId` both store integers, but they are different
C++ types.

## Architecture

```text
Domain types
    ↓
Order management
    ↓
Order book
    ↓
Matching engine
    ↓
Trade events
    ↓
Persistence and market data
```

This milestone implements only the domain-types layer.

## C++ Concepts Practiced

- Headers and include paths
- Namespaces
- Classes and scoped enums
- Explicit constructors
- Encapsulation
- Const member functions
- Passing and returning by value
- Returning by const reference
- Object lifetime
- Strong domain types
- Constructor validation
- Exceptions for invalid construction
- Header self containment
- Basic operator overloading
- Automated test executables

## Engineering Decisions

### Strong identifiers

`OrderId`, `TraderId`, and `TradeId` are separate classes rather than aliases of
`std::uint64_t`. This lets the compiler reject accidental mixing of identifiers.

### Integer price ticks

`Price` stores integer ticks instead of `double`. Integer ticks provide exact,
deterministic values for comparison and ordering. The project has not yet
defined how one tick maps to a displayed currency amount.

### Valid construction

The constructors enforce these rules:

- `Quantity` cannot be zero.
- `Price` cannot be zero.
- `Symbol` cannot be empty.

A successfully constructed object therefore satisfies its basic invariant.

### Limit orders only

The first `Order` requires a `Price`, so it currently represents a limit order.
`OrderType` is not stored in `Order` yet because allowing `market` while always
requiring a price would permit a contradictory state.

### Initial order status

The `Order` constructor sets the status to `pending`. A caller cannot construct
a new order that already claims to be filled or cancelled.

### Ownership

`Order` and `Trade` own copies of their `Symbol` values. They do not depend on
the lifetime of the symbol object passed to their constructors.

Small integer-like values are returned by value. `Symbol::value()` returns a
const reference to avoid copying its string. That reference remains valid only
while the owning `Symbol` remains alive.

## Important Things I Initially Got Wrong

### Treating a decimal display value as integer ticks

I attempted to construct:

```cpp
Price{9.50}
```

The compiler rejected the narrowing conversion from `double` to
`std::uint64_t`. The correct representation uses an integer tick value, such as
`Price{95}`. Its currency meaning will be defined separately.

### Confusing language validity with domain validity

An explicit cast can create an enum value that has no named domain enumerator:

```cpp
auto side = static_cast<Side>(42);
```

The value can have a valid C++ representation while still being invalid for the
exchange domain.

## Tests Added

The domain test executable checks that:

- Zero quantity is rejected.
- Zero price is rejected.
- An empty symbol is rejected.
- Valid values retain their data.
- A new order starts as `pending`.
- A trade retains its buy and sell order IDs.
- Terminal order status classification is correct for all six statuses.

## Alternatives and Trade-offs

### Aliases instead of strong types

Aliases require less code, but they do not prevent mixing order, trader, and
trade identifiers.

### Floating point prices

Floating point values are convenient for display but do not represent every
decimal fraction exactly. Integer ticks make exchange comparisons deterministic
but require a separately defined tick size and display conversion.

### Returning strings by value

Returning a string by value avoids reference lifetime concerns but may copy its
characters. Returning a const reference avoids the copy but requires the caller
to respect the owning object's lifetime.

### External test framework

The first tests use a small standard library test executable. This keeps the
foundation simple, but a dedicated testing framework may later provide clearer
test organization and diagnostics.

## Assessment

### C++ concepts

1. Why are `OrderId` and `TraderId` separate classes instead of aliases of
   `std::uint64_t`?
2. What does `explicit` prevent on the identifier constructors?
3. Why does `Symbol::value()` return `const std::string&`, while
   `Price::value()` returns an integer by value?
4. Can an explicitly cast `Side` contain a value other than `buy` or `sell`?

### Code reading and debugging

Analyze this function:

```cpp
const std::string& get_symbol_text()
{
    const exchange::Symbol symbol{"BTCUSD"};
    return symbol.value();
}
```

Explain compilation, destruction, the returned reference, and a safe fix.

Also explain why `Quantity{-10}` fails before its constructor body executes,
while `Quantity{0}` reaches the constructor and throws.

### Implementation challenge

Implement `exchange::is_terminal(OrderStatus)` and add tests covering every
order status.

### Engineering reasoning

1. Why are prices stored as integer ticks rather than `double`?
2. Why does every new `Order` start as `pending`?
3. Why does the current `Order` omit `OrderType`?
4. What did standalone compilation of `trade.hpp` reveal?

## Interview Knowledge

After revising this milestone, I should be able to discuss:

- Strong types versus type aliases
- Implicit versus explicit construction
- Basic class invariants (A rule that must always stay true for an object to be considered valid.)
- Returning values versus references
- Dangling references and undefined behavior
- Integer price representation
- Header self containment
- Why successful compilation does not prove unused code is valid
- The difference between an order and a trade

## What Comes Next

Milestone 2 introduces order management. The initial focus will be controlled
order to status transitions and changes to remaining quantity.

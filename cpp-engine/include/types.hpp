#pragma once
#include <cstdint>
#include <string>

namespace kalshi {

// Kalshi prices are always integer cents, 1-99
using Cents = int32_t;
using Quantity = int32_t;

struct MarketId {
    std::string ticker;
    bool operator==(const MarketId& other) const { return ticker == other.ticker; }
};

// One leg of a market group used for arbitrage checks.
// e.g. "Fed cuts 25bps" and "Fed cuts 50bps" are two legs of the same group.
struct MarketLeg {
    std::string ticker;
    std::string group_id;   // markets sharing a group_id are mutually exclusive outcomes
};

} // namespace kalshi
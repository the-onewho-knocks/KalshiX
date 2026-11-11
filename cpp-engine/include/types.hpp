#pragma once
#include <cstdint>
#include <string>
#include <chrono>
#include <vector>
using namespace std;

namespace kalshi
{

    // Kalshi prices are always integer cents, 1-99
    // payouts at the settlement is strictly 100 cents that is 1 dollar or 0 dollar
    using Cents = int32_t;
    using Quantity = int32_t;
    using TimestampNs = int64_t;

    constexpr Cents MIN_PRICE_CENTS = 1;
    constexpr Cents MAX_PRICE_CENTS = 99;
    constexpr Cents PAYOUT_CENTS = 100;

    enum class Side : uint8_t
    {
        BUY,
        SELL
    };

    enum class Outcome : uint8_t
    {

        YES,
        NO
    };

    struct MarketId
    {
        std::string ticker;
        bool operator==(const MarketId &other) const { return ticker == other.ticker; }
    };

    // One leg of a market group used for arbitrage checks.
    // e.g. "Fed cuts 25bps" and "Fed cuts 50bps" are two legs of the same group.
    struct MarketLeg
    {
        std::string ticker;
        std::string group_id; // markets sharing a group_id are mutually exclusive outcomes
    };

    struct PriceLevel
    {
        Cents price{0};
        Quantity quantity{0};
    };

    // Represents an identified arbitrage opportunity
    struct ArbOpportunity
    {
        std::string group_id;
        std::vector<std::string> tickers; // Leg tickers involved
        std::vector<Cents> prices;        // Best ask prices for each leg
        Cents total_cost{0};              // Sum of all asks (must be < 100 for buy arb)
        Cents guaranteed_profit{0};       // 100 - total_cost
        Quantity max_executable_qty{0};   // Bottleneck quantity across all legs
        TimestampNs detected_at_ns{0};    // High-resolution timestamp
    };
    // Utility to get current nanoseconds since Unix epoch
    inline TimestampNs now_ns()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
            .count();
    }

} // namespace kalshi
#pragma once
#include "types.hpp"
#include <bits/stdc++.h>
using namespace std;

namespace kalshi
{

    class OrderBook
    {
    public:
        explicit OrderBook(string ticker) : ticker_(move(ticker)) {}
        void update_bid(Cents prices, Quantity qty);
        void update_ask(Cents price, Quantity qty);

        optional<Cents> best_ask() const;
        optional<Cents> best_bid() const;

        Quantity best_ask_quantity() const;

        const string &ticker() const { return ticker_; }
        bool is_stale() const { return stale_; }
        void mark_stale(bool stale) { stale_ = stale; }

    private:
        string ticker_;
        map<Cents, Quantity> bids_;
        map<Cents, Quantity> asks_;
        bool stale_ = false;
    };
}
#pragma once
#include <cassert>
#include <algorithm>
#include <iostream>

struct Option {
    float S; // Spot of the underlying price
    float r; // risk-free interest rate
    float sig; // volatility
    float K; // Strike
    float d; // Dividend
    float T; // Maturity in years

    Option(float, float, float, float, float, float);

    virtual float payoff(float underlying_price) const = 0;
};


struct Call final: public Option {
    using Option::Option;
    float payoff(float) const override;
};


struct Put final : public Option {
    using Option::Option;
    float payoff(float) const override;
};

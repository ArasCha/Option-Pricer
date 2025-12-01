#pragma once
#include <cassert>
#include <algorithm>
#include <iostream>

struct Option {
    float spot, rate, volatility, strike, dividend;
    float maturity; // in years

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

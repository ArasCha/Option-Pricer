#include <cassert>
#include <algorithm> // for max function
#include "option.hpp"
#include <iostream>



Option::Option(float S, float r, float sig, float T, float K, float d) :
    spot(S), rate(r), volatility(sig), maturity(T), strike(K), dividend(d)
    {   assert(sig > 0); // constructeur en privé pour que seules les classes filles puissent utiliser
        assert(S >= 0);
        assert(d >= 0);
        assert(T >= 0);
    };


float Call::payoff(float underlying_price) const {
    return std::max(underlying_price - strike, 0.0f);
    // mettre 0 en float car max est définie telle que les deux param ont le même type
}

float Put::payoff(float underlying_price) const {
    return std::max(strike - underlying_price, 0.0f);
}
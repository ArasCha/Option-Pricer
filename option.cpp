#include <cassert>
#include <algorithm> // for max function
#include "option.hpp"
#include <iostream>



Option::Option(float spot, float rate, float volatility, float maturity, float strike) :
    S(spot), r(rate), sig(volatility), T(maturity), K(strike)
    {   assert(sig > 0); // constructeur en privé pour que seules les classes filles puissent utiliser
        assert(S >= 0);
        assert(T >= 0);
    };


float Call::payoff(float underlying_price) const {
    return std::max(underlying_price - K, 0.0f);
    // mettre 0 en float car max est définie telle que les deux param ont le même type
}

float Put::payoff(float underlying_price) const {
    return std::max(K - underlying_price, 0.0f);
}
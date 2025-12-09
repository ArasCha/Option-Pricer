
#include <iostream>
#include <typeinfo>
#include "option.hpp"
#include <memory>
#include "Pricers/Pricer.hpp"



int main() {
    Call call(100.0, 0.01, 0.5, 0.25, 95.0);
    Put put(100.0, 0.01, 0.5, 0.25, 95.0);
    BlackScholesPricer bspricer(call);

    std::cout << bspricer.calculate() << std::endl;
    std::cout << BlackScholesPricer(put).calculate() << std::endl;
    return 0;
}

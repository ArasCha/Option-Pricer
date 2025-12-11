
#include <iostream>
#include <typeinfo>
#include "option.hpp"
#include <memory>
#include "Pricers/Pricer.hpp"



int main() {
    Call call(1000.0, 0.01, 0.5, 0.25, 95.0);
    Put put(1000.0, 0.01, 0.5, 0.25, 95.0);

    BlackScholesPricer bspricer(call);

    int nb_samples = 10000000;
    MonteCarloPricer mcpricer(call, nb_samples);

    // int nb_runs = 10000;
    // auto bsResults = bspricer.benchmark(nb_runs);
    // auto mcResults = mcpricer.benchmark(nb_runs);

    // std::cout << "time: " << bsResults.first << " price: " << bsResults.second << std::endl;
    // std::cout << "time: " << mcResults.first << " price: " << mcResults.second << std::endl;

    std::cout << "price BS: " << bspricer.calculate() << std::endl;
    std::cout << "price MC: " << mcpricer.calculate() << std::endl;

    return 0;
}

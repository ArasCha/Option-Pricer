
#include <iostream>
#include <typeinfo>
#include "option.hpp"
#include <memory>
#include "Pricers/Pricer.hpp"



int main() {
    Call call(100.0, 0.01, 0.5, 0.25, 95.0);
    Put put(100.0, 0.01, 0.5, 0.25, 95.0);
    BlackScholesPricer bspricer(call);

    int nb_runs = 10000;
    auto results = bspricer.benchmark(nb_runs);

    std::cout << "time: " << results.first << " price: " << results.second << std::endl;
    return 0;
}

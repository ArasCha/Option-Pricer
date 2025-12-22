
#include <iostream>
#include <typeinfo>
#include "option.hpp"
#include <memory>
#include "Pricers/Pricer.hpp"
#include <iomanip>


template<int N>
void pricer_benchmark(OptionPricer** pricers, int nb_runs) {

    for (int i=0; i<N; i++) {
        auto results = pricers[i]->benchmark(nb_runs);
        std::cout << typeid(*pricers[i]).name() << std::fixed << std::setprecision(6) << " time (ms): " << results.first << " price: " << results.second << std::endl;
    }
}

int main() {
    Call call(1000.0, 0.1, 0.7, 4.25, 95.0);
    Put put(1000.0, 0.01, 0.5, 0.25, 95.0);

    BlackScholesPricer bspricer(call);

    int nb_samples = 10000;
    NaiveMCpricer naiveMCpricer(call, nb_samples);
    AntitheticMCpricer antitheticMCpricer(call, nb_samples);
    ControlVariatesMCpricer cvMCpricer(call, nb_samples);
    OptionPricer* pricers[4] = {&bspricer, &naiveMCpricer, &antitheticMCpricer, &cvMCpricer};

    pricer_benchmark<4>(pricers, 1000);

    return 0;
}

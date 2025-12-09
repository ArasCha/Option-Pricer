#include "Pricer.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include "../utils.hpp"



OptionPricer::OptionPricer(Option& _instrument) : instrument(_instrument) {}

std::pair<double, double> OptionPricer::benchmark(const int nb_runs) const {

    double durations_sum = 0;
    double prices_sum = 0;

    for (int i=0; i<nb_runs; i++) {
        auto start = std::chrono::steady_clock::now();
        double price = calculate();
        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double, std::milli> elapsed = end - start;
        durations_sum += elapsed.count();
        prices_sum += price;
    }
    double mean_duration = durations_sum / nb_runs;
    double mean_price = prices_sum / nb_runs;

    return { mean_duration, mean_price };
}


double BlackScholesPricer::calculate() const {

    if (typeid(instrument) == typeid(Call)) {
        return S0 * normal_cdf(d1) - K * std::exp(-r * T) * normal_cdf(d2);

    } else if (typeid(instrument) == typeid(Put)) {
        return K * std::exp(-r * T) * normal_cdf(-d2) - S0 * normal_cdf(-d1);
    }

    throw std::runtime_error("BlackScholesPricer::calculate: unsupported instrument type");
}

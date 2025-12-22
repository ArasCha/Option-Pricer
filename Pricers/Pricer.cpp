#include "Pricer.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include "../utils.hpp"
#include <cmath>



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


MonteCarloPricer::MonteCarloPricer(Option& _instrument, int _nb_samples) :
    OptionPricer(_instrument), nb_samples(_nb_samples) {}

double NaiveMCpricer::calculate() const {

    double sample_payoff_sum = 0.0;

    for (int i = 0; i<nb_samples; i++) {
        double G = random_standard_normal();
        double S_T = S0*std::exp( (r - 0.5*sig*sig)*T + sig*G*std::sqrt(T) );
        sample_payoff_sum += instrument.payoff(S_T);
    }

    return std::exp(-r * T) * sample_payoff_sum/nb_samples;
};


double AntitheticMCpricer::calculate() const {

    double sample_payoff_sum = 0.0;

    for (int i = 0; i<nb_samples; i++) {
        double G = random_standard_normal();
        double S_T_p = S0*std::exp( (r - 0.5*sig*sig)*T + sig*G*std::sqrt(T) );
        double S_T_m = S0*std::exp( (r - 0.5*sig*sig)*T + sig*-G*std::sqrt(T) );
        sample_payoff_sum += instrument.payoff(S_T_p) + instrument.payoff(S_T_m);
    }

    return std::exp(-r * T) * sample_payoff_sum/(2 * nb_samples);
}

double ControlVariatesMCpricer::calculate() const {

    double sample_sum = 0.0;

    for (int i = 0; i<nb_samples; i++) {
        double G = random_standard_normal();
        double S_T = S0*std::exp( (r - 0.5*sig*sig)*T + sig*G*std::sqrt(T) );
        sample_sum += instrument.payoff(S_T) - S_T ; // chosen control variable is S_T
    }

    return std::exp(-r * T) * ( sample_sum/(nb_samples) + S0*std::exp(r*T) ); // E[S_T] = S0*exp(rT)
}

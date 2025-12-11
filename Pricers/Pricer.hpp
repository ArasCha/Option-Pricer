#include "../option.hpp"



struct OptionPricer {
    
    OptionPricer(Option&);

    virtual double calculate() const = 0;
    
    /// Computes the average time to calculate the option price
    /// @param nb_runs Number of runs to average computation time
    /// @return The average computation time with nb_runs price computations
    std::pair<double, double> benchmark(const int nb_runs) const;
    
    protected:

        Option& instrument;

        float& S0 = instrument.S0;
        float& K = instrument.K;
        float& sig = instrument.sig;
        float& T = instrument.T;
        float& r = instrument.r;
};


struct BlackScholesPricer : public OptionPricer {

    using OptionPricer::OptionPricer;

    double calculate() const override;

    private:
        double d1 = ( std::log(S0/K) + (r + sig*sig/2) * T ) / (sig * std::sqrt(T));
        double d2 = d1 - sig * std::sqrt(T);
};

struct MonteCarloPricer : OptionPricer {

    int nb_samples;

    MonteCarloPricer(Option& _instrument, int nb_samples);

    double calculate() const override;
};
#include "../option.hpp"



struct OptionPricer {
    
    OptionPricer(Option&);

    virtual double calculate() const = 0;
    
    protected:

        /// Computes the average time to calculate the option price
        /// @param nb_runs Number of runs to average computation time
        /// @param args Arguments to forward to the calculate function
        /// @return The average computation time with nb_runs price computations
        template<typename... Args>
        std::pair<double, double> benchmark(const int nb_runs, Args&&... args) const;

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

    double benchmark(const int nb_runs, const int) const;
    
    private:
        double d1 = ( std::log(S0/K) + (r + sig*sig/2) * T ) / (sig * std::sqrt(T));
        double d2 = d1 - sig * std::sqrt(T);
};

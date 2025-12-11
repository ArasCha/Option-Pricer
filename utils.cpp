#include <cmath>
#include "utils.hpp"
#include <utility>
#include <random>
#include <array>



double normal_cdf(double x) {
    return 0.5 *(1 + std::erf(x/std::sqrt(2.0)));
}

std::mt19937 rng; // Mersenne_twister_engine. As std::mersenne_twister_engine is a template class,
// We would need to provide the long list of all types and parameters. So instead we use mt19937
// mt19937 is a typedef of an initialized template of this engine
std::normal_distribution<double> dist(0, 1); // standard normal distribution

template<int N>
// typename et class ne fonctionnent pas à la int, car N n'est pas un paramètre de type
// C'est un non-type template parameter, une compile-time value.
std::array<double, N>&& random_standard_gaussian_vector() {
    // Retourner une rvalue reference pour éviter de copier vec dans la variable d'arrivée

    std::array<double, N> vec;

    for (int i=0; i<N; i++) {
        vec[i] = dist(rng);
    }

    return vec;
}

double random_standard_normal() {
    return dist(rng);
}
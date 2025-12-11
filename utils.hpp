#include <array>


double normal_cdf(double x);

template<int N>
std::array<double, N>&& random_standard_gaussian_vector();

/// @return sample from random standard normal variable
double random_standard_normal();
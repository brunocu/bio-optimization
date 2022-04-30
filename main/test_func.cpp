// test_func.cpp
// 
// Test function implementations
// 
#include "test_func.h"
#include <cmath>

void ackley(const alglib::real_1d_array &x, double &func, void *ptr)
{
	const int d = x.length();
	const double a = 20;
	const double b = 0.2;
	const double c = 2 * M_PI;

	double sum1 = 0;
	double sum2 = 0;
	for (auto i = 0; i < d; i++)
	{
		const auto xi = x[i];
		sum1 = sum1 + pow(xi, 2.0);
		sum2 = sum2 + cos(c * xi);
	}

	const double term1 = -a * exp(-b * sqrt(sum1 / d));
	const double term2 = -exp(sum2 / d);

	func = term1 + term2 + a + exp(1);
}

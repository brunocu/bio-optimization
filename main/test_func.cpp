// test_func.cpp
// 
// Test function implementations
// 
#include "test_func.h"
#include <cmath>

void ackley(const alglib::real_1d_array &x, double &func, void *ptr)
{
	const int d = x.length();
	const double a = 20L;
	const double b = 0.2L;
	const double c = 2L * M_PI;

	double sum1 = 0;
	double sum2 = 0;
	for (auto i = 0; i < d; i++)
	{
		const auto xi = x[i];
		sum1 = sum1 + pow(xi, 2);
		sum2 = sum2 + cos(c * xi);
	}

	const double term1 = -a * exp(-b * sqrt(sum1 / d));
	const double term2 = -exp(sum2 / d);

	func = term1 + term2 + a + exp(1);
}

void griewank(const alglib::real_1d_array &x, double &func, void *ptr)
{
	const int d = x.length();
	double sum = 0;
	double prod = 0;

	for (auto i = 0; i < d; i++)
	{
		const auto xi = x[i];
		sum = sum + (pow(xi, 2) / 4000.0L);
		prod = prod * cos(xi / sqrt(i + 1));
	}

	func = sum - prod + 1;
}

void rastrigin(const alglib::real_1d_array &x, double &func, void *ptr)
{
	const int d = x.length();
	double sum = 0;
	for (auto i = 0; i < d; i++)
	{
		const auto xi = x[i];
		// sum = sum + (xi^2 - 10*cos(2*pi*xi))
		sum = sum + (pow(xi, 2) - 10L * cos(2L * M_PI * xi));
	}

	func = 10L * d + sum;
}

void rothyp(const alglib::real_1d_array &x, double &func, void *ptr)
{
	const int d = x.length();
	double outer = 0;
	for (auto i = 0; i < d; i++)
	{
		double inner = 0;
		for (auto j = 0; j < i; j++)
		{
			const auto xj = x[j];
			inner = inner + pow(xj, 2);
		}
		outer = outer + inner;
	}

	func = outer;
}

void spheref(const alglib::real_1d_array &x, double &func, void *ptr)
{
	const int d = x.length();
	double sum = 0;
	for (auto i = 0; i < d; i++)
	{
		const auto xi = x[i];
		sum = sum + pow(xi, 2);
	}

	func = sum;
}

void dixonpr(const alglib::real_1d_array &x, double &func, void *ptr)
{
	const int d = x.length();
	const auto x1 = x[0];
	const auto term1 = pow((x1 - 1), 2);
	double sum = 0;
	for (auto i = 1; i < d; i++)
	{
		const auto xi = x[i];
		const auto xold = x[i - 1];
		// 	new = ii * (2*xi^2 - xold)^2;
		const auto snew = i * pow((2L * pow(xi, 2) - xold), 2);
		sum = sum + snew;
	}

	func = term1 + sum;
}

void sumsq(const alglib::real_1d_array &x, double &func, void *ptr)
{
	const int d = x.length();
	double sum = 0;
	for (auto i = 0; i < d; i++)
	{
		const auto xi = x[i];
		sum = sum + i * pow(xi, 2);
	}

	func = sum;
}

void trid(const alglib::real_1d_array &x, double &func, void *ptr)
{
	const int d = x.length();
	double sum1 = pow((x[0] - 1), 2);
	double sum2 = 0;
	for (auto i = 1; i < d; i++)
	{
		const auto xi = x[i];
		const auto xold = x[i - 1];
		sum1 = sum1 + pow((xi - 1), 2);
		sum2 = sum2 + xi * xold;
	}

	func = sum1 - sum2;
}

void rosenbrock(const alglib::real_1d_array &x, double &func, void *ptr)
{
	const int d = x.length();
	double sum = 0;
	for (int i = 0; i < (d - 1L); i++)
	{
		const auto xi = x[i];
		const auto xnext = x[i + 1];
		// new = 100*(xnext-xi^2)^2 + (xi-1L)^2;
		const auto term = 100L * pow((xnext - pow(xi, 2)), 2) + pow((xi - 1), 2);
		sum = sum + term;
	}

	func = sum;
}

void levy(const alglib::real_1d_array &x, double &func, void *ptr)
{
	const int d = x.length();
	alglib::real_1d_array w;
	w.setlength(d);

	for (auto i = 0; i < d; i++)
	{
		w[i] = 1L + (x[i] - 1) / 4L;
	}
	
	// term1 = (sin(pi*w(1)))^2;
	const double term1 = pow(sin(M_PI * w[0]), 2);
	// term3 = (w(d)-1)^2 * (1+(sin(2*pi*w(d)))^2);
	const double term3 = pow((w[d - 1] - 1), 2) * (1L + pow(sin(2L * M_PI * w[d - 1]), 2));
	double sum = 0;
	for (auto i = 0; i < (d - 1); i++)
	{
		const auto wi = w[i];
		//  new = (wi-1)^2 * (1+10*(sin(pi*wi+1))^2);
		const auto term = pow((w[i] - 1), 2) * (1 + 10L * pow(sin(M_PI * w[i] + 1), 2));
		sum = sum + term;
	}

	func = term1 + sum + term3;
}

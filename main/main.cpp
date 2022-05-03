#include "ap.h"
#include "rainfall.h"
#include "test_func.h"
#include <iostream>
#include <time.h>

int main()
{
	alglib::real_1d_array sol;
	double func;

	int d[] = { 10, 20 };
	unsigned seed = 42;
	const auto clk_ref = clock();
	for (auto i = 0; i < 30; i++)
	{
		for (auto &&n : d)
		{
			std::srand(seed);
			rainfalloptimize(n, 30, 10, -32.0, 32.0, ackley, sol);
			ackley(sol, func, NULL);
			std::cout << "seed = "<< seed << "\tn=" << n << "\tf(" << sol.tostring(4) << ") = " << func << std::endl;
		}
		seed = seed + (clock() - clk_ref);
	}
}
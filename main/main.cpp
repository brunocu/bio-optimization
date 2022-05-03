#include "ap.h"
#include "rainfall.h"
#include "test_func.h"
#include <cstdio>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <limits>

int main()
{
	alglib::real_1d_array sol;
	double func;
	std::ofstream fout("rainfall_griewank.csv");
	// io manipulators
	fout << std::scientific;
	fout.precision(std::numeric_limits<double>::digits10);
	// write column names
	fout << "seed,func,d,min\n";
	printf("Grienwank\n");

	int d[] = { 10, 20 };
	unsigned seed = 42;
	const auto clk_ref = clock();
	for (auto i = 0; i < 30; i++)
	{
		for (auto &&n : d)
		{
			std::srand(seed);
			rainfalloptimize(n, 30, 10, -600.0, 600.0, griewank, sol);
			griewank(sol, func, NULL);
			printf("seed=%u\tn=%d d=%d min=%.4f\n", seed, i, n, func);
			// write to csv
			fout << seed << ",grienwank," << n << "," << func << "\n";
		}
		seed = seed + (clock() - clk_ref);
	}

	fout.close();
}
#include "ap.h"
#include "rainfall.h"
#include "test_func.h"
#include <cstdio>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <limits>

struct algo {
	std::string name;
	testFunc func;
	double lower;
	double upper;
};

int main()
{
	algo test[]{
		{"Ackley", ackley, -32.768, 32.768},
		{"Griewank", griewank, -600, 600},
		{"Rastrigin", rastrigin, -5.12, 5.12},
		{"Rotated Hyper-Ellipsoid", rothyp, -65.536, 65.536},
		{"Sphere", spheref, -5.12, 5.12},
		{"Dixon-Price", dixonpr, -10, 10},
		{"Sum Squares", sumsq, -10, 10},
		{"Trid", trid, -200, 200},
		{"Rosenbrock", rosenbrock, -5, 10},
		{"Levy", levy, -10, 10},
	};

	// write to csv
	std::ofstream fout("rainfall.csv");
	// io manipulators
	fout << std::scientific;
	fout.precision(std::numeric_limits<double>::digits10);
	// write column names
	std::cout << "seed,func,d,min\n";
	fout << "seed,func,d,min\n";

	alglib::real_1d_array sol;
	double ret;
	int d[] = { 10, 20 };
	unsigned seed = 42;
	const auto clk_ref = clock();
	for (auto i = 0; i < 30; i++)
	{
		for (auto &funcStruct : test)
		{
			for (auto &n : d)
			{
				//printf("%s [%.3f, %.3f] d=%d\n", funcStruct.name.c_str(), funcStruct.lower, funcStruct.upper, n);

				std::srand(seed);
				rainfalloptimize(n, 30, 10, funcStruct.lower, funcStruct.upper, funcStruct.func, sol);
				funcStruct.func(sol, ret, NULL);
				//printf("min=%.4f\nx=%s\n\n", ret, sol.tostring(3).c_str());
				std::cout << seed << "," << funcStruct.name << "," << n << "," << ret << "\n";
				fout << seed << "," << funcStruct.name << "," << n << "," << ret << "\n";
			}
		}
		seed = seed + (clock() - clk_ref);
	}

	fout.close();
}
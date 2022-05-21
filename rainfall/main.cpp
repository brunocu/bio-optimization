#include "ap.h"
#include "rainfall.h"
#include "test_func.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <limits>
#ifdef _WIN32
#include <Windows.h>
#endif

int main()
{
#ifdef _WIN32
	// Prevent system from going into sleep mode
	std::cout << "DISABLING SLEEP MODE" << std::endl;
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);
#endif // _WIN32

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
		for (auto &funcStruct : funcCalls)
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
#ifdef _WIN32
	// Allow system to sleep normally
	SetThreadExecutionState(ES_CONTINUOUS);
#endif // _WIN32

}
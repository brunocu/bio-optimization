#include "ap.h"
#include "test_func.h"
#include "salpswarm.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <limits>
#ifdef _WIN32
#include <Windows.h>
#endif

int main() {
	#ifdef _WIN32
		// Prevent system from going into sleep mode
		std::cout << "DISABLING SLEEP MODE" << std::endl;
		SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);
	#endif // _WIN32

		// write to csv
		std::ofstream fout("salpswarm.csv");
		// io manipulators
		fout << std::scientific;
		fout.precision(std::numeric_limits<double>::digits10);
		// write column names
		std::cout << "seed,func,d,min\n";
		fout << "seed,func,d,min\n";

		alglib::real_1d_array sol;
		double ret;
		int d[] = { 10, 20 };
		unsigned seed = 76;
		const auto clk_ref = clock();
		for (auto i = 0; i < 30; i++)
		{
			for (auto& funcStruct : funcCalls)
			{
				for (auto& n : d) {
					std::srand(seed);
					salpswarmoptimize(50, n, funcStruct.lower, funcStruct.upper, 1000, funcStruct.func, sol);
					funcStruct.func(sol, ret, NULL);
					std::cout << seed << "," << funcStruct.name << "," << n << "," << ret << "\n";
					fout << seed << "," << funcStruct.name << "," << n << "," << ret << "\n";
				}

			}
			seed = seed + (clock() - clk_ref);
		}

#ifdef _WIN32
		// Allow system to sleep normally
		SetThreadExecutionState(ES_CONTINUOUS);
#endif // _WIN32
}
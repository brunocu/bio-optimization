#include "ap.h"
#include "rainfall.h"
#include "test_func.h"
#include "ThreadPool.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <limits>
#ifdef _WIN32
#include <Windows.h>
#endif

// output mutex
std::mutex _printMutex;

int main()
{
#ifdef _WIN32
	// Prevent system from going into sleep mode
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

	int d[] = { 10, 20 };
	unsigned seed = 42;
	ThreadPool thread_pool{};
	for (auto i = 0; i < 30; i++)
	{
		for (auto &funcStruct : funcCalls)
		{
			for (auto &n : d)
			{
				thread_pool.push([=, &fout] {
					alglib::real_1d_array sol;
					double ret;
					std::srand(seed);
					rainfalloptimize(n, 30, 10, funcStruct.lower, funcStruct.upper, funcStruct.func, sol);
					funcStruct.func(sol, ret, NULL);
					{
						std::lock_guard<std::mutex> guard(_printMutex);
						std::cout << seed << "," << funcStruct.name << "," << n << "," << ret << "\n";
						fout << seed << "," << funcStruct.name << "," << n << "," << ret << "\n";
					}
					});
			}
		}
		seed = seed + clock();
	}

	// Execute jobs
	thread_pool.Start();
	while (thread_pool.busy());

	thread_pool.Stop();
	fout.close();
#ifdef _WIN32
	// Allow system to sleep normally
	SetThreadExecutionState(ES_CONTINUOUS);
#endif // _WIN32

}
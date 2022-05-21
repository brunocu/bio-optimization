// test_func.h
// 
// Functions for testing optimization algorithms
// 
// parameters:
//  x    - Array. Point to evaluate the function at.
//  func - function evaluation result
//  ptr  - required by alglib optimizer, unused
//
#ifndef TEST_FUNC_H
#define TEST_FUNC_H
#include "ap.h"

// function pointer typedef
typedef void (*testFunc)(const alglib::real_1d_array &x, double &func, void *ptr);

// Ackley Function
void ackley(const alglib::real_1d_array &x, double &func, void *ptr);

// Griewank Function
void griewank(const alglib::real_1d_array &x, double &func, void *ptr);

// Rastrigin Function
void rastrigin(const alglib::real_1d_array &x, double &func, void *ptr);

// Rotated Hyper-Ellipsoid Function
void rothyp(const alglib::real_1d_array &x, double &func, void *ptr);

// Sphere Function
void spheref(const alglib::real_1d_array &x, double &func, void *ptr);

// Dixon-Price Function
void dixonpr(const alglib::real_1d_array &x, double &func, void *ptr);

// Sum Squares Function
void sumsq(const alglib::real_1d_array &x, double &func, void *ptr);

// Trid Function
void trid(const alglib::real_1d_array &x, double &func, void *ptr);

// Rosenbrock Function
void rosenbrock(const alglib::real_1d_array &x, double &func, void *ptr);

// Levy Function
void levy(const alglib::real_1d_array &x, double &func, void *ptr);

struct algo {
	std::string name;
	testFunc func;
	double lower;
	double upper;
};

// test functon pointers and starting parameters
const algo funcCalls[]{
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

#endif // !TEST_FUNC_H

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

#endif // !TEST_FUNC_H

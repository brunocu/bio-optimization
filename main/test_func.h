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

#endif // !TEST_FUNC_H

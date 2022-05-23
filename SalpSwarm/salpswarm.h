#pragma once
#ifndef SALPSWARM_H
#define SALPSWARM_H


#include "ap.h"
#include "test_func.h"
#include "linalg.h"


/*Salp swarm Optimization Algorithm parameters:
	npop - Population size
	dim - Problem dimension
	lowBrocket - lower bound
	upBracket - upper bound
	MaxIteration - Max number of iterations
	func - target function callback, per alglib's optimize package
	solutions - solution array
*/
void salpswarmoptimize(int npop, int dim, double lowBound, double upBound, int maxIteration, testFunc func, alglib::real_1d_array &solutions);

#endif // !SALPSWARM_H
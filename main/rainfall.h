// rainfall.h
#ifndef RANFALL_H
#define RAINFALL_H
#include "ap.h"

// Rain fall Optimization Algorithm
// parameters:
//  n     - problem dimension
//  npop  - population size
//  ne    - explosion iterations
//  bndl  - lower bound
//  bndu  - upper bound
//	func  - target function callback, per alglib's optimize package
//  x     - solution array
// 
// optional parameters:
//  np    - number of neighbor points of each drop. default: 20 x n
//  nr    - neighborhood radius. default: (bndu - bndl) * 0.02
//  eb    - explosion base. default: 10
//
void rainfalloptimize(int n, int npop, int ne, double bndl, double bndu, void (*func)(const alglib::real_1d_array &x, double &func, void *ptr), alglib::real_1d_array &x);
void rainfalloptimize(int n, int npop, int ne, int np, double nr, int eb, double bndl, double bndu, void (*func)(const alglib::real_1d_array &x, double &func, void *ptr), alglib::real_1d_array &x);

#endif // !RANFALL_H
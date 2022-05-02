// rainfall.h
#ifndef RANFALL_H
#define RAINFALL_H

struct raindrop; // forward declaration
struct rainfallstate {
	int n;
	int npop;
	raindrop *drops;
	int np;

	int iteration;
};

// Algorithm initialization
// parameters:
//  n     - problem dimension
//  npop  - population size
//  bndl  - lower bound
//  bndu  - upper bound
//  state - stores algorithm state
// 
// optional parameters:
//  np    - number of neighbor points of each drop. default: 20 x n
// 
// Notes:
//  For unbounded problems you may set bndl and bndu to -INF and +INF, respectively
//
void rainfallcreate(int n, int npop, double bndl, double bndu, rainfallstate &state);
void rainfallcreate(int n, int npop, int np, double bndl, double bndu, rainfallstate &state);

#endif // !RANFALL_H
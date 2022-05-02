// rainfall.cpp

#include "rainfall.h"
#include <random>

struct raindrop {
	double *var; // variables of the optimization problem
	enum { ACTIVE, INACTIVE } status;
};

void rainfallcreate(int n, int npop, double bndl, double bndu, rainfallstate &state)
{
	int np = 20 * n;
	rainfallcreate(n, npop, np, bndl, bndu, state);
}

void rainfallcreate(int n, int npop, int np, double bndl, double bndu, rainfallstate &state)
{
	// allocate raindrop population
	state.n = n;
	state.npop = npop;
	state.drops = new raindrop[npop];

	// generate first population of raindrops
	state.iteration = 1;
	for (auto i = 0; i < npop; i++)
	{
		state.drops[i].status = raindrop::ACTIVE;
		// generate coords inside constraints
		state.drops[i].var = new double[n];
		for (auto k = 0; k < n; k++) {
			double normalized_rnd = rand() / static_cast<double>(RAND_MAX);
			double rnd = ((bndu - bndl) * normalized_rnd) + bndl;
			state.drops[i].var[k] = rnd;
		}
	}
}

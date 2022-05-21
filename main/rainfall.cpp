// rainfall.cpp

#include "rainfall.h"
#include <random>
#include <cmath>
#include <algorithm>

struct raindrop {
	alglib::real_1d_array pos; // variables of the optimization problem
	enum { ACTIVE, INACTIVE } status;
	double fitness;
	int np;
	double nr;
	int ec;
	struct neighbor {
		alglib::real_1d_array pos;
		double fitness;
	} *neighborhood;
	// using dynamic std::vector for brevity
	std::vector<double> c1, c2, rank;
};

struct rainfallstate {
	testFunc func;
	int n;
	int npop;
	int ne;
	raindrop *drops;
	int np;
	double u;	// length of nth dimensional unit vector along any axis
	int eb;	// explosion base
	double bndl;
	double bndu;

	int iteration;
};

// intermediate functions

// generate_neighbors
// parameters:
//  np    - number of neighbor points
//  ridx  - raindrop index
//  state - algorithm state
void generate_neighbors(int np, int ridx, rainfallstate &state);

// get_dominant
// parameters:
//  ridx  - raindrop index
//  state - algorithm state
// returns:
//  dominant neighbor index or -1 if no dominant neighbor
int get_dominant(int ridx, rainfallstate &state);

inline bool comp_rank(const raindrop &a, const raindrop &b)
{
	return a.rank.back() < b.rank.back();
}

inline bool comp_fit(const raindrop &a, const raindrop &b)
{
	return a.fitness < b.fitness;
}

void rainfalloptimize(int n, int npop, int ne, double bndl, double bndu, testFunc func, alglib::real_1d_array &x)
{
	int np = 20 * n;
	double nr = (bndu - bndl) * 0.02;
	int eb = 10;
	rainfalloptimize(n, npop, ne, np, nr, eb, bndl, bndu, func, x);
}

void rainfalloptimize(int n, int npop, int ne, int np, double nr, int eb, double bndl, double bndu, testFunc func, alglib::real_1d_array &x)
{
	// init algorithm state
	rainfallstate state;
	state.func = func;
	state.n = n;
	state.npop = npop;
	state.ne = ne;
	state.drops = new raindrop[npop];
	state.np = np;
	state.eb = eb;
	state.u = 1 / sqrt((double)n);
	state.bndl = bndl;
	state.bndu = bndu;

	// generate first population of raindrops
	for (auto i = 0; i < npop; i++)
	{
		state.drops[i].status = raindrop::ACTIVE;

		// generate coords inside constraints
		state.drops[i].pos.setlength(n);
		for (auto k = 0; k < n; k++) {
			double normalized_rnd = rand() / static_cast<double>(RAND_MAX);
			double rnd = ((bndu - bndl) * normalized_rnd) + bndl;
			state.drops[i].pos[k] = rnd;
		}
		// evaluate function value
		func(state.drops[i].pos, state.drops[i].fitness, NULL);
		state.drops[i].neighborhood = nullptr;
	}

	// start iterations
	state.iteration = 0;
	bool active;
	do
	{
		for (auto i = 0; i < npop; i++)
		{
			if (state.drops[i].status == raindrop::ACTIVE)
			{
				// evolve raindrop
				int n_exp = np;
				// step size
				double normalized_rnd = rand() / static_cast<double>(RAND_MAX);
				if (state.iteration == 0)
					state.drops[i].nr = nr;
				else if (state.drops[i].ec == 0)	// check last iter
					state.drops[i].nr = state.drops[i].nr * (1 + normalized_rnd);
				else
					state.drops[i].nr = state.drops[i].nr / (1 + normalized_rnd);
				state.drops[i].ec = 0;	// restart ec

				while (state.drops[i].ec < ne)
				{
					generate_neighbors(n_exp, i, state);
					int dominant = get_dominant(i, state);

					if (dominant > -1)
					{
						// there is a dominant neighbor
						// replace drop with dominant
						state.drops[i].pos = state.drops[i].neighborhood[dominant].pos;
						state.drops[i].fitness = state.drops[i].neighborhood[dominant].fitness;

						// continue to next drop
						break;
					}

					// if no dominant,
					// explode points
					n_exp = np * eb * (++(state.drops[i].ec));
				}
				// if couldn't find new point, set drop inactive
				if (state.drops[i].ec >= ne)
					state.drops[i].status = raindrop::INACTIVE;
			}

			// raindrop fitness for rank
			state.drops[i].c2.push_back(state.drops[i].fitness);
			state.drops[i].c1.push_back(state.drops[i].fitness - state.drops[i].c2[0]);
		}
		
		// iter slice
		std::vector<double> c1_i(static_cast<size_t>(npop));
		for (auto i = 0; i < npop; i++)
			c1_i[i] = state.drops[i].c1[state.iteration];
		std::vector<double> c2_i(static_cast<size_t>(npop));
		for (auto i = 0; i < npop; i++)
			c2_i[i] = state.drops[i].c2[state.iteration];

		// ordered
		std::sort(c1_i.begin(), c1_i.end());
		std::sort(c2_i.begin(), c2_i.end());
		
		// get rank
		for (auto i = 0; i < npop; i++)
		{
			auto c1_order = std::find(c1_i.begin(), c1_i.end(), state.drops[i].c1[state.iteration]) - c1_i.begin();
			auto c2_order = std::find(c2_i.begin(), c2_i.end(), state.drops[i].c2[state.iteration]) - c2_i.begin();
			state.drops[i].rank.push_back(0.5 * c1_order + 0.5 * c2_order);
		}

		// sort drops by rank
		std::sort(state.drops, state.drops + npop - 1, comp_rank);
		// make last drop inactive
		state.drops[npop - 1].status = raindrop::INACTIVE;

		state.iteration++;
		// any active?
		active = false;
		for (auto i = 0; i < npop; i++)
		{
			if (state.drops[i].status == raindrop::ACTIVE)
			{
				active = true;
				break;
			}
		}
	} while (active);
	// fee neighbors mem
	for (auto i = 0; i < npop; i++)
		delete[] state.drops[i].neighborhood;
	
	// return best drop
	std::sort(state.drops, state.drops + npop - 1, comp_fit);
	x = alglib::real_1d_array(state.drops[0].pos);
	// free raindrops
	delete[] state.drops;
}

void generate_neighbors(int np, int ridx, rainfallstate &state)
{
	// delete existing neighborhood if exists
	if (state.drops[ridx].neighborhood != nullptr)
		delete[] state.drops[ridx].neighborhood;

	state.drops[ridx].np = np;
	state.drops[ridx].neighborhood = new raindrop::neighbor[np];
	// generate neighbor coords and value
	for (auto j = 0; j < np; j++)
	{
		state.drops[ridx].neighborhood[j].pos.setlength(state.n);
		for (auto k = 0; k < state.n; k++)
		{
			double normalized_rnd = rand() / static_cast<double>(RAND_MAX);
			// scale between [-u, u];
			double rnd = ((2) * normalized_rnd) - 1;
			// scale to radius
			rnd = (rnd * state.drops[ridx].nr) + state.drops[ridx].pos[k];
			if (rnd < state.bndl)
				rnd = state.bndl;
			if (rnd > state.bndu)
				rnd = state.bndu;
			state.drops[ridx].neighborhood[j].pos[k] = rnd;
		}
		// evaluate neighbor
		state.func(state.drops[ridx].neighborhood[j].pos, state.drops[ridx].neighborhood[j].fitness, NULL);
	}
}

int get_dominant(int ridx, rainfallstate &state)
{
	int dominant = -1;
	double fit_min = state.drops[ridx].fitness;
	for (auto j = 0; j < state.drops[ridx].np; j++)
	{
		if (state.drops[ridx].neighborhood[j].fitness < fit_min)
		{
			dominant = j;
			fit_min = state.drops[ridx].neighborhood[j].fitness;
		}
	}
	return dominant;
}
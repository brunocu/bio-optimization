
#include "salpswarm.h"
#include <random>
#include <cmath>
#include <numeric>
#include <algorithm>

//double random(double from, double to) {
//	std::random_device randgen;
//	std::mt19937 generator(randgen());
//	std::uniform_real_distribution<double> distr(from, to);
//	return distr(generator);
//}

std::vector<int> argSort(std::vector<double>& v) {
	//Get the indices of a sorted vector
	std::vector<int> retIndices(v.size());
	std::iota(retIndices.begin(), retIndices.end(), 0);
	
	std::stable_sort(retIndices.begin(), retIndices.end(), [&v](int i, int j)
		{return v[i] < v[j]; });

	return retIndices;
}

alglib::real_1d_array fill_row(double* Matrix) {
	//Take 
	alglib::real_1d_array row;
	int size = sizeof(Matrix) / sizeof(double);
	row.setlength(size);
		for (size_t i = 0; i < size; i++)
		{
			row[i] = Matrix[i];
		}
		return row;
}

void salpswarmoptimize(int npop, int dim, double lowBound, double upBound, int maxIteration, testFunc func, alglib::real_1d_array& solutions) {
	//Start of the initialize process
	alglib::real_2d_array SalpPositions;
	SalpPositions.setlength(npop, dim);
		
	//Initialize dimension array with infinity.
	std::vector<double> SalpFitness(npop, std::numeric_limits<double>::infinity());

	//Initialize food
	alglib::real_1d_array FoodPosition;
	FoodPosition.setlength(dim);

	double FoodFitness = std::numeric_limits<double>::infinity();
	//double FoodFitness = 0;

	//SalpPositions.resize(npop);
	for (size_t i = 0; i < npop; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			double normalized_rand = rand() / static_cast<double>(RAND_MAX);
			SalpPositions[i][j] =  ((upBound - lowBound) * normalized_rand) + lowBound;
		}
	}

	//End of initialize process.

	//Calculate the fitness of initial salps
	for (size_t i = 0; i < npop; i++)
	{
		//Evaluate moths.
		func(fill_row(SalpPositions[i]), SalpFitness[i], NULL);
	}

	//Get the best values of first interaction
	std::vector<double> sorted_SalpFitness(SalpFitness.size());
	sorted_SalpFitness = SalpFitness;

	std::sort(sorted_SalpFitness.begin(), sorted_SalpFitness.end());
	std::vector<int> Indices_of_Sorted_SalpFitness = argSort(SalpFitness);

	std::vector<alglib::real_1d_array> Sorted_Salps;
	Sorted_Salps.resize(npop);

	for (size_t i = 0; i < npop; i++)
	{
		Sorted_Salps[i] = fill_row(SalpPositions[Indices_of_Sorted_SalpFitness[i]]);	
	}

	FoodPosition = Sorted_Salps[0];
	FoodFitness = sorted_SalpFitness[0];

	int Iteration = 1;

	//Start of main loop
	while (Iteration < maxIteration + 1) {

		//This value is calculated in order to balance exploration and explosion of algorithm.
		double coefficient_1 = 2 * exp(-(pow((4 * Iteration / maxIteration), 2)));
		
		for (size_t i = 0; i < npop; i++)
		{
			for (size_t j = 0; j < dim; j++)
			{
				if (i <= npop / 2)
				{

					double coefficient_2 = rand() / static_cast<double>(RAND_MAX);
					double coefficient_3 = rand() / static_cast<double>(RAND_MAX);
					//std::cout << "C3: " << coefficient_3 << "\n";
					if (coefficient_3 < 0.5)
					{
						SalpPositions[i][j] = FoodPosition[j] + ((coefficient_1 * (upBound - lowBound) * coefficient_2) + lowBound);
					}
					else {
						SalpPositions[i][j] = FoodPosition[j] - ((coefficient_1 * (upBound - lowBound) * coefficient_2) + lowBound);
					}


				}
				else if (i > (npop / 2) && i < (npop + 1)) {
					SalpPositions[j][i] = (SalpPositions[i][j] + SalpPositions[i - 1][j]) / 2;
				}
			}
			

		}

		for (size_t i = 0; i < npop; i++)
		{
			for (size_t j = 0; j < dim; j++)
			{
				//Check if salps are out the search domain and if yes bring it back
				if (SalpPositions[i][j] < lowBound) {
					SalpPositions[i][j] = lowBound;
				}
				if (SalpPositions[i][j] > upBound) {
					SalpPositions[i][j] = upBound;
				}
			}
			func(fill_row(SalpPositions[i]), SalpFitness[i], NULL);
			if (SalpFitness[i] < FoodFitness) {
				FoodPosition = fill_row(SalpPositions[i]);
				FoodFitness = SalpFitness[i];
			}
		}
		Iteration++;
	}
	solutions = FoodPosition;

}
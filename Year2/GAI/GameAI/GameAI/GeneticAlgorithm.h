#ifndef __GENETIC_ALGORITHM_H__
#define __GENETIC_ALGORITHM_H__

#include "Genome.h"

class GeneticAlgorithm
{
public:
	//
	// CTOR
	//
	GeneticAlgorithm(int _populationSize, double _mutationRate, 
									double _crossoverRate, int _numWeights);
	//
	// DTOR
	//
	~GeneticAlgorithm(void);

	//
	// Method:			Epoch
	// Description:		Runs the Genetic Algorithm for one generation
	// Parameters:
	//		(IN)				_oldPopulation - Population undergoing the Genetic Algorithm
	// Returns:			std::vector<Genome>, representing the new population set
	//
	std::vector<Genome> Epoch(std::vector<Genome>& _oldPopulation);

	//
	// Method:			BestFitness
	// Description:		Returns the best fitness
	// Returns:			double, representing the best fitness value
	//
	double BestFitness(void) const;
	//
	// Method:			AverageFitness
	// Description:		Returns the average fitness
	// Returns:			double, representing the average fitness value
	//
	double AverageFitness(void) const;
	//
	// Method:			GetChromosomes
	// Description:		Returns the chromosomes
	// Returns:			std::vector<Genome>, representing the chromosome set
	//
	std::vector<Genome> GetChromosomes(void) const;

private:
	int m_PopulationSize;
	int m_ChromosoneLength;
	int m_FittestGenome;
	int m_GenerationCount;

	double m_BestFitness;
	double m_TotalFitness;
	double m_WorstFitness;
	double m_MutationRate;
	double m_CrossoverRate;
	double m_AverageFitness;

	std::vector<Genome> m_Population;

	//
	// Method:			Reset
	// Description:		Reset the Genetic Algorithm
	//
	void Reset(void);
	//
	// Method:			Mutate
	// Description:		Mutates the offspring
	//
	void Mutate(std::vector<double>& _chromo);
	//
	// Method:			Crossover
	// Description:		Generates the offspring and crosses the genes from parents to offspring
	// Parameters:
	//		(OUT)				_mother, mother of the offspring
	//		(OUT)				_father, father of the offspring
	//		(OUT)				_offspring1, first offspring
	//		(OUT)				_offspring2, second offspring
	//
	void Crossover(const std::vector<double>& _mother, const std::vector<double>& _father, 
										std::vector<double>& _offspring1, std::vector<double>& _offspring2);
	//
	// Method:			CalculateBestWorstAverageTotal
	// Description:		Calculates the best, worst, average and total fitnesses
	//
	void CalculateBestWorstAverageTotal(void);
	//
	// Method:			GrabNBest
	// Description:		Grabs the N best populace
	// Parameters:
	//		(IN)				_nBest, number of best
	//		(IN)				_numCopies, number of copies
	//		(OUT)			_population, current population
	//
	void GrabNBest(int _nBest, const int _numCopies, 
						std::vector<Genome>& _population);

	//
	// Method:			GetChromosomeRoulette
	// Description:		Gets chromosomes from Roulette selection
	// Returns:			Genome, Selected Genome
	//
	Genome GetChromosomeRoulette(void);
};

#endif // __GENETIC_ALGORITHM_H__
